#ifndef MODAL_CTLSOCKET_H
#define MODAL_CTLSOCKET_H
#include "../net/udpsocket.h"

namespace Modal{
    class CtlSocket : public UDPSocket {
        public:
            CtlSocket(std::string devname,int fd);
            void setMTU();
            void setIPv6address();
        private:
            std::string devname;
            int fd;
    };
}

#endif // MODAL_CTLSOCKET_H
