#pragma once

#include <queue>
#include <vector>
#include "../graph/graph.h"

class BFS: {
	public:
		BFS(Graph * graph);
		std::vector<int> findPath(int start, int end);
	
	private:
		Graph * graph_;
};