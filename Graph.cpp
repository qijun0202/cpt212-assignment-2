// Adjacency Matrix representation in C++

#include <iostream>
using namespace std;

class Graph
{
	private:
  		bool** adjMatrix;    // Indicates if there is an edge exist between two cities.
 		int numVertices,     // Stores the number of cities.
		 	distance[5][5] = {{0    ,343  ,8730 ,16961,9715},    // Stores the distance from a city to the other city.
			 				  {343  ,0    ,8402 ,16994,9562},
							  {8730 ,8402 ,0    ,12434,8897},
							  {16961,16994,12434,0    ,7826},
							  {9715 ,9562 ,8897 ,7826 ,0}};

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

void enterRemoveEdge(Graph g)
{
	int x, y;
	
	// Ask users to enter the starting and destination city of directed edge they want to remove.
	cout << "\nPA: 1, LO: 2, LV: 3, SY: 4, TO: 5" << endl
		 << "Enter the starting and destination city of directed edge you want to remove:" << endl;
	
	// Prompt user to input starting and destination city using respective number.
	do
	{
		cout << "Starting city   : ";
		cin >> x;
		cout << "Destination city: ";
		cin >> y;
		
		if (x < 1 || x > 5 || y < 1 || y > 5)  // Print the error message if the input is incorrect.
		{
			cout << "\n*********************** ERROR! ***********************" << endl
				 << "The city number entered should be between 1 and 5!!!"     << endl
				 << "******************************************************\n" << endl;
		}
		else if (x == y)  // Print the error message if the 2 city numbers are the same.
		{
			cout << "\n******************************* ERROR! *******************************" << endl
				 << "The starting and destination city number entered must be different!!!"    << endl
				 << "**********************************************************************\n" << endl;
		}
		else if (!g.areAdjacent(x-1, y-1))  // Print the error message if the directed edge is not exist.
		{
			cout << "\n************* ERROR! *************" << endl
				 << "The directed edge is not exist!!!"    << endl
				 << "**********************************\n" << endl;
		}
	} while (x < 1 || x > 5 || y < 1 || y > 5 || x == y || !g.areAdjacent(x-1, y-1));
	
	// Remove the edge by calling the function removeEdge().
	g.removeEdge(x-1, y-1);
	cout << "The edge is removed successfully." << endl;
}

int main()
{
	// Initialize a directed and weighted graph g when this program starts up.
	Graph g(5);
	int choice = 0;

	g.toString();
	
	// Print the menu of the program. 
	while (choice != 7)
	{
		cout << "\nPlease choose one function to proceed:\n"
			 << "(1) Check strongly connected\n"
			 << "(2) Check cycle\n"
			 << "(3) Check shortest path between two cities\n"
			 << "(4) Compute minimum spanning tree\n"
			 << "(5) Reset the graph\n"
			 << "(6) Remove the edge\n" 
			 << "(7) End the program\n"
			 << "Choice : ";
		cin >> choice;
		
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
			case 6:
				enterRemoveEdge(g);
				g.toString();
				break;
			default:
				if(choice == 7)
					cout << "\nThank you for using this program.";
				break;
		}
	}

	return 0;
}

