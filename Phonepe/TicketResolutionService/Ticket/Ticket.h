#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <vector>
#include "../Common/TicketStatus.h"
#include "../Common/IssueType.h"

class Ticket {
private:
    int ticketId;
    int transactionId;
    std::string subject;
    std::string description;
    std::string userEmail;
    IssueType issueType;
    TicketStatus ticketStatus;
    int assignedAgentId = -1;
    std::vector<std::string> resolutions;
public:
    Ticket() = default;
    Ticket(int ticketId, int transactionId, std::string subject, IssueType issueType, std::string description, std::string userEmail);

    void updateStatus(TicketStatus status);
    void assignAgent(int agentId);
    int getAssignedAgentId();
    int getTicketId() const;
    void addResolution(std::string resolution);
    std::vector<std::string> getResolutions() const;
    std::string getUserEmail() const;
    IssueType getIssueType() const;
};

#endif
