#ifndef MODAL_MODROUTEREQSENDER_H
#define MODAL_MODROUTEREQSENDER_H
#include <sstream>
#include "../core/thread.h"
#include "routeTableEntry.h"

namespace Epyx {
    enum RouteReqStatus {INIT, WAITING, FAILED, SUCCESS};

    class RouteReqSender : public Thread {

    public:
        RouteReqSender();

        std::string query;

        void run();

        void giveResponse(std::string ip, int timeExpire);

        void increaseReqNumber();
        void decreaseReqNumber();

        int getStatus();

        int getNumberOfTry();

        int getNumberOfRequests();

        RoutingTableEntry* getResponse();


    private:
        static int maxNumberOfTry;

        static int attemptTime;

        int numberOfTry;

        int numberOfRequests;

        RouteReqStatus currentStatus;

        RoutingTableEntry* response;
    };
}
#endif /* MODAL_ROUTEREQSENDER_H */
