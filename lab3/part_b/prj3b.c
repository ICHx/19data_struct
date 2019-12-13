//
// Created by lenovo on 12/12/2019.
//

#define MAX 10
#define NotAVertex (-1)

#include "prj3b.h"

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
} AlGraph;

//prototypes
node_ptr initNode(int);

AlGraph Create(); //a
void initGraph(AlGraph *newGraph, int vexNum);

void InsertVertex(AlGraph *graph, int); //b
void InsertEdge(AlGraph *graph, int src, int dest); //c
void DeleteVertex(AlGraph *graph, int vex); //d
void DeleteEdge(AlGraph *g, int v1, int v2); //e
bool IsEmpty(AlGraph *g); //f
void Discover(AlGraph *graph, int v, int *visited);

void TopSort_DFS(AlGraph *G, int v);

//

AlGraph Create() {
    AlGraph newGraph = *(AlGraph *) malloc(sizeof(struct graph));
    newGraph.vexNum = 0;
    return newGraph;
}

void initGraph(AlGraph *newGraph, int vexNum) {
    newGraph->vexNum = vexNum;
    for (int i = 0; i < vexNum; ++i) {
        newGraph->AdjList[i] = initNode(i);
    }//headers
}


node_ptr initNode(int vex) {
    node_ptr newNode = (node_ptr) malloc(sizeof(struct node));
    newNode->vertex = vex; //the data
    newNode->link = NULL;
    newNode->inDeg = 0;
    return newNode;
}

void InsertVertex(AlGraph* g, int v) { //insert a new node 'v' to graph
    int current_vex_no = g->vexNum;
    g->vexNum++;
    g->AdjList[current_vex_no] = initNode(v);

}

void InsertEdge(AlGraph *graph, int src, int dest) {
    node_ptr newNode = initNode(dest);
    node_ptr src_path = graph->AdjList[src]; //start with header

    while (src_path->link != NULL) //get to the last node in the list
        src_path = src_path->link;

    src_path->link = newNode;
    graph->AdjList[dest]->inDeg++;
}

void DeleteVertex(AlGraph *graph, int vex) {
    int w;
    node_ptr current_ptr = graph->AdjList[vex]->link;
    node_ptr tmp_ptr;
    while (current_ptr != NULL) {
        w = current_ptr->vertex;
        printf("\nRemoving edge: v%d->v%d", vex, w);
        graph->AdjList[w]->inDeg -= 1;


        current_ptr = current_ptr->link;
        tmp_ptr = current_ptr;
        free(tmp_ptr);
    }
    puts("DeleteVertex done.");
}

AlGraph DeleteEdge(AlGraph g, int v1, int v2) {
    //something
}


bool IsEmpty(AlGraph *g) {
    return g->vexNum == 0;
}

void Discover(AlGraph *graph, int v, int *visited) {
    node_ptr current_ptr = graph->AdjList[v];
    int w;
    if (visited[v] == 0) {
        push(v);
        visited[v] = 1;
    }
    //backtrack :going inside, then horizontal
    while (current_ptr->link != NULL) {
        current_ptr = current_ptr->link;
        w = current_ptr->vertex;//going deeper
        if (visited[w] == 0) {
            push(w); //push for later discover
        }
    }
}

void TopSort_DFS(AlGraph *G, int v) {
    int visited[MAX] = {0};
    int item_in_stack, current_item;

    *buffer_ptr++ = v;
    Discover(G, v, visited); //start from

    while (top > -1) {
        current_item = pop();
        printf("\nnow v=%d", current_item);
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
}

void test_case1(AlGraph *diagram_i) {
    InsertEdge(diagram_i, 0, 1);
    InsertEdge(diagram_i, 0, 3);
    InsertEdge(diagram_i, 2, 1);
    InsertEdge(diagram_i, 2, 5);
    InsertEdge(diagram_i, 4, 0);
    InsertEdge(diagram_i, 4, 1);
    InsertEdge(diagram_i, 5, 4);
}

int main() {
    AlGraph current_diagram = Create();
    IsEmpty(&current_diagram) ? puts("Really empty\n") : puts("Impossible\n");

    initGraph(&current_diagram, 6);
    test_case1(&current_diagram);


    //int v=FindNewVertexOfInDegreeZero();
    //if (v==NotAVertex) exit(3);
    int v = 2;
    TopSort_DFS(&current_diagram, 2);
    puts("\nFinished TopSorting..");
    for (int i = 0; i < current_diagram.vexNum; i++)
        printf("\nfinal buffer=%d", buffer[i]);
    //top sort

    return 0;
}
