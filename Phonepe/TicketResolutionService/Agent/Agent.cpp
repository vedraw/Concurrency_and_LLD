#include "Agent.h"
using namespace std;

Agent::Agent(int id, const std::string& name, const std::string& email, std::vector<IssueType> expertise)
    : id(id), name(name), email(email), expertise(expertise) {}

int Agent::getAgentId() const { return id; }

void Agent::assignTicket(int ticketId) {
    assignedTickets.push_back(ticketId);
}

std::vector<int> Agent::getAssignedTickets() const { return assignedTickets; }

std::string Agent::getEmail() const { return email; }

std::string Agent::getName() const { return name; }

void Agent::addExpertise(IssueType issueType) { expertise.push_back(issueType); }

std::vector<IssueType> Agent::getExpertise() const { return expertise; }
