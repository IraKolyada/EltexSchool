#include <stdio.h>
#include "libcalc.h"

int main(void){
	int com = 0;
	int flag = 1;
	int num1 = 0;
	int num2 = 0;
	int result = 0;
	int state = 0;

	printf("The calcuator is running.\n"
			"\nPossible commands:\n"
			"1)Addition\n"
			"2)Subtraction\n"
			"3)Multiplication\n"
			"4)Division\n"
			"5)Exit\n");

	while(flag){
		printf("\nEnter first number:\n");
		scanf("%d",&num1);
		printf("\nEnter second number:\n");
		scanf("%d",&num2);

		printf("\nEnter the command number:\n");
		scanf("%d",&com);

		switch(com){
			case 1:
				result = add(&num1,&num2);
				printf("\nResult: %d\n", result);
				break;
			case 2:
				result = sub(&num1,&num2);
				printf("\nResult: %d\n", result);
				break;
			case 3:
				result = mul(&num1,&num2);
				printf("\nResult: %d\n", result);
				break;
			case 4:
				state = div(&num1,&num2,&result);
				if(state == 0){
					printf("The result of division isn't an integer \n");
				}
				else if (state == 1)
				{
					printf("\nThe denominator is zero\n");
				}
				else if (state == 2)
				{
					printf("\nResult: %d\n", result);
				}
				else{
					printf("\nUnknown result\n");
				}
				break;
			case 5:
				flag = 0;
				break;
			default:
				printf("\nCommand don't found!\n");
				break;
		}
	}

	return 0;
}