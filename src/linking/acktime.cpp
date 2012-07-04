#include "acktime.h"
#define TIMEOUT 1000*1000
namespace Modal{
		AckTime::AckTime(int n, Modal::List* l){
			seq=n;
			this->l=l;
		}
		void AckTime::run(){
			usleep(TIMEOUT);
			if(!answer){
				//SEND NACK
			}
			l=new List(seq,l);
			return;
		}
		void AckTime::recevoir(){
			answer=true;
		}
}
