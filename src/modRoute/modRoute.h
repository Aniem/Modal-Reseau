#ifndef MODAL_MODROUTE_H
#define MODAL_MODROUTE_H
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/time.h>
#include "../parser/gttpacket.h"
#include "routeTableEntry.h"
#include "routeReqSender.h"
#include "requestBuilder.h"

// Utiliser unistd pour sleep ?
// Qui gère les routesREQ .
// Gestion des dates

namespace Modal {

    class ModRoute {

    public:

        ModRoute();

        std::string getNextHop(const std::string ip);

        std::string rebuildRoute(const std::string ip);

        //void handleRouteRequest(GTTPacket* pkt);

        void handleRouteResponse(GTTPacket* pkt);

    private:
        std::map<std::string, RouteReqSender*> currentRequests;

        std::map<std::string, RoutingTableEntry*> routingTable;

        long getTimeMs();

        int routeValidityTime;
    };

}
#endif /* MODAL_MODROUTE_H */
