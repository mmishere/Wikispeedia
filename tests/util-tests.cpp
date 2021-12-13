#include "../cs225/catch/catch.hpp"
#include <string>
#include <fstream>
#include <iostream>
//#include "../graph.h"
#include "../bfs.h"
#include "../util/util.h"

using namespace utils;

TEST_CASE("Parsed Graph Has Correct num_vertices", "[parser]") {
    // set up test files
    std::string testing_vertex_list_path = "data_sample/nodes.txt";
    std::string testing_edge_list_path = "data_sample/edges.txt";

    Graph* g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);
    
    // count number of lines in vertex list
    int vertex_count = 0;
    std::fstream vertex_file;
    vertex_file.open(testing_vertex_list_path, std::ios::in);
    if (vertex_file.is_open()) {
        std::string line;
        while (getline(vertex_file, line)) {
            vertex_count++;
        }
        vertex_file.close();
    } else {
        std::cout << "File could not be opened! Please check your file path." << std::endl;
        return;
    }
    
    REQUIRE( g->get_num_vertices() != 0 );
    REQUIRE( g->get_num_vertices() == vertex_count );

    delete g;
}

/* NOTE: This test will need to be changed if the sample data files are edited */
TEST_CASE("Parsed Graph Has Correct Edges Manual", "[parser]") {
    // set up test files
    std::string testing_vertex_list_path = "data_sample/nodes.txt";
    std::string testing_edge_list_path = "data_sample/edges.txt";

    Graph* g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);

    REQUIRE( g->isAdjacent("first_really_long_article_name", "second_really_long_article_name") );
    REQUIRE( g->isAdjacent("second_really_long_article_name", "third_really_long_article_name") );
    REQUIRE( g->isAdjacent("third_really_long_article_name", "first_really_long_article_name") );
    REQUIRE( g->isAdjacent("third_really_long_article_name", "second_really_long_article_name") );

    delete g;
}

/*
TEST_CASE("Parsed Graph Has Correct Edges Automatic", "[parser]") {
    // set up test files
    std::string testing_vertex_list_path = "data_sample/nodes.txt";
    std::string testing_edge_list_path = "data_sample/edges.txt";

    // set split character
    string split_character = " ";

    Graph g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);
    
    // check all edges
    int edge_count = 0;
    std::fstream edge_file;
    edge_file.open(testing_edge_list_path, std::ios::in);
    if (edge_file.is_open()) {
        std::string line;
        while (getline(edge_file, line)) {
            edge_count++;
            size_t split_pos = line.find(split_character);
            REQUIRE( g.isAdjacent(line.substr(0, split_pos), line.substr(split_pos + split_character.length())) );
        }
        edge_file.close();
    } else {
        std::cout << "File could not be opened! Please check your file path." << std::endl;
        return;
    }

    REQUIRE( edge_count != 0 );
}
*/

// Note: this test case relies on the Graph and BFS constructors and centralitySorted()
TEST_CASE("Centralities Save to File Correctly", "[centrality_saver]") {
    std::string centrality_save_path = "sample_centralities";
    std::string split_character = " ";

    // set up graph values and expected results
    std::vector<std::string> vertices = {"a", "b", "c"};
    std::vector<std::pair<std::string, int>> ordered_centralities = {
        {"b", 4},
        {"a", 3},
        {"c", 3},
    };
    std::vector<std::pair<std::string, std::string>> edges = {
        {"a", "b"},
        {"b", "c"},
    };

    // set up graph and save the centralities
    Graph* g = new Graph(vertices, edges);
    BFS bfs = BFS(g);
    utils::save_centralities_to_file(centrality_save_path, bfs.centralitiesSorted());

    // check if generated file has correct values in correct order
    std::fstream centrality_file;
    centrality_file.open(centrality_save_path, std::ios::in);

    if (centrality_file.is_open()) {
        std::string line;
        int i = 0;

        while (getline(centrality_file, line)) {
            size_t split_pos = line.find(split_character);
            std::pair<std::string, int> p = std::pair<std::string, int>(line.substr(0, split_pos),
                                            stoi(line.substr(split_pos + split_character.length())));
            REQUIRE( p == ordered_centralities[i]);
            i++;
        }

        centrality_file.close();
    } else {
        std::cout << "File could not be opened! Please check your file path." << std::endl;
        return;
    }

    delete g;
}

TEST_CASE("Parsed Centralities Save to File Correctly", "[centrality_saver]") {
    std::string centrality_save_path = "sample_centralities_2";
    std::string testing_vertex_list_path = "data_sample/nodes.txt";
    std::string testing_edge_list_path = "data_sample/edges.txt";
    std::string split_character = " ";

    std::vector<std::pair<std::string, int>> ordered_centralities = {
        {"second_really_long_article_name", 6},
        {"third_really_long_article_name", 6},
        {"first_really_long_article_name", 5},
    };

    // set up graph and save the centralities
    Graph* g = utils::parse_to_graph(testing_vertex_list_path, testing_edge_list_path);
    BFS bfs = BFS(g);
    utils::save_centralities_to_file(centrality_save_path, bfs.centralitiesSorted());

    // check if generated file has correct values in correct order
    std::fstream centrality_file;
    centrality_file.open(centrality_save_path, std::ios::in);

    if (centrality_file.is_open()) {
        std::string line;
        int i = 0;

        while (getline(centrality_file, line)) {
            size_t split_pos = line.find(split_character);
            std::pair<std::string, int> p = std::pair<std::string, int>(line.substr(0, split_pos),
                                            stoi(line.substr(split_pos + split_character.length())));
            REQUIRE( p == ordered_centralities[i] );
            i++;
        }

        centrality_file.close();
    } else {
        std::cout << "File could not be opened! Please check your file path." << std::endl;
        return;
    }

    delete g;
}