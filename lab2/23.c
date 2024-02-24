#include <stdlib.h>
#include <stdio.h>

#define SIZE 6

/* Bottom triangle filled with one
   Top triangle filled with zero*/

int main(void){
	for (int line = 0; line < SIZE; line++) {
		for (int column = 0; column < SIZE; column++)
			printf("%d ", ((line + column) < (SIZE - 1)) ? 0 : 1);

		printf("\n");
	}

	return 0;
}
