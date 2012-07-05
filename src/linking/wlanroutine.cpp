#include "wlanroutine.h"

#define BIGSIZE 2048
namespace Modal {
    
    wlanRoutine::wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename,TunRoutine & tunInt):ipv6Addr(ipv6), out_port(out_port),tunInt(tunInt)
    {
        interface = new wlan(out_port,devicename);
    }
    wlanRoutine::~wlanRoutine(){
        delete interface;
    }

/*    wlanRoutine::wlanRoutine(Address ipv6, unsigned short out_port, std::string devicename):ipv6Addr(ipv6), interface(out_port,devicename),out_port(out_port)
    {
    }
    wlanRoutine::giveTunRoutine(TunRoutine &tunInt){
        this->tunInt = tunInt;
    }*/

    void wlanRoutine::run(){
        while(true){
            char data[BIGSIZE];
            ModRoute modroute(this->ipv6Addr.toString(),interface);
            GTTPacket* received = interface.recevons(data,BIGSIZE*sizeof(char));
            if (received->method.find("RREQ")!=std::string::npos)
                modroute.handleRouteRequest(received);
            if (received->method.find("RREP")!=std::string::npos)
                modroute.handleRouteReply(received);
            if (received->method.find("NACK")!=std::string::npos)
                modroute.handleNACK(received);
            if (received->method.find("PKT")!=std::string::npos){
                if (received->headers["Destination"].find(ipv6Addr.toString()) != std::string::npos){
                    return ; // Send to tuninterface
                }
                else if (received->headers["NextHop"].find(ipv6Addr.toString())!=std::string::npos){
                    received->headers["NextHop"]=modroute.getNextHop(received->headers["Destination"]);
                    wlanRoutine::sendMsg(received);
                    return; // Change nexthop, resend.
                }
            }
            if (received->method.find("ACK")!=std::string::npos && received->method.find("NACK")==std::string::npos)
                return; //give to TunRoutine
            
        }
    }
    void wlanRoutine::sendMsg(GTTPacket * pkt) {
        interface.sendBroadcast(pkt, 2048,out_port);
        delete pkt;
    }
        
} // namespace Modal
