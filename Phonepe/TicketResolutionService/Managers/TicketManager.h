#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H

#include <unordered_map>
#include <string>
#include "../Ticket/Ticket.h"
#include "../Strategy/IAssignmentStrategy.h"
#include "AgentManager.h"

class TicketManager {
private:
    IAssignmentStrategy* assignStrategy;
    std::unordered_map<int, Ticket> ticketMap;
    int nextTicketId = 1;
    AgentManager& agentManager;
public:
    TicketManager(IAssignmentStrategy* strategy, AgentManager& agentManager);
    ~TicketManager();
    int createIssue(int transactionId, IssueType issueType, std::string subject, std::string description, std::string email);
    void assignIssue(int issueId);
    std::unordered_map<int, Ticket> getTicketMap();
    void updateIssue(int issueId, TicketStatus status, std::string resolution);
    void resolveIssue(int issueId, std::string resolution);
};

#endif
