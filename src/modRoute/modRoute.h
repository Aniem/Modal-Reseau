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

namespace Modal {

    class ModRoute {

    public:
        ModRoute(const std::string ip);

        std::string getNextHop(const std::string ip);

        std::string buildRoute(const std::string ip);

        void handleRouteReply(GTTPacket* pkt);

        void handleRouteRequest(GTTPacket* pkt);

        void printRoutingTable();

    private:
        int defaultTTL;

        std::string myIP;

        std::map<std::string, RouteReqSender*> currentRequests;

        std::map<std::string, RoutingTableEntry*> routingTable;

        long getTimeMs();

        int routeValidityTime;
    };

}
#endif /* MODAL_MODROUTE_H */
