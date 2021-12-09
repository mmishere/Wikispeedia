#include "bfs.h"

using std::string;

BFS::BFS(Graph * graph) {
    graph_ = graph;
}

std::vector<string> BFS::findPath(string & start, string & end) {
    std::queue<string> queue;
    int num_vertices = graph_->get_num_vertices();
    std::unordered_map<string, int> distances;
    std::unordered_map<string, string> predecessors;
    string currentVtx;

    //starting point: distance is 0, no predecessor
    queue.push(start);
    distances[start] = 0;

    bool found = false;

    //search until queue empty
    while (!queue.empty()) {
        //break if found
        if (queue.front() == end) {
            found = true;
            break;
        }

        currentVtx = queue.front();
        queue.pop();

        //find incident edges, push into queue if not visited
        std::vector<string> adjacent = graph_->adjacent(currentVtx);
        for (auto & vtx : adjacent) {
            if (distances.find(vtx) != distances.end()) { //if not already found
                queue.push(vtx);
                predecessors[vtx] = currentVtx;
            }
        }
    }
    
    //return empty vector if not found
    if (!found) {
        return std::vector<string>();
    }

    //finalize output
    std::vector<string> output;
    output.push_back(end);
    currentVtx = end;
    while (predecessors.find(currentVtx) != predecessors.end()) {
        output.push_back(predecessors.at(currentVtx));
        currentVtx = predecessors.at(currentVtx);
    }
    return output;
}