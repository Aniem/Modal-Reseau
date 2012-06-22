#include "requestBuilder.h"

namespace Epyx {
    int RequestBuilder::defaultTTL = 10;
    std::string RequestBuilder::protocol = "MESH";

    GTTPacket RequestBuilder::buildRREQ(std::string query, int ttl) {
        GTTPacket result;
	int finalTTL = ttl == 0 ? RequestBuilder::defaultTTL : ttl;

        result.protocol = RequestBuilder::protocol;
	result.method = "RREQ";

	//result.headers.insert(std::pair<std::string, std::string>("Source", ""));
        //result.headers.insert(std::pair<std::string, std::string>("Sender", ""));
        result.headers.insert(std::pair<std::string, std::string>("Destination", query));
        result.headers.insert(std::pair<std::string, std::string>("N", RequestBuilder::fromInt(finalTTL)));

        return result;
    }

    GTTPacket RequestBuilder::buildRREP(std::string rep, std::string dest, int ttl) {
 	GTTPacket result;
	int finalTTL = ttl == 0 ? RequestBuilder::defaultTTL : ttl;

        result.protocol = RequestBuilder::protocol;
	result.method = "RREP";

	result.headers.insert(std::pair<std::string, std::string>("Source", rep));
        result.headers.insert(std::pair<std::string, std::string>("Destination", dest));
	//result.headers.insert(std::pair<std::string, std::string>("NextHop", ""));
        result.headers.insert(std::pair<std::string, std::string>("N", RequestBuilder::fromInt(finalTTL)));

        return result;
    }

    std::string RequestBuilder::fromInt(int i) {
        std::ostringstream out;
        out << i;
        return out.str();
    }
}
