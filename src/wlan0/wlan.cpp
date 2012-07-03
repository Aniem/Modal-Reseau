#include "wlan.h"
#include <sstream>
#define RREP 4 
#define RREQ 3
namespace Modal{
	wlan::wlan(Modal::TunInterface t,Modal::ModRoute mod,const std::string& ip, unsigned short port){
		this->skfd=new UDPSocket();
		this->skfd->setBroadcast(1);
		this->addr=new Address(ip,port,4);
		this->mod=&mod;
		this->t=&t;
	}
	wlan::~wlan(){
		delete addr;
		delete skfd;
	}
	int wlan::quefaire(Modal::GTTPacket * gttpkt){
		std::string s(gttpkt->method);


		if(s.compare("RREQ")==0){
			mod->handleRouteRequest(gttpkt);
				return RREQ;
		}
		else if(s.compare("RREP")==0){
			mod->handleRouteReply(gttpkt);
				return RREP;
		}
		return 0;
	}
	void wlan::sendBroadcast(GTTPacket* pkt, int size,int port){
		char* newdata=new char[size];
		pkt->build(&newdata);
		wlan::send(newdata,size,port);
		delete[] newdata;
	}
	void wlan::recevons(void* data,int size){
		skfd->recv(data,size);
		Modal::GTTParser parser;
		parser.eat((const char*)data, size);
		Modal::GTTPacket *gttpkt= parser.getPacket();
		
		switch(wlan::quefaire(gttpkt)){

			default:
				//Modal::log::info <<"Le paquet arrivé ne peut être traité."<< Modal::log::endl;;
				//On DROP
				break;
		}
		delete gttpkt;
	}

	void wlan::send(void* data, int size,int port){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = INADDR_BROADCAST;
		skfd->send(data,size,(struct sockaddr*)&that);
	}


	bool compare(){
		return true;
	}

	void wlan::run(){
		
	}
}
