#include <iostream>
#include <vector>
#include "graph.h"
#include "Matrix.h"
#include "bfs.cpp"

int main() {
  fin::Graph g = fin::read_from_file("./sg_infectious_contact_list/listcontacts_2009_04_28.txt");
  std::cout << "There are " << g.getSize() << " unique people in the dataset" << std::endl;  


  // generate adjacency matrix
  std::cout << "This is the adjacency matrix:" << std::endl;
  fin::Matrix adj = g.generate_adjacency_matrix();
  std::cout << adj << std::endl;

  // print out all person ids
  std::cout << "Here are their ids: " << std::endl;
  std::vector<fin::Graph::Node> nodes = g.getNodes();
  for(auto i : nodes) std::cout << i.id << " ";
  std::cout << std::endl;

  std::cout << "BFS ordering of the Matrix\n";
  printvector(bfs(adj));
  std::cout << std::endl; 

  return 0;
}
