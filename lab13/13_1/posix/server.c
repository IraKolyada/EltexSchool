#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>

#define MSG_SIZE 128

void halt(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main()
{
	char str[] = "HI CLIENT!!!";
	char re_str[2048];

	int flags;
	mode_t perms;
	mqd_t mqd;
	struct mq_attr attr;
	unsigned int prio, re_prio;

	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 2048;
	flags = O_CREAT | O_RDWR;
	perms = S_IRUSR | S_IWUSR;

	mqd = mq_open("/mq", flags, perms, &attr);
	if (mqd == (mqd_t) -1){
		halt("mq_open error");
	}

	prio = 1;

	if (mq_send(mqd, str, strlen(str), prio) == -1){
 		halt("error mq_send");
	}

	printf("\nPress enter to continue");
	getchar();

	if (mq_receive(mqd, re_str, attr.mq_msgsize, &re_prio) == -1){
 		halt("error mq_receive");
	}

	printf("Re_str: %s\n", re_str);

	// Close the message queue
	mq_close(mqd);
	// Delete the corresponding file from the filesystem
	mq_unlink("/mqp");
	return 0;

}