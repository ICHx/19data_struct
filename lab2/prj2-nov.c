#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX 503
#define MAX_DIG 20
#define DEBUG 0

struct node_c;
struct node;
typedef struct node_c *node_c_ptr;
typedef struct node *node_ptr;
typedef node_c_ptr stack_c;
typedef node_ptr stack;
typedef char STACK_CHAR; //using char to store char
typedef double STACK_DATA; //using double to store calculation

stack_c newStack_c();
stack newStack();
void pushc(stack_c, STACK_CHAR);
void push(stack, STACK_DATA);
STACK_CHAR popc(stack_c);
STACK_DATA pop(stack);
bool isEmpty_c(stack_c);
bool isEmpty(stack);
bool is_operator(char);
short weight(char);
bool validateBrackets(const char *infix);
char InfixConv(char *, char *);
char evaluate(const char *, double *);

struct node_c {
	STACK_CHAR data; // store single character
	node_c_ptr next; //actually is previous node
};

struct node {
	STACK_DATA data; // store
	node_ptr next; //actually is previous node
};

stack_c newStack_c() {
	stack_c stack0;
	stack0 = malloc(sizeof(struct node_c));
	if (stack0 == NULL) {
		puts("OOM!");
		exit(-1);
	}
	stack0->data = '\0';
	stack0->next = NULL;

	return stack0;
}

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

void pushc(stack_c stack0, STACK_CHAR c0) {
	stack_c stack1 = newStack_c();
	if (stack1 != NULL) {
		stack1->data = c0;
		stack1->next = stack0->next;
		stack0->next = stack1;
	}
}

void push(stack stack0, STACK_DATA float0) {
	stack stack1 = newStack();
	if (stack1 != NULL) {
		stack1->data = float0;
		stack1->next = stack0->next;
		stack0->next = stack1;
	}
}

STACK_CHAR popc(stack_c stack0) {
	
	node_c_ptr tosp;
	if (isEmpty_c(stack0)) {
		puts("\ne: Underflow");
		exit(2);
	} //signal error
	
	else {
		STACK_CHAR item;
		tosp = stack0->next;
		item = stack0->next->data;
		stack0->next = stack0->next->next;
		free(tosp);
		return (item);
	}
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

bool isEmpty_c(stack_c s) { return s->next == NULL; }
bool isEmpty(stack s) { return s->next == NULL; }

bool is_operator(char symbol) {
	if (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-' || symbol == '^')
		return 1;
	else return 0;
}

bool is_plus(char symbol) {
	if (symbol == '+' || symbol == '-')
		return 1;
	else return 0;
}

short weight(char symbol) {
	if (symbol == '*' || symbol == '/') return 2;
	else if (symbol == '+' || symbol == '-') return 1;
	else if (symbol == '^') return 3;
	else return 0;
}

bool validateBrackets(const char *infix) {
	short i = 0;
	char item;
	stack_c stack_v = newStack_c();
	
	while ((item = infix[i++]) != '\0') {
		if (item == '(') pushc(stack_v, item);
		
		else if (isdigit(item) || is_operator(item));
		
		else if (item == ')') {
			if (isEmpty_c(stack_v))
				return 0; //when ) > (
			else popc(stack_v);
			
		}
	}
	
	if (isEmpty_c(stack_v)) return 1;
	else return 0; // when ( > )
}

bool validateSymbols(const char *infix) {
	short i = 0;
	char item,count=0;
	bool after_digit,after_plus,after_opr;

	stack_c stack_v = newStack_c();

	while ((item = infix[i++]) != '\0') {
    while(!is_operator(item)) {
        i++; after_digit=1;
        after_plus=0;
        after_opr=0;
        continue;}

        if(is_plus(item)){
            after_plus=1;
            count++;
    }
    else {   //now is ^ * /
            after_opr=1;
            count++;
        }

        after_digit=0;
    }



	return 1;
}

char getDot(char *, char *, short *, short *);
char getDot(char *input, char *output, short *a, short *b) {
	short dot = 0, i = *a, j = *b;
	char item = input[i];
	do {
		if (item == '.') dot++;
		output[j++] = item;
		item = input[++i];
	} while (isdigit(item) || (item == '.'));
	i--;
	if (DEBUG) printf("dot=%d", dot);
	*a = i;
	*b = j;
	return dot;
}

char InfixConv(char infix[], char postfix[]) {
	short i = 0, j = 0;
	char item = infix[i];
	char x, dot = 0;
	stack_c stack0 = newStack_c();
	bool leading = 1; //used to determine leading sign

	if (!validateBrackets(infix)) {
		puts("e: Unbalanced bracket");
		return -1;
	}
	if (!validateSymbols(infix)) {
		puts("e: Too many Operators");
		return -1;
	}

	pushc(stack0, '(');                   /* push '(' onto stack */
	strcat(infix, ")");                  /* add ')' to infix expression */

	while (item != '\0') {
		if (DEBUG) printf("\nCurrent Item %c %d\n", item, (int) item);
		
		dot = 0; //reset dot count, handle leading dot
		
		if (item == '(') {
			pushc(stack0, item);
			leading = 1;
			
		} else if (leading && is_plus(item)) {
			leading = 0;
			if (item == '+') {
				item = infix[++i];     //only omit sign and move on if positive
				continue;
			}
			if (item == '-') {
				postfix[j++] = ' ';
				postfix[j++] = '0';
				postfix[j++] = ' ';
				
				item = infix[++i];      //get next element
				if (isdigit(item) || item == '.') {
					dot = getDot(infix, postfix, &i, &j); //get the string
					if (dot > 1) {
						puts("\ne: Too many dots");
						return -1;
					}
				} //now is bracket the hard stuff
				else if (item == '(') {
					pushc(stack0, '-');
					continue;
//					pushc(stack0, item);
//					leading = 1;
				} else {
					puts("\ne: Unbalanced Operands");
					return -1;
				}
				
				postfix[j++] = ' ';
				postfix[j++] = '-';
				
				item = infix[++i];     //move on
			postfix[j++] = ' ';
				continue;
			}
			
		} else if (isdigit(item) || item == '.') {
			leading = 0;
			dot = getDot(infix, postfix, &i, &j);
			if (dot > 1) {
				puts("\ne: Too many dots");
				return -1;
			}
			postfix[j++] = ' ';
			
		} else if (is_operator(item)) {
			leading = 1;                          //the next operator encountered will be leading sign
			x = popc(stack0);
			while (is_operator(x) && weight(x) >= weight(item)) { //pop all higher precedence opr
				postfix[j++] = x;
				x = popc(stack0);
			}
			pushc(stack0, x); //the above loop terminate and popped the failed element
			pushc(stack0, item);
			
		} else if (item == ')') {
			x = popc(stack0);
			while (x != '(') { //break if ( or \0 is encountered
				postfix[j++] = x;
				x = popc(stack0);
			}
			
		} else { //nothing match
			puts("e: invalid symbol");
			return -1;
		}
		item = infix[++i]; //move to next char
		
	}           //end of while item!='\0'
	
	if (!isEmpty_c(stack0)) { //still non-empty stack?
		puts("Unbalanced infix expression");
		return -1;
	}
	
	postfix[j] = '\0'; //end string
	return 1;
}

char evaluate(const char postfix[], double *result) {
	short i = 0, j = 0;
	stack stack3 = newStack();
	STACK_CHAR *currentS;
	STACK_CHAR current_c;
	STACK_DATA val, x1, x2;
	STACK_DATA current;
	char opr;
	
	while ((current_c = postfix[i++]) != '\0') {
		if (current_c == ' ') continue;
		
		if (isdigit(current_c) || current_c == '.') {
			currentS = malloc(sizeof(char) * 20);
			while (isdigit(current_c) || current_c == '.') {
				//current -= '0';
				currentS[j++] = current_c;
				current_c = postfix[i++];
			}
			currentS[j] = '\0'; //end a string
			if (DEBUG) printf("\ncurrentS=%s", currentS);
			if (strlen(currentS) > MAX_DIG) {
				puts("\ne: Number Too Large.");
				return -1;
			}
			
			sscanf(currentS, "%lf\n", &current); //similar to stoi()
			if (DEBUG) printf("\ncurrent=%lf", current);
			
			push(stack3, current);
			free(currentS);
			j = 0;
			continue;
		} //    end of if digit section
		
		//now assume is symbol
		x2 = pop(stack3);
		x1 = pop(stack3);
		val = x1;
		
		opr = current_c;
		if (DEBUG) printf("\nval=%.4g x1=%.4g x2=%.4g opr=%c", val, x1, x2, opr);
		
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
			
			case '^':
				if ((int) x2 != x2) {
					puts("\ne: non-integer power not implemented...");
					while (getchar() != '\n');
					return -1;
				}
				if (x2 == 0) {
					if (x1 == 0) goto DIV_ZERO;
					val = 1;
					break;
				}
				
				for (int k = abs((int) x2); k > 1; k--) { // 2^3 = 2 * 2 * 2
					val *= x1;
				}
				
				if (x2 < 0) {
					val = 1 / val;
				}
				break;
			
			case '/':
				if (x2 == 0) {
					DIV_ZERO:
					puts("\ne: divide zero");
					return (-1);
				}
				val /= x2;
				break;
			
			default:
				puts("\ne: invalid Symbol");
				return (-1);
		}
		push(stack3, val);
	}
	*result = pop(stack3);
	return 1;
	
}//end of function

int main() {
	char s0[MAX];
	char s1[MAX];
	short feedback;
	double result;
	
	printf("\nInfix to Postfix calculator\n \
		Supported operators: + - * / ^ ( )\n \
		Supported Number Range Input: 20 digits\n \
		Supported Expression Length: %d char\n\n",
	       MAX - 3); //MAX - a pair of bracket - '\0'
	
	while (1) {
		printf("\nPress 'x' to exit");
		
		NEXT:
		printf("\nPostfix_EXP>");
		
		gets(s0);

//		if (DEBUG) {
//			strncpy(s0, "(+100-22)*-2--1", 99);
////          -155
//			strncpy(s0, "1*2*3*4*5*6*-7*8", 99);
////          -4.032e+04
//			strncpy(s0, "10000000000000000000*2-10^18", 99);
////        number having 20 digits
//			strncpy(s0, "10000000000000000000^3", 99);
////          number having 20 digits, result=1e+57
//
//			validateBrackets(s0) ? puts("Valid") : puts("Invalid");
//		}
		
		if (s0[0] == 'x') break;
		puts(s0);
		
		if (strlen(s0) > MAX - 2) {
			puts("\ne: String Too Large");
			goto NEXT;
		}
		
		feedback = InfixConv(s0, s1);
		
		if (feedback > 0) {
			puts(s1);
		} else {
			puts("Infix expression error. Try again!");
			goto NEXT;
		}//catch error
		
		feedback = evaluate(s1, &result);
		if (feedback > 0) printf("\nresult=%3g\n", result);
		
		else {
			puts("Postfix evaluation error. Try again!");
			goto NEXT;
		}
		
		puts("\n===========================");
		puts("press enter...");
		s0[0] = '\0';
		while (getchar() != '\n');
	}
	
	return 0;
}
