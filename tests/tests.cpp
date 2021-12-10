#include "../cs225/catch/catch.hpp"

#include "../graph.h"

#include "../bfs.h"

#include <sstream>

using std::stringstream;

TEST_CASE("Sanity Check", "[part=1]") {
    REQUIRE( 0 == 0 );
}

TEST_CASE("Checking the structs Adjacency List") {
    // Lambda function for printing the adjacency list
    auto printAdjList = [](Graph::AdjacencyList adjList, std::ostream& out) {
        for (auto list = adjList.head; list != nullptr; list = list->next) {
            out << list->value << " ";
        }
    };

    SECTION("Testing insertAtEnd") {
        // Initializing the adjacency list works
        Graph::AdjacencyList adjList;
        adjList.insert_at_end("a");
        stringstream ss;
        printAdjList(adjList, ss);
        REQUIRE(ss.str() == "a ");
        REQUIRE(adjList.head->value == "a");

        ss.str("");

        // Inserting multiple values works
        adjList.insert_at_end("b");
        REQUIRE(adjList.head->next->value == "b");
        REQUIRE(adjList.head->value == "a");
        printAdjList(adjList, ss);
        REQUIRE(ss.str() == "a b ");
    }

    SECTION("Testing removeNode") {
        // Removing a node which exists works
        Graph::AdjacencyList adjList;
        adjList.insert_at_end("a");
        adjList.insert_at_end("b");
        adjList.insert_at_end("c");
        bool check = adjList.remove_node("b");
        stringstream ss;
        printAdjList(adjList, ss);
        REQUIRE(ss.str() == "a c ");
        REQUIRE(check == true);
        // Removing a node which does not exist works
        ss.str("");
        bool check2 = adjList.remove_node("d");
        printAdjList(adjList, ss);
        REQUIRE(ss.str() == "a c ");
        REQUIRE(check2 == false);
    }

    SECTION("Testing findPrev") {
        // Finding a node which exists works
        Graph::AdjacencyList adjList;
        adjList.insert_at_end("a");
        adjList.insert_at_end("b");
        adjList.insert_at_end("c");
        auto prev = adjList.find_prev("b");
        REQUIRE(prev->value == "a");
        // Finding a node which does not exist works
        prev = adjList.find_prev("d");
        REQUIRE(prev == NULL);
    }

    SECTION("Testing findNode") {
        // Finding a node which exists works
        Graph::AdjacencyList adjList;
        adjList.insert_at_end("a");
        adjList.insert_at_end("b");
        adjList.insert_at_end("c");
        auto node = adjList.find("b");
        REQUIRE(node->value == "b");

        // Finding a node which does not exist works
        node = adjList.find("d");
        REQUIRE(node == NULL);
    }
}

TEST_CASE("Now Checking the Graph Class") {
    // Here is the graph we will be using
    // a -> b -> c
    //      ^ \\
    //      |  \\
    //      d    e
    // The best I can do, but b points to both c and e
    // The vector we'll use for constructing the graph
    // (Currently, it's assumed to be )
    std::vector<std::string> vertices = {"a", "b", "c", "d", "e"};
    std::vector<std::pair<std::string, std::string>> edges = {
        {"a", "b"},
        {"b", "c"},
        {"b", "e"},
        {"d", "b"}
    };

    SECTION("Testing the constructor (Also checks add_edges simultaneously)") {
        Graph g(vertices, edges);
        
        stringstream ss;
        g.print_graph(ss);
        REQUIRE(ss.str() == "a:= b; b:= c --> e; d:= b; ");
    }

    SECTION("Testing remove_edge") {
        Graph g(vertices, edges);
        // Removing a normal edge
        g.remove_edge("b", "c");
        stringstream ss;
        g.print_graph(ss);
        REQUIRE(ss.str() == "a:= b; b:= e; d:= b; ");

        // Removing an edge which would cause an adjacency list to be empty
        g.remove_edge("a", "b");
        ss.str("");
        g.print_graph(ss);
        REQUIRE(ss.str() == "a:= b:= e; d:= b; ");

        // Removing an edge which does not exist. Nothing changes
        g.remove_edge("a", "c");
        ss.str("");
        g.print_graph(ss);
        REQUIRE(ss.str() == "a:= b:= e; d:= b; ");
    }

    SECTION("Testing isAdjacent") {
        Graph g(vertices, edges);
        REQUIRE(g.isAdjacent("a", "b") == true);
        REQUIRE(g.isAdjacent("b", "a") == false);
        REQUIRE(g.isAdjacent("b", "c") == true);
        REQUIRE(g.isAdjacent("b", "e") == true);
        REQUIRE(g.isAdjacent("d", "b") == true);
        REQUIRE(g.isAdjacent("d", "c") == false);
        REQUIRE(g.isAdjacent("d", "e") == false);
    }

    SECTION("Testing adjacent") {
        Graph g(vertices, edges);
        auto adj = g.adjacent("b");
        stringstream ss;
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            ss << *it << " ";
        }
        REQUIRE(ss.str() == "c e ");

        adj = g.adjacent("d");
        ss.str("");
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            ss << *it << " ";
        }
        REQUIRE(ss.str() == "b ");

        adj = g.adjacent("a");
        ss.str("");
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            ss << *it << " ";
        }
        REQUIRE(ss.str() == "b ");

        adj = g.adjacent("c");
        ss.str("");
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            ss << *it << " ";
        }
        REQUIRE(ss.str() == "");
    }
}

TEST_CASE("Now Checking the BFS Class") {
    // Here is the graph we will be using
    // a -> b -> c
    //  \\  ^ \\
    //   \\ |  \\
    //      d <--e
    // The best I can do, but b points to both c and e and a points to both b and d
    // Graph is made the have a cycle
    std::vector<std::string> vertices = {"a", "b", "c", "d", "e"};
    std::vector<std::pair<std::string, std::string>> edges = {
        {"a", "b"},
        {"b", "c"},
        {"b", "e"},
        {"d", "b"},
        {"a", "d"},
        {"e", "d"}
    };

    SECTION("Testing findPath") {
        Graph* g = new Graph(vertices, edges);
        BFS bfs(g);

        // Edge case: start node is not in the graph
        auto path = bfs.findPath("f", "c");
        REQUIRE(path.size() == 0);

        // Edge case: end node is not in the graph
        path = bfs.findPath("a", "f");
        REQUIRE(path.size() == 0);

        // Edge case: start and end node are the same
        path = bfs.findPath("a", "a");
        REQUIRE(path.size() == 1);
        REQUIRE(path[0] == "a");

        // Normal case: start and end node are different, straight line
        // Also ensures that the shortest path is found
        path = bfs.findPath("a", "c");
        stringstream ss;
        for (auto it = path.begin(); it != path.end(); ++it) {
            ss << *it << " ";
        }
        REQUIRE(ss.str() == "a b c ");

        // Normal case: start and end node are different, with a cycle
        path = bfs.findPath("a", "e");  
        ss.str("");
        for (auto it = path.begin(); it != path.end(); ++it) {
            ss << *it << " ";
        }
        REQUIRE(ss.str() == "a b e ");

        delete g;
    }
}