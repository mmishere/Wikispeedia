#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include <set>
#include "graph.h"

class BFS {
	public:
		BFS(Graph * graph);
		// Making them const so that compiler doesn't throw any errors
		std::vector<std::string> findPath(const std::string & start, const std::string & end); //returns empty vector if no path found
		bool isSC(std::string * start); //find if graph is strongly connected, from starting point
	
	private:
		Graph * graph_;
};
