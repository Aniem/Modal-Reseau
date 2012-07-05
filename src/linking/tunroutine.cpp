#include "tunroutine.h"
#include "../modRoute/modRoute.h"
#define PROCESS 42
namespace Modal {
    
    TunRoutine::TunRoutine(wlanRoutine *routine, unsigned short out_port) : out_port(out_port), wlanInt(routine), interface("tun9")
    {
        //this->wlanInt = routine;
        //interface = TunInterface("tun9");
        ipv6Addr = interface.getIPv6address();
        ack=new AckTime*[PROCESS];
        this->l=new std::list<int>();
        TunRoutine::initiate_l();
    }
    TunRoutine::TunRoutine(unsigned short out_port) : out_port(out_port), interface("tun9")
       {
           //this->wlanInt = routine;
        //interface = new TunInterface("tun9");
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
        log::debug << "TunRoutine Started" << log::endl;
        interface.setName("Tun Interface");
        interface.start();
        log::debug << "Tun Interface Started" << log::endl;
        GTTPacket * pkt;
       
        while (true){
            pkt = interface.receive();
            log::debug << "New packet Received" << log::endl;
            ModRoute modroute(ipv6Addr.toString(),wlanInt->getWlanInterface(), out_port);
            std::string nexthop = modroute.getNextHop(pkt->headers["Destination"]);
            pkt->headers["NextHop"]=nexthop;
            while(l->empty())
                usleep(1000); //On attend qu'au moins un processus se libère
		
            int seqnum = l->front();

            l->pop_front();

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
