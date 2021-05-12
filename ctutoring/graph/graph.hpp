#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <tuple>
#include <vector>

/**
 * Class that represents a graph that can be weighted and/or directed if
 * desired.
 * Does not support multi-edges or self loops.
 * Once constructed, the graph cannot be modified.
 *
 * Each vertex has a unique ID in the range [0, n - 1], where n is the number
 * of vertices. For example, if there are 5 vertices, then the IDs
 * are 0, 1, 2, 3, and 4.
 * This ID system is used in the graph file (if the first Graph
 * constructor is used) as well as in some of the methods.
 */
class Graph
{
public:

    /******************************************************
     * Constructors.
     *
     * Each of the three constructors assumes that there is at least one vertex
     * in the graph.
     *
     * Each of the three constructors throws an exception if any of the
     * following occur:
     * 1\. Use of nonexistent vertices, e.g. use of a vertex with an ID of 5
     *     when there are only 3 vertices.
     * 2\. Encountered a self loop, i.e. an edge from a vertex to itself.
     * 3\. Encountered a multi-edge. Note that in a directed graph, an edge
     *     from A to B and an edge from B to A would not together constitute
     *     a multi-edge, but two edges each from A to B would.
     * 4\. Encountered an edge with weight 0 in a weighted graph. (This only
     *     applies to the last two of the three constructors.)
     *****************************************************/


    /**
     * This constructor reads information from the file named by @filename.
     * See prog_hw3.pdf for more information.
     * An std::logic_error exception is thrown if the file could not be opened.
     * This constructor assumes that the file is always properly formatted,
     * although it still checks for the four conditions mentioned above that
     * could result in the throwing of an exception.
     */
    Graph(const std::string& filename);
    /**
     * This constructor constructs the graph from the edge list given.
     * This constructor assumes the graph is unweighted.
     */
    Graph(unsigned numVertices,
          const std::vector<std::pair<unsigned, unsigned>>& edges,
          bool isDirected);
    /**
     * This constructor is the same as the one immediately above this one,
     * except that this constructor assumes that the graph is weighted.
     */
    Graph(unsigned numVertices,
          const std::vector<std::tuple<unsigned, unsigned, int>>& edges,
          bool isDirected);

    /******************************************************
     * Delete copy constructor and copy assignment.
     * You don't need to do anything about these lines in graph.cpp.
     * We will talk about copy constructors and copy assignments later.
     *****************************************************/
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    /******************************************************
     * Accessor methods.
     *****************************************************/
    bool isWeighted() const;
    bool isDirected() const;
    unsigned getNumVertices() const;
    unsigned getNumEdges() const;
    std::vector<std::vector<int>> getMainVec();
    /**
     * Returns 2D vector of ints representing an adjacency matrix.
     * If graph is unweighted, then each int is either 1 or 0;
     * otherwise, each int is the weight.
     * 0 indicates a nonexistent edge.
     */
    std::vector<std::vector<int>> getAdjacencyMatrix() const;
    /**
     * Returns adjacency list represented by a 2D vector in which the vector at
     * index i contains the neighbor entries of vertex i.
     * For each neighbor entry, the unsigned gives the neighbor's ID,
     * and the int gives the weight of the edge to that neighbor.
     * If the graph is unweighted, then each int is 1.
     */
    std::vector<std::vector<std::pair<unsigned, int>>> getAdjacencyList() const;

    /******************************************************
     * Graph traversals.
     *
     * Returns a BFS/DFS ordering of all vertices reachable from the start node.
     * Throws exception if @start is invalid, i.e. too high.
     *****************************************************/
    std::vector<unsigned> getBFSOrdering(unsigned start) const;
    std::vector<unsigned> getDFSOrdering(unsigned start) const;

    /******************************************************
     * Other graph algorithms.
     *****************************************************/
    /**
     * Returns an adjacency matrix representing the transitive closure of
     * this graph.
     * See: https://en.wikipedia.org/wiki/Transitive_closure#In_graph_theory
     *
     * Although it contradicts the definition in the above link ("one or more
     * hops"), we will say that a node can reach itself, i.e. the main diagonal
     * of the matrix should be all true.
     */
    std::vector<std::vector<bool>> getTransitiveClosure() const;

    void inval_graph();

private:
    // TODO: Your private methods and member variables go here.
    unsigned num_of_vert;
    unsigned num_edges;
    std::vector<std::vector<int>> main_vec; 
    bool is_directed;
    bool is_weighted;
    int graph_type; //1 == adjmatrix, 2 ==  AdjList, 3 == List edges
    
    void invalid_error();
    //void invalid_check(std::vector<std::vector<int>> &main_vec1);
    int count_edges(std::vector<std::vector<int>> &main_vec1,int graph_type1);

};

#endif  // GRAPH_HPP
