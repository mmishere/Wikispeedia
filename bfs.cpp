#include "bfs.h"
#include <iostream>

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
    // int num_vertices = graph_->get_num_vertices();
    std::set<string> visited;
    std::unordered_map<string, string> predecessors;
    string currentVtx;

    //starting point: distance is 0, no predecessor
    queue.push(start);
    visited.insert(start);
    //distances[start] = 0;

    bool found = false;

    //search until queue empty
    while (!queue.empty()) {
        //break if found
        // if (queue.front() == end) {
        //     found = true;
        //     break;
        // }

        currentVtx = queue.front();
        queue.pop();

        std::vector<string> adjacent = graph_->adjacent(currentVtx);
        for (auto & vtx : adjacent) {
            

            if (visited.find(vtx) == visited.end()) { //if not already found
                queue.push(vtx);
                predecessors[vtx] = currentVtx;
                visited.insert(vtx);

                if (vtx == end) {
                    found = true;
                    break;
                }
            }
        }
        if (found == true) {
            break;
        }
        // visited.insert(currentVtx);
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

    //get vector of all node strings
    std::set<string> nodes;

    auto graphConnections = graph_->getConnections(); 
    for (AdjacencyList& adjList : graphConnections) { //for each linked list in graphConnections
        auto current = adjList.head;
        while (current != NULL) { //walk through list
            if (nodes.find(current->value) == nodes.end()) { //if value not in nodes, add it
                nodes.insert(current->value);
                // std::cout << "found node " << current->value << std::endl;
            }

            current = current->next;
        }
        
    }

    for (const string & v1 : nodes) {
        // std::cout << "searching from " << v1 << std::endl;
        for (const string & v2 : nodes) {
            std::vector<string> path = findPath(v1, v2); //BFS between nodes
            if (path.empty()) { //do nothing if no path exists
                continue;
            }

            for (string & s : path) {
                if (output.find(s) == output.end()) { //if key not already in output map
                    output[s] = 1;
                } else { //key is already in map, increment value
                    output[s]++;
                }
            }
        }
    }

    return output;

    // loop through every vertex to calculate centrality
    // for (int v = 0; v < graph_->get_num_vertices(); v++) {
    //     double total_centrality = 0;
    //     std::vector<std::vector<std::string>> paths;

    //     // run bfs on every node pair and store the path
    //     for (int s = 0; s < graph_->get_num_vertices(); s++) {
    //         for (int t = 0; t < graph_->get_num_vertices(); t++) {
    //             paths.push_back(findPath(std::to_string(s), std::to_string(t)));
    //         }
    //     }

    //     // count times v appears
    //     int count = 0;
    //     for (size_t p = 0; p < paths.size(); p++) {
    //         for (size_t n = 0; n < paths[p].size(); n++) {
    //             if (paths[p][n] == std::to_string(v)) {
    //                 count++;
    //                 break;
    //             }
    //         }
    //     }

    //     // add to final result
    //     output.insert(std::pair<std::string, double>(std::to_string(v), total_centrality));
    // // }

    // return output;
}

std::vector<std::pair<std::string, int>> BFS::centralitiesSorted() {
    std::map<std::string, int> centralities_map = centralities();
    std::vector<std::pair<std::string, int>> sorted_centralities;

    // loop through map and add to vector
    for (auto entry : centralities_map) {
        sorted_centralities.push_back(entry);
    }

    // sort the vector
    sort(sorted_centralities.begin(), sorted_centralities.end(), is_centrality_greater);

    return sorted_centralities;
}

bool is_centrality_greater(const std::pair<std::string, int>& node1, const std::pair<std::string, int>& node2) {
    return node1.second > node2.second;
}