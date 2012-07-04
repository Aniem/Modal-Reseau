#include <unistd.h>
#include <list>
#include <strings.h>
#include "../core/thread.h"
namespace Modal{
	class AckTime : public Thread{
		public:
			AckTime(int n, std::list<int>* l,std::string dest);
			void run();
			void recevoir();
			
		protected:
			int seq;
			std::list<int>* l;
			bool answer;
			std::string* s;
	};
}
