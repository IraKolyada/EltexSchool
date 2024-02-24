#include <stdlib.h>
#include <stdio.h>

/* Find the first zero in a number*/
int begin(int num) {
	for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
		if (!(num & (1 << i)))
			return i;
	}

	return 1;
}

int main(void) {
	int num = 0;
	int mask = 0;
	int begin_num = 0;

	printf("NUM: ");
	scanf("%d", &num);

	begin_num = begin(num);

	for (int i = begin_num; i >= 0; i--){
		/* Put one in place i */
		mask = 1 << i;

		if ((num & mask)) {
			printf("1");
		} else {
			printf("0");
		}
		
		if (((i % 8) == 0) && (i > 1))
			printf(" ");
	}

	printf("\n");

	return 0;
}