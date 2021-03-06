/**
 * @file udpserver.h
 * @brief UDP server abstraction layer
 */
#ifndef MODAL_UDPSERVER_H
#define MODAL_UDPSERVER_H

#include "server.h"
#include "udpsocket.h"

namespace Modal
{
    /**
     * @class UDPServer
     * @brief UDP server abstraction layer
     */
    class UDPServer : public Server
    {
    public:
        /**
         * @brief Create a new UDP server
         * @param addr IP address and UDP port to bind to
         */
        UDPServer(const Address& addr);

        /**
         * @brief Receive data for the server
         *
         * @param data received data buffer
         * @param size size of data buffer
         * @return number of received bytes
         */
        int recv(void *data, int size);

        // send is not implemented yet
        //int send(const void *data, int size);

    private:
        UDPSocket sock;
    };
}
#endif /* MODAL_UDPSERVER_H */

