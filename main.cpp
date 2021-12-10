#include <iostream>
#include <fstream>
#include "util/util.h"

using std::string;

int main() {
    // set the data file paths here:
    string vertex_list_path = "data_sample/nodes.txt";
    string edge_list_path = "data_sample/edges.txt";

    // construct the graph
    Graph graph = utils::parse_to_graph(vertex_list_path, edge_list_path);

    std::cout << "Num Vertices: " << graph.get_num_vertices() << std::endl;
}