#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MSG_SIZE 128

struct msgbuf
{
	long mtype;
	char mtext[MSG_SIZE];
};

int main()
{
	char str[] = "HI!";
	int msqid, mssend, msctl;
	key_t key;
	int flag = IPC_CREAT | 0666;
	struct msgbuf sendbuff, recvbuff;
	size_t len_b;
	ssize_t msrecv;

	key = ftok("13_1server.bin", 12);
	if(key == -1){
		perror("Error ftok");
		return EXIT_FAILURE;
	}

	msqid = msgget(key, flag);
	if(msqid == -1){
		perror("Error msgget");
		return EXIT_FAILURE;
	}

	sendbuff.mtype = 1;
	len_b = strlen(str);
	strncpy(sendbuff.mtext, str, len_b);

	mssend = msgsnd(msqid, &sendbuff, len_b, IPC_NOWAIT);
	if(mssend == -1){
		perror("Error msgsnd");
		return EXIT_FAILURE;
	}

	msrecv = msgrcv(msqid, &recvbuff, MSG_SIZE, 2, 0);
	if(msrecv == -1){
		perror("Error msgsnd");
		return EXIT_FAILURE;
	}
	else if (msrecv >= 0)
	{
		printf("%s\n", recvbuff.mtext);

		msctl = msgctl(msqid, IPC_RMID, NULL);
		if(msctl == -1){
		perror("Error msgsnd");
		return EXIT_FAILURE;
		}
	}

	return 0;
}