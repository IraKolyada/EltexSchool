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
	sigset_t blockSet, prevMask;
	int life_time = 0;
	int flag_sig = -1, flag_set = -1;

	sigemptyset(&blockSet);
	flag_set = sigaddset(&blockSet, SIGINT);
	if(flag_set == -1){
		halt("error sigprocmask");
	}

	flag_sig = sigprocmask(SIG_BLOCK, &blockSet, &prevMask);
	if(flag_sig == -1){
		halt("error sigprocmask");
	}

	while(1){
		printf("The process №%d lives for %d second\n", getpid(), life_time);

		sleep(10);
		life_time +=10;
	}

	return 0;
}