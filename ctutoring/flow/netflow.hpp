#ifndef NETFLOW_HPP
#define NETFLOW_HPP

#include <string>
#include <vector>

/**
 * Neighbor entry for adjacency list.
 */
struct NeighborEntry
{
    unsigned neighbor;
    unsigned weight;  // Since application is network flow,
                      // weights are nonnegative.
};

/**
 * I personally hate using typedef this way. (I think creating a new class
 * is better, even if the class would just have one member.) However, C++
 * programmers sometimes do this kind of thing, so you should be exposed
 * to it.
 *
 * Don't use { } when initializing the below, if you're calling any constructor
 * besides the default one. STL types tend to think that you are providing
 * all of the data if you use { } instead of ( ). Maybe this is even more
 * reason that typedef is a bad idea here. Just some thoughts.
 */
typedef std::vector<std::vector<NeighborEntry>> AdjList;

AdjList solveNetworkFlow(const AdjList& flowNetwork);

std::vector<std::string> assignTutoring(
    const std::vector<std::vector<std::string>>& preferences,
    const std::vector<std::string>& offered);

#endif  // NETFLOW_HPP
