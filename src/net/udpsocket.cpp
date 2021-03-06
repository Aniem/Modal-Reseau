#include "udpsocket.h"
#include "../core/common.h"

namespace Modal
{

    UDPSocket::UDPSocket() {
    }

    UDPSocket::UDPSocket(const Address& addr)
    :Socket(addr) {
    }

    UDPSocket::UDPSocket(int sock, const Address &addr)
    :Socket(sock, addr) {
    }

    int UDPSocket::send(const void *data, int size) {
        int bytes;
        struct sockaddr_storage saddr;

        MODAL_ASSERT(data != NULL);
        // Create a new socket if it does not exist
        if (this->sock < 0) {
            this->sock = ::socket(AF_INET, SOCK_DGRAM, 0);
            if (this->sock == -1)
                throw ErrException("UDPSocket", "socket");
        }
        address.getSockAddr((struct sockaddr *) &saddr);
        //bytes = ::sendto(this->sock, data, size, 0, (const struct sockaddr *) &saddr, sizeof (saddr));
        bytes = ::send(this->sock, data, size, 0);
        if (localAddress.empty())
            this->updateLocalAddress();
        // TODO: Implement status error (ex. Conn closed, ...)

        if (bytes < 0)
            throw ErrException("UDPSocket", "sendto");
        return bytes;
    }
    int UDPSocket::send(const void *data, int size,struct sockaddr *saddr) {
        int bytes;

        MODAL_ASSERT(data != NULL);
        // Create a new socket if it does not exist
        if (this->sock < 0) {
            this->sock = ::socket(AF_INET, SOCK_DGRAM, 0);
            if (this->sock == -1)
                throw ErrException("UDPSocket", "socket");
        }
        bytes = ::sendto(this->sock, data, size, 0, (const struct sockaddr *)&saddr, sizeof (saddr));
        if (localAddress.empty())
            this->updateLocalAddress();
        // TODO: Implement status error (ex. Conn closed, ...)

        if (bytes < 0)
            throw ErrException("UDPSocket", "sendto");
        return bytes;
    }

    int UDPSocket::recv(void * data, int size) {
        int bytes;
        struct sockaddr_storage saddr;
        socklen_t length = sizeof (saddr);
        MODAL_ASSERT(data != NULL);
        MODAL_ASSERT(this->sock >= 0);
        bytes = ::recvfrom(this->sock, data, size, 0, (struct sockaddr *) &saddr, &length);
        // TODO: Implement status error (eg. Conn closed, ...)
        if (bytes < 0)
            throw ErrException("UDPSocket", "recvfrom");

        /**
         * recv doesn't set the after-the-last byte to zero. We must do it to
         * avoid some issues.
         * (writing into a prefilled longer data buffer fucks everything up)
         */
        if (bytes < size)
            ((char*) data)[bytes] = 0;
        lastRecvAddr = Address((const sockaddr *) &saddr);
        return bytes;
    }
    void UDPSocket::create() {
            if (sock >= 0) {
                // Do nothing, it already exists
                return;
            }
            sock = ::socket(AF_INET, SOCK_DGRAM, 0);
            if (sock == -1)
                throw ErrException("UDPSocket", "socket");
    }
    void UDPSocket::setBroadcast(bool enable) {
        if (sock < 0) {
            this->create();
        }
        int boolean = (enable ? 1 : 0);
        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &boolean, sizeof (boolean))) {
            throw ErrException("UDPSocket", "setsokopt(broadcast)");
        }
    }

    Address UDPSocket::getLastRecvAddr() const {
        return lastRecvAddr;
    }

}
