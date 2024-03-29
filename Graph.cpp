#include "Vertex.cpp"

class Graph
{
private:
	SmarterArray<Vertex> V; //A graph is simply a container that contains many vertex objects where each vertex
							//will have all its connectivity information in it.

public:
	Graph();//Construct empty graph (default object V)
	Graph(const char*); //Construct a graph from a text file whose path is given by the argument cstring.

	SmarterArray<Vertex> getVertexSet() const; //Return V
	int getVertexSetSize() const; //Return the number of elements of V
	Vertex& operator[](const int& index) const; //Assert the index argument and then return the element at index
	int getVertexIndex(const String&) const; //Return the index of an element whose name matches	
													//the argument. If no such element is found, return -1.
													//Assertion should not be performed.
	int getVertexIndex(const Vertex&) const; //Return the index of the element whose name matches the
											//name of the vertex argument. If no such element is found, 
											//return -1. Assertion should not be performed.
	String getRandomVertexName() const; //Pick a vertex at random and return its name
	void appendVertex(const String&); //Append a vertex with the given name and empty E only 
						   //if no vertex with the same name already exists in the graph. If same name 
							//vertex already exists then do nothing and return. Assertion should not be performed.
	void appendVertex(const Vertex&); //Append the argument only if no vertex with the same name already exists 
										//in the graph. If same name vertex already exists then do nothing 
										//and return. Assertion should not be performed.

	void appendEdge(const String& departure, const String& destination, const double& cost);

	friend ostream& operator << (ostream&, const Graph&); 
};

Graph::Graph() {
}

Graph::Graph(const char* c) {
	String departure, destination;
	double cost;
	ifstream fin;
	fin.open(c);
	assert(!fin.fail());
	while (!fin.eof()) {
		fin >> departure;
		if (departure.empty()) {
			break;
		}
		fin >> destination;
		fin >> cost;
		this->appendVertex(departure);
		this->appendVertex(destination);
		this->appendEdge(departure, destination, cost);
		this->appendEdge(destination, departure, cost);
	}
	fin.close();
}



SmarterArray<Vertex> Graph::getVertexSet() const {
	return V;
}

int Graph::getVertexSetSize() const {
	return V.getSize();
}

Vertex& Graph::operator[](const int& index) const {
	assert(index >= 0 && index < this->getVertexSetSize());
	return (V[index]);
}

int Graph::getVertexIndex(const String& s) const {
	for (int i = 0; i < this->getVertexSetSize(); i++) {
		if (V[i].getName() == s) {
			return i;
		}
	}
	return -1;
}

int Graph::getVertexIndex(const Vertex& ver) const {
	for (int i = 0; i < this->getVertexSetSize(); i++) {
		if (V[i].getName() == ver.getName()) {
			return i;
		}
	}
	return -1;
}

String Graph::getRandomVertexName() const {
	return (V[rand() % V.getSize()].getName());
}

void Graph::appendVertex(const Vertex& ver) {
	if (this->getVertexIndex(ver) == -1) {
		V.append(ver);
	}
}

void Graph::appendVertex(const String& s) {
	Vertex ver(s);
	if (this->getVertexIndex(ver) == -1) {
		V.append(ver);
	}
}

void Graph::appendEdge(const String& dep, const String& des, const double& cost) {
	assert(this->getVertexIndex(dep) != -1 && this->getVertexIndex(des) != -1);
	V[this->getVertexIndex(dep)].appendEdge(this->getVertexIndex(des), cost);
}

ostream& operator << (ostream& out, const Graph& g)
{
	const int CITY_NAME_WIDTH = 25;
	out << endl;
	out << "The graph has " << g.getVertexSetSize() << " vertices." << endl;
	out << "These vertices are" << endl;
	for (int i = 0; i < g.getVertexSetSize(); i++)
	{
		Vertex v = g.V[i];
		out << "Vertex at index " << i << " = " << v.getName() << endl;
	}
	out << endl;
	out << "Each vertex together with its edge set looks like as follows" << endl;
	for (int i = 0; i < g.getVertexSetSize(); i++)
	{
		Vertex v = g.V[i];
		out << v << endl;
	}
	out << endl;
	out << "The graph connectivities are as follows..." << endl;
	out.setf(ios::fixed | ios::left);	//Left aligned fixed decimal places formatting
	for (int i = 0; i < g.getVertexSetSize(); i++)
	{
		Vertex depVertex = g[i];
		SmarterArray<Edge> E = depVertex.getEdgeSet();
		for (int j = 0; j < E.getSize(); j++)
		{
			int desVertexIndex = E[j].desVertexIndex;
			Vertex desVertex = g[desVertexIndex];
			out << depVertex.getName() << setw(CITY_NAME_WIDTH - depVertex.getName().length()) << " ";
			out << desVertex.getName() << setw(CITY_NAME_WIDTH - desVertex.getName().length()) << " ";
			out << setprecision(2) << E[j].cost << endl;
		}
	}
	out.unsetf(ios::fixed | ios::left);	//Removing formatting
	cout.precision(0);					//Resetting the decimal places to default
	return out;
}
