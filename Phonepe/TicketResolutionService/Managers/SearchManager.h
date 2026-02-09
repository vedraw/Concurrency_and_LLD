#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "../Ticket/Ticket.h"

class SearchManager {
public:
    std::vector<Ticket> getIssue(std::unordered_map<int, Ticket> ticketMap, int issueId);
    std::vector<Ticket> getIssue(std::unordered_map<int, Ticket> ticketMap, std::string email);
    std::vector<Ticket> getIssue(std::unordered_map<int, Ticket> ticketMap, IssueType issueType);
};

#endif
