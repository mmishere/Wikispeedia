#include "strongly_connected.h"

// initialize with NULL graph_
StronglyConnected::StronglyConnected() {
    graph_ = NULL;
}

// initialize with given graph; pointer to avoid copies, which will be slow
StronglyConnected::StronglyConnected(Graph* g) {
    graph_ = g;
    dfsHelper();
}

// for two points in the graph, are they connected
bool StronglyConnected::isConnected(string first, string second) {
    // iterate through stronglyConnectedComponents_ until we find one that contains first or second
    // then return whether it contains the other one
    for (set<string> s : stronglyConnectedComponents_) {
        if (s.count(first) > 0) {
            return s.count(second) > 0;
        }

        if (s.count(second) > 0) {
            return s.count(first) > 0;
        }
    }

    return false; // both weren't in the graph, so it wasn't a valid search
}




// set up like in g4g, so this isn't currently really doing anything useful
void StronglyConnected::fillOrder(int num, vector<bool> visited, stack<int>& stack) {
    visited.at(num) = true;

    // iterate through all vertices adjacent to the num vertex and fillOrder each of them
    Graph::AdjacencyList adjList = graph_->getListByIdx(num);
    Graph::LinkedListNode* current = adjList.head;
    while (current != NULL) {
        int idx = graph_->getIdxByNode(current->value);
        if (!visited.at(idx)) {
            fillOrder(idx, visited, stack);
        }
        current = current->next;
    }
    // all reachable vertices have been found: push num to stack
    stack.push(num);
}

void StronglyConnected::dfsHelper() {
    // uses graph_
    if (graph_ == NULL) {
        graphIsStronglyConnected_ = false;
        return;
    }

    // set up graphIsStronglyConnected_
    graphIsStronglyConnected_ = false; // TEMPORARY

    // iterate through all pieces of the graph
    // if there are multiple connected components, then graphIsStronglyConnected_ = false
    // however the normal check may take care of that


    // since these are ordered (albiet arbitrarily), we can use the algorithm from geeksforgeeks
    stack<int> stack;
    int numVertices = graph_->get_num_vertices();

    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; i++) {
        if (visited.at(i) == false) {
            fillOrder(i, visited, stack);
        }
    }

    Graph* transposed = graph_->getTranspose();

    // make all false for second dfs round
    for (int i = 0; i < numVertices; i++) {
        visited.at(i) = false;
    }

    // process vertices in the order defined by t he stack
    while (!stack.empty()) {
        int curr = stack.top();
        stack.pop();
        if (!visited.at(curr)) {
            DFSUtil(transposed, curr, visited);
            cout << endl;
        }
    }
}

void StronglyConnected::DFSUtil(Graph* g, int num, vector<bool> visited) {
    visited.at(num) = true;

    Graph::LinkedListNode* curr = g->getListByIdx(num).head;
    cout << curr->value << endl;

    while (curr != NULL) {
        int idx = g->getIdxByNode(curr->value);
        if (!visited[idx]) {
            DFSUtil(g, idx, visited);
        }
    }
}



// Graph* graph_;
// set<set<string>> stronglyConnectedComponents_;
// bool graphIsStronglyConnected_;
