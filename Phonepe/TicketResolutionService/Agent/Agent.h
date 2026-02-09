#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>
#include "../Common/IssueType.h"

class Agent {
private:
    int id;
    std::string name;
    std::string email;
    std::vector<IssueType> expertise;
    std::vector<int> assignedTickets;

public:
    Agent(int id, const std::string& name, const std::string& email, std::vector<IssueType> expertise);
    int getAgentId() const;
    void assignTicket(int ticketId);
    std::vector<int> getAssignedTickets() const;
    std::string getEmail() const;
    std::string getName() const;
    void addExpertise(IssueType issueType);
    std::vector<IssueType> getExpertise() const;
};

#endif
