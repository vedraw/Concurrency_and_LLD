#include "AgentManager.h"

void AgentManager::addAgent(Agent agent) {
    std::cout << "Adding agent: " << agent.getAgentId() << " with email: " << agent.getEmail() << std::endl;
    agentMap.insert({agent.getAgentId(), agent});
    agentIds.push_back(agent.getAgentId());
}

void AgentManager::viewAgentsWorkHistory(int agentId) {
    std::cout << "Viewing work history for agentID: " << agentId << std::endl;
    for (auto& [id, agent] : agentMap) {
        if (agent.getAgentId() == agentId) {
            std::cout << "Agent: " << agent.getName() << " with email: " << agent.getEmail() << std::endl;
        }
    }
}
