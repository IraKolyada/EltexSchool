#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int main(void) {
	int array[SIZE][SIZE] = {0};
	/* Numbers of level. 
	   Represent the array as a target.
	   The first level is the perimeter/
	   The second is the perimeter of a square of size (SIZE - 2)*/
	int level = 0;
	int begin_line = 0;
	int end_line = SIZE - 1;
	int begin_column = 0;
	int end_column = SIZE - 1;
	int num = 1;

	/* Determining the number of level */
	if (SIZE % 2 == 0)
		level = SIZE/2;
	else
		level = SIZE/2 + 1;

	/* Work wiht the array */
	while (level > 0) {

		/* Work with the top side of the perimeter.
		   At the first level it is equal to the lenght of the line.
		   At other levels, the begin of the is line increased by one,
		   the end is decreased by one*/
		for (int i = begin_column; i <= end_column; i++) {
			array[begin_line][i] = num;
			num++;
		}

		/* Work with the right side of the perimeter.
		   It is equal to the lenght of the column minus two 
		   because the first snd the last element of the column 
		   will be processed st the top snd bottom sides of the perimeter.*/
		for (int i = begin_line + 1; i <= end_line - 1; i++) {
			array[i][end_column] = num;
			num++;
		}

		/* Work with the bottom side of the perimeter. */
		for (int i = end_column; i >= begin_column; i--) {
			if(num > SIZE*SIZE)
				num = SIZE*SIZE;

			array[end_line][i] = num;
			num++;
		}

		/* Work with the left side of the perimeter. */
		for (int i = end_line - 1; i >= begin_line + 1; i--) {
			array[i][begin_column] = num;
			num++;
		}

		begin_line++;
		end_line--;
		begin_column++;
		end_column--;
		level--;
	}

	for (int line = 0; line < SIZE; line++) {
		for (int column = 0; column < SIZE; column++)
			printf("%d ", array[line][column]);

		printf("\n");
	}

	return 0;

}
