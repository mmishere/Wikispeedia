#include "graph.h"

Graph::Graph(int num_vertices): num_vertices(num_vertices) { }

Graph::Graph(std::string file1, std::string file2) {
    std::vector<std::pair<int, int>> edges = parserHelp(file1, file2);

    for (auto edge : edges) {
        addEdge(edge.first, edge.second);
    }
}

void Graph::Graph print_graph() {
    for (auto adj : adjacency_list) {
        std::cout << adj.head->value << ":= ";
        for (auto list : adj.head) {
            std::cout << list->value << " --> ";
        }
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
    adjacency_list[list_idx].head->insert_at_end(to_insert);
    adjacency_list[list_idx].num_edges += 1;
}

unsigned find_adjlist_idx(string to_find) {
    for (unsigned i = 0; i < adjacency_list.size(); i++) {
        if (adjacency_list[i].head->value == source) {
            return i;
        }
    }

    return adjacency_list.size(); // default value
}

void Graph::add_edge(string source, string destination) {
    if (source == NULL || destination == NULL) {
        std::cout << "NULL SOURCE OR DEST TO add_edge()" << std::endl;
        return;
    }

    bool found_source = false;
    unsigned source_idx = find_adjlist_idx(source);
    unsigned dest_idx = find_adjlist_idx(destination);
    unsigned start_size = adjacency_list.size(); // because this can change as we go

    if (source_idx != start_size) {
        insert_into_adjlist(source_idx, dest);
    } else {
        // make new adj node
        AdjacencyList source_list = AdjacencyList();
        source_list.insert_at_end(dest);
        source_list.num_edges += 1;

        adjacency_list.push_back(source_list);
    }

    if (dest_idx != start_size) {
        insert_into_adjlist(source_idx, dest);
    } else {
        // make new adj node
        AdjacencyList dest_list = AdjacencyList(dest_l_list);
        dest_list.insert_at_end(source);
        dest_list.num_edges += 1;

        adjacency_list.push_back(dest_list);
    }
}

void Graph::remove_edge(string source, string destination) {
    if (source == NULL || destination == NULL) {
        std::cout << "NULL SOURCE OR DEST TO remove_edge()" << std::endl;
        return;
    }

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
        std::cout << "Not adjacent; one or both didn't exist!" << std::endl;
        return false;
    }

    // watch out for issues if adjacency_list[dest_idx].find(source) == NULL or != NULL)
    return (adjacency_list[source_idx].find(destination) != NULL);
}


Graph::AdjacencyList Graph::adjacent(string vertex) {
    // 
}