#include "ssc.h"

// initialize with NULL graph_
StronglyConnected::StronglyConnected() {
    graph_ = NULL;
}

// initialize with given graph; pointer to avoid copies, which will be slow
StronglyConnected::StronglyConnected(Graph* g) {
    graph_ = g;
    kosaraju();
}

// for two points in the graph, are they connected
bool StronglyConnected::isConnected(string first, string second) {
    if (first == second) {
        return true;
    }
    // iterate through stronglyConnectedComponents_ until we find one that contains first or second
    // then return whether it contains the other one
    for (const set<string>& s : stronglyConnectedComponents_) {
        
        if (s.count(first) > 0) {
            return s.count(second) > 0;
        }

        if (s.count(second) > 0) {
            return s.count(first) > 0;
        }
    }

    return false; // both weren't in the graph, so it wasn't a valid search
}

const set<string>* StronglyConnected::getConnected(string input) {
    for (const set<string>& s : stronglyConnectedComponents_) {
        if (s.count(input) > 0) {
            return &s;
        }
    }
    
    return NULL;
}

bool StronglyConnected::entireGraphSSC() {
    // size 0 == no nodes, size 1 == full graph
    return (stronglyConnectedComponents_.size() <= 1);
}


void StronglyConnected::save_strong_connections_to_file(string save_file_path) {
    std::fstream file;
    file.open(save_file_path, std::ios::out);

    if (!file) {
        std::cout << "File not created." << std::endl;
        return;
    }


    for (const set<string>& set : stronglyConnectedComponents_) {
        for (const string& s : set) {
            file << s << "\n";
        }
        file << "\n";
    }

    file.close();
}



void StronglyConnected::kosaraju() {
    set<string> visited;
    stack<string> stack;

    auto graphConnections = graph_->getConnections();

    for (AdjacencyList adjList : graphConnections) {
        // use the head
        string point = adjList.head->value;
        if (visited.count(point) == 0) { // if not visited:
            DFS(point, stack, visited); // current adjList
        }
    }

    visited.clear();
    Graph* transposed = graph_->getTranspose();

    while (!stack.empty()) {
        string point = stack.top();
        if (visited.count(point) == 0) {
            set<string> SSC;
            transposeDFS(transposed, point, visited, SSC);
            stronglyConnectedComponents_.insert(SSC);
        }
        stack.pop();
    }

    delete transposed; // to avoid memory leaks, since it's on the heap
    // done!
}

void StronglyConnected::DFS(string& point, stack<string>& stack, set<string>& visited) {
    visited.insert(point);

    vector<string> adj = graph_->adjacent(point);
    // it's okay if adj size is 0; that just means that it's its own connected component

    for (string& child : adj) {
        if (visited.count(child) == 0) {
            DFS(child, stack, visited);
        }
    }
    stack.push(point);
}

void StronglyConnected::transposeDFS(Graph* transposed, string& point, set<string>& visited, set<string>& SSC) {
    visited.insert(point);
    SSC.insert(point);

    vector<string> adj = transposed->adjacent(point);
    for (string& child : adj) {
        if (visited.count(child) == 0) {
            transposeDFS(transposed, child, visited, SSC);
        }
    }
}void save_strong_connections_to_file(string save_file_path);