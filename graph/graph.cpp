#include "graph.h"

Graph::Graph(int num_vertices): num_vertices(num_vertices) { }

Graph::Graph(std::string file1, std::string file2) {
    std::vector<std::pair<int, int>> edges = parserHelp(file1, file2);

    for (auto edge : edges) {
        addEdge(edge.first, edge.second);
    }
}

void Graph::Graph print_graph() {
    for (auto adj : adjacency_list) {
        std::cout << adj.head->value << ":= ";
        for (auto list : adj.head) {
            std::cout << list->value << " --> ";
        }
        std::cout << std::endl;
    }
}