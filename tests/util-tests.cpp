// #include "../cs225/catch/catch.hpp"
// #include <string>
// #include <fstream>
// #include <iostream>
// #include "../graph.h"
// #include "../util/util.h"

// using namespace utils;

// TEST_CASE("Parsed Graph Has Correct num_vertices", "[parser]") {
//     // set up test files
//     std::string testing_vertex_list_path = "data_sample/nodes.txt";
//     std::string testing_edge_list_path = "data_sample/edges.txt";

//     Graph g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);
    
//     // count number of lines in vertex list
//     int vertex_count = 0;
//     std::fstream vertex_file;
//     vertex_file.open(testing_vertex_list_path, std::ios::in);
//     if (vertex_file.is_open()) {
//         std::string line;
//         while (getline(vertex_file, line)) {
//             vertex_count++;
//         }
//         vertex_file.close();
//     } else {
//         std::cout << "File could not be opened! Please check your file path." << std::endl;
//         return;
//     }
    
//     REQUIRE( g.get_num_vertices() != 0 );
//     REQUIRE( g.get_num_vertices() == vertex_count );
// }

// /* NOTE: This test will need to be changed if the sample data files are edited */
// TEST_CASE("Parsed Graph Has Correct Edges Manual", "[parser]") {
//     // set up test files
//     std::string testing_vertex_list_path = "data_sample/nodes.txt";
//     std::string testing_edge_list_path = "data_sample/edges.txt";

//     Graph g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);

//     REQUIRE( g.isAdjacent("0", "1") );
//     REQUIRE( g.isAdjacent("1", "2") );
//     REQUIRE( g.isAdjacent("2", "0") );
//     REQUIRE( g.isAdjacent("2", "1") );
// }

// /*
// TEST_CASE("Parsed Graph Has Correct Edges Automatic", "[parser]") {
//     // set up test files
//     std::string testing_vertex_list_path = "data_sample/nodes.txt";
//     std::string testing_edge_list_path = "data_sample/edges.txt";

//     // set split character
//     string split_character = " ";

//     Graph g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);
    
//     // check all edges
//     int edge_count = 0;
//     std::fstream edge_file;
//     edge_file.open(testing_edge_list_path, std::ios::in);
//     if (edge_file.is_open()) {
//         std::string line;
//         while (getline(edge_file, line)) {
//             edge_count++;
//             size_t split_pos = line.find(split_character);
//             REQUIRE( g.isAdjacent(line.substr(0, split_pos), line.substr(split_pos + split_character.length())) );
//         }
//         edge_file.close();
//     } else {
//         std::cout << "File could not be opened! Please check your file path." << std::endl;
//         return;
//     }

//     REQUIRE( edge_count != 0 );
// }
// */