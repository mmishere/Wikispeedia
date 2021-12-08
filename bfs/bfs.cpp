#include "bfs.h"

using std::string;

BFS::BFS(Graph * graph) {
    graph_ = graph;
}

std::vector<string *> BFS::findPath(string * start, string * end) {
    std::queue<string *> queue;
    int num_vertices = graph_->get_num_vertices();
    std::map<string *, int> distances;
    std::map<string *, int> predecessors;
    string * currentVtx;

    //starting point
    queue.push(start);
    distances[start] = 0;

    //search until queue empty
    while (!queue.empty()) {
        currentVtx = queue.front();
        queue.pop();

        // find incident edges, push into queue if not visited
        // Graph::AdjacencyList adjacent = graph_->adjacent(*currentVtx);
        

    }
    
    
    std::vector<string *> output;
    
    return output;
}