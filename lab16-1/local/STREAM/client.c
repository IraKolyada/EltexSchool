#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SOCK_F_NAME "socket1"
#define BACKLOG 1
#define LEN_BUFF 128

int main(void)
{
	struct sockaddr_un addr = {0};
	int fd_sock = -1, fd_connect = -1;
	int num_send = -1, num_recv = -1;
	char strbuff[128] = "FVFVDD";
	char strbuff_recv[128] = {0};

	fd_sock = socket(AF_LOCAL,SOCK_STREAM,0);
	if(fd_sock == -1){
		perror("Error socket");
		return EXIT_FAILURE;
	}

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_LOCAL;
	strncpy(addr.sun_path, SOCK_F_NAME, sizeof(addr.sun_path) - 1);

	fd_connect = connect(fd_sock, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));
	if(fd_connect == -1){
		perror("Error listen");
		return EXIT_FAILURE;
	}

	num_send = send(fd_sock, strbuff, LEN_BUFF, 0);
	if(num_send == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	num_recv = recv(fd_sock, strbuff_recv, LEN_BUFF , 0);
	if(num_recv == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	printf("\n %s\n",strbuff_recv);

	close(fd_sock);
	return 0;
}