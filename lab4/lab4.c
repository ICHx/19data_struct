#include <stdio.h>  //This is useful to do i/o to test the code
#include <stdlib.h> //exit()
#include <time.h> //time count
#include <unistd.h> //time count
#include <string.h> //strlen()
#include <ctype.h>

#define DEBUG 1
#define MAX 10010
#define StrMAX 10000000


FILE *input0;
FILE *output0;

int read_inputs_from_ip_if(int[]);
void write_output_to_op_if(int array[], int N);
void doSort(int choice);

int read_inputs_from_ip_if(int array[]) {
	//place your input code here
	//to read the current state of the available sensors
	char *temp = malloc(sizeof(char) * StrMAX);
	char *ptr;
	int current;
	int count = 0;
	
	input0 = fopen("input.txt", "r");
	if (input0 == NULL) {
		puts("e: File create failed.");
		fclose(input0);
		exit(2);
	} //still NULL
	
	fgets(temp, StrMAX, input0);//10 entries
	fgets(temp, StrMAX, input0);//100
	fgets(temp, StrMAX, input0);//10000 entries
	
	if (temp[0] == '\0') {
		puts("E: file empty");
		exit(1);
	}
	
	current = (int) strtol(temp, &ptr, 10);
	array[count] = current;
	
	
	while (!iscntrl(ptr[0])) {
		count++;
		current = (int) strtol(ptr, &ptr, 10);
		array[count] = current;
	}
	
	
	fclose(input0);
	return (count + 1);
}
void write_output_to_op_if(int array[], int N) {
	//place your output code here
	//to display/print the state of the 3 actuators (DLA/BELL/BA)
	output0 = fopen("output.txt", "w");//initiate the file
	if (output0 == NULL) {
		puts("e: File create failed.");
		exit(2);
	} //still NULL
	
	
	fprintf(output0, "Sorted=\n");
	for (int i = 0; i < N; ++i) {
		fprintf(output0, "%d ", array[i]);  //bell alert
	}
	fclose(output0);//if not closed, files are not written
}

void InsSort(int *array, int N) { // [column] insertion sort
	int temp = 0, i, j;
	for (i = 1; i < N; ++i) {
		temp = array[i];
		for (j = i; j > 0 && array[j - 1] > temp; j--) {
			// if j is within bounds and pass item is smaller than current item from array
			array[j] = array[j - 1];
			array[j - 1] = temp;
		}
	}
}

void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int median(int a[], int left, int right) {
	int centre = (left + right) >> 1;
	
	if (a[left] > a[centre]) swap(&a[left], &a[centre]);
	if (a[left] > a[right]) swap(&a[left], &a[right]);
	if (a[centre] > a[right]) swap(&a[centre], &a[right]);
	
	swap(&a[centre], &a[right - 1]); //hide pivot
	return a[right - 1];
}
#define cutoff 2
void QuickSort(int *A, int left, int right) {
	//data is totally random, it is good middle element as pivot
	int i, j, pivot;
	
	if (left + cutoff <= right) { //the cut off point for quick-sort
		pivot = median(A, left, right);
		i = left, j = right - 1;
		for (;;) {
			while (A[++i] < pivot) {}
			while (A[--j] > pivot) {}
			if (i < j)
				swap(&A[i], &A[j]);
			else break;
		}
		swap(&A[i], &A[right - 1]);//restore pivot
		
		QuickSort(A, left, i - 1);
		QuickSort(A, i + 1, right);
		
	} else InsSort(A + left, right - left + 1);
	
	
}

void doSort(int choice) {
	int array[MAX] = {0};
	int count;
	clock_t start, end;
	double duration;
	
	count = read_inputs_from_ip_if(array);
	
	start = clock(); /* records the ticks at the beginning of the function call */
	
	//sort here
	if (choice) {
		puts("Ins");
		InsSort(array, count);
	} else {
		puts("Quick");
		QuickSort(array, 0, count - 1);
	}
	
	end = clock(); /* records the ticks at the end of the function call */
	duration = ((double) (end - start)) / CLOCKS_PER_SEC; //CLK_TCK depreciated
	printf("Time=%5.2le sec\n===\n", duration);
	write_output_to_op_if(array, count);
}

int main(int argc, char *argv[]) {
	
	for (int k = 5; k > 0; k--)
		doSort(0);
//	getchar();
	for (int k = 5; k > 0; k--)
		doSort(1);
	
	return 0;
}
