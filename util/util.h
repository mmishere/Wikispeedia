#pragma once

#include <iostream> 
#include <fstream>
#include <string>
#include "../graph/graph.h"

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
    Graph parse_to_graph(string vertex_file_path, string edge_file_path);

} // namespace utils