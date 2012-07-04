#include "wlanroutine.h"
#include "../wlan0/wlan.h"
#include "../modRoute/modRoute.h"
#define BIGSIZE 2048
namespace Modal {
    
    wlanRoutine::wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename):ipv6Addr(ipv6), interface(out_port,devicename)
    {
    }
    void wlanRoutine::run(){
        while(true){
            char data[BIGSIZE];
            GTTPacket* received = interface.recevons(data,BIGSIZE);
            if (received->method.find("RREQ")!=std::string::npos)
                ModRoute::handleRouteRequest(received);
            if (received->method.find("RREP")!=std::string::npos)
                ModRoute::handleRouteReply(received);
            if (received->method.find("NACK")!=std::string::npos)
                ModRoute::handleNACK(received);
            if (received->method.find("PKT")!=std::string::npos)
                if (received->headers["Destination"].find(ipv6Addr.toString()) != std::string::npos)
                    return ; // Send to tuninterface
                else if (received->headers["NextHop"].find(ipv6Addr.toString())!=std::string::npos){
                    return; // Change nexthop, resend.
                }
            if (received->method.find("ACK")!=std::string::npos && received->method.find("NACK")==std::string::npos)
                return; //give to TunRoutine
            
        }
    }
        
} // namespace Modal
