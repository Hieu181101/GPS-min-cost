#include "Graph.cpp"

class Path
{
private:
	SmarterArray<int> P; //The indices (singular index) the vertices along the path
public:
	Path(); //Construct an empty path. Default object P.
	int length() const; //Return the number of vertices along the path (the number of elements of P)
	int find(const int& vertexIndex) const; //Return the index of an element of P such that P[index] == vertexIndex. 
											//If no element satisfies the condition, then return -1

	double computePathCost(const Graph&) const; //Compute the sum of the costs of edges along this path 
		//given the underlying Graph argument. 

		//For example, if the Path object contains P = [3, 8, 6, 4, 9] then this function will return the 
		//cost(from vertex whose index in G is 3 to the vertex whose index in G is 8) +
		//cost(from vertex whose index in G is 8 to the vertex whose index in G is 6) +
		//cost(from vertex whose index in G is 6 to the vertex whose index in G is 4) +
		//cost(from vertex whose index in G is 4 to the vertex whose index in G is 9)

	int& operator [](const int& index) const; //Assert index is valid in P and then return P[index]
	void insert(const int& index, const int& vertexIndex); //Assert the condition index >= 0 && 
											//index <= the length and then insert the vertexIndex argument 
											//at the specified index. If index is equal to the length, then 
											//perform append.
	void append(const int& vertexIndex); //Insert the argument as a last element.
	void remove(const int& index); //Assert the index argument and then remove the element P[index]
	SmarterArray<String> getPathNamesList(const Graph&) const; 
	friend ostream& operator << (ostream&, const Path&); 
};

SmarterArray<String> Path::getPathNamesList(const Graph& g) const
{
	SmarterArray<String> path;
	for (int i = 0; i < this->length(); i++)
	{
		int vertexIndex = (*this)[i];
		path.append(g[vertexIndex].getName());
	}
	return path;
}

ostream& operator << (ostream& out, const Path& path)
{
	out << "[";
	if (path.length() > 0)
	{
		for (int i = 0; i < path.length() - 1; i++)
			out << path[i] << " -> ";
		out << path[path.length() - 1];
	}
	out << "]";
	return out;
}

Path::Path() {
}

int Path::length() const {
	return this->P.getSize();
}

int Path::find(const int& vertexIndex) const {
	return this->P.find(vertexIndex);
}


int& Path::operator [](const int& index) const {
	assert(index < this->length() && index >= 0);
	return this->P[index];
}

void Path::append(const int& vertexIndex) {
	this->P.append(vertexIndex);
}

void Path::insert(const int& index, const int& vertexIndex) {
	assert(index < this->length() && index >= 0);
	this->P.insert(index, vertexIndex);
}

void Path::remove(const int& index) {
	this->P.remove(index);
}


double Path::computePathCost(const Graph& g) const {
	double totalCost = 0;
	Vertex V;
	SmarterArray <Edge> E;
	for (int i = 0; i < this->length() - 1; i++) {
		bool found = false;
		V = g[P[i]];
		E = V.getEdgeSet();
		for (int j = 0; j < V.getEdgeSetSize(); j++) {
			if (g.getVertexIndex(g[E[j].desVertexIndex].getName()) == P[i + 1]) {
				found = true;
				totalCost += E[j].cost;
				break;
			}
		}
		if (!found) {
			cout << "Path route does not exsist. " << endl;
			abort();
		}
	}
	return totalCost;
}

Path computeMinCostPath(const Graph& g, const String& departure, const String& destination, int& pathCount, Path& currentPath) {
	assert(g.getVertexSetSize() > 0);
	int depVertexIndex = g.getVertexIndex(departure);
	int desVertexIndex = g.getVertexIndex(destination);
	assert(desVertexIndex != -1 && depVertexIndex != -1);
	if (departure == destination) {
		Path minCostPath = currentPath;
		minCostPath.append(desVertexIndex);
		cout << "Path found: " << minCostPath << " with cost " << minCostPath.computePathCost(g) << endl;
		pathCount++;
		return minCostPath;
	}
	else if (currentPath.find(depVertexIndex) != -1) {
		Path minCostPath = currentPath;
		return minCostPath;
	}
	else {
		Vertex depVertex = g[depVertexIndex];
		SmarterArray<Edge> E = depVertex.getEdgeSet();
		Path minCostPath;
		currentPath.append(g.getVertexIndex(depVertex.getName()));
		for (int i = 0; i < E.getSize(); i++) {
			String nextVertexName = g[E[i].desVertexIndex].getName();
			if (currentPath.find(g.getVertexIndex(nextVertexName)) == -1) {
				Path candidatePath = computeMinCostPath(g, nextVertexName, destination, pathCount, currentPath);
				if (candidatePath.length() > 0) {
					if (candidatePath[candidatePath.length() - 1] == g.getVertexIndex(destination)) {
						if (minCostPath.length() == 0 || minCostPath.computePathCost(g) > candidatePath.computePathCost(g)) {
							minCostPath = candidatePath;
						}
					}
				}
			}
		}
		currentPath.remove(currentPath.length() - 1);
		return minCostPath;
	}
}
