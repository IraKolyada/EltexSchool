#include <stdlib.h>
#include <stdio.h>

#define SIZE 4

/* Fill in from one to SIZE^2*/

int main(void) {
	for (int line = 0; line < SIZE; line++) {
		for (int column = 0; column < SIZE; column++)
			printf("%d ", line * SIZE + column + 1);

		printf("\n");
	}

	return 0;
}
