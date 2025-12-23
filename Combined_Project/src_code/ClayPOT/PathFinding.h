#pragma once
class Pathfinder {

private:
	int width, height;
	std::vector<std::vector<int>> graph;   // adjacency list

public:

	Pathfinder(int width, int height, const std::vector<std::vector<int>>& graph)
		: width(width), height(height), graph(graph) {
	}

	// A* on adjacency list
	std::vector<int> findPath(int start, int goal)
	{
		const int n = graph.size();

		std::vector<float> gCost(n, std::numeric_limits<float>::infinity());
		std::vector<int> parent(n, -1);

		// Min-heap priority queue (fCost, node)
		using NodePair = std::pair<float, int>;
		std::priority_queue<NodePair, std::vector<NodePair>, std::greater<NodePair>> pq;

		// Heuristic: simple (0) since graph is unweighted (Dijkstra == A*)
		auto heuristic = [&](int a, int b) {
			return 0.0f;   // For pure unweighted graph, this is fine
			};

		gCost[start] = 0;
		pq.push({ heuristic(start, goal), start });

		while (!pq.empty())
		{
			auto [fScore, current] = pq.top();
			pq.pop();

			// Goal reached
			if (current == goal)
				break;

			for (int neighbor : graph[current])
			{
				float newCost = gCost[current] + 1;   // unweighted → cost = 1

				if (newCost < gCost[neighbor])
				{
					gCost[neighbor] = newCost;
					parent[neighbor] = current;

					float f = newCost + heuristic(neighbor, goal);
					pq.push({ f, neighbor });
				}
			}
		}

		// Reconstruct final path
		std::vector<int> path;
		if (gCost[goal] == std::numeric_limits<float>::infinity())
			return path;  // No path found

		for (int node = goal; node != -1; node = parent[node])
			path.push_back(node);

		std::reverse(path.begin(), path.end());
		return path;
	}
};