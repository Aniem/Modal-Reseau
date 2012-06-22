#include "requestBuilder.h"

namespace Modal {
    int RequestBuilder::defaultTTL = 10;
    std::string RequestBuilder::protocol = "MESH";

    static N2NP::Packet buildRREQ(std::string query, int ttl) {
	int finalTTL = ttl == 0 ? RequestBuilder::defaultTTL : ttl;

        result.protocol = RequestBuilder::protocol;
	result.method = "RREQ";
        //result.version = "1";
        //result.pktID = 2010;

	result.headers.insert(std::pair<std::string, std::string>("Source", "")); // TODO récupérer l'IP courante
        result.headers.insert(std::pair<std::string, std::string>("Destination", query));
        result.headers.insert(std::pair<std::string, std::string>("N", RequestBuilder::fromInt(finalTTL)));

        return result;
    }

    N2NP::Packet RequestBuilder::buildRREP(std::string rep, std::string dest, int ttl) {
 	N2NP::Packet result;
	int finalTTL = ttl == 0 ? RequestBuilder::defaultTTL : ttl;

        result.protocol = RequestBuilder::protocol;
	result.method = "RREP";

	result.headers.insert(std::pair<std::string, std::string>("Source", rep));
        result.headers.insert(std::pair<std::string, std::string>("Destination", dest));
	result.headers.insert(std::pair<std::string, std::string>("NextHop", "")); // TODO récupérer l'IP courante
        result.headers.insert(std::pair<std::string, std::string>("N", RequestBuilder::fromInt(finalTTL)));

        return result;
    }

    std::string RequestBuilder::fromInt(int i) {
        std::ostringstream out;
        out << i;
        return out.str();
    }
}
