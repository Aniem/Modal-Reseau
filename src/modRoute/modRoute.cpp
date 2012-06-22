#include "modRoute.h"
#include <sstream>

namespace Epyx {
    ModRoute::ModRoute() {
        this->routeValidityTime = 1000;
    }

    std::string ModRoute::getNextHop(const std::string ip) {
        std::map<std::string, RoutingTableEntry*>::iterator itRoute = (this->routingTable).find(ip);

        if(itRoute == (this->routingTable).end()) {
            return rebuildRoute(ip);
        }

        else if(itRoute->second->expires > this->getTimeMs()) {
            (this->routingTable).erase(ip);
            return rebuildRoute(ip);
        }
        else {
            return itRoute->second->nextHop;
        }
    }

    std::string ModRoute::rebuildRoute(std::string ip) {
        RouteReqSender *sender;
        std::map<std::string, RouteReqSender*>::iterator itRoute = (this->currentRequests).find(ip);
        if(itRoute != (this->currentRequests).end()) {
            sender = itRoute->second;
            sender->increaseReqNumber();
        }
        else {
            sender = new RouteReqSender();
            (this->currentRequests).insert(std::pair<std::string, RouteReqSender*>(ip, sender));
            sender->start();
        }

        while(sender->getStatus() == WAITING) {
            usleep(100000);
        }

        if(sender->getStatus() == SUCCESS) {
            RoutingTableEntry* response = sender->getResponse();
            (this->routingTable).insert(std::pair<std::string, RoutingTableEntry*>(ip, response));
            sender->decreaseReqNumber();

            if(sender->getNumberOfRequests() <= 0) {
                delete sender;
                sender = NULL;
            }

            return response->nextHop;
        }
        else return NULL;
    }


    void ModRoute::handleRouteResponse(GTTPacket* pkt) {
        std::map<std::string, std::string>::iterator targetIp = pkt->headers.find("Source");
        std::map<std::string, std::string>::iterator nextHop = pkt->headers.find("Sender");
        if(targetIp == pkt->headers.end() || nextHop == pkt->headers.end()) return;

        std::map<std::string, RouteReqSender*>::iterator itRoute = (this->currentRequests).find(targetIp->second);
        if(itRoute == this->currentRequests.end()) return;

        itRoute->second->giveResponse(nextHop->second, this->getTimeMs() + this->routeValidityTime);
    }

/*
    void ModRoute::handleRouteRequest(GTTPacket* pkt) {

        //  comparer l'IP de la requete a la notre
        // Si égal, envoyer une routeREP
        // Sinon, reconstruire la route et envoyer une routeREP
    }
*/

    long ModRoute::getTimeMs() {
        struct timeval now;

        gettimeofday(&now, NULL);

        return now.tv_usec + 1000*now.tv_sec;
    }
}
