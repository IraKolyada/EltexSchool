#include <stdio.h>
#include <stdlib.h>

#define MASK_1_2_BYTE 0x0000FFFF
#define MASK_4_BYTE 0xFF000000

int main(void) {
	int Num = 0;
	int new_Byte = 0;

	printf("Num: ");
	scanf("%d", &Num);

	printf("New byte: ");
	scanf("%d", &new_Byte);

	new_Byte = (new_Byte << 16);

	Num = (Num & MASK_4_BYTE) + new_Byte + (Num & MASK_1_2_BYTE);

	printf("New num: %d\n", Num);

	return 0;
}
