#pragma once

#include <queue>
#include <vector>
#include "../graph/graph.h"

class BFS {
	public:
		BFS(Graph * graph);
		std::vector<int> findPath(int start, int end); //returns empty vector if no path found
		bool isSC(int start); //find if graph is strongly connected, from starting point
	
	private:
		Graph * graph_;
};