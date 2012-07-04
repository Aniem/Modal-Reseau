#include "tunroutine.h"
#include "../modRoute/modRoute.h
#include "../core/string.h"
namespace Modal {
    
    TunRoutine::TunRoutine(wlanRoutine routine) : wlanInt(routine)
    {
    }
    
    void TunRoutine::run(){
        GTTPacket * pkt;
        while (pkt = interface.receive()){
            std::string nexthop = ModRoute::getNextHop(pkt->headers["Destination"]);
            pkt->headers["NextHop"]=nexthop;
            int seqnum = 42; //pick new seq number. This line has to change.
            pkt->headers["Seq"]=String::fromInt(seqnum);
            wlanInt.sendMsg(pkt);
            //Put here ACK/NACK timeout functionality. Start timeout Here
        }
    }
    void TunRoutine::write(GTTPacket *pkt){
        interface.write(pkt);
        delete pkt;
    }
} // namespace Modal
