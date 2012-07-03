#include "wlan.h"
#include "address.h";
namespace{
	int wlan::wlan(){

	      this.skfd=new UDPSocket();

	  return 0;
	}
	void wlan:recevons(void* data,int size){
		skfd->recv(data,size);
		
	}
	Modal::GTTPacket parse(void* data, int size){
		    Modal::GTTParser parser;
		    parser.eat(data, size);
		    return parser.getPacket();
	}
	/*Modal::GTTParser parser;
    Modal::GTTPacket *gttpkt = NULL;
	Modal::GTTPacket*/
}
