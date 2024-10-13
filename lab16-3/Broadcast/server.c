#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define CLT_PORT 33333
#define CLT_ADDR "192.168.1.255"
#define BUFF_LEN 64

void halt(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}


int main(void)
{
	int fd_sock = -1;
	struct sockaddr_in addr_clt = {0};
	char str[BUFF_LEN] = {0};
	socklen_t addr_size = 0;
	int opt = -1;

	fd_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd_sock == -1){
		halt("socket");
	}

	/*
	 * Fill in the data for mailing to clients. In this case, you need to allow broadcast sending for the server
	 */
	addr_size = sizeof(addr_clt);
	addr_clt.sin_family = AF_INET;
	addr_clt.sin_port = htons(CLT_PORT);
	addr_clt.sin_addr.s_addr = inet_addr(CLT_ADDR);
	opt = 1;
	if (setsockopt(fd_sock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(int)) == -1){
		close(fd_sock);
		halt("setsockopt");
	}

	while (1){
		printf("Send to clients: ");
		scanf("%s", str);
		sendto(fd_sock, str, strlen(str) + 1, 0, (struct sockaddr *)&addr_clt, addr_size);
		if (!strcmp(str, "disconnect"))
			break;
	}

	if(close(fd_sock) == -1)
		halt("Error close");

	return 0;
}
