#include "wlanroutine.h"

#define BIGSIZE 2048
namespace Modal {
    
    wlanRoutine::wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename,TunRoutine & tunInt):ipv6Addr(ipv6), interface(out_port,devicename),out_port(out_port),TunInt(tunInt)
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
                if (received->headers["Destination"].find(ipv6Addr.toString()) != std::string::npos){
			tun
                    return ; // Send to tuninterface
		}
                else if (received->headers["NextHop"].find(ipv6Addr.toString())!=std::string::npos){
                    return; // Change nexthop, resend.
                }
            if (received->method.find("ACK")!=std::string::npos && received->method.find("NACK")==std::string::npos)
                return; //give to TunRoutine
            
        }
    }
    void wlanRoutine::sendMsg(GTTPacket * pkt) {
        interface.sendBroadcast(GTTPacket *pkt, 2048,out_port);
        delete pkt;
    }
        
} // namespace Modal
