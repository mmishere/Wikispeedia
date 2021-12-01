#include "bfs.h"

BFS::BFS(Graph * graph) {
    graph_ = graph;
}

std::vector<int> BFS::findPath(int start, int end) {
    std::queue<int> queue;
    std::vector<int> distance(graph_->num_vertices);
    std::vector<int> predecessor(graph_->num_vertices);
    int currentVtx;

    for (int i = 0; i < graph_->num_vertices; i++) {
        distance[i] = -1;
        predecessor[i] = -1;
    }

    //starting point
    queue.push(start);
    distance[start] = 0;

    //search until queue empty
    while (!queue.empty()) {
        currentVtx = queue.front();
        queue.pop();



    }
    
    
    std::vector<int> output;
    
    return output;
}