#include "../net/udpsocket.h"
#include "../net/address.h";
#include "../core/thread.h";

namespace Modal{
	class wlan : public Thread {
		public:
			int wlan(Modal::TunInterface tun,Modal::ModRoute mod,const std::string& ip, unsigned short port);
			~wlan();
			void recevons(void* buf, int size);
			void sendons(
			void run();
		protected:
			Modal::UDPSocket skfd=UDPSocket();
			Modal::TunInterface *t;
			Modal::ModRoute *mod;
			Modal::Address *addr;
	};
}
