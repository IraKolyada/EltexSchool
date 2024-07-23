#include <stdio.h>
#include <stdlib.h>

#define BIG_SIZE 10
#define SUB_SIZE 4

int main(void){
	/*String*/
	char big_string[BIG_SIZE] = {0};
	/*Substring*/
	char sub_string[SUB_SIZE] = {0};
	/*Pointer for string*/
	char *big_ptr = NULL;
	/*Pointer for substring*/
	char *sub_ptr = NULL;
	/*Pointer for save place start substring*/
	char *one_ptr = NULL;

	int place = 0;

	big_ptr = (char*) big_string;

	printf("Enter string( < 10): ");
	scanf(" %10s", big_ptr);

	sub_ptr = (char*) sub_string;

	printf("Enter subsrting( < 4): ");
	scanf(" %4s", sub_ptr);

	printf("\n");

	big_ptr = (char*) &big_string[0];
	sub_ptr = (char*) &sub_string[0];

	char *two_ptr = NULL;

	int sub_long = 0;

	two_ptr = sub_ptr;
	
	/*
	 *Go along the string
	 */
	for(place = 0; place < (BIG_SIZE - 1); place++) {
		/*
		 *If first simbol substr
		 
		sub_ptr = two_ptr;

		if (*sub_ptr == *big_ptr) {
			one_ptr = big_ptr;

			for (int i = 0;i < SUB_SIZE; i++) {
				
				if (*sub_ptr != *big_ptr) {
					big_ptr = one_ptr + 1;
					one_ptr = NULL;
					
					i = SUB_SIZE;
				}

				sub_ptr++;
				big_ptr++;
			}	
		}

		if (one_ptr != NULL)
			break;

		big_ptr++;
		*/

		if(*sub_ptr == *big_ptr){
			one_ptr = big_ptr;
			while(sub_long < SUB_SIZE){
				if(*(one_ptr+1) ==  *(sub_ptr+1)){
					sub_long++;
					one_ptr++;
					sub_ptr++;
					if (sub_long == (SUB_SIZE-1)){
						one_ptr -=4;
						break;
					}
				}
				else{
					one_ptr = NULL;
					break;
				}
			}

			if (one_ptr != NULL)
						break;
					big_ptr++;

		}
	}

	if(one_ptr == NULL)
		printf("\nno\n");
	else
		printf("\n%c\n", *one_ptr);

	return 0;
}

