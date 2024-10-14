#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define SIG 10

void halt(char *msg){
	perror(msg);
	exit(1);
}


void sig_new( int sig){
	printf("\n Signal №%d received\n", sig);
	sleep(5);
}

int main(void){
	struct sigaction act = { 0 };
	int life_time = 0;
	int flag_sig = -1;

	act.sa_handler = &sig_new;

	flag_sig = sigaction(SIG, &act, NULL);
	if(flag_sig == -1){
		halt("error sigation");
	}

	while(1){
		printf("The process №%d lives for %d second\n", getpid(), life_time);

		sleep(10);
		life_time +=10;
	}

	return 0;
}