#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <pair>

using std::string;

class Graph {

	struct LinkedList {
		string value;
		LinkedList *next;

		LinkedList(string value) {
			this->value = value;
			this->next = nullptr;
		}

		LinkedList(string value, LinkedList *next) {
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

		bool remove_node(string to_remove) {
			if (head->value == to_remove) {
				// special case
				LinkedList* temp = head;
				head = head->next;
				delete temp;
				return;
			}

			LinkedList* prev = head;
			LinkedList* current = head;
			while (current != NULL) {
				current = current->next;
				if (current->value == to_remove) {
					// remove this node
					prev->next = current->next;
					delete current;
					return;
				}
				prev = prev->next;
			}
		}

		void insert_at_end(string to_insert) {
			if (head == NULL) {
				head = new LinkedList(to_insert);
				return;
			}


			LinkedList* current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = LinkedList(to_insert);
		}

		// returns null if not found
		LinkedList* find_prev(string to_find) { 
			LinkedList* current = head;
			while (current != NULL) {
				if (current->next->value == to_find) {
					return current;
				}
				current = current->next;
			}
			return NULL;
		}

		// returns null if not found
		LinkedList* find(string to_find) {
			LinkedList* current = head;
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
				LinkedList* temp = head;
				head = head->next;
				delete head;
			}

			LinkedList* remove = find_prev(to_remove);
			if (remove == NULL) {
				return;
			}
			LinkedList* temp = remove->next;
			remove->next = temp->next;
			delete temp;
		}
	};

	public:
		Graph(int num_vertices);
		Graph(std::string file1, std::string file2);

		void add_edge(string source, string destination);
		void remove_edge(string source, string destination);
		void print_graph();

		bool isAdjacent(string source, string destination);

		AdjacencyList adjacent(string vertex);

	private:
		std::vector<AdjacencyList> adjacency_list;
		int num_vertices;

		std::vector<std::pair<int, int>> parserHelper(std::string file1, std::string file2);
		void insert_into_adjlist(unsigned list_idx, string to_insert);
		unsigned find_adjlist_idx(string to_find); // if this doesn't find it, it will return adjlist.size

};
