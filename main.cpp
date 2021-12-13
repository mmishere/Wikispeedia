#include <iostream>
#include <fstream>
#include <algorithm>
// #include <string>
#include "util/util.h"
#include "bfs.h"
#include "ssc.h"

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    // 2 (+1) args: nodes_file, edges_file: display graph info (connectedness, highest centrality points)
    // 4 (+1) args: nodes_file, edges_file, output_file, BC: print centrality data to output_file
    // 4 (+1) args: nodes_file, edges_file, output_file, SSC: print SSC data to output_file
    // 4 (+1) args: nodes_file, edges_file, start_node, end_node: display path between nodes if any
    
    // check bounds
    if (argc != 3 && argc != 5) {
        cout << "Wrong number of arguments: received " << argc - 1 << ", expected 2 or 4." << endl;
        cout << "Usage: ./wikispeedia [nodes data file] [edges data file]" << endl;
        cout << "Usage: ./wikispeedia [nodes data file] [edges data file] [betweenness centrality output file] BC" << endl;
        cout << "Usage: ./wikispeedia [nodes data file] [edges data file] [strong connections output file] SSC" << endl;
        cout << "Usage: ./wikispeedia [nodes data file] [edges data file] [BFS starting point] [BFS ending point]" << endl;
        return 0;
    }

    cout << "Using nodes file: " << argv[1] << endl;
    string nodes_path = argv[1];
    cout << "Using edges file: " << argv[2] << endl;
    string edges_path = argv[2];
    // cout << endl;

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

        

    cout << "Parsing graph data..." << endl;
    Graph * g = utils::parse_to_graph(nodes_path, edges_path);


    if (argc == 3) { // display graph info
        // cout << "(display graph info)" << endl;

        BFS bfs(g);
        cout << "Calculating betweenness centralities..." << endl;
        std::vector<std::pair<std::string, int>> centralities = bfs.centralitiesSorted();

        // std::string::size_type sz;
        cout << "Nodes with highest betweenness centrality:" << endl;
        // for (unsigned i = 0; i < std::min((unsigned long) 10, centralities.size()); i++) {
        //     cout << centralities[i].first << "\t" << centralities[i].second << endl;;
        //     cout << centralities.size() << endl;
        //     // int titleIdx = std::stoi(centralities[i].first, &sz);
        //     // cout << "\t" << titles[titleIdx] << ": " << centralities[i].second << endl;
        // }

        int shown = 0;
        for (auto & centrality : centralities) {
            cout << "\t" << centrality.second << ":\t" << centrality.first << endl;;
        }

        cout << endl;
        StronglyConnected sc(g);
        if (sc.entireGraphSSC()) { //is connected
            cout << "The graph IS strongly connected: every page is reachable from every other page." << endl;
        } else { //is not
            cout << "The graph IS NOT strongly connected: some pages are unreachable from other pages." << endl;
        }

        delete g;
        return 0;
    }

    if (argc == 5 && std::string(argv[4]) == "BC") { // print centrality data to file
        BFS bfs(g);
        cout << "Calculating betweenness centralities..." << endl;

        std::vector<std::pair<std::string, int>> centralities = bfs.centralitiesSorted();
        utils::save_centralities_to_file(argv[3], centralities);

        cout << "Printed betweenness centrality data to: " << argv[3] << endl;
        
        delete g;
        return 0;

    } else if (argc == 5 && std::string(argv[4]) == "SSC") { // print SSC data to file
        cout << "Calculating strong connections..." << endl;
        StronglyConnected ssc(g);

        cout << "Outputting strong connections to " << argv[3] << endl;
        ssc.save_strong_connections_to_file(argv[3]);
        cout << "Complete." << endl;

        if (ssc.entireGraphSSC()) {
            cout << "The graph IS strongly connected: every page is reachable from every other page." << endl;
        } else { //is not
            cout << "The graph IS NOT strongly connected: some pages are unreachable from other pages." << endl;
        }

        delete g;
        return 0;

        
    } else if (argc == 5) { // find path between nodes
        // CHECK FOR PATH SEARCH
        {
            // cout << "args: " << endl;
            // for (int i = 0; i < 5; i++) {
            //     cout << "  " << std::string(argv[i]) << endl;
            // }
            // cout << endl;

            string start = argv[3];
            string end = argv[4];
            if (std::find(titles.begin(), titles.end(), start) == titles.end()) {
                cout << "Title not found: " << start << endl;
                return 0;
            }
            if (std::find(titles.begin(), titles.end(), end) == titles.end()) {
                cout << "Title not found: " << end << endl;
                return 0;
            }
        }

        // find path between nodes
            // cout << "(find path between: " << argv[3] << ", " << argv[4] << ")" << endl;

            string start = argv[3];
            string end = argv[4];

            // auto itStart = std::find(titles.begin(), titles.end(), start);
            // auto itEnd = std::find(titles.begin(), titles.end(), end);
            // if (itStart == titles.end()) {
            //     cout << "Starting point not found: " << start << endl;
            //     return 0;
            // }
            // if (itEnd == titles.end()) {
            //     cout << "Ending point not found: " << end << endl;
            //     return 0;
            // }

            // int startIdx = itStart - titles.begin();
            // int endIdx = itEnd - titles.begin();
            // string startIdxS = std::to_string(startIdx);
            // string endIdxS = std::to_string(endIdx);

            BFS bfs(g);
            cout << "Searching for path..." << endl;
            std::vector<string> path = bfs.findPath(start, end);
            if (path.empty()) {
                cout << "No path found." << endl;
                return 0;
            }

            // std::string::size_type sz;

            cout << "Path found:" << endl;
            // for (string & s : path) {
            //     int titleIdx = std::stoi(s, &sz);
            //     cout << "\t" << titles[titleIdx] << endl;
            // }

            for (string & s : path) {
                cout << "\t" << s << endl;
            }
            delete g;
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