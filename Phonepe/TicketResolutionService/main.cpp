#include <iostream>
#include "Managers/AgentManager.h"
#include "Managers/TicketManager.h"
#include "Managers/SearchManager.h"
#include "Strategy/StrategyFactory.h"

int main() {
    AgentManager am;
    am.addAgent(Agent(1, "Agent1", "agent1@example.com", {IssueType::PAYMENT, IssueType::GOLD}));
    am.addAgent(Agent(2, "Agent2", "agent2@example.com", {IssueType::PAYMENT}));

    IAssignmentStrategy* strat = StrategyFactory::createStrategy(StrategyType::FirstAvailable);
    TicketManager tm(strat, am);
    tm.createIssue(1, IssueType::PAYMENT, "Issue 1", "Description 1", "UserEmail1@example.com");
    tm.createIssue(2, IssueType::PAYMENT, "Issue 2", "Description 2", "UserEmail2@example.com");
    tm.createIssue(3, IssueType::MUTUAL_FUND, "Issue 3", "Description 3", "UserEmail3@example.com");

    tm.assignIssue(1);
    tm.assignIssue(2);
    tm.assignIssue(3);
    am.viewAgentsWorkHistory(1);

    SearchManager sm;
    auto res = sm.getIssue(tm.getTicketMap(), "UserEmail1@example.com");
    std::cout << "Search results: " << res.size() << std::endl;
    for (auto& ticket : res) {
        std::cout << "Ticket: " << ticket.getTicketId() << " with email: " << ticket.getUserEmail() << std::endl;
    }

    res = sm.getIssue(tm.getTicketMap(), 1);
    std::cout << "Search results: " << res.size() << std::endl;
    for (auto& ticket : res) {
        std::cout << "Ticket: " << ticket.getTicketId() << " with email: " << ticket.getUserEmail() << std::endl;
    }

    res = sm.getIssue(tm.getTicketMap(), IssueType::PAYMENT);
    std::cout << "Search results: " << res.size() << std::endl;
    for (auto& ticket : res) {
        std::cout << "Ticket: " << ticket.getTicketId() << " with email: " << ticket.getUserEmail() << std::endl;
    }

    tm.updateIssue(1, TicketStatus::IN_PROGRESS, "Resolution 1");
    tm.resolveIssue(1, "Resolution 1");

    return 0;
}
