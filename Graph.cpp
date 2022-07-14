// Adjacency Matrix representation in C++
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <list>
#include <stack>
using namespace std;

class Graph
{
	list<int> *adj;    // Pointer to an array containing adjacency lists
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
    	adj = new list<int>[numVertices];
    	
    	for (int i = 0; i < numVertices; i++)
      		adjMatrix[i] = new bool[numVertices];
      		
    	for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
				adjMatrix[i][j] = false;
	  	}
  	}

	// Add edges
  	void addEdge(int i, int j)
	{
    	adjMatrix[i][j] = true;
    	adj[i].push_back(j); // Add w to v's list.
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

	// Print the matrix
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
	  	adj = new list<int>[numVertices];
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
	
	
	bool isCyclicUtil(int v, bool visited[], bool *recStack)
	{
    	if(visited[v] == false)
    	{
    	    // Mark the current node as visited and part of recursion stack
    	    visited[v] = true;
    	    recStack[v] = true;
  	
  	    	// Recur for all the vertices adjacent to this vertex
  	    	list<int>::iterator i;
  	    	for(i = adj[v].begin(); i != adj[v].end(); ++i)
   			{
            	if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                	return true;
            	else if (recStack[*i])
                	return true;
        	}
  
    	}
    	recStack[v] = false;  // remove the vertex from recursion stack
    	return false;
	}
	
	bool isCyclic()
	{
   		// Mark all the vertices as not visited and not part of recursion
    	// stack
    	bool *visited = new bool[numVertices];
    	bool *recStack = new bool[numVertices];
    	for(int i = 0; i < numVertices; i++)
    	{
    	    visited[i] = false;
    	    recStack[i] = false;
    	}
  
    	// Call the recursive helper function to detect cycle in different
    	// DFS trees
    	for(int i = 0; i < numVertices; i++)
    	    if ( !visited[i] && isCyclicUtil(i, visited, recStack))
    	        return true;
  
    	return false;
	}
  
	// A recursive function to print DFS starting from v
	void DFSUtil(int v, bool visited[])
	{
		// Mark the current node as visited and print it
    	visited[v] = true;
 
    	// Recur for all the vertices adjacent to this vertex
    	list<int>::iterator y;
    	for (y = adj[v].begin(); y != adj[v].end(); ++y)
    	    if (!visited[*y])
    	        DFSUtil(*y, visited);
	}
	
	// Function that returns reverse (or transpose) of this graph
	Graph getTranspose()
	{
	    Graph gTrans(numVertices);
    	for (int v = 0; v < numVertices; v++)
    	{
       		// Recur for all the vertices adjacent to this vertex
        	list<int>::iterator z;
        	for(z = adj[v].begin(); z != adj[v].end(); ++z)
        	{
        	    gTrans.adj[*z].push_back(v);
        	}
    	}
    	return gTrans;
	}
	
	// The main function that returns true if graph
	// is strongly connected
	bool isStrongConnected()
	{
	    // Step 1: Mark all the vertices as not visited
	    // (For first DFS)
	    bool visited[numVertices];
	    for (int i = 0; i < numVertices; i++)
	        visited[i] = false;
	 
	    // Step 2: Do DFS traversal starting from first vertex.
	    DFSUtil(0, visited);
	 
	     // If DFS traversal doesn't visit all vertices,
	     // then return false.
	    for (int i = 0; i < numVertices; i++)
	        if (visited[i] == false)
	             return false;
	 
	    // Step 3: Create a reversed graph
	    Graph gReversed = getTranspose();
	 
	    // Step 4: Mark all the vertices as not visited
	    // (For second DFS)
	    for(int i = 0; i < numVertices; i++)
	        visited[i] = false;
	 
	    // Step 5: Do DFS for reversed graph starting from
	    // first vertex. Starting Vertex must be same starting
	    // point of first DFS
	    gReversed.DFSUtil(0, visited);
	 
	    // If all vertices are not visited in second DFS, then
	    // return false
	    for (int i = 0; i < numVertices; i++)
	        if (visited[i] == false)
	             return false;
	 
	    return true;
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
	cout << "*******************************************************************************************\n";
	cout << "PA: 1, LO: 2, LV: 3, SY: 4, TO: 5, Cancel: 0" << endl;
	cout << "Enter the starting and destination city of directed edge you want to remove:" << endl;
	cout << "*******************************************************************************************\n";
	
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
	cout << endl;
	cout << "*******************************************************************************************\n";
	cout << "The edge is removed successfully." << endl;
	cout << "*******************************************************************************************\n";
}

//Find the minimum distance value from cities that have not included in shortest path tree.
int minDistance(int dist[], bool read[])
{
	int u, min = INT_MAX, min_index;
	
	//For all cities, find minimum distance from source, and set the corresponding index number.
	for (u = 0; u < 5; u++)
	{
		if (dist[u] <= min && read[u] == false)
		{
			min = dist[u];
			min_index = u;
		}
	}	
	
	return min_index;
}

//Print the corresponded city name for each vertice.
void printCity(int i)
{
	switch(i)
	{
		case 0:
			cout<<"Paris";
			break;
		case 1:
			cout<<"London";
			break;
		case 2:
			cout<<"Las Vegas";
			break;
		case 3:
			cout<<"Sydney";
			break;
		case 4:
			cout<<"Tokyo";
			break;
	}
}

//Print shortest path from source to i using parent array.
void printPath(Graph &g, int parent[],int i)
{
	//The city is the source city.
	if (parent[i] == -1)
	{
		cout << endl;
		cout << "Path: ";
		printCity(i);
		return;
	}
	
	//Repeat the function to print parent's parent city.
	printPath(g, parent, parent[i]);
	
	//Print the name and distance from the previous city.
	cout << " --> ";
	printCity(i);
	cout<<" ("<<g.getDistance(parent[i],i)<<")";
}

//Dijsktra algorithm to find short path for two city.
void Dijsktra(Graph &g)
{
	int x, y, u;
	int dist[5], parent[5];
	bool read[5];
	
	//Print instructions.
	cout << "*******************************************************************************************\n";
	cout << "PA: 1, LO: 2, LV: 3, SY: 4, TO: 5, Cancel: 0" << endl;
	cout << "Enter the starting and destination city of directed edge you want to remove:" << endl;
	cout << "*******************************************************************************************\n";
	
	//Let user select two available cities that are not repeated.	 
	do
	{
		selectTwoCities(x, y);
	}while (x < 1 || x > 5 || y < 1 || y > 5 || x == y);
	

	//Repeat the loop if there is no path to arrive destination city.
	for(dist[y-1] = INT_MAX; dist[y-1] == INT_MAX; g.randomEdge())
	{
		//Reset all array in the function.
		for (int i = 0; i < 5; i++)	
		{
		parent[i] = -1;
		dist[i] = INT_MAX;
		read[i] = false;
		}
		
		//The distance of source city to itself is 0.
		dist[x-1] = 0;
		
		for(int k = 0; k < 4; k++)
		{
			//Pick the minimum distance city from the source city.
			u = minDistance(dist, read);
			
			//Mark the city as processed.
			read[u] = true;
			
			//Update the city minimum distance and parent when the other cities is not yet processed and has an edge between u and v while
			//the total distance from source city to v through u is smaller than current value dist[v].
			for (int v = 0; v < 5; v++)
			{
				if (!read[v] && g.areAdjacent(u, v) && dist[u] != INT_MAX && dist[u]+g.getDistance(u,v) < dist[v])
				{
					parent[v] = u;
					dist[v] = dist[u] + g.getDistance(u,v);
				}
			}
		}
	}
	
	//Print the shortest distance and the shortest path graph.
	cout<<endl<<"Shortest Distance : "<<dist[y-1]<<endl;
	printPath(g, parent, y-1);
}

void printSC(int choice)
{
	switch(choice)
	{
		case 1:
			cout << endl << endl;
			cout << "*******************************************************************************************\n";
			cout << "Original graph is strongly connected!" << endl;
			cout << "*******************************************************************************************\n";
			break;
		case 2:
			cout << endl << endl;
			cout << "*******************************************************************************************\n";
			cout << "Original graph is NOT strongly connected!" << endl;
			cout << "*******************************************************************************************\n";	
			break;
		case 3:
			cout << endl << endl;
			cout << "*******************************************************************************************\n";
			cout << "Modified graph is strongly connected!" << endl;
			cout << "*******************************************************************************************\n";
			break;
		case 4:
			cout << endl << endl;
			cout << "*******************************************************************************************\n";
			cout << "Modified graph is still NOT strongly connected!" << endl;
			cout << "*******************************************************************************************\n";	
			break;
	}
}

int main()
{
	// Initialize a directed and weighted graph g when this program starts up.
	Graph g(5);
	g.resetGraph(); 
	int choice = 0;
	bool cycle, strong;

	// Print the menu of the program. 
	do
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
			 << "(8) End the program\n"
			 << "Choice : ";
		cin >> choice;
		cout<< endl;
		
		switch(choice)
		{
			case 1:
				//To store boolean value of strong connected graph
				strong = g.isStrongConnected();
				
				if(strong == true)
				{
					printSC(1);
				}
				else if(strong == false)
				{
					printSC(2);
					while(strong == false)
					{
						//Auto generate random edge until the graph is strongly connected
						g.randomEdge();
						cout << "After a random edge is generated:" << endl;
   						cout << "Modified Graph:" << endl;
   						cout << "*******************************************************************************************\n";
						//Print modified graph after a random edge is generated
						g.toString();
						cout << "*******************************************************************************************\n";
						//Check whether modified graph is strongly connected
						strong = g.isStrongConnected();
						if(strong == true)
						{
							printSC(3);
						}
						else if(strong == false)
						{
							printSC(4);
						}	
					}
				}
				system("pause");
				system("cls");
				break;
			case 2:
				cycle=g.isCyclic();
				
				if(cycle==true)
				{
					cout << "*******************************************************************************************\n";
        			cout << "Original graph contains cycle\n";
        			cout << "*******************************************************************************************\n";
				}
				
   				else
   				{
   					cout << "*******************************************************************************************\n";
   					cout << "Original graph doesn't contain cycle\n";
   					while(cycle==false)
   					{
   						g.randomEdge();
   						cout << "After a random edge is generated:\n";
   						cout << "Modified Graph:\n";
   						cout << "*******************************************************************************************\n";
						g.toString();
						cout << "*******************************************************************************************\n";
   						cycle=g.isCyclic();
   						if(cycle==true)
        					cout << "Graph contains cycle\n\n";
   						else
   							cout << "Graph still doesn't contain cycle\n\n";
					}		
				}
				system("pause");
				system("cls");	        			
				break;
			case 3:
				system("cls");
				Dijsktra(g);
				cout << endl << endl;
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				//kg add here
				break;
			case 5:
				system("cls");
				g.resetGraph();
				cout << endl;
				cout << "*******************************************************************************************\n";
				cout << "The graph has been reset" << endl;
				cout << "*******************************************************************************************\n";
				break;
			case 6:
				system("cls");
				enterRemoveEdge(g);
				break;
			case 7:
				g.randomEdge();
				break;
			default:
				if(choice == 8)
					cout << endl;
					cout << "*******************************************************************************************\n";
					cout << "Thank you for using this program." << endl;
					cout << "*******************************************************************************************\n";
				break;
		}
	} while (choice != 8);
	
	return 0;
}
