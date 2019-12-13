//
// Created by lenovo on 12/12/2019.
//

#ifndef DATASTRUCT_PRJ3B_H
#define DATASTRUCT_PRJ3B_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#endif //DATASTRUCT_PRJ3B_H

/* declared here as global variable because stack[]
* is used by more than one fucntions */
int stack[MAX];
int buffer[MAX];
int *buffer_ptr = buffer;
int top = -1;

/* define push operation */

void push(int item) {
	if (top >= MAX - 1) {
		printf("\nStack Overflow.");
	} else {
		top = top + 1;
		stack[top] = item;
	}
}

/* define pop operation */
int pop() {
	int item;
	
	if (top < 0) {
		printf("stack under flow: invalid infix expression");
		getchar();
		/* underflow may occur for invalid expression */
		/* where ( and ) are not matched */
		exit(1);
	} else {
		item = stack[top];
		stack[top] = 0;
		top = top - 1;
		return (item);
	}
}