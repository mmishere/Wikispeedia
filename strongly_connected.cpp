#include "strongly_connected.h"

// initialize with NULL graph_
StronglyConnected::StronglyConnected() {
    graph_ = NULL;
}

// initialize with given graph; pointer to avoid copies, which will be slow
StronglyConnected::StronglyConnected(Graph* g) {
    graph_ = g;
    kosaraju();

    // now pick some arbitrary point and then see if it has the full set
    for (const set<string>& set : stronglyConnectedComponents_) {
        graphIsStronglyConnected_ = (set.size() == g->get_num_vertices());
        break; // only doing this loop to access a set element, since we don't have any particular vertices available here
    }
}

// for two points in the graph, are they connected
bool StronglyConnected::isConnected(string first, string second) {
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

bool StronglyConnected::entireGraphSSC() {
    return graphIsStronglyConnected_;
}

void StronglyConnected::kosaraju() {
    set<string> visited;
    stack<string> stack;

    auto graphConnections = graph_->getAdjacencyList(); 
    for (Graph::AdjacencyList adjList : graphConnections) {
        // use the head
        string point = adjList.head->value;
        if (visited.count(point) == 0) { // if not visited:
            DFS(point, stack, visited, adjList); // current adjList
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

    // done!
}

void StronglyConnected::DFS(string& point, stack<string>& stack, set<string>& visited) {
    visited.insert(point);

    Graph::LinkedListNode* curr = graph_->getAdjListByNode(point).head->next; // BE CAREFUL OF SEGFAULTS however they shouldn't happen here so if they do then something went horribly wrong
    while (curr != NULL) {
        string& child = curr->value;
        if (visited.count(child) == 0) {
            DFS(child, stack, visited);
        }
    }
    stack.push(point);
}

void transposeDFS(Graph* transposed, string& point, set<string>& visited, set<string>& SSC) {
    visited.insert(point);
    SSC.insert(point);

    Graph::LinkedListNode* curr = transposed->getAdjListByNode(point).head->next; // same thing with segfaults here
    while (curr != NULL) {
        string& child = curr->value;
        if (visited.count(child) == 0) {
            transposeDFS(transposed, child, visited, SSC);
        }
    }
}