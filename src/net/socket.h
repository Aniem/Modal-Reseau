/**
 * @file socket.h
 * @brief Socket astraction layer
 */

#ifndef MODAL_SOCKET_H
#define MODAL_SOCKET_H

#include "../core/mutex.h"
#include "address.h"
#include <string>

namespace Modal
{
    /**
     * @class Socket
     *
     * @brief Socket abstraction layer
     */
    class Socket
    {
    public:
        /**
         * @brief Global initialisation of Socket API
         */
        static void init();

        /**
         * @brief Global finition of Socket API
         */
        static void fini();

        /**
         * @brief Initialise an empty socket
         */
        Socket();
        /**
         * @brief Initialise a socket with a remote address
         */
        Socket(const Address& addr);
        /**
         * @brief Build a new Socket object from an existing connection
         */
        Socket(int sock, const Address &addr);
        /**
         * @brief Destructor
         */
        virtual ~Socket();

        /**
         * @brief Set a new file descriptor
         *
         * NOTE: The socket must be closed before calling this method.
         */
        void setFd(int sockfd);
        /**
         * @brief Get the internal file descriptor, or -1 if it is closed
         */
        int getFd() const;
        /**
         * @brief Tell wether the socket is opened or closed
         */
        bool isOpened() const;

        /**
         * @brief Set the remote address
         */
        void setAddress(const Address& addr);
        /**
         * @brief Get the remote address
         */
        Address getAddress() const;
        /**
         * @brief Set the local address
         */
        void setLocalAddress(const Address& addr);
        /**
         * @brief Get the local address
         */
        Address getLocalAddress() const;
        /**
         * @brief Update local address from socket
         */
        void updateLocalAddress();

        /**
         * @brief Shutdown and close the socket
         */
        void close();

        /**
         * @brief Virtual method to send data
         * @param data buffer pointer
         * @param size buffer size
         * @return number of sent bytes
         */
        virtual int send(const void *data, int size) = 0;
        /**
         * @brief Send all bytes through the network
         * @param data buffer pointer
         * @param size buffer size
         * @return true if all data was sent
         */
        bool sendAll(const void *data, int size);
        /**
         * @brief Send text through the network
         * @param message text to send
         * @return true on success
         */
        bool write(std::string message);

        /**
         * @brief Virtual method to receive data
         * @param data buffer pointer
         * @param size buffer size
         * @return number of received bytes
         */
        virtual int recv(void *data, int size) = 0;
        /**
         * @brief Receive exactly (size) bytes from the network
         * @param data buffer pointer
         * @param size buffer size
         * @return true if the buffer is filled
         */
        bool recvAll(void *data, int size);

    protected:
        /**
         * @brief Socket file descriptor
         */
        int sock;

        /**
         * @brief IP + port associated with the socket
         */
        Address address;

        /**
         * @brief Local address for the socket or "*" if unknown
         */
        Address localAddress;

    private:
        // Global initialisation stuff
        static int is_init;
        static Mutex init_mutex;

        // Disable copy
        Socket(const Socket&);
        const Socket& operator=(const Socket&);

        // Last end-of-line caracter (\r or \n)
        char last_eol;
    };
}
#endif /* MODAL_SOCKET_H */
