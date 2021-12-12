#include <iostream>
#include <fstream>
#include "util/util.h"
#include "bfs.h"

using std::string;

int main() {
    // set the file paths here:
    string vertex_list_path = "data_sample/nodes.txt";
    string edge_list_path = "data_sample/edges.txt";
    string centrality_save_path = "results/centralities.txt";

    // construct the graph
    Graph* g = utils::parse_to_graph(vertex_list_path, edge_list_path);
    BFS bfs = BFS(g);

    std::cout << "Num Vertices: " << g->get_num_vertices() << std::endl;

    utils::save_centralities_to_file(centrality_save_path, bfs.centralitiesSorted());
}