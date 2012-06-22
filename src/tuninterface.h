#ifndef MODAL_TUNINTERFACE_H
#define MODAL_TUNINTERFACE_H

#include "net/tcpsocket.h"
#include "net/udpsocket.h"
#include "core/thread.h"

namespace Modal {
    
    class TunInterface : public Thread
    {
        public:
            TunInterface(char * dev);
            int openDevNetTun(char* dev);
            ~TunInterface();
            void run();
        private:
            char* deviceName;
            int descriptor;
            
    };
    
} // namespace Modal

#endif // MODAL_TUNINTERFACE_H
