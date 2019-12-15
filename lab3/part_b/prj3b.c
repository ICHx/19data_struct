//
// Created by lenovo on 12/12/2019.
//

#define MAX 20 //max number of nodes
#define DEBUG 0

#include "prj3b.h"

#define NotAVertex (-1)

//linked list def
struct node;
typedef struct node *node_ptr;
typedef struct node {
	char vertex; //the data. of the vertex
	char inDeg; //traversal record
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
void initGraph(AlGraph *newGraph, char vexNum, const char *data);

void InsertVertex(AlGraph *graph, char vex); //b
void InsertEdge(AlGraph *graph, char src, char dest); //c
void DeleteVertex(AlGraph *graph, char vex); //d
void DeleteEdge(AlGraph *graph, char src_v, char dest_v); //e
void DeleteAllOutEdge(AlGraph *graph, char src_v, int src);
bool IsEmpty(AlGraph *g); //f
void TopSort_Payload(AlGraph *graph, int v_index, int *visited);
void TopSort_DFS(AlGraph *G);
char FindNewVertexOfInDegreeZero(AlGraph *graph);

//

AlGraph Create() {
	AlGraph newGraph = *(AlGraph *) malloc(sizeof(struct graph));
	newGraph.vexNum = 0;
	newGraph.vexNumDeleted = 0;
	return newGraph;
}

void initGraph(AlGraph *newGraph, char vexNum, const char data[]) {
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
	else printf("Not empty, There are %d vertices.", test);
	return 0;
}

void TopSort_DFS(AlGraph *G) {
	int visited[MAX] = {0};
	
	int test;
	test = FindNewVertexOfInDegreeZero(G);
	if (test == NotAVertex) {
		puts("E: No element with 0 in-deg, loop exist");
		exit(3);
	}
	
	for (int i = 0; i < G->vexNum; i++) {
		if (!(visited[i]) && (G->listOfVex[i] != '\0')) { //skip deleted cells too
			TopSort_Payload(G, i, visited);
		}
	}
	
	//print result
	int current_v;
	puts("TopSorting..");
	printf("Order=");
	
	while (top > -1) {
		current_v = pop();
		printf("%c", G->AdjList[current_v]->vertex);
	}
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
	
	//insert a vex
	puts("add vZ");
	InsertVertex(diagram_i, 'Z');
	IsEmpty(diagram_i);
	
	//test add edge
	puts("add F->Z");
	InsertEdge(diagram_i, 'F', 'Z');
	
	//view sort
	TopSort_DFS(diagram_i);
	
	//del an edge
	puts("\ndel E->B");
	puts("del E->A");
	DeleteEdge(diagram_i, 'E', 'B');
	DeleteEdge(diagram_i, 'E', 'A');
	
	//view sort again
	TopSort_DFS(diagram_i);
	
	//del a vertex
	puts("\ndel vZ");
	DeleteVertex(diagram_i, 'Z');
	IsEmpty(diagram_i);
	
	//view sort again
	TopSort_DFS(diagram_i);
}

void input_case(AlGraph *g) {
	char vertex_string[MAX * 2];
	char edge_string[MAX * 10];
	char vertex[MAX];
	char count = 0;
	
	//get vertex - process string
	char *token;
	const char delimiter[2] = " ";
	puts("\nPlease enter vertices separated by ONE space, only use alphabets!");
	gets(vertex_string); //assumed correct format
	token = strtok(vertex_string, delimiter);
	while (token != NULL) {
		vertex[count++] = *token;
		token = strtok(NULL, delimiter);
	}
	vertex[count] = '\0'; //mark end of array sequence
	initGraph(g, count, vertex);// vertex - inserting
	
	// edges
	char current_c, a, b;
	count = 0; //reset count
	puts("\nPlease enter directional edges separated by ONE comma, end with zero."
	     "\nlike AB,CD0 for A->B and C->D");
	gets(edge_string);  //assume all entered vertices are valid
	count = (char) strlen(edge_string);
	if (edge_string[count - 1] != '0') {
		puts("E: No end for input for edges");
		exit(5);
	}
	
	count = 0; //reset count
	while ((current_c = edge_string[count++]) != '0') {
		
		while (current_c == ',')
			current_c = edge_string[count++]; //skip comma
		
		a = current_c;
		current_c = edge_string[count++];
		b = current_c;
		if ((a + b) < 190) { //either a or b is non-alphabet,probably some symbol is tucked here
			puts("E: singular input for edge");
			exit(6);
		}
		InsertEdge(g, a, b);
		
	}
	
	TopSort_DFS(g);
}

char FindNewVertexOfInDegreeZero(AlGraph *graph) {
	char index, i;
	for (i = 0; i < graph->vexNum; i++) {
		index = graph->AdjList[i]->inDeg;
		if (!index) return i; //index==0
	}
	return -1;
}
void TopSort_Payload(AlGraph *graph, int v_index, int *visited) {
	visited[v_index] = 1;
	char next_vex;
	node_ptr current_ptr, tmp_ptr, prev_ptr;
	
	current_ptr = graph->AdjList[v_index]->link;
	while (current_ptr != NULL) {
		next_vex = findVex(graph, current_ptr->vertex);
		if (!visited[next_vex])
			TopSort_Payload(graph, next_vex, visited);
		
		current_ptr = current_ptr->link;
	}
	push(v_index);
}

int main() {
	AlGraph current_diagram = Create();
	IsEmpty(&current_diagram) ? puts("Really empty\n") : puts("Impossible\n");

	test_case1(&current_diagram);
//	input_case(&current_diagram);
	return 0;
}
