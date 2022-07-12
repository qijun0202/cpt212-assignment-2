// Adjacency Matrix representation in C++

#include <iostream>
#include <limits>
using namespace std;

class Graph
{
	private:
  		bool** adjMatrix;    // Indicates if there is an edge exist between two cities.
 		int numVertices,     // Stores the number of cities.
		 	distance[5][5] = {{0,343,8730,16961,9715},{343,0,8402,16994,9562},{8730,8402,0,12434,8897},{16961,16994,12434,0,7826},{9715,9562,8897,7826,0}};  // Stores the distance from a city to the other city.

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
  	void addEdge(int i, int j)
	{
    	adjMatrix[i][j] = true;
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
		  	{
		  		if ( adjMatrix[i][j] == false)
		    		cout << adjMatrix[i][j] << "\t";
		    	else
		    		cout << distance[i][j] << "\t";
		    }
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
		addEdge(PA, TO);
		addEdge(PA, LO);
		addEdge(TO, SY);
		addEdge(LV, SY);
		addEdge(LV, LO);
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
	int choice = 0;

	g.toString();
	
	while ( choice != 6)
	{
		cout<<"\nPlease choose one function to proceed:\n"
			<<"(1) Check strongly connected\n"
			<<"(2) Check cycle\n"
			<<"(3) Check shortest path between two cities\n"
			<<"(4) Compute minimum spanning tree\n"
			<<"(5) Reset the graph\n"
			<<"(6) End the program\n"
			<<"Choice : ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				g.resetGraph();
				g.toString();
				break;
			default:
				if(choice == 6)
					cout<<"Thank you for using this program.";
				break;
		}
	}
	
	return 0;
}

