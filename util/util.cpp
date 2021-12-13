#include "util.h"
#include <string>

Graph* utils::parse_to_graph(string vertex_file_path, string edge_file_path) {
    // set split character
    string split_character = " ";

    // get files
    std::fstream vertex_file;
    std::fstream edge_file;
    
    // parse vertexes
    std::vector<string> vertices;
    vertex_file.open(vertex_file_path, std::ios::in);
    if (vertex_file.is_open()) {
        string line;
        while (getline(vertex_file, line)) {
            vertices.push_back(line);
        }
        vertex_file.close();
    }
    
    // parse edges
    std::vector<std::pair<string, string>> edges;
    edge_file.open(edge_file_path, std::ios::in);
    if (edge_file.is_open()) {
        string line;
        std::string::size_type sz;
        while (getline(edge_file, line)) {
            // find the edge split 
            size_t split_pos = line.find(split_character);
            
            //add both vertexes to the edge list
            std::pair<string, string> new_edge = std::pair<string, string>(line.substr(0, split_pos), line.substr(split_pos + split_character.length()));

            int start = std::stoi(new_edge.first, &sz);
            int end = std::stoi(new_edge.second, &sz);

            std::pair<string, string> title_pair(vertices[start], vertices[end]);

            // edges.push_back(new_edge);
            edges.push_back(title_pair);
        }
        edge_file.close();
    }
    
    // construct graph
    return new Graph(vertices, edges);
}

void utils::save_centralities_to_file(string save_file_path, std::vector<std::pair<std::string, int>> centralities) {
    std::fstream file;
    file.open(save_file_path, std::ios::out);

    // if file was not created, print error and exit
    if (!file) {
        std::cout << "File not created." << std::endl;
        return;
    }

    // add map of centralities to file
    for (auto entry : centralities) {
        file << entry.first << "\t" << entry.second << std::endl;
    }

    file.close();
}