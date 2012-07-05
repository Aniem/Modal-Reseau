#ifndef MODAL_TUNROUTINE_H
#define MODAL_TUNROUTINE_H
#include "../core/thread.h"
#include "../tuntap/tuninterface.h"
#include "wlanroutine.h"
#include "acktime.h"
#include "../core/string.h"
#include <unistd.h>
#include "list.h"
//#include <map>

namespace Modal {
    class wlanRoutine;
    class TunRoutine : public Thread
    {
        public:
            TunRoutine(wlanRoutine  * wlanR, unsigned short out_port);
            TunRoutine(unsigned short out_port);
            void giveWlanRoutine(wlanRoutine * wlanR);
            Address getIPv6Address();
            void run();
            void write(GTTPacket * pkt);
            void initiate_l();
            void receiveAck(GTTPacket *pkt);
        private :
	    unsigned short out_port;
            TunInterface interface;
            Modal::wlanRoutine * wlanInt;
            AckTime** ack;
            std::list<int>* l;
            Address ipv6Addr;
//            std::map<int,long> acktime;
    };
    
} // namespace Modal

#endif // MODAL_TUNROUTINE_H
