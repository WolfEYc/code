#include "../cs225/catch/catch.hpp"

#include "../src/graph.h"
#include "../src/Matrix.h"
#include <iostream>

TEST_CASE("Graph::createNode") {
  fin::Graph g;
  g.createNode(1);
  g.createNode(10);
  g.createNode(1001001);

  REQUIRE(g.getPerson(1).id != 0);
  REQUIRE(g.getPerson(10).id != 0);
  REQUIRE(g.getPerson(1001001).id != 0); 

  REQUIRE(g.getPerson(2).id == 0);
  REQUIRE(g.getPerson(-50).id == 0);
}

TEST_CASE("Graph::linkPeople") {
  fin::Graph g;
  g.createNode(1);
  g.createNode(2);

  //link existing people
  g.linkPeople(1, 2);
  REQUIRE(g.getPerson(1).connections[0] == 1);
  REQUIRE(g.getPerson(2).connections[0] == 0);

  //link nonexisting people 
  g.linkPeople(3, 4);
  REQUIRE(g.getPerson(3).connections[0] == 3);
  REQUIRE(g.getPerson(4).connections[0] == 2);
}

TEST_CASE("Graph::generate_adjacency_matrix") {
    fin::Graph g;
    g.createNode(1);
    g.createNode(2);
    g.linkPeople(1, 2);
    double ans[2][2] = { {0, 1},{1, 0} };
    fin::Matrix actual = fin::Matrix(ans);
    REQUIRE(g.generate_adjacency_matrix() == actual); 

}


