#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define SIG 10

void halt(char *msg){
	perror(msg);
	exit(1);
}

int main(void){
	sigset_t blockSet;
	int sig;
	int *sigptr = &sig;
	int ret_val;
	int flag_sig = -1, flag_set = -1;

	printf("The process №%d\n", getpid());

	sigemptyset(&blockSet);
	flag_set = sigaddset(&blockSet, SIGUSR1);
	if(flag_set == -1){
		halt("error sigprocmask");
	}

	flag_sig = sigprocmask(SIG_BLOCK, &blockSet, NULL);
	if(flag_sig == -1){
		halt("error sigprocmask");
	}

	while(1){
		ret_val = sigwait(&blockSet,sigptr);
		if(ret_val == -1){
			halt("Sigwait error");
		}
		if(*sigptr == 10)
			printf("SIGUSR1 was received\n");
		else
			printf("sigwait returned with sig: %d\n", *sigptr);

	}

	return 0;
}