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
        void dfsHelper();


    private:
        Graph* graph_;
        // each inner set contains all vertices that have a strong connection to each other (i.e. canTravel(a, b) && canTravel(b, a))
        set<set<string>> stronglyConnectedComponents_; // all components; set up in dfsHelper()
        bool graphIsStronglyConnected_; // is the entire graph strongly connected? built in constructor

        void fillOrder(int num, vector<bool> visited, stack<int>& stack);
        void DFSUtil(Graph* graph, int num, vector<bool> visited);

};