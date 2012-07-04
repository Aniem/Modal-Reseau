#ifndef MODAL_TABLE_ENTRY
#define MODAL_TABLE_ENTRY

#include <string>

namespace Modal{

struct RoutingTableEntry {
    RoutingTableEntry();
    std::string nextHop;
    long expires;
};

} //end Modal

#endif /* MODAL_TABLE_ENTRY */
