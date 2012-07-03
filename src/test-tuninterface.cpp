#include "tuninterface.h"
#include "core/common.h"
#include "core/atom/counter.h"
#include "core/atom/map.h"
#include "net/netselect.h"
#include "core/thread.h"
#include "core/log.h"
#include "net/socket.h"

#include <cstdlib>

using namespace Modal;

int main(){
    Thread::init();
    log::init(log::CONSOLE, "");
    Socket::init();
    try{
        log::debug << "Initialized, Opening /dev/net/tun" << log::endl;
        Modal::TunInterface test("tun9");
        log::debug << "/dev/net/tun opened. Trying the test" << log::endl;
        log::flush();
        test.setName("Tun module");
        test.start();
        ::system("ifconfig wlan0");
        test.wait();
        ::system("ifconfig tun9");
        log::debug << "It worked" << log::endl;
        log::flush();
    }catch(Modal::Exception e) {
        Modal::log::fatal << e << Modal::log::endl;
    }
}
