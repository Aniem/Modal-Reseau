/**
 * @file tcpserver.h
 * @brief TCP server implementation
 */

#ifndef MODAL_TCPSERVER_H
#define MODAL_TCPSERVER_H

#include "server.h"

namespace Modal
{
    /**
     * @class TCPServer
     * @brief TCP Server implementation
     */
    class TCPServer : public Server
    {
    public:
        /**
         * @brief Create a new TCP server
         * @param addr IP address and TCP port to bind to
         * @param nbConn maximum connection number
         */
        TCPServer(const Address& addr, unsigned int nbConn);
    };

}
#endif /* MODAL_TCPSERVER_H */
