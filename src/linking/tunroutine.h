#ifndef MODAL_TUNROUTINE_H
#define MODAL_TUNROUTINE_H
#include "../core/thread.h"
#include "../tuntap/tuninterface.h"
#include "wlanroutine.h"
#include <map>

namespace Modal {
    
    class TunRoutine : public Thread
    {
        public:
            TunRoutine(wlanRoutine wlanR);
            void run();
            void write(GTTPacket * pkt);
        private :
            TunInterface interface;
            wlanRoutine wlanInt;
//            std::map<int,long> acktime;
    };
    
} // namespace Modal

#endif // MODAL_TUNROUTINE_H
