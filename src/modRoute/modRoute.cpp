#include "modRoute.h"
#include <sstream>

namespace Modal {
     ModRoute::ModRoute(std::string ip, wlan * w, unsigned short port) {
        this->routeValidityTime = 1000;
        this->defaultTTL = 10;
        this->myIP = ip;
        this->w = w;
        this->port = port;
    }

    std::string ModRoute::getNextHop(const std::string ip) {
        std::map<std::string, RoutingTableEntry*>::iterator itRoute = (this->routingTable).find(ip);

        if(itRoute == (this->routingTable).end()) {
            //std::cout << "getNextHop : no entry in routing table" << std::endl;
            return buildRoute(ip);
        }
        else if(itRoute->second->expires < this->getTimeMs()) {
            //std::cout << "getNextHop : old entry deleted ( " << itRoute->second->expires << " < " << this->getTimeMs() << ")" << std::endl;
            (this->routingTable).erase(ip);
            return buildRoute(ip);
        }
        else {
            //std::cout << "getNextHop : routing table was up to date ( " << itRoute->second->expires << " >= " << this->getTimeMs() << ")" << std::endl;
            return itRoute->second->nextHop;
        }
    }

    std::string ModRoute::buildRoute(std::string ip) {
        RouteReqSender *sender = NULL;
        std::map<std::string, RouteReqSender*>::iterator itSender = (this->currentRequests).find(ip);
        if(itSender != (this->currentRequests).end()) {
            sender = itSender->second;
            sender->increaseReqNumber();
        }
        else {
            sender = new RouteReqSender(ip, this->myIP, this->w, this->port);
            sender->setName("RETR"+ip);
            (this->currentRequests).insert(std::pair<std::string, RouteReqSender*>(ip, sender));
            sender->start();
        }

        while(sender->getStatus() == WAITING || sender->getStatus() == INIT) {
            usleep(100000);
        }

        if(sender->getStatus() == SUCCESS) {
            sender->decreaseReqNumber();

            if(sender->getNumberOfRequests() <= 0) {
                delete sender;
                sender = NULL;
            }

            std::map<std::string, RoutingTableEntry*>::iterator itRoute = (this->routingTable).find(ip);
            if(itRoute == (this->routingTable).end()) {
                return ""; // This should not happen, since we just got a response to our route request
            }
            else {
                return itRoute->second->nextHop;
            }
        }
        else return "";
    }


    void ModRoute::handleRouteReply(GTTPacket* pkt) {
        // Retreive usefull datas from the transmitted packet and do nothing if it was not well-formed
        std::map<std::string, std::string>::iterator sender = pkt->headers.find("Source");
        std::map<std::string, std::string>::iterator replyTo = pkt->headers.find("Destination");
        std::map<std::string, std::string>::iterator nextHopToSender = pkt->headers.find("Sender");
        std::map<std::string, std::string>::iterator pktTarget = pkt->headers.find("NextHop");
        std::map<std::string, std::string>::iterator n = pkt->headers.find("N");
        if(sender == pkt->headers.end() || replyTo == pkt->headers.end() || nextHopToSender == pkt->headers.end() || pktTarget == pkt->headers.end() || n == pkt->headers.end()) return;

        int ttl;
        std::istringstream ss(n->second);
        ss >> ttl;

        // Do nothing the packet is not for me
        if(this->myIP.compare(pktTarget->second) != 0)  { return; }

        // Do nothing if TTL is too small
        if(ttl <= 0) { return; }

        //std::cout << "Received non dropped RREP" << std::endl;

        // Insert or update the routing table entry of the IP that send the reply
        RoutingTableEntry* requesterEntry = new RoutingTableEntry();
        requesterEntry->nextHop = nextHopToSender->second;
        requesterEntry->expires = this->getTimeMs() + this->routeValidityTime;
        std::map<std::string, RoutingTableEntry*>::iterator itRoute = this->routingTable.find(sender->second);

        if(itRoute != this->routingTable.end()) { this->routingTable.erase(sender->second); }
        this->routingTable.insert(std::pair<std::string, RoutingTableEntry*>(sender->second, requesterEntry));

        if(replyTo->second.compare(this->myIP) != 0) {
            // The RREQ is not for me -> transmit the RREP
            this->w->sendBroadcast(RequestBuilder::buildRREP(sender->second, replyTo->second, this->myIP, this->getNextHop(replyTo->second), --ttl), 2048, this->port);
        } else {
             std::map<std::string, RouteReqSender*>::iterator itSender = (this->currentRequests).find(sender->second);
             if(itSender != (this->currentRequests).end()) {
                itSender->second->setSuccessful();
             }
        }
    }

    void ModRoute::handleRouteRequest(GTTPacket* pkt) {
        // Retreive usefull datas from the transmitted packet and do nothing if it was not well-formed
        std::map<std::string, std::string>::iterator targetIP = pkt->headers.find("Destination");
        std::map<std::string, std::string>::iterator requestedBy = pkt->headers.find("Source");
        std::map<std::string, std::string>::iterator nextHopToRequester = pkt->headers.find("Sender");
        std::map<std::string, std::string>::iterator n = pkt->headers.find("N");
        if(targetIP == pkt->headers.end() || requestedBy == pkt->headers.end() || nextHopToRequester == pkt->headers.end() || n == pkt->headers.end()) return;

        int ttl;
        std::istringstream ss(n->second);
        ss >> ttl;

        // Do nothing if TTL is too small
        if(ttl <= 0) return;

        // Insert or update the routing table entry of the IP that made the request
        RoutingTableEntry* requesterEntry = new RoutingTableEntry();
        requesterEntry->nextHop = nextHopToRequester->second;
        requesterEntry->expires = this->getTimeMs() + this->routeValidityTime;
        std::map<std::string, RoutingTableEntry*>::iterator itRoute = (this->routingTable).find(requestedBy->second);

        if(itRoute != this->routingTable.end()) { this->routingTable.erase(requestedBy->second); }
        this->routingTable.insert(std::pair<std::string, RoutingTableEntry*>(requestedBy->second, requesterEntry));
            
        if(targetIP->second.compare(this->myIP) == 0) {
            // The RREQ is for me -> answer with a RREP
            this->w->sendBroadcast(RequestBuilder::buildRREP(this->myIP, requestedBy->second, this->myIP, nextHopToRequester->second, this->defaultTTL), 2048, this->port);
        }
        else {
            // The RREQ is not for me -> broadcast it with a smaller ttl
            this->w->sendBroadcast(RequestBuilder::buildRREQ(requestedBy->second, targetIP->second, this->myIP, --ttl), 2048, this->port);
        }
    }

    void ModRoute::handleNACK(GTTPacket* pkt) {
        std::map<std::string, std::string>::iterator from = pkt->headers.find("Source");
        std::map<std::string, std::string>::iterator to = pkt->headers.find("Destination");
        std::map<std::string, std::string>::iterator pktTarget = pkt->headers.find("NextHop");

        if(from == pkt->headers.end() || to == pkt->headers.end() || pktTarget == pkt->headers.end()) return;

        // Do nothing the packet is not for me
        if(this->myIP.compare(pktTarget->second) != 0)  { std::cout << "Not addressed to me" << std::endl; return; }

        this->routingTable.erase(from->second);

        if(this->myIP.compare(to->second) != 0)  { 
             this->w->sendBroadcast(RequestBuilder::buildNACK(from->second, to->second, this->getNextHop(to->second)), 2048, this->port);
        }

    }

    long ModRoute::getTimeMs() {
        struct timeval now;

        gettimeofday(&now, NULL);

        return now.tv_usec + 1000*now.tv_sec;
    }

    void ModRoute::printRoutingTable() {
          std::cout << "Printing routing table :" << std::endl;
          std::map<std::string, RoutingTableEntry*>::iterator it;

          for(it = this->routingTable.begin() ; it != this->routingTable.end(); it++ )
              std::cout << (*it).first << " => " << (*it).second->nextHop << "(validity : " << (*it).second->expires << ")" << std::endl;

    }
}
