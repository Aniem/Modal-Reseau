#ifndef MODAL_TABLE_ENTRY
#define MODAL_TABLE_ENTRY
struct RoutingTableEntry {
    std::string nextHop;
    long expires;
};
#endif /* MODAL_TABLE_ENTRY */
