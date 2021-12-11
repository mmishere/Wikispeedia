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

		AdjacencyList() {
			this->head = nullptr;
			this->num_edges = 0;
		}

		AdjacencyList(LinkedListNode *head) {
			this->head = head;
			this->num_edges = 0;
		}

		~AdjacencyList() {
			LinkedListNode* curr = head;
			while (curr != NULL) {
				curr = curr->next;
				delete head;
				head = curr;
			}
		}

		AdjacencyList(const AdjacencyList& other) {
			copy(other);
			
		}

		AdjacencyList& operator=(const AdjacencyList& other) {
			if (this != &other) {
				copy(other);
			}
			return *this;
		}

		void copy(const AdjacencyList& other) {
			this->num_edges = other.num_edges;
			LinkedListNode* curr = other.head;
			while (curr != NULL) {
				this->insert_at_end(curr->value);
				curr = curr->next;
			}
		}

		bool remove_node(string to_remove) {
			if (head->value == to_remove) {
				// special case
				LinkedListNode* temp = head;
				head = head->next;
				delete temp;
				return true;
			}

			LinkedListNode* prev = head;
			LinkedListNode* current = head;
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
		LinkedListNode* find_prev(string to_find) { 
			LinkedListNode* current = head;
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

		void insert_at_end(string to_insert) {
			if (head == NULL) {
				head = new LinkedListNode(to_insert);
				return;
			}


			LinkedListNode* current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = new LinkedListNode(to_insert);
		}

		// returns null if not found
		LinkedListNode* find(string to_find) {
			LinkedListNode* current = head;
			while (current != NULL) {
				if (current->value == to_find) {
					return current;
				}
				current = current->next;
			}
			return NULL;
		}

		void remove(string to_remove) {
			if (head == NULL) {
				return;
			}

			if (head->value == to_remove) {
				LinkedListNode* temp = head;
				head = head->next;
				delete head;
			}

			LinkedListNode* remove = find_prev(to_remove);
			if (remove == NULL) {
				return;
			}
			LinkedListNode* temp = remove->next;
			remove->next = temp->next;
			delete temp;
		}
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
