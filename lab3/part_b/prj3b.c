//
// Created by lenovo on 12/12/2019.
//

#include "prj3b.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10
#define NotAVertex (-1)

//linked list def
struct node;
typedef struct node *node_ptr;
typedef struct node {
	int vertex; //the no. of the vertex
	char known; //traversal record
	char processed; //traversal record
	int inDeg; //traversal record
	node_ptr link;
} node;

typedef struct graph {
	int vexNum; /* total number of nodes  (from 0 to max-1)*/
	node_ptr AdjList[MAX]; //the head nodes
} ALGraph;

node_ptr initNode(int vex) {
	node_ptr newNode = (node_ptr) malloc(sizeof(struct node));
	newNode->vertex = vex;
	newNode->link = NULL;
	newNode->known = 0;
	newNode->inDeg = 0;
	newNode->processed = 0;
	
	return newNode;
}

ALGraph *Create() {
	ALGraph *newGraph = *(ALGraph *) malloc(sizeof(struct graph));
	return newGraph;
}

ALGraph *initGraph(ALGraph *newGraph, int vexNum) {
	newGraph->vexNum = vexNum;
	int i;
	for (i = 0; i < vexNum; ++i) {
		newGraph->AdjList[i] = initNode(i);
	}//headers
	return newGraph;
}

void InsertEdge(ALGraph *graph, int src, int dest) {
	node_ptr newNode = initNode(dest);
	node_ptr src_path = graph->AdjList[src]; //start with header
	
	while (src_path->link != NULL) //get to the last node in the list
		src_path = src_path->link;
	
	src_path->link = newNode;
	graph->AdjList[dest]->inDeg++;
}

void test_case1(ALGraph *diagram_i) {
	InsertEdge(diagram_i, 0, 1);
	InsertEdge(diagram_i, 0, 3);
	InsertEdge(diagram_i, 2, 1);
	InsertEdge(diagram_i, 2, 5);
	InsertEdge(diagram_i, 4, 0);
	InsertEdge(diagram_i, 4, 1);
	InsertEdge(diagram_i, 5, 4);
}

//void removeVexFromGraph(ALGraph *G,int vex){
//	int w;
//	node_ptr current_ptr = G->AdjList[vex]->link;
//	node_ptr tmp_ptr;
//	while(current_ptr!=NULL){
//		w=current_ptr->vertex;
//		printf("\nRemoving edge: v%d->v%d",vex,w);
//		G->AdjList[w]->inDeg-=1;
//
//
//		current_ptr=current_ptr->link;
//		tmp_ptr=current_ptr;
//		free (tmp_ptr);
//	}
//	puts("removeVexFromGraph done.");
//}

void RecursiveDiscover(ALGraph *G, int v, int *visited) {
	node_ptr current_ptr = G->AdjList[v];
	int w;
	if (visited[v] == 0) push(v);
	
	visited[v] = 1;
	//backtrack :going inside, then horizontal
	while (current_ptr->link != NULL) {
		current_ptr = current_ptr->link;
		w = current_ptr->vertex;//going deeper
		
		if (visited[w] == 0) {
			push(w);
		}
	}
}

void DFS(ALGraph *G, int v) {
	int visited[MAX] = {0};
	int item_stacked, item_last;
//	char forked;
	
	*buffer_ptr++ = v;
	RecursiveDiscover(G, v, visited); //start from
	
	for (int i = 0; i <= top; i++) {
		item_last = pop();
		printf("\nnow v=%d", item_last);
		for (int i = 0; i <= top; i++) {
			printf("\nnow stack=%d", stack[i]);
		}
		puts("\n====");
		
		
		if (top > -1) { //more than one
			item_stacked = stack[top];
			
			if ((G->AdjList[item_last]->inDeg >
			     G->AdjList[item_stacked]->inDeg)) {//switch pos of forks according to inDeg
				pop();
				push(item_last);
				item_last = item_stacked;
			}
		}
		*buffer_ptr++ = item_last;
		
		if (!visited[item_last]) {
			RecursiveDiscover(G, item_last, visited);
		}
	}
	
	
}

int main() {
	ALGraph *current_diagram = Create();
	initGraph(current_diagram, 6);
	test_case1(current_diagram);
	//int v=FindNewVertexOfInDegreeZero();
	//if (v==NotAVertex) exit(3);
	int v = 2;
	DFS(current_diagram, 2);
	
	puts("\nFinished TopSorting..");
	for (int i = 0; i < current_diagram->vexNum; i++)
		printf("\nfinal buffer=%d", buffer[i]);
	getchar();
	return 0;
}