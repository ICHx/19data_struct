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
    char vertex; //the data. of the vertex
    int inDeg; //traversal record
    node_ptr link;
} node;

typedef struct graph {
    int vexNum; /* total number of nodes  (from 0 to max-1)*/
    node_ptr AdjList[MAX]; //the head nodes
    char listOfVex[MAX];
} AlGraph;

//prototypes
node_ptr initNode(char);

AlGraph Create(); //a
void initGraph(AlGraph *newGraph, int vexNum, char *data);

void InsertVertex(AlGraph *graph, char vex); //b
void InsertEdge(AlGraph *graph, char src, char dest); //c
void DeleteVertex(AlGraph *graph, char vex); //d
void DeleteEdge(AlGraph *g, char v1, char v2); //e
bool IsEmpty(AlGraph *g); //f
void Discover(AlGraph *graph, int v, int *visited);

void TopSort_DFS(AlGraph *G, int v);

//

AlGraph Create() {
    AlGraph newGraph = *(AlGraph *) malloc(sizeof(struct graph));
    newGraph.vexNum = 0;
    return newGraph;
}

void initGraph(AlGraph *newGraph, int vexNum, char data[]) {
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

int findVex(AlGraph *g, char vex) {
    for (int i = 0; i < g->vexNum; i++) {
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

    node_ptr newNode = initNode(dest);
    node_ptr src_path = graph->AdjList[src]; //start with header

    while (src_path->link != NULL) //get to the last node in the list
        src_path = src_path->link;

    src_path->link = newNode;
    graph->AdjList[dest]->inDeg++;
}


void DeleteVertex(AlGraph *graph, char vex_V) {
    int vex = findVex(graph, vex_V);
    int current_vex;
    char w;
    node_ptr current_ptr, tmp_ptr;


    //empty in degree
    for (int i = 0; i < graph->vexNum; i++) {
        current_ptr = graph->AdjList[i]->link;
        current_vex = graph->AdjList[i]->vertex;

        while (current_ptr != NULL) {
            if (current_ptr->vertex == current_vex) {
                w = current_ptr->vertex;
                printf("\nRemoving in-edge: v%c->v%c", vex_V, w);
                graph->AdjList[w]->inDeg -= 1;
                current_ptr = current_ptr->link;
                tmp_ptr = current_ptr;
                free(tmp_ptr);
            }
        }
    }

    //empty the adjacency list
    current_ptr = graph->AdjList[vex]->link;
    while (current_ptr != NULL) {
        w = current_ptr->vertex;
        printf("\nRemoving out-edge: v%d->v%d", vex, w);
        graph->AdjList[w]->inDeg -= 1;

        current_ptr = current_ptr->link;
        tmp_ptr = current_ptr;
        free(tmp_ptr);
    }


    puts("DeleteVertex done.");
}

void DeleteEdge(AlGraph *g, char v1, char v2) {
    //something
    return;
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
//test add edge
    InsertEdge(diagram_i, 'F', 'Z');
//del a vertex
    DeleteVertex(diagram_i, 'C');
//del an edge
    DeleteEdge(diagram_i,'F','E');



}

int main() {
    AlGraph current_diagram = Create();
    IsEmpty(&current_diagram) ? puts("Really empty\n") : puts("Impossible\n");


    test_case1(&current_diagram);





    //int v=FindNewVertexOfInDegreeZero();
    //if (v==NotAVertex) exit(3);
    int v = 2;
    TopSort_DFS(&current_diagram, v);
    puts("\nFinished TopSorting..");
    for (int i = 0; i < current_diagram.vexNum; i++)
        printf("\nfinal buffer=%d", buffer[i]);
    //top sort

    return 0;
}
