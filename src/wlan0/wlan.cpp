#include "wlan.h"
#include "../core/log.h"
#include <sstream>
#define RREP 4 
#define RREQ 3
#define PKT 2
#define ACK 1
#define NACK 5
namespace Modal{
	wlan::wlan(unsigned short port,std::string devicename):skfd(){
		//this->skfd=new UDPSocket();
		skfd.create();
        setsockopt(this->skfd.getFd(),SOL_SOCKET, SO_BINDTODEVICE, devicename.c_str(), devicename.size());
		this->skfd.setBroadcast(1);
        this->addr=new Address("169.254.42.42",port,4); //random address, not useful
        
	}
	wlan::~wlan(){
		delete addr;
		//delete skfd;
	}
	/*int wlan::quefaire(Modal::GTTPacket * gttpkt){
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

		return 0;
	} // */
	void wlan::sendBroadcast(GTTPacket* pkt, int size,unsigned short port){
		char* newdata=new char[size];
        int s = (int) pkt->build(&newdata);
		send(newdata,s,port);
		delete[] newdata;
	}
	void wlan::sendUnicast(GTTPacket* pkt, int size,unsigned short port,std::string ip){
		char* newdata=new char[size];
		pkt->build(&newdata);
		wlan::sendToSomeone(newdata,size,port,ip);
		delete[] newdata;
	}

	GTTPacket* wlan::recevons(void* data,int size){
        Modal::GTTParser parser;
        Modal::GTTPacket *gttpkt = NULL;
        do{
            skfd.recv(data,size);
            parser.eat((const char*)data, size);
		}while((gttpkt= parser.getPacket())==NULL);
		

		//int res=wlan::quefaire(gttpkt);
		return gttpkt;
	}

	void wlan::send(void* data, int size,unsigned short port){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = INADDR_BROADCAST;
        try{
            skfd.send(data,size,(struct sockaddr*)&that);
        }catch(Exception e){
            log::fatal << e << log::endl;
        }
	}

	void wlan::sendToSomeone(void* data, int size,unsigned short port,std::string ip){
		struct sockaddr_in that;
		bzero(&that,sizeof(that));
		that.sin_family = AF_INET;
		that.sin_port = htons(port);
		that.sin_addr.s_addr = inet_addr(ip.c_str());
		skfd.send(data,size,(struct sockaddr*)&that);
	}


	bool compare(){
		return true;
	}

}
