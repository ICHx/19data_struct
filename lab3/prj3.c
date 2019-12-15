//
// Created by lenovo on 12/12/2019.
//
#include <stdio.h>
#include <stdlib.h>

#define SIZE 60
#include "prj3.h"


int xHeight = 0;
BinTree CreatBinTree2(char *);
void BFS(BinTree, int);
void RecordHeight(int record);

BinTree CreatBinTree2(char *string1) {
	int length = (int) strlen(string1);
	if (length > SIZE) {
		puts("E: Exceeds vertex limits.\n");
		exit(-1);
	}
	char ch = 0;
	BinTree T = newNode();
	
	node_ptr current_ptr = T; //root node
	node_ptr parent_ptr = T;
	node_ptr new_ptr;
	
	ch = string1[0];
	parent_ptr->data = ch;
//	push(parent_ptr);
	
	for (int i = 1; i < length; i++) {
		
		ch = string1[i];
		if (ch == '*') { //if null, do not go deeper

//			current_ptr = parent_ptr; //????
			
			switch (current_ptr->visited) { //not going deeper
				case 0:
					current_ptr->visited += 1;
					break;
				case 1:
					current_ptr->visited = 2;
					if (i != (length - 1)) {//dont backtrack anymore if is last
						do {
							parent_ptr = pop();
							current_ptr = parent_ptr;  //backtrack until there
						} while (current_ptr->visited == 2);
					}
					break;
				case 2:
					do {
						parent_ptr = pop();
						current_ptr = parent_ptr;  //backtrack until there
					} while (current_ptr->visited == 2);
					break;
				default:
					puts("Impossible?\n");
			}
			continue;
		}
		
		if ((current_ptr->visited) != 2) {
			new_ptr = newNode(); /*create a node*/
			new_ptr->data = ch;
		}
		switch (current_ptr->visited) { //going deeper
			case 2:
				do {
					parent_ptr = pop();
					current_ptr = parent_ptr;  //backtrack until there
				} while (current_ptr->visited == 2);
				break;
			case 0:
				parent_ptr = current_ptr;
				push(parent_ptr);
				current_ptr->lchild = new_ptr;
				current_ptr = current_ptr->lchild;
				parent_ptr->visited = 1;
				break;
			case 1:
				parent_ptr = current_ptr;
				push(parent_ptr);
				current_ptr->rchild = new_ptr;
				current_ptr = current_ptr->rchild;
				parent_ptr->visited = 2;
				break;
			default:
				puts("Impossible?\n");
//				goto SWITCH1; //redo switch
		}
	}
	
	return T;
}
void BFS(BinTree tree0, int depth) {
	if (tree0 != NULL) {
		if (depth == 0) printf("tree entry: %c, at depth %d\n", tree0->data, depth);
		RecordHeight(depth);
		if (tree0->lchild != NULL)printf("tree entry: %c, at depth %d\n", tree0->lchild->data, depth + 1);
		if (tree0->rchild != NULL)printf("tree entry: %c, at depth %d\n", tree0->rchild->data, depth + 1);
		
		BFS(tree0->lchild, depth + 1);
		BFS(tree0->rchild, depth + 1);
	} else return;
}

void Destroy(BinTree tree0) {//similar to BFS
	if (tree0 == NULL) return;
	Destroy(tree0->lchild);
	Destroy(tree0->rchild);
	free(tree0);
}

void RecordHeight(int record) {
	if (record > xHeight) xHeight = record;
}

int main(int argc, char **argv) {
	BinTree Tree = NULL;
	if (argc > 1) {
		printf("string:%s\n", argv[1]);
		Tree = CreatBinTree2(argv[1]);
		BFS(Tree, 0);
		printf("Max Height:%d\n", xHeight);
	} else puts("Please input string as argument\n");
	
	Destroy(Tree);
	return 0;
}