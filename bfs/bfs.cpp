#include "bfs.h"

using std::string;

BFS::BFS(Graph * graph) {
    graph_ = graph;
}

std::vector<string> BFS::findPath(string & start, string & end) {
    std::queue<string> queue;
    int num_vertices = graph_->get_num_vertices();
    std::map<string, int> distances;
    std::map<string, int> predecessors;
    string currentVtx;

    //starting point
    queue.push(start);
    distances[start] = 0;

    bool found = false;

    //search until queue empty
    while (!queue.empty()) {
        //break if found
        if (queue.front() == end) {
            break;
        }

        currentVtx = queue.front();
        queue.pop();

        //find incident edges, push into queue if not visited
        std::vector<string> adjacent = graph_->adjacent(currentVtx);
        for (auto & vtx : adjacent) {
            if (distances.find(vtx) != distances.end()) {
                queue.push(vtx);
            }
        }
    }
    
    
    std::vector<string> output;
    
    return output;
}