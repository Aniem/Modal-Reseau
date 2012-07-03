#include "routeReqSender.h"
#include "modRoute.h"

namespace Modal {
    int RouteReqSender::maxNumberOfTry = 10;
    int RouteReqSender::attemptTime = 500000;

    RouteReqSender::RouteReqSender(std::string request) {
        this->currentStatus = INIT;
        this->numberOfTry = 0;
        this->numberOfRequests = 1;
        this->request = request;
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

    void RouteReqSender::setSuccessful() {
        this->currentStatus = SUCCESS;
    }

    void RouteReqSender::run() {
        this->currentStatus = WAITING;

        while(this->currentStatus == WAITING) {
            //TODO UNKNWOWNCLASS::sendRequest(requestBuilder::buildRREQ(this->query));
            (this->numberOfTry)++;
            usleep(this->attemptTime);
            if(this->numberOfTry >= RouteReqSender::maxNumberOfTry) {
                this->currentStatus = FAILED;
            }
        }
    }

    void RouteReqSender::increaseReqNumber() { 
        this->numberOfRequests++; 
    }

    void RouteReqSender::decreaseReqNumber() { 
        this->numberOfRequests--; 
    }

}
