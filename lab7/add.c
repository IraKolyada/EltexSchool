#include <stdio.h>
#include<stdlib.h>
#include <errno.h>
/**
 * add - returns the sum of two integers
 * @num1, @num2: added numbers
*/
int add(int *num1, int *num2){

	if(num1 == NULL){
		perror("Pointer num1 empty");
		exit(EXIT_FAILURE);
	}

	if(num2 == NULL){
		perror("Pointer num2 empty");
		exit(EXIT_FAILURE);
	}

	int summ;

	summ = *num1 + *num2;

	return summ;
}