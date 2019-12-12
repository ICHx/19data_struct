//
// Created by lenovo on 12/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "prj3.h"

BinTree CreatBinTree(void) {
	BinTree T;
	char ch;
	if ((ch = getchar()) == '*')
		return (NULL);       /*input is ‘*’，return null vector*/
	else {
		T = (BinTNode *) malloc(sizeof(BinTNode)); /*create a node*/
		T->data = ch;
		T->lchild = CreatBinTree();        /*create the left subtree*/
		T->rchild = CreatBinTree();        /*create the right subtree*/
		return (T);
	}
}

BinTree CreatBinTree2(char *string1) {
	int length = (int) strlen(string1);
	BinTree T = newNode();
	node_ptr current_ptr = T; //root node
	node_ptr parent_ptr = T; //root node
	char ch = 0;
	
	for (int i = 0; i < length; i++) {
		ch = string1[i++];
		if (ch != '*') {
			parent_ptr = current_ptr;
			current_ptr = current_ptr->lchild;
		} else if ((ch = string1[i++]) != '*') {
			parent_ptr = current_ptr;
			current_ptr = current_ptr->rchild;
		} else {
			current_ptr = parent_ptr;
		}
		
		
		current_ptr = newNode(); /*create a node*/
		current_ptr->data = ch;
	}
	
}

int main(int argc, char **argv) {
	if (argc > 1) {
		printf("string:%s\n", argv[1]);
		CreatBinTree2(argv[1]);
	}
	return 0;
}