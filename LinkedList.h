#include <iostream>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;

class ListNode
{
	public:
		int weight;           // Node represents the weight/distance of edge.
		int start;      	  // Node represents the starting vertex.
		int dest; 	          // Node represents the destination vertex.
		int vertex;           // Node represents the vertex.
		ListNode *next;       // Pointer to the next node.
		
		// Constructor
		ListNode (int distance, int startVertex, int destVertex)
			{ weight = distance; start = startVertex; dest = destVertex; next = NULL; }
		ListNode (int cityVertex)
			{ vertex = cityVertex; next = NULL; }
};

// The class LinkedList arrange the nodes value in ascending order.
class LinkedList
{
	public:
		ListNode *head;  // head pointer.
		
	public:
		LinkedList()           // Constructor.
			{ head = NULL; }
		~LinkedList();         // Destructor.

		// Linked list operations.
		void insertNode(int);             // to insert node (for storing cluster member).
		void insertNode(int, int, int);   // to insert node (arrange weight in ascending order).
		void removeMin(int&, int&, int&); // to remove and return the minimum node.
		void convertArray(int[], int);    // put every vertex in the cluster into the array.
		void clearList();
		int getHeadVertex()               // return the value in head node of cluster list.
			{ return head->vertex; }
		int getNumNodes();                // return the number of nodes in the list.
};
#endif

void LinkedList::insertNode(int cityVertex)
{
	ListNode *newNode;             // To point to a new node.
	ListNode *nodePtr;             // To traverse the list.
	ListNode *previousNode = NULL; // The previous node.
	
	newNode = new ListNode(cityVertex);    // Allocate a new node to store new weight.
	
	// If there are no nodes in the list, make newNode the first node.
	if(!head)
	{
		head = newNode;
		newNode->next = NULL;
	}
	else  // Otherwise, insert newNode in ascending order.
	{
		
		nodePtr = head;      // Position nodePtr at the head of list.
		previousNode = NULL; // Initialize previousNode to nullptr.
		
		// Skip all nodes whose vertex is less than cityVertex.
		while (nodePtr != NULL && nodePtr->vertex < cityVertex )
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		
		// If the new node is to be the 1st in the list, insert it before all other nodes.
		if (previousNode == NULL)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else  // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

void LinkedList::insertNode(int newWeight, int start, int dest)
{
	ListNode *newNode;             // To point to a new node.
	ListNode *nodePtr;             // To traverse the list.
	ListNode *previousNode = NULL; // The previous node.
	
	newNode = new ListNode(newWeight, start, dest);    // Allocate a new node to store new weight.
	
	// If there are no nodes in the list, make newNode the first node.
	if(!head)
	{
		head = newNode;
		newNode->next = NULL;
	}
	else  // Otherwise, insert newNode in ascending order.
	{
		
		nodePtr = head;      // Position nodePtr at the head of list.
		previousNode = NULL; // Initialize previousNode to nullptr.
		
		// Skip all nodes whose weight is less than newWeight.
		while (nodePtr != NULL && nodePtr->weight < newWeight )
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		
		// If the new node is to be the 1st in the list, insert it before all other nodes.
		if (previousNode == NULL)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else  // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

void LinkedList::removeMin(int &weight, int &start, int &dest)
{
	ListNode *nodePtr;       // To traverse the list.
	ListNode *previousNode;  // To point to the previous node.
	
	// If the list is empty, do nothing.
	if (!head)
		return;
	
	// Remove and return the first node with minimum weight.
	nodePtr = head->next;
	
	// The deleted weight, starting vertex and destination vertes is passed by reference.
	weight = head->weight;
	start = head->start;
	dest = head->dest;
	
	delete head;   // Delete the head which possess the minimum weight.
	head = nodePtr;
}

void LinkedList::convertArray(int arr[], int num)
{
	ListNode *nodePtr; // To traverse the list.
	nodePtr = head;
	arr[num];
	
	for(int i = 0; nodePtr != NULL; i++)
	{
		arr[i] = nodePtr->vertex;
		nodePtr = nodePtr->next;
	}
}

int LinkedList::getNumNodes()
{
	ListNode *nodePtr; // To traverse the list.
	nodePtr = head;
	
	int num = 0;
	while(nodePtr != NULL)
	{
		num++;
		nodePtr = nodePtr->next;
	}
	return num;
}

void LinkedList::clearList()
{
	ListNode *nodePtr;    // To traverse the list.
	ListNode *nextNode;   // To point to the next node.
	
	// Position nodePtr at the head of the list.
	nodePtr = head;
	
	// While nodePtr is not at the end of the list.
	while(nodePtr != NULL)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;
		
		// Delete the current node.
		delete nodePtr;
		
		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
	head = NULL;
}

LinkedList::~LinkedList()
{
	ListNode *nodePtr;    // To traverse the list.
	ListNode *nextNode;   // To point to the next node.
	
	// Position nodePtr at the head of the list.
	nodePtr = head;
	
	// While nodePtr is not at the end of the list.
	while(nodePtr != NULL)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;
		
		// Delete the current node.
		delete nodePtr;
		
		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
	head = NULL;
}
