#include "ctlsocket.h"
#include "../core/log.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

namespace Modal {
    CtlSocket::CtlSocket(std::string devname) : devname(devname)
    {
        this->sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    }
    void CtlSocket::setMTU(int i){
        struct ifreq ifr;
        strncpy(ifr.ifr_name,devname.c_str(),IFNAMSIZ);
        ifr.ifr_mtu = 1;
        ioctl(sock, SIOCSIFMTU, &ifr);
    }
    
    void CtlSocket::activate(){
        struct ifreq ifr;
        strncpy(ifr.ifr_name,devname.c_str(),IFNAMSIZ);
        ifr.ifr_flags = IFF_UP;
        ioctl(sock, SIOCSIFFLAGS, &ifr);        
    }

    void CtlSocket::setIPv6address(std::string devnametocopy){
        struct ifreq ifr;
        strncpy(ifr.ifr_name,devnametocopy.c_str(),IFNAMSIZ);
        ioctl(sock,SIOCGIFHWADDR, &ifr);
        std::stringstream msg;
        char* addr1 = ifr.ifr_hwaddr.sa_data;
        long addr = (long) addr1;
        msg <<"0x" << std::hex << addr1;
        
        log::debug << "CtlSocket sa_data size : " << sizeof(ifr.ifr_hwaddr.sa_data) << log::endl;
        log::debug << "CtlSocket sa_data hex : " << msg.str() << log::endl;
        log::debug << "CtlSocket sa_family : " << ifr.ifr_hwaddr.sa_family << log::endl;
        
        //WILL HAVE TO BE CHANGED
        std::string command = "ifconfig ";
        command += devname;
        command += " add ";
        command += "aaaa::1989/64";
        system(command.c_str());
                   
    }
}

