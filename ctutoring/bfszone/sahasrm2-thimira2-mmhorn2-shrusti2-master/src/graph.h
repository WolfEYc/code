#ifndef GRAPH_H
#define GRAPH_H

#include <iostream> 
#include <map>
#include <vector>
#include <string>

#include "Matrix.h"

namespace fin {

class Graph {
  public:
    // default constructor. Creates an empty graph
    Graph();

    // frees all Node Pointers in hashmap
    ~Graph();

    // Streture to represent a node in the graph
    struct Node {
        int id;                       // person id. Taken directly from the input file
        std::vector<int> connections; // list of people id's of other people in graph
    };

    // Add a node with a certain id.
    void createNode(int id);

    // add a connection between two people
    // This creates a connection from p1->p2 and p2->p1
    void linkPeople(int p1_id, int p2_id);

    // Get the Node of a person if you know their id
    Node getPerson(int id);
    std::vector<Node> getNodes();
    int getSize();

    // Create an adjacency matrix from data within graph
    Matrix generate_adjacency_matrix();

  private:
    //number of nodes in graph
    int size_;  

    //map of Nodes that make the graph. Speeds up
    //node lookup times
    std::map<int, int> ids_;

    // sortest list of ids for adjaceny matrix
    std::vector<Node> nodes_; 
};

// Create a graph from a file of data
// Disregards the time information
Graph read_from_file(const char *fname);

}


#endif

