#pragma once

#include <queue>
#include <vector>
#include <map>
#include "../graph/graph.h"

class BFS {
	public:
		BFS(Graph * graph);
		std::vector<std::string> findPath(std::string start, std::string end); //returns empty vector if no path found
		bool isSC(std::string start); //find if graph is strongly connected, from starting point
	
	private:
		Graph * graph_;
};