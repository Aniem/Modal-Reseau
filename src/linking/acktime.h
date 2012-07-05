#ifndef ACKTIME_H
#define ACKTIME_H
#include <unistd.h>
#include <list>
#include <strings.h>
#include "../parser/gttpacket.h"
#include "../modRoute/requestBuilder.h"
#include "../modRoute/modRoute.h"
#include "../core/thread.h"
namespace Modal{
	class AckTime : public Thread{
		public:
			AckTime(int n, std::list<int>* l,std::string dest,std::string src);
			void run();
			void recevoir();
			void sendNACK();
		protected:
			int seq;
			std::list<int>* l;
			std::string* src;
			bool answer;
			std::string* s;
	};
}
#endif
