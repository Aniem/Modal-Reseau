#include "list.h"
#include <unistd.h>
#include "../core/thread.h"
namespace Modal{
	class AckTime : public Thread{
		public:
			AckTime(int n, Modal::List* l);
			void run();
			void recevoir();
			
		protected:
			int seq;
			Modal::List* l;
			bool answer;
	};
}
