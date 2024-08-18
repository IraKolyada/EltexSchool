#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * sub - returns the difference of two integers
 * @num1: minuend
 * @num2: subtrahend
*/
int sub(int *num1, int *num2){
	if(num1 == NULL){
		perror("Pointer num1 empty");
		exit(EXIT_FAILURE);
	}

	if(num2 == NULL){
		perror("Pointer num2 empty");
		exit(EXIT_FAILURE);
	}

	int diff;

	diff = *num1 - *num2;

	return diff;
}