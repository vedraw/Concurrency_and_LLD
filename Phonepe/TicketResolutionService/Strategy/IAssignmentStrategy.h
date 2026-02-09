#ifndef IASSIGNMENTSTRATEGY_H
#define IASSIGNMENTSTRATEGY_H

#include "../Ticket/Ticket.h"
#include <vector>

class IAssignmentStrategy {
public:
    virtual int execute(Ticket ticket, std::vector<int> agentIds) = 0;
    virtual ~IAssignmentStrategy() {}
};

#endif
