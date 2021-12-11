#include "bfs.h"

using std::string;

BFS::BFS(Graph * graph) {
    graph_ = graph;
}

// Making them const so that compiler stops throwing errors
std::vector<string> BFS::findPath(const string & start, const string & end) {
    //edge case, empty strings
    if (start.empty() || end.empty()) {
        return std::vector<string>(); //empty vector
    }
    
    std::vector<string> output;
    
    //edge case, same start and end
    if (start == end) {
        output.push_back(start);
        return output;
    }
    
    std::queue<string> queue;
    int num_vertices = graph_->get_num_vertices();
    std::set<string> visited;
    std::unordered_map<string, string> predecessors;
    string currentVtx;

    //starting point: distance is 0, no predecessor
    queue.push(start);
    //distances[start] = 0;

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

        std::vector<string> adjacent = graph_->adjacent(currentVtx);
        for (auto & vtx : adjacent) {
            if (visited.find(vtx) == visited.end()) { //if not already found
                queue.push(vtx);
                predecessors[vtx] = currentVtx;
            }
        }
        visited.insert(currentVtx);
    }
    
    //return empty vector if not found
    if (!found) {
        return std::vector<string>();
    }

    //finalize output
    output.push_back(end);
    currentVtx = end;
    while (predecessors.find(currentVtx) != predecessors.end()) {
        output.push_back(predecessors.at(currentVtx));
        currentVtx = predecessors.at(currentVtx);
    }
    std::reverse(output.begin(), output.end());
    return output;
}

std::map<std::string, int> BFS::centralities() {
    std::map<std::string, int> output;

    // loop through every vertex to calculate centrality
    /*
    for (int v = 0; v < graph_->get_num_vertices(); v++) {
        double total_centrality = 0;
        std::vector<std::string> paths;

        // run bfs on every node pair

        // store path

        // count times v appears

        // divide by total num paths

        // add to final result
    }
    */

    return output;
}