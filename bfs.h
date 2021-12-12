#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>

#include "graph.h"

class BFS {
	public:
		BFS(Graph * graph);
		/**
		* Finds the shortest apth between two nodes using a BFS.
		* Making them const so that compiler doesn't throw any errors
		*
		* @param start The start node.
		* @param end The end node.
		* @returns A vector of strings representing each node in the path.
		*/
		std::vector<std::string> findPath(const std::string & start, const std::string & end); //returns empty vector if no path found
		
		/**
		* Calculates the betweenness centralities of each vertex (naive implementation).
		*
		* @returns A map of strings representing nodes to their betweenness centralities.
		*/
		std::map<std::string, int> centralities();
	
		/**
		* Calculates the betweenness centralities of each vertex (naive implementation)
		* and sorts them from greatest to least centrality.
		*
		* @returns A sorted vector of strings representing nodes and their betweenness centralities.
		*/
		std::vector<std::pair<std::string, int>> centralitiesSorted();

	private:
		Graph * graph_;
};

/**
* Helper function to compare betweenness centralities of two nodes.
*
* @param node1 The first node to compare.
* @param node2 The second node to compare.
* @returns Whether or not node1 is greater than node2.
*/
bool is_centrality_greater(const std::pair<std::string, int>& node1, const std::pair<std::string, int>& node2);
