#include "../catch/catch.hpp"

#include "../graph.h"

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