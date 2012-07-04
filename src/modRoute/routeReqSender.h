#ifndef MODAL_MODROUTEREQSENDER_H
#define MODAL_MODROUTEREQSENDER_H
#include <sstream>
#include "../core/thread.h"
#include "routeTableEntry.h"

namespace Modal {
     enum RouteReqStatus {INIT, WAITING, FAILED, SUCCESS};

    class RouteReqSender : public Thread {

    public:
        RouteReqSender(std::string request, std::string myIP);

        void run();

        int getStatus();

        int getNumberOfTry();

        void increaseReqNumber();

        void decreaseReqNumber();

        void setSuccessful();

        int getNumberOfRequests();

    private:
        int numberOfRequests;

        std::string request;

        std::string myIP;

        static int maxNumberOfTry;

        static int attemptTime;

        int numberOfTry;

        RouteReqStatus currentStatus;

        RoutingTableEntry* response;
    };
}
#endif /* MODAL_ROUTEREQSENDER_H */
