#pragma once

#include <iostream>
#include <vector>

class Graph {

	struct LinkedList {
		int value;
		LinkedList *next;

		LinkedList(int value) {
			this->value = value;
			this->next = nullptr;
		}

		LinkedList(int value, LinkedList *next) {
			this->value = value;
			this->next = next;
		}
	};

	struct AdjacencyList {
		LinkedList *head;
		int num_edges;

		AdjacencyList() {
			this->head = nullptr;
			this->num_edges = 0;
		}

		AdjacencyList(LinkedList *head) {
			this->head = head;
			this->num_edges = 0;
		}
	};

	public:
		Graph(int num_vertices);
		Graph();

		void add_edge(int source, int destination);
		void remove_edge(int source, int destination);
		void print_graph();

		bool isAdjacent(int source, int destination);

		AdjacencyList adjacent(int vertex);

	private:
		std::vector<AdjacencyList> adjacency_list;
		int num_vertices;
};
		
