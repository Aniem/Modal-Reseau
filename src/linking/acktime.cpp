
#include "acktime.h"
#define TIMEOUT 1000*100
namespace Modal{
		AckTime::AckTime(int n, std::list<int>* l,std::string dest,std::string src){
			seq=n;
			this->l=l;
			s = new std::string(dest);
			this->src=new std::string(src);
		}
		void AckTime::sendNACK(){
			/*GTTPacket *pkt=RequestBuilder::buildNACK(*src,*s,ModRoute::getNextHop(*s));
			char* newdata=new char[2048];
			pkt->build(&newdata);
			wlan::send(newdata,2048,1337);
			delete[] newdata;
			delete pkt;*/
}
		void AckTime::run(){
			usleep(TIMEOUT);
			if(!answer){
				AckTime::sendNACK();
			}
			l->insert(l->begin(),seq);
			return;
		}
		void AckTime::recevoir(){
			answer=true;
		}
}

