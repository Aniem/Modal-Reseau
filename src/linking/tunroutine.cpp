#include "tunroutine.h"
#include "../modRoute/modRoute.h
#include "../core/string.h"
#include <unistd.h>
#define PROCESS 42
namespace Modal {
    
    TunRoutine::TunRoutine(wlanRoutine routine) : wlanInt(routine)
    {
	ack=new AckTime*[PROCESS];
	this->l=new List();
	initiate_l();
    }
    Modal::List TunRoutine::initiate_l(){
		for (int k=0; k<PROCESS;k++){
			l=new List(k,l);
		}
		return (this->l=&l);
	}
    void TunRoutine::run(){
        GTTPacket * pkt;
        while (pkt = interface.receive()){
            std::string nexthop = ModRoute::getNextHop(pkt->headers["Destination"]);
            pkt->headers["NextHop"]=nexthop;
		while(l.isEmpty())
			usleep(1000); //On attend qu'au moins un processus se libère
		
            int seqnum = l.value(); //pick new seq number. This line has to change.

		Modal::List tmp=l.next();
		delete l;
		l=l.next();

            pkt->headers["Seq"]=String::fromInt(seqnum);
            wlanInt.sendMsg(pkt);
            //Put here ACK/NACK timeout functionality. Start timeout Here
		ack[seqnum]=new AckTime(seqnum,l);
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
