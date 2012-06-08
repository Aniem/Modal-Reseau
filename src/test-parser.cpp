#include "api.h"

// Maximum packet length
static const int MAXLENGTH = 10000;

bool test_parser() {
    // Build a N2NP packet
    std::string testmethod("Test");
    std::string message("Hello World. Let me introduce you to Modal.");
    Modal::N2NP::Packet pkt(testmethod, message.length(), message.c_str());
    pkt.from = Modal::N2NP::NodeId("Modal@129.104.13.37:42");
    pkt.to = Modal::N2NP::NodeId("World@");
    pkt.method = "PING";
    pkt.version = "1";
    pkt.pktID = 2010;

    // Raw packet
    Modal::log::info << "Building packet " << pkt << Modal::log::endl;
    char *data = NULL;
    unsigned long size = pkt.build(&data);
    Modal::log::info << "Raw packet:\n" << std::string(data, size) << Modal::log::endl;

    // Parse
    Modal::GTTParser parser;
    Modal::GTTPacket *gttpkt = NULL;
    parser.eat(data, size);
    gttpkt = parser.getPacket();
    delete[] data;
    data = NULL;
    if (gttpkt == NULL) {
        Modal::log::info << "Incomplete raw packet :(" << Modal::log::endl;
        return false;
    }
    Modal::log::info << "Parsed GTT packet:\n" << *gttpkt << Modal::log::endl;
    // Create N2NP packet from GTT
    Modal::N2NP::Packet n2nppkt(*gttpkt);
    delete gttpkt;
    gttpkt = NULL;
    Modal::log::info << "Parsed N2NP packet: " << n2nppkt << Modal::log::endl;
    return true;
}

int main() {
    Modal::API epyx;
    try {
        test_parser();
    } catch (Modal::Exception e) {
        Modal::log::fatal << e << Modal::log::endl;
    }
    return 0;
}
