#ifndef MODAL_TUNINTERFACE_H
#define MODAL_TUNINTERFACE_H

#include "../net/tcpsocket.h"
#include "../net/udpsocket.h"
#include "../core/thread.h"
#include "../parser/gttpacket.h"
#include "../core/blocking-queue.h"
#include "tunwriter.h"

namespace Modal {
    
    class TunInterface : public Thread
    {
        public:
            TunInterface(char * dev);
            int openDevNetTun(std::string dev);
            ~TunInterface();
            void setMTU(int i);
            void setIPv6address(std::string dev);
            GTTPacket* receive();
            void write(const GTTPacket & pkt );
            void run();
            
        private:
            std::string extractIPv6Address(char* data, int pos);
            void activate();
            std::string deviceName;
            int descriptor;
            int read(char* data, int maxsize);
            BlockingQueue<GTTPacket> toRead;
            TunWriter writer;
            void CharToHex(char c, char *Hex);
            char HexDigit(char c);
    };
    
} // namespace Modal

#endif // MODAL_TUNINTERFACE_H
