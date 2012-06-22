#ifndef MODAL_MODROUTE_H
#define MODAL_MODROUTE_H
#include <string>
#include <sstream>
#include "../parser/gttpacket.h"
#include "routeReqSender.h"
#include "requestBuilder.h"

// Construction des paquets ? (N2NP ou gttpacket)
// Gestion des dates
// Gestion des thread (sleep, stop)

namespace Modal {

    typedef struct RoutingTableEntry RoutingTableEntry;
    struct RoutingTableEntry {
        std::string nextHop;
        int expires;
    };

    class ModeRoute {
    public:

        ModeRoute();

        std::string getNextHop(const std::string ip);

        std::string rebuildRoute(const std::string ip);

        void handleRouteRequest(GTTPacket pkt);

        void handleRouteResponse(GTTPacket pkt);

    private:
        std::map<std::string, RouteReqSender> currentRequests;

        std::map<std::string, RoutingTableEntry> routingTable;
    };

}
#endif /* MODAL_MODROUTE_H */
