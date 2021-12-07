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

void Graph::print_graph() {
    for (auto adj : adjacency_list) {
        std::cout << adj.head->value << ":= ";
        // for (auto list : adj.head) {
        //     std::cout << list->value << " --> ";
        // }
        std::cout << std::endl;
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
        source_list.insert_at_end(destination);
        source_list.num_edges += 1;

        adjacency_list.push_back(source_list);
    }

    if (dest_idx != start_size) {
        insert_into_adjlist(source_idx, destination);
    } else {
        // make new adj node
        AdjacencyList dest_list = AdjacencyList();
        dest_list.insert_at_end(source);
        dest_list.num_edges += 1;

        adjacency_list.push_back(dest_list);
    }
}

void Graph::remove_edge(string source, string destination) {
    // first ensure that both source and dest actually exist in the adj list
    unsigned start_idx = adjacency_list.size();
    unsigned source_idx = find_adjlist_idx(source);
    unsigned dest_idx = find_adjlist_idx(destination);

    if (source_idx == start_idx || dest_idx == start_idx) {
        std::cout << "ONE OR BOTH ITEMS DIDN'T EXIST IN remove_edge()" << std::endl;
        return;
    }

    // remove them from each other's lists
    // don't remove them from the adj list overall

    adjacency_list[source_idx].remove(destination);
    adjacency_list[dest_idx].remove(source);
}

bool Graph::isAdjacent(string source, string destination) {
    unsigned source_idx = find_adjlist_idx(source);
    unsigned dest_idx = find_adjlist_idx(destination);

    if (source_idx == adjacency_list.size() || dest_idx == adjacency_list.size()) {
        std::cout << "Not adjacent; one or both didn't have a node in the graph!" << std::endl;
        return false;
    }

    // watch out for potential issues if adjacency_list[dest_idx].find(source) == NULL or != NULL)
    // it shouldn't be a problem though
    return (adjacency_list[source_idx].find(destination) != NULL);
}


Graph::AdjacencyList Graph::adjacent(string vertex) {
    // search for it; if found, return
    for (unsigned i = 0; i < adjacency_list.size(); i++) {
        if (adjacency_list[i].head->value == vertex) {
            return adjacency_list[i];
        }
    }
    // else, return empty adj list
    return AdjacencyList();
}

int Graph::get_num_vertices() {
    return num_vertices;
}