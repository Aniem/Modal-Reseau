#include "acktime.h"
#define TIMEOUT 1000*1000
namespace Modal{
		AckTime::AckTime(int n, std::list<int>* l,std::string dest){
			seq=n;
			this->l=l;
			s = new std::string(dest);
		}
		void AckTime::run(){
			usleep(TIMEOUT);
			if(!answer){
				//SEND NACK
			}
			l->insert(l->begin(),seq);
			return;
		}
		void AckTime::recevoir(){
			answer=true;
		}
}
