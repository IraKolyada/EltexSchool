#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	pid_t pid;
	int ret_num = 0;

	pid = fork();
	if(pid == -1){
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	if(pid == 0){
		printf("I am child:\n"
				"My PID:%d\n"
				"My PPID:%d\n",getpid(),getppid());

		ret_num = 1;
		exit(ret_num);
	}
	if(pid != 0 && pid != -1){
		printf("I am parent:\n"
				"My PID: %d\n"
				"My PPID: %d\n"
				"PID my child: %d\n",getpid(),getppid(),pid);

		wait(&ret_num);
		printf("Child return is: %d\n",WEXITSTATUS(ret_num));
	}
	return 0;
}