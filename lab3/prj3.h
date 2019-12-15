//
// Created by lenovo on 2019-10-07.
//

#ifndef DATASTRUCT_PRJ3_H
#define DATASTRUCT_PRJ3_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#endif //DATASTRUCT_PRJ3_H

typedef struct node {
	char data;
	char visited; // 0=none, 1=left, 2=right
	struct node *lchild, *rchild;
} BinTNode;    //define the data type of the node
typedef BinTNode *BinTree;

typedef struct node *node_ptr;

BinTree newNode();
BinTree newNode() {
	BinTree L;
	L = (BinTNode *) malloc(sizeof(BinTNode));
	if (L == NULL) {
		puts("ERROR: OOM");
		exit(-1);
	}
	L->lchild = NULL;
	L->rchild = NULL;
	L->visited = 0;
	return L;
}
node_ptr stack[SIZE];
int top = -1;
void push(node_ptr item) {
	if (top >= SIZE - 1) {
		printf("\nE: Stack overflow.");
	} else {
		top = top + 1;
		stack[top] = item;
	}
}
node_ptr pop() {
	node_ptr item;
	if (top < 0) {
		printf("E: Stack under flow");
		getchar();
		exit(1);
	} else {
		item = stack[top];
		top = top - 1;
		return (item);
	}
}
