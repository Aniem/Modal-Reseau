#include "tunroutine.h"
#include "../modRoute/modRoute.h"
#define PROCESS 42
namespace Modal {
    
    TunRoutine::TunRoutine(wlanRoutine *routine) : interface("tun0"), wlanInt(routine)
    {
        //this->wlanInt = routine;
        ipv6Addr = interface.getIPv6address();
        ack=new AckTime*[PROCESS];
        this->l=new std::list<int>();
        TunRoutine::initiate_l();
    }
    TunRoutine::TunRoutine() : interface("tun9")
       {
           //this->wlanInt = routine;
           ipv6Addr = interface.getIPv6address();
           ack=new AckTime*[PROCESS];
           this->l=new std::list<int>();
           TunRoutine::initiate_l();
       }
    void TunRoutine::giveWlanRoutine(wlanRoutine *wlanR){
        this->wlanInt = wlanR;
    }

    void TunRoutine::initiate_l(){
		for (int k=0; k<PROCESS;k++){
			l->insert(l->begin(),k);
		}
		return;
	}
    Address TunRoutine::getIPv6Address(){
        return this->ipv6Addr;
    }

    void TunRoutine::run(){
        GTTPacket * pkt;
       
        while (true){
            pkt = interface.receive();
            ModRoute modroute(ipv6Addr.toString());
            std::string nexthop = modroute.getNextHop(pkt->headers["Destination"]);
            pkt->headers["NextHop"]=nexthop;
		while(l->empty())
			usleep(1000); //On attend qu'au moins un processus se libère
		
        int seqnum = l->front();

		l->erase(l->begin());

            pkt->headers["Seq"]=String::fromInt(seqnum);
            wlanInt->sendMsg(pkt);
		ack[seqnum]=new AckTime(seqnum,l,pkt->headers["Destination"]);
		ack[seqnum]->start();
        }
    }
    void TunRoutine::write(GTTPacket *pkt){
        interface.write(pkt);
        delete pkt;
    }
    void TunRoutine::receiveAck(GTTPacket *pkt){
	}
} // namespace Modal
