//
// Created by lenovo on 2019-10-07.
//

#ifndef DATASTRUCT_PRJ3_H
#define DATASTRUCT_PRJ3_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#endif //DATASTRUCT_PRJ3_H

#define SIZE 60

typedef struct node {
	char data;
	struct node *lchild, *rchild;
} BinTNode;    //define the data type of the node

typedef BinTNode *BinTree;
typedef struct node *node_ptr;

enum visited {
	none = 0b0, left = 0b10, both = 0b11
};

BinTree newNode();
BinTree newNode() {
	BinTree L;
//    L = (node_ptr) malloc(sizeof(struct node));
	L = (BinTNode *) malloc(sizeof(BinTNode)); /*create a node*/
	
	if (L == NULL) {
		puts("ERROR: OOM");
		exit(-1);
	}
	L->lchild = NULL;
	L->rchild = NULL;
	enum visited;
	return L;
}

node_ptr stack[SIZE];
int top = -1;

/* define push operation */

void push(node_ptr item) {
	if (top >= SIZE - 1) {
		printf("\nStack Overflow.");
	} else {
		top = top + 1;
		stack[top] = item;
	}
}

/* define pop operation */
node_ptr pop() {
	node_ptr item;
	
	if (top < 0) {
		printf("stack under flow: invalid infix expression");
		getchar();
		/* underflow may occur for invalid expression */
		/* where ( and ) are not matched */
		exit(1);
	} else {
		item = stack[top];
		top = top - 1;
		return (item);
	}
}