#include "SmarterArray.cpp"

struct Edge
{
	int desVertexIndex; //the index (in the underlying graph) of the destination vertex of this edge
	double cost;//cost of an edge
};

class Vertex
{
private:
	String name; //Name of the city at the vertex
	SmarterArray<Edge> E; //A container to store the edges emanating from this vertex. All the elements of 
			 //E have the same origin vertex which is the *this object. But they have different destination
			 //vertices which are given by the desVertexIndex member variable of each element of the E container

public:
	Vertex(); //Assign name = "N/A" and initialize E to an empty container (default object E)
	Vertex(const String&); //Assign name = the argument and initialize E to an empty container
	String getName() const; //Return the name
	SmarterArray<Edge> getEdgeSet() const; //Return E
	int getEdgeSetSize() const; //Return the size of E
	Edge getEdge(const int& desVertexIndex) const; //Assert an edge whose destination vertex index is 
												//equal to the argument is found in E. Then return the edge
	double getEdgeCost(const int& desVertexIndex) const; //Assert an edge whose destination vertex index 
											//is equal to the argument is found in E. Then return its cost
	void setEdgeCost(const int& desVertexIndex, const double& cost); //Assert an edge whose destination vertex index 
											//is equal to the argument is found in E. Then assign its cost the argument
	void appendEdge(const int& desVertexIndex, const double& cost); //Assert there is no element of E 
				//whose destination vertex index and cost are equal to the argument values. Then append
				//a new element whose destination vertex index and cost are initialized with the
				//argument values to E
	friend ostream& operator << (ostream&, const Vertex&); 
};

ostream& operator << (ostream& out, const Vertex& vertex)
{
	out << "Name = " << vertex.name << endl;
	out << "Edge Set" << endl;
	for (int i = 0; i < vertex.E.getSize(); i++)
		out << "\t to ---> " << vertex.E[i].desVertexIndex << ", cost = " << vertex.E[i].cost << endl;
	return out;
}

Vertex::Vertex() {
	name = "N/A";
}

Vertex::Vertex(const String& s) {
	name = s;
}

String Vertex::getName() const {
	return name;
}

SmarterArray<Edge> Vertex::getEdgeSet() const {
	return E;
}

int Vertex::getEdgeSetSize() const {
	return E.getSize();
}

Edge Vertex::getEdge(const int& num) const {
	assert(num >= 0 && num < E.getSize());
	for (int i = 0; i < E.getSize(); i++) {
		if (E[i].desVertexIndex == num) {
			return E[i];
		}
	}
}

double Vertex::getEdgeCost(const int& desVertexIndex) const {
	assert(desVertexIndex >= 0 && desVertexIndex < E.getSize());
	for (int i = 0; i < E.getSize(); i++) {
		if (E[i].desVertexIndex == desVertexIndex) {
			return E[i].cost;
		}
	}
}

void Vertex::setEdgeCost(const int& desVertexIndex, const double& cost) {
	assert(desVertexIndex >= 0 && desVertexIndex < E.getSize());
	for (int i = 0; i < E.getSize(); i++) {
		if (E[i].desVertexIndex == desVertexIndex) {
			E[i].cost = cost;
			break;
		}
	}
}

void Vertex::appendEdge(const int& desVertexIndex, const double& cost) {
	Edge newE;
	newE.desVertexIndex = desVertexIndex;
	newE.cost = cost;
	E.append(newE);
}
