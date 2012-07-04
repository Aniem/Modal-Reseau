#ifndef MODAL_TUNROUTINE_H
#define MODAL_TUNROUTINE_H
#include "../core/thread.h"
#include "../tuntap/tuninterface.h"


namespace Modal {
    
    class TunRoutine : public Thread
    {
        public:
            TunRoutine();
        private :
            TunInterface interface;
                            
    };
    
} // namespace Modal

#endif // MODAL_TUNROUTINE_H
