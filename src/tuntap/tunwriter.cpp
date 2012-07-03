#include "tunwriter.h"

#include <unistd.h>



namespace Modal {
    
    TunWriter::TunWriter()
    {
    }
    void TunWriter::setDescriptor(int fd)
    {
        this->fd=fd;
    }

    void TunWriter::addTask(GTTPacket * pkt){
        toWrite.push(pkt);
    }
    void TunWriter::run(){
        while(true){
            if (!toWrite.empty()){
                GTTPacket* pkt = toWrite.pop();
                ::write(fd,pkt->body,pkt->size);
            }else{
                sleep(1);
            }
        }
    }
    
} // namespace Modal
