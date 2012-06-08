#include "netselectreader.h"
#include "../core/common.h"

namespace Modal
{

    NetSelectReader::NetSelectReader()
    :owner(NULL) {
    }

    NetSelectReader::~NetSelectReader() {
    }

    NetSelect* NetSelectReader::getOwner() const {
        MODAL_ASSERT(owner != NULL);
        return owner;
    }

    void NetSelectReader::setOwner(NetSelect *ns) {
        MODAL_ASSERT(owner == NULL);
        owner = ns;
    }
}
