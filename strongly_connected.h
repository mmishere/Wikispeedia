#pragma once

#include "graph.h"

#include <set>
#include <string>
#include <stack>
#include <iostream>
using std::set;
using std::string;
using std::stack;
using std::cout; using std::endl;

class StronglyConnected {
    public:
        StronglyConnected(); // initialize with NULL graph_

        // initialize with given graph; pointer to avoid copies, which will be slow
        // PASSED IN GRAPH* HAS TO BE ON THE HEAP OR OTHERWISE NOT DESTRUCTED UNTIL THE END OF main()
        StronglyConnected(Graph* g); 

        // for two points in the graph, are they connected
        bool isConnected(string first, string second);

        // helper for constructor, sets up stronglyConnectedComponents_
        // uses kosaraju's algorithm: https://www.geeksforgeeks.org/strongly-connected-components/
        void kosaraju();

        bool entireGraphSSC();


    private:
        Graph* graph_;
        // each inner set contains all vertices that have a strong connection to each other (i.e. canTravel(a, b) && canTravel(b, a))
        set<set<string>> stronglyConnectedComponents_; // all components; set up in dfsHelper()
        bool graphIsStronglyConnected_; // is the entire graph strongly connected? built in constructor
        
        // it is VERY VERY IMPORTANT that these go by reference; they need to alter the values!!!
        void DFS(string& point, stack<string>& stack, set<string>& visited);
        void transposeDFS(Graph* transposed, string& point, set<string>& visited, set<string>& SSC);
        

};

// pseudocode
/*
kosaraju:
  visited = empty set<string>
  stack = empty stack

  for each point:
    if not visited:
      DFS(point, stack, visited)

  empty visited
  transposed = transpose(graph)

  for each point in stack:
    if not visited:
      create set // to hold the strongly connected component
      transposeDFS(transposed, point, visited, set)
      add set to stronglyConnectedComponents_
    pop stack // because it will be visited by this point
  



DFS(point, stack, visited):
  mark point as visited
  for each child:
    if child not visited:
      DFS(child, stack, visited)
  add point to stack // because we're done processing children



transposeDFS(transposed, point, visited, set):
  mark point as visited
  add point to set
  for each child of point in transposed:
    if child not visited:
      transposeDFS(transposed, child, visited, set)
  

*/
