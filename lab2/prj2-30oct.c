#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct node;
typedef struct node *node_ptr;
typedef node_ptr stack;
#define MAX 100

struct node {
    char data; // store single character
    node_ptr next; //actually is previous node
};

stack newStack();

void push(stack, char);

char pop(stack);

void show(node_ptr);

bool isEmpty(stack);

stack makeEmpty(stack);

short weight(char);

int calculate(char *);

stack newStack() {
    stack stack0;
    stack0 = malloc(sizeof(struct node));
    if (stack0 == NULL) {
        puts("OOM!");
        exit(333);
    }
    return stack0;
}

void push(stack stack0, char c0) {
    stack stack1 = newStack();
    if (!stack1 == NULL) {
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

/* define pop operation */
char pop(stack stack0) {
    char item;

    node_ptr tosp;
    if (isEmpty(stack0)) {
        puts("Underflow");
        return '#';
    } //signal error

    else {
        tosp = stack0->next;
        item = stack0->next -> data;
        stack0->next = stack0->next->next;
        free(tosp);
        return (item);
    }
}

int InfixConv(char infix[], char postfix[]) {
    int i = 0, j = 0;
    char item = infix[i];
    char x;
    stack stack0 = newStack();
    node_ptr tosp = stack0->next;

	push(stack0,'(');                               /* push '(' onto stack */
	strcat(infix,")");                  /* add ')' to infix expression */

    while (item != '\0') {
        if (item == '(') push(stack0, item);

        else if (isdigit(item))
            postfix[j++] = item;

        else if (is_operator(item)) {
            x = pop(stack0);
            while (is_operator(x) && weight(x) >= weight(item)) { //pop all higher precendence opr
                postfix[j++] = x;
                x = pop(stack0);
            }
            push(stack0, x); //the above loop terminate and popped the failed element
            push(stack0, item);}

        else if (item == ')') {
            x = pop(stack0);
            while (x != '(') { //break if ( or \0 is encountered
                postfix[j++] = x;
                x = pop(stack0);

                if (x == '#') {
                    puts("Unbalanced brackets");
                    getchar();
                    return -1;
                }
            }

        } else { //nothing match
            puts("invalid symbol");
            getchar();
            return -1;
        }
        item = infix[++i]; //move to next char
    } //end while
    if (tosp != NULL) { //still non-empty stack?
        puts("Unbalanced infix expression");
        getchar();
        return -1;
    }

    postfix[j] = '\0'; //end string
    return 1;
}


float evaluate(char postfix[]) {
    int i=0,j=0;
    float val=1;
    bool used_plus_minus=0, first_run=1;
    stack stack3;
    char current=postfix[0];
    while (current!='\0') {
		while(isdigit(current) ){push(stack3,current);i++;}
	    char opr =is_operator(postfix[i]);

		switch(opr){
			case '+': val=val+pop(stack3)+pop(stack3);
					 used_plus_minus=1;break;
			case '-': val=val-pop(stack3)+pop(stack3);
					 used_plus_minus=1;break;
			case '*': val*=pop(stack3)*pop(stack3);break;

			case '/': val=pop(stack3)*pop(stack3);break;
		}
			if(first_run)	if(used_plus_minus){val--;first_run=0;}  //take out the initial one;





    }
}


int main() {
	while (1) {
		char s0[100]="(2+3)/7"; char s1[100];
		short feedback;

//		printf("\nPostfix_EXP>");
//		gets(s0);

		feedback=InfixConv(s0,s1);
		(feedback>0)?puts(s1):puts("Try again!");
//        strncpy(s1,fixConv(s0),100);

//		s1=calculate(s1);
		break;
	}

	return 0;
}

