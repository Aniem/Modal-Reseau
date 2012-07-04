#include "tunroutine.h"
#include "../modRoute/modRoute.h"
#define PROCESS 42
namespace Modal {
    
    TunRoutine::TunRoutine(wlanRoutine routine) : wlanInt(routine)
    {
	ack=new AckTime*[PROCESS];
	this->l=new std::list<int>()
	TunRoutine::initiate_l();
    }
    Modal::List TunRoutine::initiate_l(){
		for (int k=0; k<PROCESS;k++){
			l->insert(l->begin(),k);
		}
		return (this->l=&l);
	}
    void TunRoutine::run(){
        GTTPacket * pkt;
        while (pkt = interface.receive()){
            std::string nexthop = ModRoute::getNextHop(pkt->headers["Destination"]);
            pkt->headers["NextHop"]=nexthop;
		while(l->empty())
			usleep(1000); //On attend qu'au moins un processus se libère
		
            int seqnum = l->value();

		l.erase(l->begin());

            pkt->headers["Seq"]=String::fromInt(seqnum);
            wlanInt.sendMsg(pkt);
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
