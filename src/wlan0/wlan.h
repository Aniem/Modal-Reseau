#include "../net/udpsocket.h"

namespace Modal{
	class wlan : public Thread {
		public:
			int wlan(Modal::TunInterface tun,Modal::ModRoute mod);
			void recevons(void* buf, int size);
			void run();
		protected:
			Modal::UDPSocket skfd=UDPSocket();
			Modal::TunInterface *t;
			Modal::ModRoute *mod;
			
	};
}
