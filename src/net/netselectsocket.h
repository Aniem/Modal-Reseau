/**
 * @file netselectsocket.h
 * @brief Implementation of NetSelectReader on sockets
 */

#ifndef MODAL_NETSELECTSOCKET_H
#define MODAL_NETSELECTSOCKET_H

#include "netselectreader.h"
#include "socket.h"

namespace Modal
{

    /**
     * @class NetSelectSocket
     *
     * @brief NetSelect can watch wait data on sockets
     */
    class NetSelectSocket : public NetSelectReader
    {
    public:
        /**
         * @brief Constructor with a reference
         *
         * Create a new NetSelectSocket with a socket whose allocation is NOT
         * managed by this object.
         *
         * @param sock socket reference
         */
        NetSelectSocket(Socket &sock);

        /**
         * @brief Constructor used with new Socket()
         *
         * Create a new NetSelectSocket with a socket whose allocation is
         * managed by this object: the socket is DELETED in the destructor.
         *
         * @param psock socket pointer
         */
        NetSelectSocket(Socket *psock);

        virtual ~NetSelectSocket();

        int getFileDescriptor() const;

        bool read();

    protected:
        /**
         * @brief Eat read data
         */
        virtual void eat(const char *data, long size) = 0;

        /**
         * @brief Get internal socket
         */
        Socket& socket() const;

    private:
        // sock may be deleted by this object to prevent memory leak
        Socket *sock;
        bool dynamicSock;
    };
}
#endif /* MODAL_NETSELECTREADER_H */
