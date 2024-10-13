#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define CLT_PORT 33333
#define GRP_ADDR "239.0.0.34"
#define LEN_BUFF 64

void halt(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main()
{
	int fd_sock = -1;
	struct sockaddr_in addr_grp = {0};
	char msg[LEN_BUFF] = {0};

	fd_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd_sock == -1){
		halt("socket");
	}

	addr_grp.sin_family = AF_INET;
	addr_grp.sin_port = htons(CLT_PORT);
	addr_grp.sin_addr.s_addr = inet_addr(GRP_ADDR);

	while (1){
		printf("Send to clients: ");
		scanf("%s", msg);
		sendto(fd_sock, msg, strlen(msg) + 1, 0, (struct sockaddr *)&addr_grp, sizeof(addr_grp));
		if (!strcmp(msg, "disconnect"))
			break;
	}

	if(close(fd_sock) == -1)
		halt("Error close");

	return 0;
}
