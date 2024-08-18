#include <stdio.h>
#include<stdlib.h>
#include <errno.h>
/**
 * div - division function, return integer number or NULL
 * @num1: numerator
 * @num2: denominator
 * 
 * Returns NULL if the denominator is zero 
 * or the result of division isn't int
*/
int div(int *num1, int *num2, int *res){

	if(num1 == NULL){
		perror("Pointer num1 empty");
		exit(EXIT_FAILURE);
	}

	if(num2 == NULL){
		perror("Pointer num2 empty");
		exit(EXIT_FAILURE);
	}

	if(res == NULL){
		perror("Pointer res empty");
		exit(EXIT_FAILURE);
	}


	if(*num2 == 0)
		return 1;
	else{
		*res = (*num1) / (*num2);
		if((*res) * (*num2) != (*num1)){
			return 0;
		}
	}
	return 2;
}