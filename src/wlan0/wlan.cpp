#include "wlan.h"
#include <sstream>
#define RREP 4 
#define RREQ 3
#define PKT 2
#define ACK 1
#define NACK 5
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
			//mod->handleRouteRequest(gttpkt);
				return RREQ;
		}
		else if(s.compare("RREP")==0){
			//mod->handleRouteReply(gttpkt);
				return RREP;
		}
		else if(s.compare("PKT")==0){
				return PKT;
		}
		else if(s.compare("ACK")==0){
				return ACK;
		}
		else if(s.compare("NACK")==0){
				return NACK;
		}
		else
			return 0;
	}
	void wlan::sendBroadcast(GTTPacket* pkt, int size,int port){
		char* newdata=new char[size];
		pkt->build(&newdata);
		wlan::send(newdata,size,port);
		delete[] newdata;
	}
	void wlan::sendUnicast(GTTPacket* pkt, int size,int port,std::string ip){
		char* newdata=new char[size];
		pkt->build(&newdata);
		wlan::sendToSomeone(newdata,size,port,ip);
		delete[] newdata;
	}
	Modal::GTTPacket* wlan::recevons(void* data,int size){
		skfd->recv(data,size);
		Modal::GTTParser parser;
		parser.eat((const char*)data, size);
		Modal::GTTPacket *gttpkt= parser.getPacket();
		
		int res=wlan::quefaire(gttpkt);
		return gttpkt;
	}

	void wlan::send(void* data, int size,int port){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = INADDR_BROADCAST;
		skfd->send(data,size,(struct sockaddr*)&that);
	}

	void wlan::sendToSomeone(void* data, int size,int port,std::string ip){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = inet_addr(ip.c_str());
		skfd->send(data,size,(struct sockaddr*)&that);
	}


	bool compare(){
		return true;
	}

	void wlan::run(){
		
	}
}
