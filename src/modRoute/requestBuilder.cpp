#include "requestBuilder.h"

namespace Modal {
    std::string RequestBuilder::protocol = "MESH";

   GTTPacket* RequestBuilder::buildRREQ(std::string source, std::string dest, std::string sender, int ttl) {
        GTTPacket* result = new GTTPacket();

        result->protocol = RequestBuilder::protocol;
	result->method = "RREQ";

	result->headers.insert(std::pair<std::string, std::string>("Source", source));
        result->headers.insert(std::pair<std::string, std::string>("Destination", dest));
        result->headers.insert(std::pair<std::string, std::string>("Sender", sender));
        result->headers.insert(std::pair<std::string, std::string>("N", RequestBuilder::fromInt(ttl)));

        return result;
    }

    GTTPacket* RequestBuilder::buildRREP(std::string source, std::string dest, std::string sender, std::string nextHop, int ttl) {
 	GTTPacket* result = new GTTPacket();

        result->protocol = RequestBuilder::protocol;
	result->method = "RREP";

	result->headers.insert(std::pair<std::string, std::string>("Source", source));
        result->headers.insert(std::pair<std::string, std::string>("Destination", dest));
        result->headers.insert(std::pair<std::string, std::string>("Sender", sender));
	result->headers.insert(std::pair<std::string, std::string>("NextHop", nextHop));
        result->headers.insert(std::pair<std::string, std::string>("N", RequestBuilder::fromInt(ttl)));

        return result;
    }

    GTTPacket* RequestBuilder::buildNACK(std::string source, std::string dest, std::string nextHop) {
        GTTPacket* result = new GTTPacket();

        result->protocol = RequestBuilder::protocol;
	result->method = "NACK";

	result->headers.insert(std::pair<std::string, std::string>("Source", source));
        result->headers.insert(std::pair<std::string, std::string>("Destination", dest));
	result->headers.insert(std::pair<std::string, std::string>("NextHop", nextHop));

        return result;
    }

    std::string RequestBuilder::fromInt(int i) {
        std::ostringstream out;
        out << i;
        return out.str();
    }
}
