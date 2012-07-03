#include "wlan.h"
#include <sstream>

namespace Modal{
	wlan::wlan(Modal::TunInterface t,Modal::ModRoute mod,const std::string& ip, unsigned short port){
		this->skfd=new UDPSocket();
		this->skfd->setBroadcast(1);
		this->addr=new Address(ip,port,4);

	}
	wlan::~wlan(){
		delete addr;
		delete skfd;
	}
	int wlan::quefaire(Modal::GTTPacket * gttpkt){
		std::string s(gttpkt->method);
		std::map<std::string, std::string>::iterator replyTo = gttpkt->headers.find("Destination");
		if(s.compare("RREQ")==0){
			Modal::ModRoute::handleRouteRequest(&gttpkt);
			std::string getNextHop(replyTo->second);
		}
		return 0;
	}
	void wlan::recevons(void* data,int size){
		skfd->recv(data,size);
		Modal::GTTParser parser;
		parser.eat((const char*)data, size);
		Modal::GTTPacket *gttpkt= parser.getPacket();
		
		int res=wlan::quefaire(&gttpkt);
		if(res==2){
			skfd.send(data,size);
		}
		if(res==1){
			t.send(gttpkt);
		}
		if(res==0){
		}
		delete gttpkt;
	}

	void wlan::send(void* data, int size,int port){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = INADDR_BROADCAST;
		skfd.sendto(data,size,&that);
	}


	boolean compare(){
		
	}

	void wlan::run(){
		
	}
}
