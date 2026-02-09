#ifndef FIRSTAVAILABLE_H
#define FIRSTAVAILABLE_H

#include "IAssignmentStrategy.h"

class FirstAvailable : public IAssignmentStrategy {
public:
    int execute(Ticket ticket, std::vector<int> agentIds) override;
};

#endif
