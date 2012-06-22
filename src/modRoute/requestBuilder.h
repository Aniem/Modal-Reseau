#ifndef MODAL_REQBUILDER_H
#define MODAL_REQBUILDER_H
#include "../core/thread.h"
#include "../parser/gttpacket.h"
#include <sstream>

namespace Modal {
    class RequestBuilder : public Thread {

    public:
    static GTTPacket buildRREQ(std::string query, int ttl);
    static GTTPacket buildRREP(std::string rep, std::string dest, int ttl);

    private:
    static std::string fromInt(int i);
    static int defaultTTL;
    static std::string protocol;
    };
}

#endif /* MODAL_REQBUILDER_H */
