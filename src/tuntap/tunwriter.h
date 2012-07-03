#ifndef MODAL_TUNWRITER_H
#define MODAL_TUNWRITER_H
#include "../core/thread.h"
#include "../core/blocking-queue.h"
#include "../parser/gttpacket.h"

namespace Modal {
    
    class TunWriter : public Thread
    {
        public:
            TunWriter();
            void run();
            void addTask(GTTPacket *pkt);
            void setDescriptor(int fd);
        private:
            int fd;
            BlockingQueue<GTTPacket> toWrite;
    };
    
} // namespace Modal

#endif // MODAL_TUNWRITER_H
