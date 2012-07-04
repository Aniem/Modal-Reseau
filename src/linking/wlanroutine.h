#ifndef MODAL_WLANROUTINE_H
#define MODAL_WLANROUTINE_H
#include "../net/address.h"
#include "../core/thread.h"

namespace Modal {
    
    class wlanRoutine : public Thread
    {
        public:
            wlanRoutine(Address ipv6);
            void run();
            
        private:
            Address ipv6Addr;
    };
    
} // namespace Modal

#endif // MODAL_WLANROUTINE_H
