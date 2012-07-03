#include "../net/udpsocket.h"
#include "../net/address.h"
#include "../core/thread.h"
#include "../modRoute/modRoute.h"
#include "../tuntap/tuninterface.h"
#include "../parser/gttpacket.h"
#include "../parser/gttparser.h"
#include "../modRoute/requestBuilder.h"
#include <iostream>
#include <string>
#include <strings.h>
//#include "../api.h"
namespace Modal{
	class wlan : public Thread {
		public:
			wlan(Modal::TunInterface tun,Modal::ModRoute mod,const std::string& ip, unsigned short port);
			~wlan();
			void recevons(void* buf, int size);
			void send(void* data, int size,int port);
			void sendToSomeone(void* data, int size,int port,std::string ip);
			void run();
			int quefaire(Modal::GTTPacket * gttpkt);
			void sendBroadcast(GTTPacket* pkt,  int size,int port);
			void sendUnicast(GTTPacket* pkt, int size,int port,std::string ip);
		protected:
			Modal::UDPSocket* skfd;
			Modal::TunInterface *t;
			Modal::ModRoute *mod;
			Modal::Address *addr;
	};
}
