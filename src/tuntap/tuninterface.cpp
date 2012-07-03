#define MAXSIZE 2048

#include "tuninterface.h"

#include "../core/log.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

#include <iomanip>
#include <string>

#include "../core/exception.h"
#include "ctlsocket.h"

namespace Modal {
    
    int TunInterface::openDevNetTun(std::string dev){
        struct ifreq ifr;
        int fd, err;
       
        if( (fd = ::open("/dev/net/tun", O_RDWR)) < 0 )
            throw ErrException("TunInterface","Unable to open /dev/net/tun");// */
        
        log::debug << "/dev/net/tun opened" << log::endl;
        
        memset(&ifr, 0, sizeof(ifr));
        
             /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
              *        IFF_TAP   - TAP device  
              *
              *        IFF_NO_PI - Do not provide packet information  
              */ 
        ifr.ifr_flags = IFF_TUN | IFF_NO_PI; 
        if( !dev.empty() )
            ::strncpy(ifr.ifr_name, dev.c_str(), IFNAMSIZ);
        log::debug << "calling ioctl ..." << log::endl;
        if( ioctl(fd, TUNSETIFF, (void *) &ifr) < 0 ){
            close(fd);
            throw ErrException("TunInterface", "Ioctl");
        }
        std::string devname (ifr.ifr_name);
        this->deviceName=devname;
        log::debug << "Done. Device name is " << deviceName << log::endl;
        return fd;
    }

    TunInterface::TunInterface(char * dev)
    {
        this->descriptor = openDevNetTun(dev);
        this->writer.setDescriptor(descriptor);
    }
    TunInterface::~TunInterface(){
        close(this->descriptor);
    }
    
    void TunInterface::setMTU(int i){
        CtlSocket sock(this->deviceName);
        sock.setMTU(i);
        sock.close();
    }
    void TunInterface::setIPv6address(std::string dev){
        CtlSocket sock(this->deviceName);
        sock.setIPv6address(dev);
        sock.close();
    }

    int TunInterface::read(char* data, int maxsize){
        return ::read(this->descriptor,data, maxsize);
    }
    
    void TunInterface::activate(){
        CtlSocket sock(this->deviceName);
        sock.activate();
        sock.close();
    }
     
    char TunInterface::HexDigit(char c)
    {
       if(c<10)
         return '0'+c;
       else
         return c-10+'A';
    }
    void TunInterface::CharToHex(char c, char *Hex)
    {
       Hex[0]=HexDigit((c>>4)&0xF);
       Hex[1]=HexDigit(c&0xF);
    }
    
    void TunInterface::run(){
        activate();
        setMTU(1500);
        setIPv6address("wlan0");
        writer.setName("TunWriter");
        writer.start();
        while(true){
            std::stringstream pkt;
            char data[1500];
            int s = this->read(data,1500);
            //TODO : read data, encapsulate to a GTT PKT packet
            // extract source and dst IPv6 address.
            pkt << std::string(data,s) << std::endl << "Hex : " << std::endl;
            for (int i = 0; i < s; i++){
                char hexD[2];
                CharToHex(data[i],hexD);
                pkt << hexD[0] << hexD[1];
                if (i%4==3)
                    pkt << std::endl;
                else
                    pkt << " ";
            }
            log::info << "New packet received. size : " << s << log::endl << "data : " << pkt.str() << log::endl;
            Address source = buildIPv6Address((unsigned char *)data+8);
            Address dest = buildIPv6Address((unsigned char *)data+24);
            GTTPacket * packet = new GTTPacket();
            packet->body = data;
            packet->protocol="MESH";
            packet->method="PKT";
            packet->headers["Source"]=source.toString();
            packet->headers["Destination"]=dest.toString();
            packet->size=s;
            packet->headers["Content-length"]=s;
            toRead.push(packet);
            
            char essai[4096];
            s = packet->build(&essai);
            std::string msg (essai,s);
            log::debug << msg << log::endl;
        }
        
    }
    
    std::string TunInterface::extractIPv6Address(char* data, int pos){
        std::stringstream ip;
        for(int i = 0; i < 8; i++){
            ip << HexDigit(data[pos+2*i])<<HexDigit(data[pos+2*i+1]);
            if (i<7)
                ip<<":";
        }
        return ip.str();
    }

    void TunInterface::write(GTTPacket * pkt){
        this->writer.addTask(pkt);
    }
    GTTPacket* TunInterface::receive(){
        return toRead.pop();
    }
    
    Address TunInterface::buildIPv6Address(const unsigned char hwaddr[6]){
        struct sockaddr_in6 saddr;
                unsigned char *ipv6 = saddr.sin6_addr.s6_addr;
                saddr.sin6_family = AF_INET6;
                saddr.sin6_flowinfo = 0;
                saddr.sin6_scope_id = 0;
                saddr.sin6_port = 0;
        
                // Prefix fd00:0da1:0000::/40
                ipv6[0] = 0xfd;
                ipv6[1] = 0;
                ipv6[2] = 0x0d;
                ipv6[3] = 0xa1;
                ipv6[4] = 0;
                ipv6[5] = 0;
                // Random bytes
                ipv6[6] = rand() & 0xff;
                ipv6[7] = rand() & 0xff;
                // MAC address
                ipv6[8] = hwaddr[0];
                ipv6[9] = hwaddr[1];
                ipv6[10] = hwaddr[2];
                ipv6[11] = 0xff;
                ipv6[12] = 0xfe;
                ipv6[13] = hwaddr[3];
                ipv6[14] = hwaddr[4];
                ipv6[15] = hwaddr[5];
                return Address((struct sockaddr*) &saddr);
    }
} // namespace Modal
