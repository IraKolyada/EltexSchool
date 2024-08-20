#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int write_pipe(int disc){
	FILE *pipe_wr;

	pipe_wr = fdopen(disc,"w");
	if(pipe_wr == NULL){
		printf("error open");
		return EXIT_FAILURE;
	}

	fprintf (pipe_wr, "HI!\n");

	fclose(pipe_wr);
	return 1;

}