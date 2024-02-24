#include <stdio.h>
#include <stdlib.h>

/*
* Find the first unit in a number
*/
int begin(int num) {
	for (int i = sizeof(num)*8 - 1; i >= 0; i--) {
		if(num & (1 << i))
			return i;
	}

	return 0;
}

int main(void) {
	int num = 0;
	int begin_num = 0;
	int mask = 0;
	/* Number of one for the third task */
	int Num_of_1 = 0;

	/* Enter number */
	printf("NUM: ");
	scanf("%d", &num);

	begin_num = begin(num);

	for (int i = begin_num; i >= 0; i--) {
		/* Put one in place i */
		mask = 1 << i;

		if (num & mask) {
			printf("1");
			Num_of_1++;
		} else {
			printf("0");
		}
		
		if (((i % 8) == 0) && (i > 1))
			printf(" ");
	}

	printf("\nNumber of units a NUM: %d\n",Num_of_1);

	return 0;
}
