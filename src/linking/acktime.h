#include <unistd.h>
#include <list>
#include "../core/thread.h"
namespace Modal{
	class AckTime : public Thread{
		public:
			AckTime(int n, std::list<int>* l);
			void run();
			void recevoir();
			
		protected:
			int seq;
			std::list<int>* l;
			bool answer;
	};
}
