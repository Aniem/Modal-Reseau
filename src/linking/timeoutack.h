#ifndef MODAL_TIMEOUTACK_H
#define MODAL_TIMEOUTACK_H
#include "../core/thread.h"
#include "tunroutine.h"

namespace Modal {
    
    class TimeoutACK : public Thread
    {
        public:
            TimeoutACK(int time, TunRoutine inter);
            void run();
            void acknowledge();
        private:
            int timeoutTime;
            bool ackreceived;
            TunRoutine interface;
            
    };
    
} // namespace Modal

#endif // MODAL_TIMEOUTACK_H
