#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	pid_t pid_1, pid_2, pid_3, pid_4, pid_5;
	int ret_num = 0;

	pid_1 = fork();
	if(pid_1 == -1){
		perror("Error fork process 1");
		exit(EXIT_FAILURE);
	}

	pid_2 = fork();
	if(pid_2 == -1){
		perror("Error fork process 2");
		exit(EXIT_FAILURE);
	}

	if(pid_1 == 0){
		pid_3 = fork();
		if(pid_3 == -1){
			perror("Error fork process 1");
			exit(EXIT_FAILURE);
		}

		if(pid_3 == 0){
			printf("I am child - p3:\n"
				"My PID(3):%d\n"
				"My PPID(3):%d\n", getpid(), getppid());
			ret_num = 3;
			exit(ret_num);
		}

		pid_4 = fork();
		if(pid_4 == -1){
			perror("Error fork process 2");
			exit(EXIT_FAILURE);
		}

		if(pid_4 == 0){
			printf("I am child - p4:\n"
				"My PID(4):%d\n"
				"My PPID(4):%d\n", getpid(), getppid());
			ret_num = 4;
			exit(ret_num);
		}
		printf("I am child - p1:\n"
				"My PID(1):%d\n"
				"My PPID(1):%d\n"
				"PID my child 3: %d\n"
				"PID my child 4: %d\n", getpid(), getppid(), pid_3, pid_4);

		waitpid(pid_3, &ret_num, WUNTRACED | WCONTINUED);
		waitpid(pid_4, &ret_num, WUNTRACED | WCONTINUED);

		ret_num = 1;
		exit(ret_num);
	}

	if(pid_2 == 0){
		pid_5 = fork();
		if(pid_5 == -1){
			perror("Error fork process 1");
			exit(EXIT_FAILURE);
		}

		if(pid_5 == 0){
			printf("I am child - p5:\n"
				"My PID(5):%d\n"
				"My PPID(5):%d\n", getpid(), getppid());
			ret_num = 5;
			exit(ret_num);
		}

		printf("I am child - p2:\n"
				"My PID(2):%d\n"
				"My PPID(2):%d\n"
				"PID my child 5: %d\n", getpid(), getppid(), pid_5);

		waitpid(pid_5, &ret_num, WUNTRACED | WCONTINUED);
		ret_num = 2;
		exit(ret_num);
	}
	if((pid_1 != 0 && pid_1 != -1) && (pid_2 != 0 && pid_2 != -1)){
		printf("I am parent:\n"
				"My PID: %d\n"
				"My PPID: %d\n"
				"PID my child 1: %d\n"
				"PID my child 2: %d\n", getpid(), getppid(), pid_1, pid_2);

		waitpid(pid_1, &ret_num, WUNTRACED | WCONTINUED);
		waitpid(pid_2, &ret_num, WUNTRACED | WCONTINUED);
	}
	return 0;
}