#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int main(void) {
	
	int array[SIZE] = {0};
	int half = 0;
	int bubble = 0;

	half = (SIZE % 2) ? SIZE/2 + 1 : SIZE/2;

	printf("Old array: ");

	/* Fill in from one to SIZE*/

	for (int i = 0; i < SIZE; i++) {
		array[i] = i + 1;
		printf("%d ", array[i]);
	}

	printf("\n");

	/* Swap plase */

	for (int i = 0; i < half; i++) {
		bubble = array[i];
		array[i] = array[SIZE -(i+1)];
		array[SIZE - (i+1)] = bubble;
		bubble = 0;
	}

	printf("New array: ");

	for (int i = 0; i < SIZE; i++) {
		printf("%d ", array[i]);
	}

	printf("\n");

	return 0;
}
