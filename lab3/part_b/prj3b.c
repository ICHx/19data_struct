//
// Created by lenovo on 12/12/2019.
//

#define MAX 10 //max number of nodes

#include "prj3b.h"

//linked list def
struct node;
typedef struct node *node_ptr;
typedef struct node {
	char vertex; //the data. of the vertex
	int inDeg; //traversal record
	node_ptr link;
} node;

typedef struct graph {
	node_ptr AdjList[MAX]; //the head nodes
	char listOfVex[MAX]; //store valid vertex
	char emptySlot[MAX]; //store information about empty slots(after deletion)
	char vexNum; /* total number of nodes  (from 0 to max-1)*/
	char vexNumDeleted; //keep track of the number
} AlGraph;

//prototypes
node_ptr initNode(char);

AlGraph Create(); //a
void initGraph(AlGraph *newGraph, char vexNum, char *data);

void InsertVertex(AlGraph *graph, char vex); //b
void InsertEdge(AlGraph *graph, char src, char dest); //c
void DeleteVertex(AlGraph *graph, char vex); //d
void DeleteEdge(AlGraph *graph, char src_v, char dest_v); //e
void DeleteAllOutEdge(AlGraph *graph, char src_v, int src);
bool IsEmpty(AlGraph *g); //f
void Discover(AlGraph *graph, int v_index, int *visited);

void TopSort_DFS(AlGraph *G, char v_index);

//

AlGraph Create() {
	AlGraph newGraph = *(AlGraph *) malloc(sizeof(struct graph));
	newGraph.vexNum = 0;
	newGraph.vexNumDeleted = 0;
	return newGraph;
}

void initGraph(AlGraph *newGraph, char vexNum, char data[]) {
	newGraph->vexNum = vexNum;
	char ch;
	int i;
	for (i = 0; i < vexNum; ++i) {
		ch = data[i];
		newGraph->AdjList[i] = initNode(ch);
		newGraph->listOfVex[i] = ch;
	}
	//headers
	
	newGraph->listOfVex[i] = '\0';
	
}

char findVex(AlGraph *g, char vex) {
	for (char i = 0; i < g->vexNum; i++) {
		if (g->listOfVex[i] == vex) {
			return i;
		}
	}
	return -1; //not found or deleted
}

node_ptr initNode(char vex) {
	node_ptr newNode = (node_ptr) malloc(sizeof(struct node));
	newNode->vertex = vex; //the data
	newNode->link = NULL;
	newNode->inDeg = 0;
	return newNode;
}

void InsertVertex(AlGraph *g, char v) { //insert a new node 'v' to graph
	int current_vex_no = g->vexNum;
	g->vexNum++;
	g->AdjList[current_vex_no] = initNode(v);
	g->listOfVex[current_vex_no] = v;
}

void InsertEdge(AlGraph *graph, char src_v, char dest_v) {
	int src = findVex(graph, src_v);
	int dest = findVex(graph, dest_v);
	
	if (src == dest) { puts("It's a loop"); }
	
	node_ptr newNode = initNode(dest_v);
	node_ptr src_path = graph->AdjList[src]; //start with header
	
	while (src_path->link != NULL) //get to the last node in the list
		src_path = src_path->link;
	
	src_path->link = newNode;
	graph->AdjList[dest]->inDeg++;
}

void DeleteVertex(AlGraph *graph, char vex_V) {
	char vex = findVex(graph, vex_V);
	node_ptr current_ptr, parent_ptr, tmp_ptr;
	
	
	//empty in degree
	char out_vex;
	for (int i = 0; i < graph->vexNum; i++) {
		parent_ptr = graph->AdjList[i];
		current_ptr = graph->AdjList[i]->link;
		out_vex = graph->AdjList[i]->vertex;
		
		while (current_ptr != NULL) {
			if (current_ptr->vertex == vex_V) {
				
				printf("\nRemoving in-edge: v%c->v%c", out_vex, vex_V);
				graph->AdjList[vex]->inDeg -= 1;
				parent_ptr->link = current_ptr->link; //skipping current node
				
				tmp_ptr = current_ptr; //swap and delete
				current_ptr = current_ptr->link;
				free(tmp_ptr);
			} else {
				parent_ptr = current_ptr;
				current_ptr = current_ptr->link;
			}
		}
	}
	
	//empty the adjacency list
	DeleteAllOutEdge(graph, vex_V, vex);
	
	//mark as delete
	graph->listOfVex[vex] = '\0';
	graph->AdjList[vex]->vertex = '\0';
	graph->emptySlot[(graph->vexNumDeleted)++] = vex;
	
	puts("\nDeleteVertex done.\n");
}

void DeleteEdge(AlGraph *graph, char src_v, char dest_v) {
	int src = findVex(graph, src_v);
	int dest = findVex(graph, dest_v);
	node_ptr current_ptr, tmp_ptr;
	bool notFound = 1;
	
	tmp_ptr = graph->AdjList[src];
	current_ptr = graph->AdjList[src]->link;
	while (current_ptr != NULL) {
		
		if (current_ptr->vertex == dest_v) {
			printf("\nRemoving out-edge: v%c->v%c\n", src_v, dest_v);
			graph->AdjList[dest]->inDeg -= 1;
			
			tmp_ptr->link = current_ptr->link;
			free(current_ptr);
			
			notFound = 0;
			break;
		}
		
		tmp_ptr = current_ptr; //store previous pointer
		current_ptr = current_ptr->link; //move to next node
	}
	
	if (notFound) puts("E: edge not found.");
	//something
}

void DeleteAllOutEdge(AlGraph *graph, char src_v, int src) {
	int dest;
	char dest_v;
	node_ptr current_ptr, parent_ptr, tmp_ptr;
	
	parent_ptr = graph->AdjList[src];
	current_ptr = graph->AdjList[src]->link;
	while (current_ptr != NULL) {
		dest_v = current_ptr->vertex;
		dest = findVex(graph, dest_v);
		printf("\nRemoving out-edge: v%c->v%c\n", src_v, dest_v);
		graph->AdjList[dest]->inDeg -= 1;
		
		tmp_ptr = current_ptr;
		current_ptr = current_ptr->link; //move to next node
		free(tmp_ptr); //free the previous node
		parent_ptr->link = current_ptr; //update link pointer
	}
	
	//something
}

bool IsEmpty(AlGraph *g) {
	int test = (g->vexNum) - (g->vexNumDeleted);
	if (test == 0) return 1;
	else printf("No, There are %d vertices.", test);
	return 0;
}

void Discover(AlGraph *graph, int v_index, int *visited) {
	node_ptr current_ptr = graph->AdjList[v_index];
	char w; //the data of vertex
	int w_index;
	
	if (visited[v_index] == 0) {
		push(v_index);
		visited[v_index] = 1;
	}
	//backtrack :going inside, then horizontal
	while (current_ptr->link != NULL) {
		current_ptr = current_ptr->link;
		w = current_ptr->vertex;//going deeper
		w_index = findVex(graph, w);
		if (visited[w_index] == 0) {
			push(w_index); //push for later discover
		}
	}
}

void TopSort_DFS(AlGraph *G, char v_index) {
	int visited[MAX] = {0};
	int item_in_stack, current_item;
	char *buffer_ptr = buffer;
	*buffer_ptr++ = v_index;
	Discover(G, v_index, visited); //start from
	
	while (top > -1) {
		current_item = pop();
		printf("\nnow v_index=%d", current_item);
//        for (int j = 0; j <= top; j++) {
//            printf("\nnow stack=%d", stack[j]);
//        }
		puts("\n====");
		
		if (top != -1) { //more than one in stack, compare
			item_in_stack = stack[top];
			
			if ((G->AdjList[current_item]->inDeg > G->AdjList[item_in_stack]->inDeg)) {//exchange pos according to inDeg
				pop();
				push(current_item);
				current_item = item_in_stack;
			}
		}
		
		if (!visited[current_item]) {
			*buffer_ptr++ = current_item;
			Discover(G, current_item, visited);
		}
	}
	top = -1; //reset stack
	*buffer_ptr++ = -1; //mark end
}

void test_case1(AlGraph *diagram_i) {
	
	char sequence[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
	initGraph(diagram_i, 6, sequence);
	
	
	InsertEdge(diagram_i, 'A', 'B');
	InsertEdge(diagram_i, 'A', 'D');
	InsertEdge(diagram_i, 'C', 'B');
	InsertEdge(diagram_i, 'C', 'F');
	InsertEdge(diagram_i, 'E', 'A');
	InsertEdge(diagram_i, 'E', 'B');
	InsertEdge(diagram_i, 'F', 'E');
	
	
	
	//insert an edge
	InsertVertex(diagram_i, 'Z');
	IsEmpty(diagram_i);
	
	//test add edge
	InsertEdge(diagram_i, 'F', 'Z');
	//del an edge
	DeleteEdge(diagram_i, 'F', 'Z');
	
	//del a vertex
	DeleteVertex(diagram_i, 'Z');
	IsEmpty(diagram_i);
	
	
}

int main() {
	AlGraph current_diagram = Create();
	IsEmpty(&current_diagram) ? puts("Really empty\n") : puts("Impossible\n");
	
	
	test_case1(&current_diagram);
	
	
	
	
	
	//int v=FindNewVertexOfInDegreeZero();
	//if (v==NotAVertex) exit(3);
	int v = 2, current_v, real_vex_num;
	TopSort_DFS(&current_diagram, v);
	puts("\nFinished TopSorting..");
	printf("\nOrder=");
	
	real_vex_num = current_diagram.vexNum - current_diagram.vexNumDeleted;
	for (int i = 0; i < real_vex_num; i++)
		if ((current_v = buffer[i]) >= 0)
			
			printf("%c", current_diagram.AdjList[current_v]->vertex);
	//top sort
	
	return 0;
}
