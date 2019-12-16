/*
This example program sounds the bell when driver is on seat AND haven't closed the doors. Use the general framework and the function shells, replace the code inside  the control_action() function with your own code.

Note: This code is designed to run in an infinite loop to mimic a real control system. 
If you prefer to read the inputs from a file, modify the code appropriately to terminate the loop when all the inputs have been processed.

run this file as : gcc filename.c -o executableName

Created By WilliamHe(2018053277) & RTsui(2018058445)
*/
#include <stdio.h>  //This is useful to do i/o to test the code
#include <stdlib.h> //exit()
#include <unistd.h> //sleep() for UNIX/mingw-w64
#include <string.h> //strlen()

#define DEBUG 1
#define MAX 64
#define StrMAX 256


FILE *input0;
FILE *output0;
int before[MAX];
int after[MAX];

void read_inputs_from_ip_if();
void write_output_to_op_if();

void read_inputs_from_ip_if() {
	//place your input code here
	//to read the current state of the available sensors
	char temp[MAX];
	char *ptr;
	
	input0 = fopen("input.txt", "r");
	if (input0 == NULL) {
		puts("e: File create failed.");
		fclose(input0);
		exit(2);
	} //still NULL
	
}
else );

fgets(temp,
StrMAX,input0 ); //the last character is '\n', so we need to get the second last character

driver_on_seat = strtol(&temp[strlen(temp) - 2], &ptr, 10);

printf("DOS=%u\t", driver_on_seat);
fclose(input0);
}

void write_output_to_op_if() {
	//place your output code here
	//to display/print the state of the 3 actuators (DLA/BELL/BA)
	output0 = fopen("output.txt", "w");//initiate the file
	if (output0 == NULL) {
		puts("e: File create failed.");
		exit(2);
	} //still NULL
	
	
	
	fprintf(output0, "BELL=%u\n", bell);  //bell alert
	
	
	fclose(output0);//if not closed, files are not written
}

//The code segment which implements the decision logic
void doSort() {
	int before[MAX]
	
	
}

/* ---     You should not have to modify anything below this line ---------*/

int main(int argc, char *argv[]) {
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	
	
	read_inputs_from_ip_if();
	doSort();
	write_output_to_op_if();
	DEBUG ? sleep(2) : 0;
	
	
}
