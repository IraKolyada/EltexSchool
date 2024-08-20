#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int read_pipe(int disc){
	FILE *pipe_r;
	char *string = (char*)malloc(sizeof(char));
	size_t num_r;

	pipe_r = fdopen(disc,"r");
	if(pipe_r == NULL){
		printf("error open");
		return EXIT_FAILURE;
	}

	do{
		num_r = fread(string, sizeof(char), 1, pipe_r);
		if(num_r == 0){
			if (ferror(pipe_r) == 0){
				break;
			}else{
				printf("error read");
				return EXIT_FAILURE;
			}
		}
		printf("%s",string);
	}while((*string) != EOF);

	fclose(pipe_r);
	return 1;
}