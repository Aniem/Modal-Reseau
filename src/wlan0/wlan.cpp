#include "wlan.h"
#include "address.h";
namespace{
	int wlan::wlan(Modal::TunInterface t,Modal::ModRoute mod){
		this.t=t;
		this.mod=mod;
	  return 0;
	}
	void wlan:recevons(void* data,int size){
		Modal::N2NP::Packet *n2np=skfd.recv(data,size);
		mod.send(n2np);
		int res=mod.recv();
	}
	Modal::N2NP::Packet parse(void* data, int size){
		    Modal::GTTParser parser;
		    parser.eat(data, size);
		    Modal::GTTPacket *gttpkt= parser.getPacket();
   		    Modal::N2NP::Packet n2nppkt(*gttpkt);
		    delete gttpkt;
		    return n2nppkt;
	}
	int quoifaire(Modal::N2NP::Packet* gtt){
		if(strcpy(gtt->method,"
	}
	/*Modal::GTTParser parser;
    Modal::GTTPacket *gttpkt = NULL;
	Modal::GTTPacket*/
}