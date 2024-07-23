/*
 *Changed code
 */
#include <stdlib.h>
#include <stdio.h>

int main(void){
	float x = 5.0;

	printf("x = %f, ", x);

	float y = 6.0;

	printf("y = %f\n", y);
	
	/*Changed string*/
	float *xp = &y;
	float *yp = &y;

	printf("Output: %f\n", *xp+*yp);

	return 0;
}
