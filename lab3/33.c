/*
 * Using a pointer to display an array 
 */
#include <stdio.h>
#include <stdlib.h>

/*Array size*/
#define SIZE 10

int main(void){
	int array[SIZE] = { 0 };
	int *ptr_array = NULL;
	int num = 1;

	ptr_array = (int*) array;

	/*
	 * Assigning a number
	 * Printed
	 * Moving the pointer
	 * Add one unit to the number
	 */
	while(num <= SIZE){
		*ptr_array = num;
		printf(" %d", *ptr_array);
		ptr_array++;
		num++;
	}

	printf("\n");

	return 0;
}
