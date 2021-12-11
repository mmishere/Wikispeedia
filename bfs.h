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
		// Making them const so that compiler doesn't throw any errors
		std::vector<std::string> findPath(const std::string & start, const std::string & end); //returns empty vector if no path found
		std::map<std::string, int> centralities(); //returns map of strings to their betweenness centralities
	
	private:
		Graph * graph_;
};
