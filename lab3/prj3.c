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
    char ch = 0;
    BinTree T = newNode();

    node_ptr current_ptr = T; //root node
    node_ptr parent_ptr = T;
    node_ptr new_ptr;

    parent_ptr->data = ch;
    push(parent_ptr);


    for (int i = 0; i < length; i++) {
        switch (current_ptr->visited) {
            default: //case 0
                parent_ptr = current_ptr;
                push(parent_ptr);
                current_ptr = current_ptr->lchild;
                parent_ptr->visited = 1;
                break;
            case 1:
                parent_ptr = current_ptr;
                push(parent_ptr);
                current_ptr = current_ptr->rchild;
                parent_ptr->visited = 2;
                break;
            case 2:
                while (current_ptr->visited != 2) {
                    parent_ptr = pop();
                    current_ptr = parent_ptr;  //backtrack until there
                }
                continue; //go to next loop
        }

        ch = string1[i];
        if (ch != '*')


        current_ptr = newNode(); /*create a node*/
        current_ptr->data = ch;
    }

    return T;
}


    {
        T = newNode(); /*create a node*/
        T->data = ch;
        T->lchild = CreatBinTree();        /*create the left subtree*/
        T->rchild = CreatBinTree();        /*create the right subtree*/
        return (T);
    }


int main(int argc, char **argv) {
    if (argc > 1) {
        printf("string:%s\n", argv[1]);
        CreatBinTree2(argv[1]);
    }
    return 0;
}