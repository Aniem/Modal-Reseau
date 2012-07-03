#include "../net/udpsocket.h"

namespace Modal{
	class wlan : public Thread {
		public:
			int wlan();
			void recevons(void* buf, int size);
		protected:
			UDPSocket *skfd;
	};
}
