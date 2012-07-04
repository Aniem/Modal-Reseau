#ifndef MODAL_WLANROUTINE_H
#define MODAL_WLANROUTINE_H
#include "../net/address.h"
#include "../core/thread.h"
#include "../wlan0/wlan.h"

namespace Modal {
    
    class wlanRoutine : public Thread
    {
        public:
            wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename);
            void run();
            
        private:
            Address ipv6Addr;
            wlan interface;
    };
    
} // namespace Modal

#endif // MODAL_WLANROUTINE_H
