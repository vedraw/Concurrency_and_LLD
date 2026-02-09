#include "FirstAvailable.h"

int FirstAvailable::execute(Ticket ticket, std::vector<int> agentIds) {
    if (agentIds.empty()) return -1;
    return agentIds[0];
}
