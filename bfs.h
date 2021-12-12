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
		* @returns A map of strings to their betweenness centralities.
		*/
		std::map<std::string, int> centralities();
	
	private:
		Graph * graph_;
};
