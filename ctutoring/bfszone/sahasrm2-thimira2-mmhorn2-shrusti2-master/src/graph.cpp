#include "graph.h"
#include <fstream>
#include <sstream>

namespace fin {


  Graph::Graph() {
    size_ = 0;
  }

  Graph::~Graph() {
  }

  void Graph::createNode(int id) {
    Node n;
    n.id = id;
    
    ids_.insert(std::make_pair(id, size_));
    nodes_.push_back(n);
    size_ += 1;
  }

  void Graph::linkPeople(int p1_id, int p2_id) {
    if(ids_.find(p1_id) == ids_.end())
      createNode(p1_id);
    if(ids_.find(p2_id) == ids_.end())
      createNode(p2_id);
    
    nodes_[ids_[p1_id]].connections.push_back(ids_[p2_id]);
    nodes_[ids_[p2_id]].connections.push_back(ids_[p1_id]);
  }

  Graph::Node Graph::getPerson(int id) {
    if(ids_.find(id) == ids_.end())
      return Node();
    return nodes_[ids_[id]];
  }

  std::vector<Graph::Node> Graph::getNodes() { return nodes_; }
  int Graph::getSize() { return size_; }

  Matrix Graph::generate_adjacency_matrix() {
    Matrix adj(size_, size_);

    for(int i = 0; i < size_; i++) {
      std::vector<int> conns = nodes_[i].connections;
      for(auto con : conns) {
        adj[i][con] = 1;
      }
    }

    return adj;
  }

  Graph read_from_file(const char* fname) {
    Graph g;
    std::ifstream infile(fname);

    std::string line;
    while( getline(infile, line) ) {
      std::stringstream ss(line);

      int t, person1, person2;
      ss >> t >> person1 >> person2;
      g.linkPeople(person1,person2);
    }
    infile.close();
    return g;
  }
}

