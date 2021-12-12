#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "util/util.h"
#include "bfs.h"
#include "ssc.h"

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    // 2 args: nodes_file, edges_file: display graph info (connectedness, highest centrality points)
    // 3 args: nodes_file, edges_file, output_file: print centrality data to output_file
    // 4 args: nodes_file, edges_file, start_node, end_node: display path between nodes if any
    
    // check bounds
    if (argc < 3) {
        cout << "Too few arguments: received " << argc - 1 << ", expected at least 2." << endl;
        return 0;
    }
    if (argc > 5) {
        cout << "Too many arguments: received " << argc - 1 << ", expected at most 4." << endl;
        return 0;
    }

    cout << "Using nodes file: " << argv[1] << endl;
    string nodes_path = argv[1];
    cout << "Using edges file: " << argv[2] << endl;
    string edges_path = argv[2];
    cout << endl;

    std::vector<string> titles;
    std::fstream file;
    file.open(nodes_path.c_str(), std::ios::in);
    if (file) {
        string str;
        while (std::getline(file, str)) {
            titles.push_back(str);
        }
        file.close();
    }

    Graph * g = utils::parse_to_graph(nodes_path, edges_path);

    if (argc == 3) { // display graph info
        // cout << "(display graph info)" << endl;

        BFS bfs(g);
        std::vector<std::pair<std::string, int>> centralities = bfs.centralitiesSorted();

        std::string::size_type sz;
        cout << "Nodes with highest betweenness centrality:" << endl;
        for (unsigned i = 0; i < std::min((unsigned long) 10, centralities.size()); i++) {
            int titleIdx = std::stoi(centralities[i].first, &sz);
            cout << "\t" << titles[titleIdx] << ": " << centralities[i].second << endl;
        }

        cout << endl;
        StronglyConnected sc(g);
        if (sc.entireGraphSSC()) { //is connected
            cout << "The graph IS strongly connected: every page is reachable from every other page." << endl;
        } else { //is not
            cout << "The graph IS NOT strongly connected: some pages are unreachable from other pages." << endl;
        }


        return 0;
    }

    if (argc == 4) { // print centrality data to file
        // cout << "(print centrality data to: " << argv[3] << ")" << endl;

        BFS bfs(g);
        std::vector<std::pair<std::string, int>> centralities = bfs.centralitiesSorted();

        std::string::size_type sz;

        std::ofstream outputFile;
        outputFile.open(argv[3]);

        for (unsigned i = 0; i < centralities.size(); i++) {
            int titleIdx = std::stoi(centralities[i].first, &sz);
            outputFile << centralities[i].second << "\t" << titles[titleIdx] << endl;
        }
        outputFile.close();

        cout << "Printed betweenness centrality data to: " << argv[3] << endl;

        return 0;
    }

    if (argc == 5) { // find path between nodes
        // cout << "(find path between: " << argv[3] << ", " << argv[4] << ")" << endl;

        string start = argv[3];
        string end = argv[4];

        auto itStart = std::find(titles.begin(), titles.end(), start);
        auto itEnd = std::find(titles.begin(), titles.end(), end);
        if (itStart == titles.end()) {
            cout << "Starting point not found: " << start << endl;
            return 0;
        }
        if (itEnd == titles.end()) {
            cout << "Ending point not found: " << end << endl;
            return 0;
        }

        int startIdx = itStart - titles.begin();
        int endIdx = itEnd - titles.begin();
        string startIdxS = std::to_string(startIdx);
        string endIdxS = std::to_string(endIdx);

        BFS bfs(g);
        std::vector<string> path = bfs.findPath(startIdxS, endIdxS);
        if (path.empty()) {
            cout << "No path found." << endl;
            return 0;
        }

        std::string::size_type sz;

        cout << "Path found:" << endl;
        for (string & s : path) {
            int titleIdx = std::stoi(s, &sz);
            cout << "\t" << titles[titleIdx] << endl;
        }

        return 0;
    }


    // // set the file paths here:
    // string vertex_list_path = "data_sample/nodes.txt";
    // string edge_list_path = "data_sample/edges.txt";
    // string centrality_save_path = "results/centralities.txt";

    // // construct the graph
    // Graph* g = utils::parse_to_graph(vertex_list_path, edge_list_path);
    // BFS bfs = BFS(g);

    // std::cout << "Num Vertices: " << g->get_num_vertices() << std::endl;

    // utils::save_centralities_to_file(centrality_save_path, bfs.centralitiesSorted());
}