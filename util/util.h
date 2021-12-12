#pragma once

#include <iostream> 
#include <fstream>
#include <string>
#include <map>
#include "../graph.h"

using std::string;

// clang++ util/util.cpp -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c

namespace utils {
    /**
    * Parses the passed vertex and edge files and converts them into a Graph datastructure.
    *
    * @param vertex_file_path The path to the vertex list file.
    * @param edge_file_path The path to the edge list file.
    * @returns A graph with the listed vertices and edges.
    */
    Graph* parse_to_graph(string vertex_file_path, string edge_file_path);

    /**
    * Saves the betweenness centrality calculations for each node to a human-readable file.
    * If the passed file path does not exist, it will be automatically created.
    *
    * @param save_file_path The file in which to save the data.
    * @param centralities The map of nodes and their centralities.
    */
    void save_centralities_to_file(string save_file_path, std::map<std::string, int> centralities);

} // namespace utils