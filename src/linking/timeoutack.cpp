#include "timeoutack.h"
#include "wlanroutine.h"

namespace Modal {
    
    TimeoutACK::TimeoutACK(int time, TunRoutine& inter): timeoutTime(time), interface(inter)
    {
    }
    void TimeoutACK::run(){
        sleep(timeoutTime);
        
    }
    
} // namespace Modal
