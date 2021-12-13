#include "../cs225/catch/catch.hpp"

#include "../graph.h"

#include "../bfs.h"
#include "../ssc.h"

#include <sstream>

using std::stringstream;

using std::vector;
using std::string;
#include <iostream>
using std::cout; using std::endl;

TEST_CASE("Sanity Check", "[part=1]") {
    REQUIRE( 0 == 0 );
}

TEST_CASE("Checking the structs Adjacency List") {
    // Lambda function for printing the adjacency list
    auto printAdjList = [](Graph::AdjacencyList & adjList, std::ostream& out) {
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
        REQUIRE(ss.str() == "a:= b; b:= c --> e; c:= ; d:= b; e:= ; ");
    }

    SECTION("Testing remove_edge") {
        Graph g(vertices, edges);
        // Removing a normal edge
        g.remove_edge("b", "c");
        stringstream ss;
        g.print_graph(ss);
        REQUIRE(ss.str() == "a:= b; b:= e; c:= ; d:= b; e:= ; ");

        // Removing an edge which would cause an adjacency list to be empty
        g.remove_edge("a", "b");
        ss.str("");
        g.print_graph(ss);
        REQUIRE(ss.str() == "a:= ; b:= e; c:= ; d:= b; e:= ; ");

        // Removing an edge which does not exist. Nothing changes
        g.remove_edge("a", "c");
        ss.str("");
        g.print_graph(ss); 
        REQUIRE(ss.str() == "a:= ; b:= e; c:= ; d:= b; e:= ; ");
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


    SECTION("Testing getTranspose()") {
        std::vector<std::string> vertices = {"a", "b", "c", "d", "e"};
        std::vector<std::pair<std::string, std::string>> edges = {
            {"a", "b"},
            {"b", "c"},
            {"b", "e"},
            {"d", "b"},
            {"a", "d"},
            {"e", "d"}
        };

        Graph* g = new Graph(vertices, edges);
        Graph* gT = g->getTranspose();

        REQUIRE(gT->isAdjacent("b", "a"));
        REQUIRE(gT->isAdjacent("b", "d"));
        REQUIRE(gT->isAdjacent("d", "a"));
        REQUIRE(gT->isAdjacent("d", "e"));
        REQUIRE(gT->isAdjacent("c", "b"));
        REQUIRE(gT->isAdjacent("e", "b"));

        // no original edges allowed
        REQUIRE(!(gT->isAdjacent("a", "b")));
        REQUIRE(!(gT->isAdjacent("b", "c")));
        REQUIRE(!(gT->isAdjacent("b", "e")));
        REQUIRE(!(gT->isAdjacent("d", "b")));
        REQUIRE(!(gT->isAdjacent("a", "d")));
        REQUIRE(!(gT->isAdjacent("e", "d")));

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

TEST_CASE("Betweenness centrality") {

    SECTION("Basic graph") {
        // a -> b -> c
        std::vector<std::string> vertices = {"a", "b", "c"};
        std::vector<int> centralities = {3, 4, 3};
        std::vector<std::pair<std::string, std::string>> edges = {
            {"a", "b"},
            {"b", "c"},
        };

        Graph* g = new Graph(vertices, edges);
        BFS bfs(g);

        std::map<std::string, int> output = bfs.centralities();
        for (unsigned i = 0; i < vertices.size(); i++) {
            REQUIRE(output.at(vertices[i]) == centralities[i]);
        }

        delete g;
    }
}

TEST_CASE("Strongly Connected Components") {
    SECTION("One node") {
        vector<string> vertices = {"a"};
        vector<std::pair<string, string>> edges = {};

        Graph* g = new Graph(vertices, edges);
        StronglyConnected ssc(g);

        const set<string>* strongConnections = ssc.getConnected("a");
        REQUIRE(strongConnections->size() == 1);

        const set<string>* invalid = ssc.getConnected("");
        REQUIRE(invalid == NULL);

        delete g;
    }

    SECTION ("Two nodes, connected") {
        vector<string> vertices = {"a", "bb"};
        vector<std::pair<string, string>> edges = {
            {"a", "bb"},
            {"bb", "a"},
        };
        Graph* g = new Graph(vertices, edges);

        StronglyConnected ssc(g);
        const set<string>* strongConnections = ssc.getConnected("a");
        REQUIRE(strongConnections->size() == 2);

        REQUIRE(ssc.isConnected("a", "bb"));
        REQUIRE(ssc.isConnected("bb", "a"));

        const set<string>* invalid = ssc.getConnected("");
        REQUIRE(invalid == NULL);

        delete g;
    }

    SECTION("Two nodes, unconnected") {
        vector<string> vertices = {"a", "bb"};
        vector<std::pair<string, string>> edges = {
            {"a", "bb"},
        };
        Graph* g = new Graph(vertices, edges);

        StronglyConnected ssc(g);
        const set<string>* strongConnectionsA = ssc.getConnected("a");
        REQUIRE (strongConnectionsA->size() == 1);

        const set<string>* strongConnectionsBB = ssc.getConnected("bb");
        REQUIRE (strongConnectionsBB->size() == 1);

        REQUIRE(!(ssc.isConnected("a", "bb")));
        REQUIRE(!(ssc.isConnected("bb", "a")));

        const set<string>* invalid = ssc.getConnected("");
        REQUIRE(invalid == NULL);

        delete g;
    }

    SECTION("Basic graph w 1 cycle") {
        vector<string> vertices = {"a", "b", "c", "d", "e", "f", "g", "h"};
        // ab, bd, da cycle
        // bc, ce, ec
        // fe, fg
        vector<std::pair<string, string>> edges = {
            {"a", "b"},
            {"b", "d"},
            {"d", "a"},
            {"b", "c"},
            {"c", "e"},
            {"e", "c"},
            {"f", "e"},
            {"f", "g"},
        };
        Graph* g = new Graph(vertices, edges);

        StronglyConnected ssc(g);
        const set<string>* strongConnectionsA = ssc.getConnected("a");
        REQUIRE (strongConnectionsA->size() == 3);

        const set<string>* strongConnectionsB = ssc.getConnected("b");
        REQUIRE (strongConnectionsB->size() == 3);

        const set<string>* strongConnectionsC = ssc.getConnected("c");
        REQUIRE (strongConnectionsC->size() == 2);

        const set<string>* strongConnectionsD = ssc.getConnected("d");
        REQUIRE (strongConnectionsD->size() == 3);

        const set<string>* strongConnectionsE = ssc.getConnected("e");
        REQUIRE (strongConnectionsE->size() == 2);

        const set<string>* strongConnectionsFB = ssc.getConnected("f");
        REQUIRE (strongConnectionsFB->size() == 1);

        const set<string>* strongConnectionsG = ssc.getConnected("g");
        REQUIRE (strongConnectionsG->size() == 1);

        const set<string>* strongConnectionsH = ssc.getConnected("h");
        REQUIRE (strongConnectionsH->size() == 1);


        // cycle
        REQUIRE(ssc.isConnected("a", "b"));
        REQUIRE(ssc.isConnected("b", "d"));
        REQUIRE(ssc.isConnected("d", "a"));

        // require opposite connections as well; they're in the same ssc
        REQUIRE(ssc.isConnected("b", "a"));
        REQUIRE(ssc.isConnected("d", "b"));
        REQUIRE(ssc.isConnected("a", "d"));

        // ce pair
        REQUIRE(ssc.isConnected("c", "e"));
        REQUIRE(ssc.isConnected("e", "c"));


        // nodes with only themselves in the ssc
        REQUIRE(ssc.isConnected("f", "f"));
        REQUIRE(ssc.isConnected("g", "g"));
        REQUIRE(ssc.isConnected("h", "h"));

        // now ensure that nothing is connected that shouldn't be
        REQUIRE(!(ssc.isConnected("a", "c")));
        REQUIRE(!(ssc.isConnected("a", "e")));
        REQUIRE(!(ssc.isConnected("a", "f")));
        REQUIRE(!(ssc.isConnected("a", "g")));
        REQUIRE(!(ssc.isConnected("a", "h")));
        REQUIRE(!(ssc.isConnected("b", "c")));
        REQUIRE(!(ssc.isConnected("b", "e")));
        REQUIRE(!(ssc.isConnected("b", "f")));
        REQUIRE(!(ssc.isConnected("b", "g")));
        REQUIRE(!(ssc.isConnected("b", "h")));
        REQUIRE(!(ssc.isConnected("d", "c")));
        REQUIRE(!(ssc.isConnected("d", "e")));
        REQUIRE(!(ssc.isConnected("d", "f")));
        REQUIRE(!(ssc.isConnected("d", "g")));
        REQUIRE(!(ssc.isConnected("d", "h")));

        REQUIRE(!(ssc.isConnected("c", "a")));
        REQUIRE(!(ssc.isConnected("c", "b")));
        REQUIRE(!(ssc.isConnected("c", "d")));
        REQUIRE(!(ssc.isConnected("c", "f")));
        REQUIRE(!(ssc.isConnected("c", "g")));
        REQUIRE(!(ssc.isConnected("c", "h")));
        REQUIRE(!(ssc.isConnected("e", "a")));
        REQUIRE(!(ssc.isConnected("e", "b")));
        REQUIRE(!(ssc.isConnected("e", "d")));
        REQUIRE(!(ssc.isConnected("e", "f")));
        REQUIRE(!(ssc.isConnected("e", "g")));
        REQUIRE(!(ssc.isConnected("e", "h")));

        REQUIRE(!(ssc.isConnected("f", "a")));
        REQUIRE(!(ssc.isConnected("f", "b")));
        REQUIRE(!(ssc.isConnected("f", "d")));
        REQUIRE(!(ssc.isConnected("f", "c")));
        REQUIRE(!(ssc.isConnected("f", "e")));
        REQUIRE(!(ssc.isConnected("f", "g")));
        REQUIRE(!(ssc.isConnected("f", "h")));

        REQUIRE(!(ssc.isConnected("g", "a")));
        REQUIRE(!(ssc.isConnected("g", "b")));
        REQUIRE(!(ssc.isConnected("g", "d")));
        REQUIRE(!(ssc.isConnected("g", "c")));
        REQUIRE(!(ssc.isConnected("g", "e")));
        REQUIRE(!(ssc.isConnected("g", "f")));
        REQUIRE(!(ssc.isConnected("g", "h")));

        REQUIRE(!(ssc.isConnected("h", "a")));
        REQUIRE(!(ssc.isConnected("h", "b")));
        REQUIRE(!(ssc.isConnected("h", "d")));
        REQUIRE(!(ssc.isConnected("h", "c")));
        REQUIRE(!(ssc.isConnected("h", "e")));
        REQUIRE(!(ssc.isConnected("h", "f")));
        REQUIRE(!(ssc.isConnected("h", "g")));


        // and as always an invalid check
        const set<string>* invalid = ssc.getConnected("ksldjfsdf");
        REQUIRE(invalid == NULL);

        delete g;
    }
}