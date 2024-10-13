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
	char str[] = "Hello!";

	int flags;
	mode_t perms;
	mqd_t mqd;
	struct mq_attr attr;
	unsigned int prio, re_prio;

	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 2048;
	flags = O_RDWR;
	perms = S_IRUSR | S_IWUSR;
	char re_str[attr.mq_msgsize];

	mqd = mq_open("/mq", flags, perms, &attr);
	if (mqd == (mqd_t) -1){
		halt("mq_open error");
	}

	prio = 2;

	if (mq_receive(mqd, re_str, attr.mq_msgsize, &re_prio) == -1){
		halt("error mq_receive");
	}

	printf("Re_str: %s\n", re_str);

	if (mq_send(mqd, str, strlen(str), prio) == -1){
		halt("error mq_send");
	}

	// Close the message queue
	mq_close(mqd);
	// Delete the corresponding file from the filesystem
	mq_unlink("/mqp");
	return 0;

}