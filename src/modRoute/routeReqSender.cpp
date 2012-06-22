#include "routeReqSender.h"
#include "modRoute.h"

namespace Modal {
    int RouteReqSender::maxNumberOfTry = 10;
    int RouteReqSender::attemptTime = 500;

    RouteReqSender::RouteReqSender() {
        this->currentStatus = INIT;
        this->numberOfTry = 0;
        this->numberOfRequests = 1;
    }

    int RouteReqSender::getStatus() {
        return this->currentStatus;
    }

    int RouteReqSender::getNumberOfTry() {
        return this->numberOfTry;
    }

    RoutingTableEntry RouteReqSender::getResponse() {
        return this->response;
    }

    void RouteReqSender::run() {
        this->currentStatus = WAITING;

        while(this->currentStatus == WAITING) {
            //TODO UNKNWOWNCLASS::sendRequest(requestBuilder::buildRREQ(this->query));
            //TODO : Faire dormir le thread pendant attemptTime ms
            (this->numberOfTry)++;
            if(this->numberOfTry >= RouteReqSender::maxNumberOfTry) {
                this->currentStatus = FAILED;
            }
        }
    }

    void RouteReqSender::giveResponse(std::string ip, int validity) {
        this->nextHop = ip;
        this->currentStatus = SUCCESS;
    }

    void RouteReqSender::increaseReqNumber() { 
        this->numberOfRequests++; 
    }

    void RouteReqSender::decreaseReqNumber() { 
        this->numberOfRequests--; 
    }

}
