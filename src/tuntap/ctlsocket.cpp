#include "ctlsocket.h"
#include <iostream>
#include <strstream>

namespace Modal {
    CtlSocket::CtlSocket(std::string devname, int fd) : devname(devname), fd(fd)
    {
    }
    void CtlSocket::setMTU(int i){
        struct ifreq ifr;
        memcopy(ifr.ifrname,devname.c_str());
        ifr.mtu = i;
        ioctl(fd, SIOCSIFMTU, ifr);
    }

    void CtlSocket::setIPv6address(){
        struct ifreq ifr;
        ioctl(fd,SIOCGIFHWADDR, ifr);
        std::cout << ifr.hwaddr;
    }
}

