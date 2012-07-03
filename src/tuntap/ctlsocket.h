#ifndef MODAL_CTLSOCKET_H
#define MODAL_CTLSOCKET_H
#include "../net/udpsocket.h"

namespace Modal{
    class CtlSocket : public UDPSocket {
        public:
            CtlSocket(std::string devname);
            void setMTU(int i);
            Address setIPv6address(std::string devnametocopy);
            void activate();
        private:
            std::string devname;
            int fd;
    };
}

#endif // MODAL_CTLSOCKET_H
