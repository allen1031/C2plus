// Data_Struct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#define QUEUE_SIZE 10; //define the length of the working queue
#define NUM_NODE 7; // define the num of nodes in the graph

/****************************************FIFO Queue Definition*************************************************/
typedef struct {

	int head;
	int tail;
	int *myqueue;
	int size;

} myQueue;
bool myQueueIsEmpty(myQueue* obj);
bool myQueueIsFull(myQueue* obj);
/** Initialize your data structure here. Set the size of the queue to be k. */
myQueue* myQueueCreate(int k) {
	myQueue* queue = (myQueue*)malloc(sizeof(myQueue));
	queue->myqueue = (int*)malloc(k * sizeof(int));
	for (int i = 0; i<k; i++) {
		queue->myqueue[i] = -1;
	}
	queue->size = k;
	queue->head = queue->tail = 0;
	return queue;
}

/** Insert an element into the queue. Return true if the operation is successful. */
bool myQueueEnQueue(myQueue* obj, int value) {
	if (myQueueIsFull(obj)) {
		printf("the queue is full\n");
		return false;
	}
	else if (myQueueIsEmpty(obj)) {
		obj->myqueue[obj->tail] = value;
		printf("the queue is empty\n");
		return true;
	}
	else {
		obj->tail = obj->tail + 1;
		if (obj->tail == obj->size) {
			obj->tail = 0;
		}
		obj->myqueue[obj->tail] = value;
		return true;
	}
}


/** Delete an element from the queue. Return true if the operation is successful. */
bool myQueueDeQueue(myQueue* obj) {
	if (!myQueueIsEmpty(obj)) {
		obj->myqueue[obj->head] = -1;
		if (!(obj->head == obj->tail)) {
			obj->head = obj->head + 1;
			if (obj->head == obj->size) {
				obj->head = 0;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

/** Get the front item from the queue. */
int myQueueFront(myQueue* obj) {
	if (myQueueIsEmpty(obj)) {
		return -1;
	}
	else {
		return obj->myqueue[obj->head];
	}
}

/** Get the last item from the queue. */
int myQueueRear(myQueue* obj) {
	if (myQueueIsEmpty(obj)) {
		return -1;
	}
	else {
		return obj->myqueue[obj->tail];
	}
}

/** Checks whether the queue is empty or not. */
bool myQueueIsEmpty(myQueue* obj) {

	if ((obj->tail == obj->head) && obj->myqueue[obj->head] == -1) {
		return true;
	}
	else {
		return false;
	}
}

/** Checks whether the queue is full or not. */
bool myQueueIsFull(myQueue* obj) {
	if (obj->tail + 1 == obj->head || (obj->head == 0 && obj->tail == obj->size - 1)) {
		return true;
	}
	else {
		return false;
	}
}

/** Free the dynamic memory. */
void myQueueFree(myQueue* obj) {
	free(obj->myqueue);
	free(obj);
}

/** Get current number of items in the queue */
int getNumOfItemsFromQueue(myQueue* obj) {
	int size = 0;
	if (myQueueIsEmpty(obj)) {
		size = 0;
	}
	else if (myQueueIsFull(obj)) {
		size = obj->size;
	}else if (obj->tail >= obj->head) {
		size = obj->tail - obj->head + 1;
	}
	else {
		size = obj->size - (obj->head - obj->tail) + 1;
	}
	return size;
}

/** Print out the queue */
void printQueue(myQueue* obj) {

	int i = obj->head;
	while (i != obj->tail) {
		printf("%d->", obj->myqueue[i]);
		i++;
	}
	printf("%d\n", obj->myqueue[obj->tail]);
}


/****************************Graph Definition**********************************************/

typedef struct Node {
	int val;
	struct Node* next;
}Node;

typedef struct
{
	int num_members;
	Node *head;
}NeighborNodeList;

typedef struct {

	int num_nodes;
	NeighborNodeList* neighbor_nodes_list;
	int num_edges;
}Graph;

int doesEdgeExist(Graph *graph, int src, int dest);
/** Create a new node */
Node* createNewNode(int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return NULL;
	}
	newNode->val = value;
	newNode->next = NULL;
	return newNode;
}
/** Create a new graph */
Graph *createGraph(int num_nodes)
{
	int i;

	Graph *graph = (Graph*)malloc(sizeof(Graph));

	if (graph == NULL)
	{
		return NULL;
	}

	graph->num_nodes = num_nodes;

	graph->neighbor_nodes_list = (NeighborNodeList *)malloc(num_nodes * sizeof(NeighborNodeList));

	if (graph->neighbor_nodes_list == NULL)
	{
		free(graph);
		return NULL;
	}

	for (i = 0; i < num_nodes; i++)
	{
		graph->neighbor_nodes_list[i].head = NULL;
		graph->neighbor_nodes_list[i].num_members = 0;
	}

	return graph;
}
/** delete the created graph */
void deleteGraph(Graph *graph)
{
	if (graph != NULL)
	{
		if (graph->neighbor_nodes_list != NULL)
		{
			int node_id;

			for (node_id = 0; node_id < graph->num_nodes; node_id++)
			{
				Node *listIterator = graph->neighbor_nodes_list[node_id].head;

				while (listIterator != NULL)
				{
					Node *temp = listIterator;
					listIterator = listIterator->next;
					free(temp);
				}
			}

			free(graph->neighbor_nodes_list);
		}

		free(graph);
	}
}
/** Add edge to the graph */
void addEdge(Graph *graph, int src, int dest)
{
	if ((src >= graph->num_nodes || src  < 0) || (dest >= graph->num_nodes || dest < 0))
		return;

	if (doesEdgeExist(graph, src, dest))
		return;

	
	Node *newNode = createNewNode(dest);

	if (newNode != NULL)
	{
		//newNode1->next = newNode;
		newNode->next = graph->neighbor_nodes_list[src].head;
		graph->neighbor_nodes_list[src].head = newNode;
		graph->neighbor_nodes_list[src].num_members++;
		graph->num_edges++;

	}
}
/** Check if the edge already exists on the graph*/
int doesEdgeExist(Graph *graph, int src, int dest)
{
	Node *srcPointer = graph->neighbor_nodes_list[src].head;

	while (srcPointer != NULL)
	{
		if (srcPointer->val == dest)
		{
			return 1;
		}
		else
			srcPointer = srcPointer->next;
	}

	return 0;
}
/** Display the graph */
void displayGraph(Graph *graph)
{
	int node_id;

	for (node_id = 0; node_id < graph->num_nodes; node_id++)
	{
		Node *listIterator = graph->neighbor_nodes_list[node_id].head;

		printf("Node %d is adjacent to ", node_id);

		while (listIterator != NULL)
		{
			printf("%d->", listIterator->val);
			listIterator = listIterator->next;
		}

		printf("NULL\n");
	}
}



/****************************************************Breadth First Search(BFS)***************************************************************/


int BFS(Graph* graph, int root, int target) {
	int size = QUEUE_SIZE;
	int step = 0; // number of steps from root to the current node.
	myQueue* searchQueue = myQueueCreate(size); // queue to store the processing node.
	myQueueEnQueue(searchQueue, root);

	
	while (!myQueueIsEmpty(searchQueue)) {
		step = step + 1;
		//iteration to find the targe node

		int num_nodes = getNumOfItemsFromQueue(searchQueue);
		printf("step %d and there is %d in the queue\n", step, num_nodes);
		for (int i = 0; i < num_nodes; ++i) {
			int cur = myQueueFront(searchQueue);
			if (cur == -1) {
				printf("error happens in step\n");
				return step;
			}
			printQueue(searchQueue);
			if (cur == target) {
				printf("find the target node: %d\n",cur);
				return step;
			}
			else {
				Node *listIterator = graph->neighbor_nodes_list[cur].head;
				while (listIterator != NULL)
				{
					myQueueEnQueue(searchQueue, listIterator->val);
					//printf("%d->", listIterator->val);
					listIterator = listIterator->next;
				}

			}
			//printQueue(searchQueue);
			myQueueDeQueue(searchQueue);
			printQueue(searchQueue);
		}

	}

	return -1;

}

int main() {

	Graph *myGraph = createGraph(7);

	if (myGraph == NULL)
	{
		printf("Memory Allocation Error.");
		exit(EXIT_FAILURE);
	}

	addEdge(myGraph, 0, 1);
	addEdge(myGraph, 0, 2);
	addEdge(myGraph, 0, 3);
	addEdge(myGraph, 1, 4);
	addEdge(myGraph, 2, 4);
	addEdge(myGraph, 2, 5);
	addEdge(myGraph, 3, 6);
	addEdge(myGraph, 5, 6);

	displayGraph(myGraph);

	
	printf("We find the number of steps to get our target");
	BFS(myGraph, 0, 6);

	while (1);
	deleteGraph(myGraph);
	
	return 0;


}