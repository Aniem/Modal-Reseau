/**
 * @file udpsocket.h
 * @brief UDP socket abstraction layer
 */
#ifndef MODAL_UDPSOCKET_H
#define MODAL_UDPSOCKET_H

#include "socket.h"

namespace Modal
{
    class UDPServer;

    /**
     * @class UDPSocket
     * @brief UDP socket abstraction layer
     */
    class UDPSocket : public Socket
    {
    public:
        /**
         * @brief Initialise an empty TCP socket
         */
        UDPSocket();
        /**
         * @brief Initialise a TCP socket with a remote address
         */
        UDPSocket(const Address& addr);
        /**
         * @brief Build a new Socket object from an existing connection
         */
        UDPSocket(int sock, const Address &addr);

        /**
         * @brief Send data through the socket
         *
         * @param data sent data
         * @param size size of data to be sent
         * @return number of sent bytes
         */
        int send(const void *data, int size);
	int send(const void *data, int size,struct sockaddr *saddr);
        /**
         * @brief Receive data from the socket
         *
         * @param data received data buffer
         * @param size size of data buffer
         * @return number of received bytes
         */
        int recv(void *data, int size);

        /**
         * @brief Get the remote address from which the last packet was received
         * @return remote address
         */
        Address getLastRecvAddr() const;

        
        void setBroadcast(bool enable);
        void create();
    private:
        Address lastRecvAddr;
    };

}
#endif /* MODAL_UDPSOCKET_H */
