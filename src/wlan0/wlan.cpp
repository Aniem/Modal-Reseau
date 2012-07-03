#include "wlan.h"
#include <sstream>
#define RREP 4 //Le paquet RREQ nous est destiné
#define BRDCST 1 //Le RREQ/RREP n'est pas pour nous : on le broadcast
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
			std::map<std::string, std::string>::iterator sender = gttpkt->headers.find("Source");
			std::map<std::string, std::string>::iterator replyTo = gttpkt->headers.find("Destination");
			std::map<std::string, std::string>::iterator nextHopToSender = gttpkt->headers.find("Sender");
			std::map<std::string, std::string>::iterator pktTarget = gttpkt->headers.find("NextHop");
			std::map<std::string, std::string>::iterator n = gttpkt->headers.find("N");
			std::istringstream ss(n->second);
			int ttl;
			ss >> ttl;
		        if(ttl <= 0) return 0; 
			mod->handleRouteRequest(gttpkt);
			std::string s1(replyTo->second);
			std::string s2(addr->getIp());
			if(s1.compare(s2)==0)
				return RREP;
			else{
				
				return BRDCST;
					
			}
		}
		return 0;
	}
	void wlan::sendBroadcast(GTTPacket* pkt, void* data, int size,int port){
		char* newdata=new char[size];
		pkt->build(&newdata);
		wlan::send(newdata,size,port);
	}
	void wlan::recevons(void* data,int size){
		skfd->recv(data,size);
		Modal::GTTParser parser;
		parser.eat((const char*)data, size);
		Modal::GTTPacket *gttpkt= parser.getPacket();
		
		switch(wlan::quefaire(gttpkt)){
			case BRDCST:
				break;
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
