#include "Ticket.h"

Ticket::Ticket(int ticketId, int transactionId, std::string subject, IssueType issueType, std::string description, std::string userEmail)
    : ticketId(ticketId), transactionId(transactionId), subject(subject), issueType(issueType),
      description(description), userEmail(userEmail), ticketStatus(TicketStatus::OPEN) {}

void Ticket::updateStatus(TicketStatus status) {
    ticketStatus = status;
}

void Ticket::assignAgent(int agentId) {
    assignedAgentId = agentId;
}

int Ticket::getAssignedAgentId() {
    return assignedAgentId;
}

int Ticket::getTicketId() const {
    return ticketId;
}

void Ticket::addResolution(std::string resolution) {
    resolutions.push_back(resolution);
}

std::vector<std::string> Ticket::getResolutions() const {
    return resolutions;
}

std::string Ticket::getUserEmail() const {
    return userEmail;
}

IssueType Ticket::getIssueType() const {
    return issueType;
}
