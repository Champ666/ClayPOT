#pragma once
class AStarComponent
{

public:
	AStarComponent(std::vector<std::vector<int>> graph, int maxX)
		: graph(graph), maxX(maxX) {
	}

	~AStarComponent() = default;


	// Convert (x,y) → linear index
	int calculateGoal(sf::Vector2i pos) {
		return pos.y * this->maxX + pos.x;
	}

	// Convert linear index → world position
	sf::Vector2f getWorldPos(int index) const
	{
		float x = (index % maxX) * 64.f;
		float y = (index / maxX) * 64.f;
		return sf::Vector2f(x, y);
	}

	// Manhattan distance heuristic (best for grid movement)
	float heuristic(int a, int b) const
	{
		sf::Vector2f A = getWorldPos(a);
		sf::Vector2f B = getWorldPos(b);

		return std::abs(A.x - B.x) + std::abs(A.y - B.y);
	}


	// --------------------
	// A* PATHFINDING
	// --------------------
	std::vector<int> findPath(sf::Vector2i from, sf::Vector2i end)
	{
		int start = calculateGoal(from);
		int goal = calculateGoal(end);

		const int n = graph.size();

		std::vector<float> gCost(n, std::numeric_limits<float>::infinity());
		std::vector<int> parent(n, -1);

		using NodePair = std::pair<float, int>;
		std::priority_queue<NodePair, std::vector<NodePair>, std::greater<NodePair>> pq;

		gCost[start] = 0.f;
		pq.push({ heuristic(start, goal), start });

		while (!pq.empty())
		{
			auto [fScore, current] = pq.top();
			pq.pop();

			if (current == goal)
				break;

			for (int neighbor : graph[current])
			{
				float newCost = gCost[current] + 1;

				if (newCost < gCost[neighbor])
				{
					gCost[neighbor] = newCost;
					parent[neighbor] = current;

					float f = newCost + heuristic(neighbor, goal);
					pq.push({ f, neighbor });
				}
			}
		}

		// ---- Reconstruct path ----
		std::vector<int> path;
		if (gCost[goal] == std::numeric_limits<float>::infinity())
			return path;

		for (int node = goal; node != -1; node = parent[node])
			path.push_back(node);

		std::reverse(path.begin(), path.end());
		return path;
	}



private:
	std::vector<std::vector<int>> graph;
	int maxX;
};
