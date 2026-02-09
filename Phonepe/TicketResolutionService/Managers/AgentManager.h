#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include "../Agent/Agent.h"

class AgentManager {
public:
    std::unordered_map<int, Agent> agentMap;
    std::vector<int> agentIds;
    void addAgent(Agent agent);
    void viewAgentsWorkHistory(int agentId);
};

#endif
