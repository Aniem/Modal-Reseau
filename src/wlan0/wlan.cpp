#include "wlan.h"

namespace{
	int wlan::wlan(Modal::TunInterface t,Modal::ModRoute mod,const std::string& ip, unsigned short port){
		this.t=t;
		this.mod=mod;
		this.skfd.setBroadcast(1);
		this.addr=new Address(ip,port,4);
	  return 0;
	}
	~wlan(){
		delete addr;
	}
	void wlan:recevons(void* data,int size){
		skfd.recv(data,size);
		Modal::N2NP::Packet *n2np=parse(data,size);
		
		int res=quefaire(n2np);
		if(res==2){
			skfd.send(data,size);
		}
		if(res==1){
			t.send(n2np);
		}
		if(res==0){
		}
	}
	void wlan:send(void* data, int size,int port){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = INADDR_BROADCAST;
		skfd.sendto(data,size,&that);
	}
	Modal::N2NP::Packet parse(void* data, int size){
		    Modal::GTTParser parser;
		    parser.eat(data, size);
		    Modal::GTTPacket *gttpkt= parser.getPacket();
   		    Modal::N2NP::Packet n2nppkt(*gttpkt);
		    delete gttpkt;
		    return n2nppkt;
	}
	int quefaire(Modal::N2NP::Packet n2np){
		return 0;
	}

	void run(){
		
	}
}
