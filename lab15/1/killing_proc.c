#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void halt(char *msg){
	perror(msg);
	exit(1);
}

int main(void)
{
	int sig;
	int id ;
	int flag_kill;
	while (1){
		printf("Enter PID \n");
		scanf("%d", &id);
		printf("Enter signal \n");
		scanf("%d",&sig) ;
		printf("Send signal %d to %d\n", sig , id);
		flag_kill = kill(id, sig);
		if(flag_kill == -1){
			halt("error kill");
		}
	}
}

