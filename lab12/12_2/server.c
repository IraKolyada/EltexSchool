#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


int main(void){
	char SERVER[] = "fifowork";
	int fifo_res;
	FILE* fd_dummy;

	fifo_res = mkfifo("fifowork", S_IRUSR | S_IWUSR | S_IWGRP);
	if(fifo_res == -1){
		printf("error mkfifo");
		return EXIT_FAILURE;
	}

	/*open for write*/
	fd_dummy = fopen(SERVER, "w");
	if(fd_dummy == NULL){
		printf("error open");
		return EXIT_FAILURE;
	}

	fprintf (fd_dummy, "HI!\n");
	fclose(fd_dummy);


	return 0;
}