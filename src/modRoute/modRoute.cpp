#include "modRoute.h"

namespace Modal {
    ModeRoute::ModeRoute() {
    }

    std::string ModeRoute::getNextHop(const std::string ip) {
        std::map<std::string, RoutingTableEntry>::iterator itRoute = (this->routingTable).find(ip);

        if(itRoute == (this->routingTable).end()) {
            return rebuildRoute(ip);
        }
        // TODO : récupérer la date sous forme d'entier
        else if((itRoute->second).expires > 0) {
            (this->routingTable).erase(ip);
            return rebuildRoute(ip);
        }
        else {
            return (itRoute->second).nextHop;
        }
    }

    std::string ModeRoute::rebuildRoute(std::string ip) {
        RouteReqSender *sender;
        std::map<std::string, RouteReqSender>::iterator itRoute = (this->currentRequests).find(ip);
        if(itRoute != (this->currentRequests).end()) {
            sender = &(itRoute->second);
            sender->increaseReqNumber();
        }
        else {
            // TODO : lancer un thread routeReqSender
        }

        while(sender->getStatus() == WAITING) {
            // TODO : sleep
        }

        if(sender->getStatus() == SUCCESS) {
            (this->routingTable).insert(std::pair<std::string, RoutingTableEntry>(ip, sender->giveResponse()));
            sender->decreaseReqNumber();
            //TODO : si plus de req, detruire l'objet routeReqSender
            return sender->getResponse();
        }
        else return NULL;
    }

    void ModeRoute::handleRouteRequest(GTTPacket pkt) {
        std::string ip;
        
        // TODO comparer l'IP de la requete a la notre
        if(ip == req.) {
        }
        // Si égal, envoyer une routeREP
        // Sinon, reconstruire la route et envoyer une routeREP
    }

    void ModeRoute::handleRouteResponse(GTTPacket pkt) {
        // Rechercher dans les requetes en cour
        // Si presente, resoudre la requete et la supprimer
    }
}
