#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mypipe.h"
#include <errno.h>

int main(void){
	pid_t pid;
	int pipefd[2];
	int pipe1;

	pipe1 = pipe(pipefd);
	if(pipe1 == -1){
		perror("Error pipe");
		return EXIT_FAILURE;
	}

	pid = fork();
	if(pid == -1){
		perror("Error fork");
		return EXIT_FAILURE;
	}

	if(pid == 0){
		/*Work child*/
		close(pipefd[1]);
		read_pipe(pipefd[0]);
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	} else {
		/*Work parent*/
		close(pipefd[0]);
		write_pipe(pipefd[1]);
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	return 0;

}