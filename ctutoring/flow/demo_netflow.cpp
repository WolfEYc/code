#include "netflow.hpp"

#include <iostream>

static void printAdjList(const AdjList& adjList)
{
    for (unsigned from = 0; from < adjList.size(); ++from)
    {
        const auto& neighborList = adjList[from];
        std::cout << from << ": ";
        for (unsigned toIndex = 0; toIndex < neighborList.size(); ++toIndex)
            std::cout << neighborList[toIndex].neighbor << " ("
                << neighborList[toIndex].weight << ") ";
        std::cout << '\n';
    }
}

static void printAssignment(const std::vector<std::string>& preferences)
{
    for (unsigned i = 0; i < preferences.size(); ++i)
        std::cout << "Tutor #" << i << " assigned to: " << preferences[i] << '\n';
}

int main()
{
    // Create the flow network shown in slide 59 of the graphs slide deck.
    AdjList adjList{6};
    // I could have also done adjList[0].emplace_back(1, 5) if NeighborEntry
    // had a constructor that took the neighbor and weight as parameters.
    adjList[0].push_back({1, 5});
    adjList[0].push_back({2, 10});
    adjList[2].push_back({1, 5});
    adjList[1].push_back({3, 10});
    adjList[2].push_back({3, 3});
    adjList[2].push_back({4, 1});
    adjList[3].push_back({4, 20});
    adjList[3].push_back({5, 5});
    adjList[4].push_back({5, 7});
    auto maxFlow = solveNetworkFlow(adjList);
    std::cout << "=== Adjacency list of the flow ===\n";
    printAdjList(maxFlow);
    std::vector<std::vector<std::string>> prefs(5);
    prefs.at(0).insert(prefs[0].begin(), {"ECS 20", "ECS 36A"});
    prefs.at(1).insert(prefs[1].begin(), {"ECS 20", "ECS 36B", "ECS 36C"});
    prefs.at(2).insert(prefs[2].begin(), {"ECS 36B", "ECS 36C"});
    prefs.at(3).insert(prefs[3].begin(), {"ECS 20", "ECS 36C"});
    prefs.at(4).insert(prefs[4].begin(), {"ECS 36C"});
    auto assignment = assignTutoring(prefs, 
        {"ECS 20", "ECS 36A", "ECS 36B", "ECS 36C"});
    std::cout << "=== Tutor assignments ===\n";
    printAssignment(assignment);
}
