#include "TicketManager.h"
#include <iostream>

TicketManager::TicketManager(IAssignmentStrategy* strategy, AgentManager& agentManager)
    : assignStrategy(strategy), agentManager(agentManager) {}

TicketManager::~TicketManager() {
    delete assignStrategy;
}

int TicketManager::createIssue(int transactionId, IssueType issueType, std::string subject, std::string description, std::string email) {
    std::cout << "Creating issue: " << subject << " with email: " << email << " and transactionId: " << transactionId << std::endl;
    Ticket t(nextTicketId, transactionId, subject, issueType, description, email);
    ticketMap.insert({t.getTicketId(), t});
    return nextTicketId++;
}

void TicketManager::assignIssue(int issueId) {
    int agentId = assignStrategy->execute(ticketMap.at(issueId), agentManager.agentIds);
    if (agentId != -1) {
        ticketMap.at(issueId).assignAgent(agentId);
        agentManager.agentMap.at(agentId).assignTicket(issueId);
    }
    std::cout << "Assigning issue: " << issueId << " to agent: " << agentId << std::endl;
}

std::unordered_map<int, Ticket> TicketManager::getTicketMap() {
    return ticketMap;
}

void TicketManager::updateIssue(int issueId, TicketStatus status, std::string resolution) {
    std::cout << "Updating issue: " << issueId << std::endl;
    ticketMap.at(issueId).updateStatus(status);
    ticketMap.at(issueId).addResolution(resolution);
}

void TicketManager::resolveIssue(int issueId, std::string resolution) {
    std::cout << "Resolving issue: " << issueId << std::endl;
    ticketMap.at(issueId).updateStatus(TicketStatus::RESOLVED);
    ticketMap.at(issueId).addResolution(resolution);
}
