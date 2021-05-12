/**
 * Code (released to the students) for demonstrating the use of the Graph
 * class.
 * Uses a mix of assert()-based unit testing and printing out values.
 */

#include "graph.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>

#define INPUT_FILE_DIR "demo_graph_files"

static void printAdjMatrix(
    const std::vector<std::vector<int>>& adjMatrix,
    bool weighted)
{
    for (unsigned i = 0; i < adjMatrix.size(); ++i)
    {
        std::cout << i << ": ";
        for (int weight : adjMatrix[i]) 
        {
            if (weighted)
            {
                // Unfortunately and strangely, if I use the ternary operator
                // here, the ASCII value of '.' gets printed out. I guess
                // the C++ compiler assigns a specific type to the output of
                // the ternary operator.
                if (weight == 0) std::cout << '.';
                else std::cout << weight;
                std::cout << ' ';
            }
            else std::cout << (weight == 0 ? '.' : 'X') << ' ';
        }
        std::cout << std::endl;
    }
}

static void printAdjList(
    const std::vector<std::vector<std::pair<unsigned, int>>>& adjList,
    bool weighted)
{
    for (unsigned i = 0; i < adjList.size(); ++i)
    {
        std::cout << i << ": ";
        for (std::pair<unsigned, int> neighborEntry : adjList[i])
        {
            std::cout << neighborEntry.first;
            if (weighted) std::cout << " (" << neighborEntry.second << ')';
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

static void demo1()
{
    std::vector<std::pair<unsigned, unsigned>> edges;
    // More on emplace_back(): https://www.cplusplus.com/reference/vector/vector/emplace_back/
    edges.emplace_back(3, 2);
    edges.emplace_back(0, 1);
    edges.emplace_back(0, 2);
    // Invoke the second of the three constructors.
    Graph g1{4, edges, true};
    assert(!g1.isWeighted()); 
    assert(g1.isDirected());
    assert(g1.getNumVertices() == 4);
    assert(g1.getNumEdges() == 3);
    std::cout << "=== g1's adjacency matrix ===\n";
    printAdjMatrix(g1.getAdjacencyMatrix(), g1.isWeighted());
    std::cout << "=== g1's adjacency list ===\n";
    printAdjList(g1.getAdjacencyList(), g1.isWeighted());

    // Invoke the first of the three constructors.
    Graph g2{INPUT_FILE_DIR"/adj_list2.txt"};
    assert(g2.isWeighted());
    assert(g2.isDirected());
    assert(g2.getNumVertices() == 4);
    assert(g2.getNumEdges() == 5);
    std::cout << "=== g2's adjacency matrix ===\n";
    printAdjMatrix(g2.getAdjacencyMatrix(), g2.isWeighted());
    std::cout << "=== g2's adjacency list ===\n";
    printAdjList(g2.getAdjacencyList(), g2.isWeighted());

    // Again, invoke the first of the three constructors, this time with
    // an undirected graph.
    Graph g3{INPUT_FILE_DIR"/edge_list2.txt"};
    assert(g3.isWeighted());
    assert(!g3.isDirected());
    assert(g3.getNumVertices() == 4);
    assert(g3.getNumEdges() == 3);
    std::cout << "=== g3's adjacency matrix ===\n";
    printAdjMatrix(g3.getAdjacencyMatrix(), g3.isWeighted());
    std::cout << "=== g3's adjacency list ===\n";
    printAdjList(g3.getAdjacencyList(), g3.isWeighted());

    // Try a nonexistent file.
    Graph g4{"nonexistent_file"};

    // Not reached, because an exception is thrown above.
    std::cerr << "End of " << __FUNCTION__ << "() reached.\n";
}

static void demo2()
{
    // Try a graph in which invalid vertex IDs are used.
    Graph g5{INPUT_FILE_DIR"/edge_list_bad1.txt"};

    // Not reached, because an exception is thrown above.
    std::cerr << "End of " << __FUNCTION__ << "() reached.\n";
}

static void demo3()
{
    // Try a graph in which there is a self loop.
    Graph g6{INPUT_FILE_DIR"/adj_list_bad1.txt"};

    // Not reached, because an exception is thrown above.
    std::cerr << "End of " << __FUNCTION__ << "() reached.\n";
}

static void demo4()
{
    // Demonstrate the remaining graph methods.

    Graph g7{INPUT_FILE_DIR"/edge_list3.txt"};
    assert(!g7.isWeighted());
    assert(g7.isDirected());
    assert(g7.getNumVertices() == 4);
    assert(g7.getNumEdges() == 5);
    std::cout << "One BFS ordering (many are possible), starting at 0:\n";
    std::vector<unsigned> ordering = g7.getBFSOrdering(0);
    for (unsigned v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "Another BFS ordering, starting at 2:\n";
    ordering = g7.getBFSOrdering(2);
    for (unsigned v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "One DFS ordering, starting at 3:\n";
    ordering = g7.getDFSOrdering(3);
    for (int v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "Transitive closure:\n";
    auto tc = g7.getTransitiveClosure();
    for (auto row : tc)
    {
        for (bool val : row)
            std::cout << val << ' ';
        std::cout << '\n';
    }

    Graph g8{INPUT_FILE_DIR"/edge_list4.txt"};
    assert(!g8.isWeighted());
    assert(g8.isDirected());
    assert(g8.getNumVertices() == 6);
    assert(g8.getNumEdges() == 6);
    std::cout << "One BFS ordering (many are possible), starting at 0:\n";
    ordering = g8.getBFSOrdering(0);
    for (unsigned v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "Another BFS ordering, starting at 2:\n";
    ordering = g8.getBFSOrdering(2);
    for (unsigned v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "One DFS ordering, starting at 3:\n";
    ordering = g8.getDFSOrdering(3);
    for (int v : ordering)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "Transitive closure:\n";
    tc = g8.getTransitiveClosure();
    for (auto row : tc)
    {
        for (bool val : row)
            std::cout << val << ' ';
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of command-line arguments.\n";
        return 1;
    }
    int caseNum = atoi(argv[1]);
    switch (caseNum)
    {
        case 1: demo1(); break;
        case 2: demo2(); break;
        case 3: demo3(); break;
        case 4: demo4(); break;
        default:
            std::cerr << "Invalid case number.\n";
            return 2;
    }
    return 0;
}
