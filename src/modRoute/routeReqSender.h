#ifndef MODAL_MODROUTEREQSENDER_H
#define MODAL_MODROUTEREQSENDER_H
#include "../core/thread.h"
#include "modRoute.h"

namespace Modal {
    enum RouteReqStatus {INIT, WAITING, FAILED, SUCCESS};

    class RouteReqSender : public Thread {

    public:
        RouteReqSender();

        std::string query;

        void run();

        void giveResponse(std::string ip);

        void increaseReqNumber();
        void decreaseReqNumber();

        int getStatus();

        int getNumberOfTry();

        RoutingTableEntry getResponse();


    private:
        static int maxNumberOfTry;

        static int attemptTime;

        int numberOfTry;

        int numberOfRequests;

        RouteReqStatus currentStatus;

        RoutingTableEntry response;
    };
}
#endif /* MODAL_ROUTEREQSENDER_H */
