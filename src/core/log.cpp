#include "log.h"
#include "mutex.h"
#include <errno.h>
#include <cstring>

namespace Modal {
namespace log {

    Worker* _worker = NULL;
    TLSPointer<BufferContainer>* _buffers = NULL;
    EndlStruct endl;
    ErrstdStruct errstd;
    bool initialized = false;

    static BufferContainer* create_buffers(){
        return new BufferContainer;
    }

    void init(int flags, const std::string& file){
        MODAL_ASSERT_NO_LOG(Thread::isInitialized());
        _worker = new Worker(flags, file);
        _buffers = new TLSPointer<BufferContainer>(create_buffers);
        initialized = true;
    }

    void flush(){
        _worker->flush(false);
    }

    void waitFlush(){
        _worker->flush(true);
    }
    void flushAndQuit(){
        _worker->quit();
    }

    Stream::Stream(int prio): priority(prio) {}

    Stream::~Stream(){}

    Stream& Stream::operator<<(const EndlStruct& f) {
        MODAL_ASSERT_NO_LOG(log::initialized);
        std::ostringstream* buffer = &_buffers->get()->b[this->priority];
        _worker->write(buffer->str(), this->priority);
        buffer->str("");
        return *this;
    }

    Stream& Stream::operator<<(const ErrstdStruct& f) {
        MODAL_ASSERT_NO_LOG(log::initialized);
        int err_code = errno;
        static Mutex strerrorMutex;
        strerrorMutex.lock();
        const char *err_str = std::strerror(err_code);
        strerrorMutex.unlock();
        *this << err_str << " (errno #" << err_code << ")";
        return *this;
    }
}
}
