#ifndef MODAL_WLANROUTINE_H
#define MODAL_WLANROUTINE_H
#include "../net/address.h"
#include "../core/thread.h"
#include "../wlan0/wlan.h"
#include "tunroutine.h"
#include "../modRoute/modRoute.h"
namespace Modal {
    
    class wlanRoutine : public Thread
    {
        public:
            wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename, TunRoutine &tunInt);
            void run();
            void sendMsg(GTTPacket * pkt);
            
        private:
            Address ipv6Addr;
            wlan interface;
            unsigned short out_port;
            TunRoutine tunInt;
    };
    
} // namespace Modal

#endif // MODAL_WLANROUTINE_H
