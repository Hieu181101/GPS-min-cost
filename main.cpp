#include "Path.cpp"

int main()
{
	srand(time(0));
	Graph g("BiggerMap.txt");
	cout << "Graph constructed successfully." << endl;
	cout << g << endl;

	String departure, destination;
	int pathCount;

	for (int i = 0; i < 10; i++)
	{
		cout << endl << "Test #" << i + 1 << endl;
		departure = g.getRandomVertexName();
		destination = g.getRandomVertexName();
		cout << "Computing shortest path from " << departure << " to " << destination << endl;
		pathCount = 0;
		Path temp;
		Path minCostPath = computeMinCostPath(g, departure, destination, pathCount, temp);
		cout << "There were " << pathCount << " possible paths found." << endl;
		cout << "The minimum cost path is: " << minCostPath << " Cost = " << std::fixed << std::setprecision(2) << minCostPath.computePathCost(g) << endl;
		cout << "The cities along the minimum cost path are " << endl;
		cout << "[";

		if (minCostPath.length() > 0)
		{
			SmarterArray<String> p = minCostPath.getPathNamesList(g);
			for (int i = 0; i < p.getSize() - 1; i++)
				cout << p[i] << " -> ";
			cout << p[p.getSize() - 1];
		}

		cout << "]" << endl << endl;

	}

	system("Pause");
	return 0;
}