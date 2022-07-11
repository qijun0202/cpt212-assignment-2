// Adjacency Matrix representation in C++

#include <iostream>
using namespace std;

class Graph {
   private:
  bool** adjMatrix;
  int numVertices;
  int Distance[5][5] = {{0,1,2,3,4}, {4,5,6,7,8}, {8,9,10,11,12},{11,12,13,14,15},{14,15,16,17,18}};

   public:
  // Initialize the matrix 
  Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new bool*[numVertices];
    for (int i = 0; i < numVertices; i++) {
      adjMatrix[i] = new bool[numVertices];
    }
    resetGraph();
  }

  // Add edges
  void addEdge(int i, int j) {
    adjMatrix[i][j] = true;
  }

  // Remove edges
  void removeEdge(int i, int j) {
    adjMatrix[i][j] = false;
  }
  
  // Get adjMatrix[i][j]
  bool areAdjacent(int i, int j){
  	return adjMatrix[i][j];
  }
  
  // Get Distance[i][j]
  int getDistance(int i, int j){
  	return Distance[i][j];
  }

  // Print the martix
  void toString() {
    for (int i = 0; i < numVertices; i++) {
      cout << i << " : ";
      for (int j = 0; j < numVertices; j++)
        cout << adjMatrix[i][j] << " ";
      cout << "\n";
    }
  }
  
  //Initialise and reset the graph
  void resetGraph() {
  	for (int i = 0; i < numVertices; i++){
  		for (int j = 0; j < numVertices; j++){
  			adjMatrix[i][j] = false;
		  }
	  }
	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(1, 2);
	addEdge(2, 0);
	addEdge(2, 3);
  }

  ~Graph() {
    for (int i = 0; i < numVertices; i++)
      delete[] adjMatrix[i];
    delete[] adjMatrix;
  }
};

int main() {
  Graph g(5);

  g.toString();
}

