// Adjacency Matrix representation in C++

#include <iostream>
#include <limits>
using namespace std;

class Graph
{
	private:
  		bool** adjMatrix;    // Indicates if there is an edge exist between two cities.
 		int numVertices,     // Stores the number of cities.
		 	distance[5][5];  // Stores the distance from a city to the other city.

   	public:
   		
  	// Initialize the adjacency matrix
	Graph(int numVertices)
	{
  		this->numVertices = numVertices;
    	adjMatrix = new bool*[numVertices];
    	
    	for (int i = 0; i < numVertices; i++)
      		adjMatrix[i] = new bool[numVertices];
      		
    	resetGraph();
  	}

	// Add edges
  	void addEdge(int i, int j, int weight)
	{
    	adjMatrix[i][j] = true;
    	distance[i][j] = weight;
  	}

  	// Remove edges
  	void removeEdge(int i, int j)
	{
   		adjMatrix[i][j] = false;
  	}
  
  	// Get adjMatrix[i][j] or check if city j is adjacent to city i.
  	bool areAdjacent(int i, int j)
  	{
  		return adjMatrix[i][j];
  	}
  
  	// Get Distance[i][j]
	int getDistance(int i, int j)
	{
	  	return distance[i][j];
	}

	// Print the martix
	void toString() {
		for (int i = 0; i < numVertices; i++)
		{
			cout << i << " : ";
		  	for (int j = 0; j < numVertices; j++)
		    	cout << adjMatrix[i][j] << " ";
		  	cout << endl;
		}
	}

	//Initialise and reset the graph
	void resetGraph()
	{
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
				adjMatrix[i][j] = false;
	  	}
	  	
	  	// Add the edges and their corresponding distance/weight to the adjacency matrix.
	  	int PA=0, LO=1, LV=2, SY=3, TO=4;		
		addEdge(PA, TO, 9715);
		addEdge(PA, LO, 343);
		addEdge(TO, SY, 7826);
		addEdge(LV, SY, 12434);
		addEdge(LV, LO, 8402);
		
		// In the adjacency matrix, if the edge is not present, then it will be infinity. For same node, it will be 0.
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
				if (adjMatrix[i][j] == false)
					adjMatrix[i][j] = numeric_limits<int>::infinity();
			}
	  	}
	}

  	~Graph()
	{
    	for (int i = 0; i < numVertices; i++)
      		delete[] adjMatrix[i];
    	delete[] adjMatrix;
  	}
};

int main()
{
	// Initialize a directed and weighted graph when this program starts up.
	Graph g(5);

	g.toString();
	
	// Display the distance
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << g.getDistance(i, j) << "\t";
		cout << endl;	
	}
	
	return 0;
}

