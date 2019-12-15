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

int stack[MAX];
int buffer[MAX];
int top = -1;

void push(int item) {
	if (top >= MAX - 1) {
		printf("\nStack Overflow.");
	} else {
		top = top + 1;
		stack[top] = item;
	}
}

int pop() {
	int item;
	if (top < 0) {
		printf("stack under flow: invalid infix expression");
		getchar();
		exit(1);
	} else {
		item = stack[top];
		stack[top] = 0;
		top = top - 1;
		return (item);
	}
}