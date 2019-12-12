//
// Created by ricts on 15/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

typedef struct node{
    char data;
    struct node *lchild,*rchild;
}BinTNode;    //define the data type of the node
typedef BinTNode *BinTree;

BinTree CreatBinTree(void){
    BinTree T;
    char ch;
    if((ch=getchar())=='*')
        return(NULL);       /*input is ‘*’，return null vector*/
    else{
        T= (BinTNode *)malloc(sizeof(BinTNode)); /*create a node*/
        T->data=ch;
        T->lchild=CreatBinTree();        /*create the left subtree*/
        T->rchild=CreatBinTree();        /*create the right subtree*/
        return(T);
    }
}
