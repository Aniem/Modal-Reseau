#include "routeReqSender.h"
#include "modRoute.h"

namespace Modal {
    int RouteReqSender::maxNumberOfTry = 10;
    int RouteReqSender::attemptTime = 500000;

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

    int RouteReqSender::getNumberOfRequests() {
        return this->numberOfRequests;
    }

    RoutingTableEntry *RouteReqSender::getResponse() {
        return this->response;
    }

    void RouteReqSender::run() {
        this->currentStatus = WAITING;

        while(this->currentStatus == WAITING) {
            //TODO UNKNWOWNCLASS::sendRequest(requestBuilder::buildRREQ(this->query));

            usleep(this->attemptTime);
            (this->numberOfTry)++;

            if(this->numberOfTry >= RouteReqSender::maxNumberOfTry) {
                this->currentStatus = FAILED;
            }
        }
    }

    void RouteReqSender::giveResponse(std::string ip, int timeExpire) {
        this->response = new RoutingTableEntry();
        this->response->nextHop = ip;
        this->response->expires = timeExpire;
        this->currentStatus = SUCCESS;
    }

    void RouteReqSender::increaseReqNumber() { 
        this->numberOfRequests++; 
    }

    void RouteReqSender::decreaseReqNumber() { 
        this->numberOfRequests--; 
    }

}
