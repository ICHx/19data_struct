#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 0

struct node;
typedef struct node *node_ptr;
typedef node_ptr stack;
typedef float STACK_DATA;
#define MAX 100

struct node {
	STACK_DATA data; // store single character
	node_ptr next; //actually is previous node
};

stack newStack();

void push(stack, STACK_DATA);

STACK_DATA pop(stack);

bool isEmpty(stack);

short weight(char);


stack newStack() {
	stack stack0;
	stack0 = malloc(sizeof(struct node));
	if (stack0 == NULL) {
		puts("OOM!");
		exit(-1);
	}
	stack0->data = '\0';
	stack0->next = NULL;

	return stack0;
}

void push(stack stack0, STACK_DATA c0) {
	stack stack1 = newStack();
	if ((stack1 != NULL) {
		stack1->data = c0;
		stack1->next = stack0->next;
		stack0->next = stack1;
	}
}

bool isEmpty(stack s) { return s->next == NULL; }

int is_operator(char symbol) {
	if (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-')
		return 1;
	else return 0;
}

short weight(char symbol) {
	if (symbol == '*' || symbol == '/') return 2;
	else if (symbol == '+' || symbol == '-') return 1;
	else return 0;
}

STACK_DATA pop(stack stack0) {

	node_ptr tosp;
	if (isEmpty(stack0)) {
		puts("\ne: Underflow");
		exit(2);
	} //signal error

	else {
		STACK_DATA item;
		tosp = stack0->next;
		item = stack0->next->data;
		stack0->next = stack0->next->next;
		free(tosp);
		return (item);
	}
}

int InfixConv(char infix[], char postfix[]) {
	typedef char STACK_DATA;
	short i = 0, j = 0;
	char item = infix[i];
	char x;
	stack stack0 = newStack();

	push(stack0, '(');                               /* push '(' onto stack */
	strcat(infix, ")");                  /* add ')' to infix expression */

	while (item != '\0') {
		printf("\nCurrent Item %c %d\n", item, (int) item);
		if (item == '(') push(stack0, item);

		else if (isdigit(item))
			postfix[j++] = item;

		else if (is_operator(item)) {
			x = pop(stack0);
			while (is_operator(x) && weight(x) >= weight(item)) { //pop all higher precedence opr
				postfix[j++] = x;
				x = pop(stack0);
			}
			push(stack0, x); //the above loop terminate and popped the failed element
			push(stack0, item);
		} else if (item == ')') {
			x = pop(stack0);
			while (x != '(') { //break if ( or \0 is encountered
				postfix[j++] = x;
				x = pop(stack0);
			}
			//x = pop(stack0);

		} else { //nothing match
			puts("e: invalid symbol");
			getchar();
			return -1;
		}
		item = infix[++i]; //move to next char
	} //end while

	if (!isEmpty(stack0)) { //still non-empty stack?
		puts("Unbalanced infix expression");
		getchar();
		return -1;
	}

	postfix[j] = '\0'; //end string
	return 1;
}

bool valid_bracket(char *infix) {
//
}

float evaluate(char postfix[]) {
	typedef float STACK_DATA;
	short i = 0;
	float val = 1, x1, x2;
	stack stack3 = newStack();
	int current;
	char opr;

	while ((current = postfix[i++]) != '\0') {
		if (isdigit(current)) {
			current -= '0';
			if (DEBUG) printf("\ncurrent=%d", current);

			push(stack3, current);
			continue;
		}
		//now assume is symbol

		x2 = pop(stack3);
		x1 = pop(stack3);
		val = x1;

		opr = current;
		if (DEBUG) printf("\nval=%.2f x1=%.2f x2=%.2f opr=%c", val, x1, x2, opr);

		switch (opr) {
			case '+':
				val += x2;
				break;
			case '-':
				val -= x2;
				break;
			case '*':
				val *= x2;
				break;

			case '/':
				if (x2 == 0) {
					puts("\ne: divide zero");
					return ('\0');
				}
				val /= x2;
				break;

			default:
				puts("\ne: invalid Symbol");
				return ('\0');
		}
		push(stack3, val);
	}
	return pop(stack3);
}//end of function




int main() {
	char s0[100] = "(5+3)/5+7*(2+3)";
	char s1[100]; // 53+5/1+ = 2.6 , 53+5/723+*+=36.6
	float feedback;
	while (1) {
		puts(s0);
		feedback = InfixConv(s0, s1);
		if (feedback > 0) {
			puts(s1);
		} else {
			puts("Try again!");
			goto NEXT;
		}//catch error

		feedback = evaluate(s1);
		if (feedback != '\0') printf("\nresult=%3.2f\n", feedback);

		else puts("Try again!");


		NEXT:
		puts("press enter...");
		getchar();

		printf("\nPostfix_EXP>");
		s0[0] = '\0';
		gets(s0);
	}

	return 0;
}
