#include "graph.h"

Graph::Graph(int num_vertices): num_vertices(num_vertices) { }

Graph::Graph(std::vector<string> vertices, std::vector<std::pair<string, string>> edges) {
    // add vertexes
    num_vertices = vertices.size();
    
    // add edges
    for (std::pair<string, string> edge : edges) {
        add_edge(edge.first, edge.second);
    }
}

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