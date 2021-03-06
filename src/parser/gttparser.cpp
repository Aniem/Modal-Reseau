#include "gttparser.h"
#include "../core/common.h"
#include <string.h>

namespace Modal
{

    GTTParser::GTTParser()
    :currentPkt(NULL), hasError(false) {
        this->reset();
    }

    GTTParser::~GTTParser() {
        this->reset();
    }

    void GTTParser::reset() {
        // Discard previous data
        lineParser.reset();
        this->startPacket();
    }

    void GTTParser::startPacket() {
        // Set up inernal state
        if (currentPkt != NULL) {
            delete currentPkt;
            currentPkt = NULL;
        }
        datapos = dataposFirstLine;
        hasError = false;
        errorMessage = "";
    }

    bool GTTParser::getError(std::string& userErr) {
        if (!hasError) {
            userErr.assign("");
            return false;
        } else {
            userErr.assign(errorMessage);
            return true;
        }
    }

    void GTTParser::eat(const char *data, long size) {
        MODAL_ASSERT(data != NULL && size > 0);
        lineParser.push(data, size);
    }

    GTTPacket* GTTParser::getPacket() {
        std::string line;
        try {
            while (true) {
                switch (datapos) {
                    case dataposFirstLine:
                        // Allocate a new packet
                        if (currentPkt == NULL)
                            currentPkt = new GTTPacket();

                        // Read first line
                        if (!lineParser.popLine(line))
                            return NULL;

                        this->parseFirstLine(line);

                        datapos = dataposHeaders;
                        /* Go through */
                    case dataposHeaders:
                        // Return lines
                        if (!lineParser.popLine(line))
                            return NULL;
                        if (line.length() != 0) {
                            this->parseHeaderLine(line);
                            break;
                        }
                        // Empty line
                        datapos = dataposContent;
                        /* Go through */
                    case dataposContent:
                        if (currentPkt->size > 0) {
                            // Read body
                            char *body = new char[currentPkt->size];
                            if (!lineParser.popData(body, currentPkt->size)) {
                                delete[] body;
                                return NULL;
                            }
                            currentPkt->body = body;
                            body = NULL;
                        }
                        GTTPacket* pkt = currentPkt;
                        currentPkt = NULL;
                        this->startPacket();
                        return pkt;
                }
            }
        } catch (ParserException e) {
            log::error << "An error occured in GTTParser while processing a packet:\n" <<
                e.getMessage() << log::endl;
            errorMessage = e.getMessage();
            hasError = true;
            return NULL;
        }
        return NULL;
    }

    void GTTParser::parseFirstLine(const std::string& line) {
        const char *l = line.c_str();
        int i = 0, iMethod = 0;

        if (line.length() == 0)
            throw ParserException("GTTParser", "empty first line");

        // Read protocol name
        if (!isupper(l[i]))
            throw ParserException("GTTParser", "protocol name should begin with capital letters");
        i++;
        while (l[i] != ' ') {
            if (!(isupper(l[i]) || isdigit(l[i]) || (l[i] == '_')))
                throw ParserException("GTTParser", "protocol name should continue with [A-Z0-9]* or end with a space");
            i++;
        }
        currentPkt->protocol = std::string(l, i);
        i++;

        // Read method name
        iMethod = i;
        if (!isupper(l[i]))
            throw ParserException("GTTParser", "method name should begin with capital letters");
        i++;
        while (l[i] != 0) {
            if (!(isupper(l[i]) || isdigit(l[i]) || (l[i] == '_')))
                throw ParserException("GTTParser", "method name should continue with [A-Z0-9]* or end with a space");
            i++;
        }
        currentPkt->method = std::string(l + iMethod, i - iMethod);
    }

    void GTTParser::parseHeaderLine(const std::string& line) {
        const char *l = line.c_str();
        int i = 0, iValue = 0;
        MODAL_ASSERT(line.length() != 0);

        // Read flag name
        if (!isalpha(l[i]))
            throw ParserException("GTTParser", "flag_name should begin with [a-zA-Z] or we should add newline to end the header");
        i++;
        while (l[i] != ':') {
            if (!(isalnum(l[i]) || (l[i] == '_') || (l[i] == '-')))
                throw ParserException("GTTParser", "flag name should continue with [A-Za-z0-9-_]* or end with a space");
            i++;
        }
        std::string flagName(l, i);
        i++;

        // Skip spaces
        while (l[i] == ' ')
            i++;
        if (l[i] == 0)
            throw ParserException("GTTParser", "flag without value");

        // Read value
        iValue = i;
        while (l[i] != 0) {
            if (!(l[i] >= 32 && l[i] < 126))
                throw ParserException("GTTParser", "flag_value should consist of printable characters or just end with CRLF");
            i++;
        }
        std::string flagValue(l + iValue, i - iValue);

        // Content length
        if (!strcasecmp(flagName.c_str(), "content-length")) {
            if (currentPkt->size > 0)
                throw ParserException("GTTParser", "content-length flag has already appeared");
            currentPkt->size = String::toInt(flagValue.c_str());
            if (currentPkt->size <= 0)
                throw ParserException("GTTParser", "not valid body size, body size should be a positive integer");
        } else {
            currentPkt->headers[flagName] = flagValue;
        }
    }
}
