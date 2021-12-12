#include <iostream>
#include <fstream>
#include "util/util.h"
#include "bfs.h"

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    // 2 args: nodes_file, edges_file: display graph info (connectedness, highest centrality points)
    // 3 args: nodes_file, edges_file, output_file: print centrality data to output_file
    // 4 args: nodes_file, edges_file, start_node, end_node: display path between nodes if any
    
    if (argc < 3) {
        cout << "Too few arguments: received " << argc - 1 << ", expected at least 2." << endl;
        return 0;
    }

    if (argc == 3) { // display graph info
        cout << "(display graph info)" << endl;
        return 0;
    }

    if (argc == 4) { // print centrality data to file
        cout << "(print centrality data to: " << argv[3] << ")" << endl;
        return 0;
    }

    if (argc == 5) { // find path between nodes
        cout << "(find path between: " << argv[3] << ", " << argv[4] << ")" << endl;
        return 0;
    }

    cout << "Too many arguments: received " << argc - 1 << ", expected at most 4." << endl;
    return 0;
    
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