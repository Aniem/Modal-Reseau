#ifndef MODAL_TUNROUTINE_H
#define MODAL_TUNROUTINE_H
#include "../core/thread.h"
#include "../tuntap/tuninterface.h"
#include "wlanroutine.h"
#include "acktime.h"
#include "../modRoute/modRoute.h"
#include "../core/string.h"
#include <unistd.h>
#include <list>
#include <map>

namespace Modal {
    
    class TunRoutine : public Thread
    {
        public:
            TunRoutine(wlanRoutine wlanR);
            void run();
            void write(GTTPacket * pkt);
	    void initiate_l();
        private :
            TunInterface interface;
            wlanRoutine wlanInt;
		AckTime** ack;
		std::list<int> l;
//            std::map<int,long> acktime;
    };
    
} // namespace Modal

#endif // MODAL_TUNROUTINE_H
