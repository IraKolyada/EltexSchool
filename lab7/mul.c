#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * mul - returns the product of two integers
 * @num1: multiplicand
 * @num2: multiplier
*/
int mul(int *num1, int *num2){
	if(num1 == NULL){
		perror("Pointer num1 empty");
		exit(EXIT_FAILURE);
	}

	if(num2 == NULL){
		perror("Pointer num2 empty");
		exit(EXIT_FAILURE);
	}

	int prod;

	prod = (*num1) * (*num2);

	return prod;
}