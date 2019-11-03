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
void pop(stack);
void show(node_ptr);
bool isEmpty(stack);
stack makeEmpty(stack);
short weight(char*);
char *fixConv(char *);
int calculate(char *);

stack newStack() {
    stack stack0;
    stack0 = malloc(sizeof(struct node));
    if (stack0 == NULL){puts("OOM!");exit(333);}
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


void pop(stack stack0) {
    node_ptr tosp;
    if (isEmpty(stack0)) puts("Empty stack");
    else {
        tosp = stack0->next;
        stack0->next = stack0->next->next;
        free(tosp);
    }
}

void show(node_ptr stack0) {
    node_ptr tosp;
    while (!isEmpty(stack0)) {
        tosp = stack0->next;
        putchar(stack0->next);
    }
}


stack makeEmpty(stack stack0) {
    if (stack0 == NULL) puts("Create stack first");
    else while (!isEmpty(stack0)) pop(stack0);
}


short weight(char* ptr){
    short weight;
    if(*ptr == '*' || *ptr == '/') weight=2;
    else if (*ptr == '+' || *ptr == '-') weight=1;
    if(*ptr=='\0') weight = 0;

    return weight;
};

char *fixConv(char *input0) { //numbers are put in string, operands are in stack

    char *ptr = input0;
    char *output;
    stack stack_operands=newStack();
    short last_weight=-1; //first number
    short stack_weight;
    short count=0;

    while (*ptr != '\0') {



            if (*ptr >='0'&& *ptr <='9') { //where the check&pop begin
                putc(*ptr++, output); //move to next operand
                continue;
            }
            else if(*ptr!='('||*ptr!=')')count++; //after a number


//            if (*ptr == '(') //need to also balance brackets
//                push(output,ptr);
//
            if (*ptr == '*' || *ptr == '/') {
                last_weight=2;
                push(stack_operands, *ptr++);
                continue;
            }

            if (*ptr == '+' || *ptr == '-'){
                last_weight=1;
                push(stack_operands, *ptr++);
                continue;
               }
//            if (*ptr == ')') { //need to also balance brackets
//                do pop(ptr);
//                while (*ptr != '(' || *ptr!='\0' );
//                if(*ptr!='\0')
//                pop(ptr); //pop once more
//            }

            if(!(count%2) & !count) { //if count is nonzero and even
                stack_weight = weight(&stack_operands->next->data);
                if(last_weight < stack_weight){
                    putc(stack_operands->next->data,output);
                    pop(stack_operands);
                    push(stack_operands, *ptr++);
                }
                else {
                    putc(*ptr++,output);
                }

                continue;
            }

            }
    while (!isEmpty(stack_operands)) {
        putc(stack_operands->next->data,output);
        pop(stack_operands);}
    return output;
}



int calculate(char *input0) {

}

int main() {
    while (1) {
        char s0[100]="2+3/7";
        char* s1;

        printf("\nPostfix_EXP>");
        //gets(s0);

        s1=fixConv(s0);
//        strncpy(s1,fixConv(s0),100);
        puts(s1);
//		s1=calculate(s1);
        break;
    }

    return 0;
}