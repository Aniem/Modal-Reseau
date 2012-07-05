#include "routeReqSender.h"
#include "modRoute.h"

namespace Modal {
    int RouteReqSender::maxNumberOfTry = 10;
    int RouteReqSender::attemptTime = 500000;

    RouteReqSender::RouteReqSender(std::string request, std::string myIP, wlan* w, unsigned short port) {
        this->currentStatus = INIT;
        this->numberOfTry = 0;
        this->numberOfRequests = 1;
        this->request = request;
        this->myIP = myIP;
        this->port = port;
        this->w = w;
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
        //std::cout << "Attempting to retrieve nextHop for " << this->request << std::endl;

        while(this->currentStatus == WAITING) {
            this->w->sendRequest(requestBuilder::buildRREQ(this->myIP, this->myIP, this->request, 10), 2048, this->port);
            this->numberOfTry++;
            //std::cout << "Attempt "<< this->numberOfTry <<" / " << RouteReqSender::maxNumberOfTry << " for " << this->request << std::endl;
            usleep(this->attemptTime);
            if(this->numberOfTry >= RouteReqSender::maxNumberOfTry) {
                this->currentStatus = FAILED;
                //std::cout << "Failed to retrieve next hop for " << this->request << std::endl;
            }
        }

        //std::cout << "Retrieving thread ended for " << this->request << std::endl;
    }

    void RouteReqSender::increaseReqNumber() { 
        this->numberOfRequests++; 
    }

    void RouteReqSender::decreaseReqNumber() { 
        this->numberOfRequests--; 
    }

}
