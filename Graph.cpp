// Adjacency Matrix representation in C++
#include<ctime>
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
		string place[] = {"Paris\t\t","London\t\t","LasVegas\t","Sydney\t\t","Tokyo\t\t"};
		cout << "Name\t\t: " << place[0] << place[1] << place[2] << place[3] << place[4] << endl;
		for (int i = 0; i < numVertices; i++)
		{
			cout << place[i] << ": ";
		  	for (int j = 0; j < numVertices; j++)
		  	{
		  		if ( adjMatrix[i][j] == false)
		    		cout << adjMatrix[i][j] << "\t\t";
		    	else
		    		cout << distance[i][j] << "\t\t";
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
	
	void randomEdge()
{
	srand((unsigned) time(0));
	int a=rand()%5, b=rand()%5;
	
	while(a==b || adjMatrix[a][b]==true)
	{
		a=rand()%5;
		b=rand()%5;
	}

	addEdge(a,b);
}
	
  	~Graph()
	{
    	for (int i = 0; i < numVertices; i++)
      		delete[] adjMatrix[i];
    	delete[] adjMatrix;
  	}
  	
};

void selectTwoCities(int &x, int &y)
{	
	cout << "Starting city   : ";
	cin >> x;
	cout << "Destination city: ";
	cin >> y;
	
	if (x == 0 || y == 0)	//Finish function if x or y equal to 0.
	{
		return;
	}
	else if (x == y)  // Print the error message if the 2 city numbers are the same.
	{
		cout << "\n******************************* ERROR! *******************************" << endl
			 << "The starting and destination city number entered must be different!!!"    << endl
			 << "**********************************************************************\n" << endl;
	}
	else if (x < 1 || x > 5 || y < 1 || y > 5 )  // Print the error message if the input is incorrect.
	{
		cout << "\n*********************** ERROR! ***********************" << endl
			 << "The city number entered should be between 1 and 5!!!"     << endl
			 << "******************************************************\n" << endl;
	}
}

void enterRemoveEdge(Graph &g)
{
	int x, y;
	
	// Ask users to enter the starting and destination city of directed edge they want to remove.
	cout << "\nPA: 1, LO: 2, LV: 3, SY: 4, TO: 5, Cancel: 0" << endl
		 << "Enter the starting and destination city of directed edge you want to remove:" << endl;
	
	// Prompt user to input starting and destination city using respective number.
	do
	{
		selectTwoCities(x,y);
		
		//Finish function if x or y equal to 0.
		if(x == 0 || y == 0)
		{
			return;
		}
		else if (!g.areAdjacent(x-1, y-1) && x != y )  // Print the error message if the directed edge is not exist.
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

//Find the minimum distance value from cities that have not included in shortest path tree.
int minDistance(int dist[], bool read[])
{
	int u, min = INT_MAX, min_index;
	for (u = 0; u < 5; u++)
	{
		//Find minimum distance from source, and set the corresponding index number.
		if (dist[u] <= min && read[u] == false)
		{
			min = dist[u];
			min_index = u;
		}
	}
	
	return min_index;
}

//Dijsktra algorithm to find short path for two city.
void Dijsktra(Graph &g)
{
	int x, y, u;
	int dist[5];
	bool read[5];
	

	
	cout << "\nPA: 1, LO: 2, LV: 3, SY: 4, TO: 5, Cancel: 0" << endl
		 << "Enter the starting and destination city of directed edge you want to remove:" << endl;
		 
	do
	{
		selectTwoCities(x, y);
	}while (x < 1 || x > 5 || y < 1 || y > 5 || x == y);
	

	
	for(dist[y-1] = INT_MAX; dist[y-1] == INT_MAX; g.randomEdge())
	{
	for (int i = 0; i < 5; i++)
	{
	dist[i] = INT_MAX;
	read[i] = false;
	}
		
	dist[x-1] = 0;
		
	for(int k = 0; k < 4; k++)
	{
		u = minDistance(dist, read);
		
		read[u] = true;

		for (int v = 0; v < 5; v++)
		{
			if (!read[v] && g.areAdjacent(u, v) && dist[u] != INT_MAX && dist[u]+g.getDistance(u,v) < dist[v])
				dist[v] = dist[u] + g.getDistance(u,v);
		}
	}
	}
	cout<<endl<<dist[y-1]<<endl;
}



int main()
{
	// Initialize a directed and weighted graph g when this program starts up.
	Graph g(5);
	int choice = 0;

	// Print the menu of the program. 
	while (choice != 8)
	{
		g.toString();
		cout << "\nPlease choose one function to proceed:\n"
			 << "(1) Check strongly connected\n"
			 << "(2) Check cycle\n"
			 << "(3) Check shortest path between two cities\n"
			 << "(4) Compute minimum spanning tree\n"
			 << "(5) Reset the graph\n"
			 << "(6) Remove the edge\n" 
			 << "(7) Random edge\n"
			 << "Choice : ";
		cin >> choice;
		cout<< endl;
		
		switch(choice)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				Dijsktra(g);
				break;
			case 4:
				break;
			case 5:
				g.resetGraph();
				break;
			case 6:
				enterRemoveEdge(g);
				break;
			case 7:
				g.randomEdge();
				break;
			default:
				if(choice == 8)
					cout << "\nThank you for using this program.";
				break;
		}
	}

	return 0;
}

