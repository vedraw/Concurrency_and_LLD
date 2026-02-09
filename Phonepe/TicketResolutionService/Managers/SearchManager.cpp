#include "SearchManager.h"

std::vector<Ticket> SearchManager::getIssue(std::unordered_map<int, Ticket> ticketMap, int issueId) {
    std::vector<Ticket> results;
    for (auto& [id, ticket] : ticketMap) {
        if (ticket.getTicketId() == issueId) {
            results.push_back(ticket);
        }
    }
    return results;
}

std::vector<Ticket> SearchManager::getIssue(std::unordered_map<int, Ticket> ticketMap, std::string email) {
    std::vector<Ticket> results;
    for (auto& [id, ticket] : ticketMap) {
        if (ticket.getUserEmail().find(email) != std::string::npos) {
            results.push_back(ticket);
        }
    }
    return results;
}

std::vector<Ticket> SearchManager::getIssue(std::unordered_map<int, Ticket> ticketMap, IssueType issueType) {
    std::vector<Ticket> results;
    for (auto& [id, ticket] : ticketMap) {
        if (ticket.getIssueType() == issueType) {
            results.push_back(ticket);
        }
    }
    return results;
}
