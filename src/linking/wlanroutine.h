#ifndef MODAL_WLANROUTINE_H
#define MODAL_WLANROUTINE_H
#include "../net/address.h"
#include "../core/thread.h"
#include "../wlan0/wlan.h"
#include "tunroutine.h"
#include "../modRoute/modRoute.h"
namespace Modal {
    class TunRoutine;    
    class wlanRoutine : public Thread
    {
        public:
            wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename, TunRoutine &tunInt);
/*            wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename);
            void giveTunRoutine(TunRoutine & tunInt);*/
            void run();
            wlan * getWlanInterface();
            ~wlanRoutine();
            void sendMsg(GTTPacket * pkt);
            
        private:
            Address ipv6Addr;
            wlan * interface;
            unsigned short out_port;
            TunRoutine & tunInt;
    };
    
} // namespace Modal

#endif // MODAL_WLANROUTINE_H
