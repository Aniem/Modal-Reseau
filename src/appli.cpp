#include "wlan0/initialisation.h"
#include "tuntap/tuninterface.h"
#include "core/common.h"
#include "core/atom/counter.h"
#include "core/atom/map.h"
#include "net/netselect.h"
#include "core/thread.h"
#include "core/log.h"
#include "net/socket.h"
#include "linking/tunroutine.h"
#include "linking/wlanroutine.h"

using namespace Modal;

int main(int argc, char* argv[]){
    Thread::init();
    log::init(log::CONSOLE, "");
    Socket::init();
    
    TunRoutine tunR(1337);
    wlanRoutine wlanR(tunR.getIPv6Address(),1337,"wlan0",tunR);
    tunR.giveWlanRoutine(&wlanR);
    log::debug << "Associating" << log::endl;
    associate("modal");
    log::debug << "Associated" << log::endl;
    
    tunR.setName("TunRoutine");
    wlanR.setName("WlanRoutine");
    try{
        log::debug << "Starting tun routine" << log::endl;
        tunR.start();
        log::debug << "Starting wlan routine" << log::endl;
        wlanR.start();
        
        tunR.wait();
    }catch(Exception e){
        Modal::log::fatal << e << Modal::log::endl;
        log::flushAndQuit();
    } //*/
}
