#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility> // for pair

using std::string;
using std::vector;

class Graph {

public:
	struct LinkedListNode {
		string value;
		LinkedListNode *next;

		LinkedListNode(string value) {
			this->value = value;
			this->next = nullptr;
		}

		LinkedListNode(string value, LinkedListNode *next) {
			this->value = value;
			this->next = next;
		}
	};

public:
	struct AdjacencyList {
		LinkedListNode *head;
		int num_edges;

		AdjacencyList();
		AdjacencyList(LinkedListNode *head);
		~AdjacencyList();
		AdjacencyList(const AdjacencyList& other);
		AdjacencyList& operator=(const AdjacencyList& other);

		void copy(const AdjacencyList& other);

		bool remove_node(string to_remove);
		// returns null if not found
		LinkedListNode* find_prev(string to_find);
		// returns null if not found
		LinkedListNode* find(string to_find);
		void insert_at_end(string to_insert);
		void remove(string to_remove);
	};

	
		Graph(int num_vertices);
		/**
		* Constructs a Graph from a list of vertices and edges.
		*
		* @param vertices The list of vertices of the graph.
		* @param edges The list of edges (connections) for the graph.
		*/
		Graph(std::vector<string> vertices, std::vector<std::pair<string, string>> edges);

		void add_edge(string source, string destination);
		void remove_edge(string source, string destination);
		void print_graph(std::ostream &out);

		bool isAdjacent(string source, string destination);

		vector<string> adjacent(string vertex);

		/** @return The number of vertices in the graph. */
		int get_num_vertices();


		// helpers for SSC
		const std::vector<AdjacencyList>& getConnections() const; 
		// indexes are very arbitrary but that's okay because they are ordered.
		AdjacencyList& getAdjListByNode(string node);
		Graph* getTranspose();

	private:
		std::vector<AdjacencyList> adjacency_list;
		int num_vertices;

		void insert_into_adjlist(unsigned list_idx, string to_insert);
		unsigned find_adjlist_idx(string to_find); // if this doesn't find it, it will return adjlist.size

};
