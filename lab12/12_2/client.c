#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


int main(void){
	char SERVER[] = "fifowork";
	int num_r, num_remove;
	FILE* fd_dummy;
	char *string = (char*)malloc(sizeof(char));

	/*open for read*/
	fd_dummy = fopen(SERVER, "r");
	if(fd_dummy == NULL){
		perror("error open\n");
		return EXIT_FAILURE;
	}

	do{
		num_r = fread(string, sizeof(char), 1, fd_dummy);
		if(num_r == 0){
			if(ferror(fd_dummy) == 0){
				break;
			}else{
				perror("error read\n");
				return EXIT_FAILURE;
			}
		}
		printf("%s",string);
	}while((*string) != EOF);

	fclose(fd_dummy);
	printf ("Remove file: ");
	num_remove = remove(SERVER);
	if (num_remove == -1){
		perror("error remove\n");
		return EXIT_FAILURE;
	}
	else{
		printf ("Good remove\n");
	}
	return 0;
}