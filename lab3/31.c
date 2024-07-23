/*
 * Change of the third byte in the numder type int
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){
	/*Number for changes*/
	int num = 0;
	/*New byte*/
	int byte = 0;
	/*Pointer to byte for change*/
	char *new_byte = 0;

	new_byte = (char*)&num;

	/*Because my architecture is Little endian,
	 * to change the third byte in the number 
	 * I change the second byte*/
	/*In case Big endian - new_byte + 1; */
	new_byte = new_byte + 2;

	printf("Enter number: ");
	scanf("%d", &num);

	printf("Enter new byte: ");
	scanf("%d", &byte);

	*new_byte = byte;

	printf("New number: %d\n", num);

	return 0;
}
