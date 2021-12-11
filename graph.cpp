#include "graph.h"

/// LinkedListNode functions
Graph::LinkedListNode::LinkedListNode(string value) {
    this->value = value;
    this->next = nullptr;
}

Graph::LinkedListNode::LinkedListNode(string value, Graph::LinkedListNode *next) {
    this->value = value;
    this->next = next;
}



/// AdjacencyList functions
void Graph::AdjacencyList::insert_at_end(string to_insert) {
    if (head == NULL) {
        head = new Graph::LinkedListNode(to_insert);
        return;
    }

    LinkedListNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new LinkedListNode(to_insert);
}

Graph::AdjacencyList::AdjacencyList() {
    this->head = nullptr;
    this->num_edges = 0;
}

Graph::AdjacencyList::AdjacencyList(LinkedListNode *head) {
    this->head = head;
    this->num_edges = 0;
}

Graph::AdjacencyList::~AdjacencyList() {
    Graph::LinkedListNode* curr = head;
    while (curr != NULL) {
        curr = curr->next;
        delete head;
        head = curr;
    }
}

Graph::AdjacencyList::AdjacencyList(const AdjacencyList& other) {
    copy(other);
    
}

Graph::AdjacencyList& Graph::AdjacencyList::operator=(const Graph::AdjacencyList& other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

void Graph::AdjacencyList::copy(const Graph::AdjacencyList& other) {
    this->num_edges = other.num_edges;
    Graph::LinkedListNode* curr = other.head;
    while (curr != NULL) {
        this->insert_at_end(curr->value);
        curr = curr->next;
    }
}

bool Graph::AdjacencyList::remove_node(string to_remove) {
    if (head->value == to_remove) {
        // special case
        Graph::LinkedListNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Graph::LinkedListNode* prev = head;
    Graph::LinkedListNode* current = head;
    while (current != NULL) {
        current = current->next;
        // In case nothing matches the value, current will become NULL
        // which will cause a segfault on line 65, hence this if check
        if (current == NULL) {
            return false;
        }
        if (current->value == to_remove) {
            // remove this node
            prev->next = current->next;
            delete current;
            return true;
        }
        prev = prev->next;
    }
    return false;
}

// returns null if not found
Graph::LinkedListNode* Graph::AdjacencyList::find_prev(string to_find) { 
    Graph::LinkedListNode* current = head;
    // Here, the check was only checking if current is NULL
    // which was screwing up the inner if loop in case the string
    // was not found
    // Changed current to current->next to fix this on line 97(the line below)
    while (current->next != NULL) {
        if (current->next->value == to_find) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// returns null if not found
Graph::LinkedListNode* Graph::AdjacencyList::find(string to_find) {
    Graph::LinkedListNode* current = head;
    while (current != NULL) {
        if (current->value == to_find) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void Graph::AdjacencyList::remove(string to_remove) {
    if (head == NULL) {
        return;
    }

    if (head->value == to_remove) {
        Graph::LinkedListNode* temp = head;
        head = head->next;
        delete head;
    }

    Graph::LinkedListNode* remove = find_prev(to_remove);
    if (remove == NULL) {
        return;
    }
    Graph::LinkedListNode* temp = remove->next;
    remove->next = temp->next;
    delete temp;
}









/// Graph functions

Graph::Graph(int num_vertices): num_vertices(num_vertices) { }

Graph::Graph(std::vector<string> vertices, std::vector<std::pair<string, string>> edges) {
    // add vertexes
    num_vertices = vertices.size();
    
    // add edges
    for (std::pair<string, string> edge : edges) {
        add_edge(edge.first, edge.second);
    }
}

// Graph::Graph(const Graph& other) {
//    copy(other);
// }
// Graph& Graph::operator=(const Graph& other) {
//     if (this != &other) {
//         copy(other);
//     }
//     return *this;
// }

// void Graph::copy(const Graph& other) {
//     this->num_vertices = other.num_vertices;
//     for (const AdjacencyList& adjList : other.adjacency_list) {
//         AdjacencyList newList(adjList); // uses rule of 3 for adjlist
//         this->adjacency_list.push_back(newList);
//     }
// }
// Graph::~Graph() {
//     // do nothing, adjlist destructor should handle it
// }

void Graph::print_graph(std::ostream& out) {
    for (auto adj : adjacency_list) {
        out << adj.head->value << ":= ";
        for (auto header = adj.head->next; header != NULL; header = header->next) {
            if (header->next != NULL) {
                out << header->value << " --> ";
            } else {
                out << header->value << "; ";
            }
        }
    }
}


/*
iterate through adajency_list and look at heads

if source not head of any:
  make new adjlist
  place dest into adjlist
  insert into vec
if dest not head of any:
  make new adjlist
  place source into adjlist
  insert into vec
*/
void Graph::insert_into_adjlist(unsigned list_idx, string to_insert) {
    // adjacency_list[list_idx].push_back(to_insert);
    // add to end of linked list
    adjacency_list[list_idx].insert_at_end(to_insert);
    adjacency_list[list_idx].num_edges += 1;
}

unsigned Graph::find_adjlist_idx(string to_find) {
    for (unsigned i = 0; i < adjacency_list.size(); i++) {
        if (adjacency_list[i].head->value == to_find) {
            return i;
        }
    }

    return adjacency_list.size(); // default value
}

void Graph::add_edge(string source, string destination) {
    bool found_source = false;
    unsigned source_idx = find_adjlist_idx(source);
    unsigned dest_idx = find_adjlist_idx(destination);
    unsigned start_size = adjacency_list.size(); // because this can change as we go

    if (source_idx != start_size) {
        insert_into_adjlist(source_idx, destination);
    } else {
        // make new adj node
        AdjacencyList source_list = AdjacencyList();
        source_list.insert_at_end(source);
        source_list.insert_at_end(destination);
        source_list.num_edges += 1;

        adjacency_list.push_back(source_list);
    }
}

void Graph::remove_edge(string source, string destination) {
    // first ensure that both source and dest actually exist in the adj list
    unsigned start_idx = adjacency_list.size();
    unsigned source_idx = find_adjlist_idx(source);

    // Changed this because it doesn't matter whether the destination has it's own adj list or not
    // What matters is that the source has it's own adj list
    if (source_idx == start_idx) {
        std::cout << "ONE OR BOTH ITEMS DIDN'T EXIST IN remove_edge()" << std::endl;
        return;
    }

    // remove them from each other's lists
    // don't remove them from the adj list overall

    adjacency_list[source_idx].remove(destination);
}

bool Graph::isAdjacent(string source, string destination) {
    unsigned source_idx = find_adjlist_idx(source);

    if (source_idx == adjacency_list.size()) {
        std::cout << "Not adjacent; one or both didn't have a node in the graph!" << std::endl;
        return false;
    }

    // watch out for potential issues if adjacency_list[dest_idx].find(source) == NULL or != NULL)
    // it shouldn't be a problem though
    return (adjacency_list[source_idx].find(destination) != NULL);
}


vector<string> Graph::adjacent(string vertex) {
    vector<string> toReturn;
    // search for it; if found, add all to toReturn
    for (unsigned i = 0; i < adjacency_list.size(); i++) {
        if (adjacency_list[i].head->value == vertex) {
            // search in here
            LinkedListNode* current = adjacency_list[i].head;
            current = current->next;
            // now iterate through until null and add to toReturn
            while (current != nullptr) {
                toReturn.push_back(current->value);
                current = current->next;
            }
            break;
        }
    }
    // else, return empty vec
    return toReturn;
}

int Graph::get_num_vertices() {
    return num_vertices;
}


// functions for SSC

const std::vector<Graph::AdjacencyList>& Graph::getConnections() const {
    return adjacency_list;
}

Graph* Graph:: getTranspose() {
    Graph* toReturn = new Graph(num_vertices);

    // add all nodes to adj list in the same order; empty for now
    for (AdjacencyList& a : adjacency_list) {
        AdjacencyList toPush;
        toPush.insert_at_end(a.head->value);
        toReturn->adjacency_list.push_back(toPush);
    }

    for (unsigned i = 0; i < adjacency_list.size(); i++) {
        string currentString = adjacency_list[i].head->value; // this has to exist so if it segfaults that's a good thing
        // iterate through the current vertex adjlist, adding inverses
        AdjacencyList& currAdjList = adjacency_list.at(i);
        LinkedListNode* currNode = currAdjList.head;
        while (currNode != NULL) {
            // insert into desired adjlist
            getAdjListByNode(currNode->value).insert_at_end(currentString);
            currNode = currNode->next;
        }
    }

    return toReturn;
}

Graph::AdjacencyList& Graph::getAdjListByNode(string node) {
    for (AdjacencyList& a : adjacency_list) {
        if (a.head->value == node) {
            return a;
        }
    }

    // if not found, throw an exception; return is just to make this compile
    throw std::invalid_argument("Invalid node input!");
    return adjacency_list.at(0);
}