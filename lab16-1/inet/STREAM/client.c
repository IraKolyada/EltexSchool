#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
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
	struct sockaddr_in addr = {0};
	int fd_sock = -1, fd_connect = -1;
	int num_bind = -1, num_send = -1, num_recv = -1;
	socklen_t serv_len = 0;
	char strbuff[120] = {0};
	char strbuff_recv[128] = {0};

	fd_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_sock == -1){
		perror("Error socket");
		return EXIT_FAILURE;
	}

	serv_len = sizeof(addr);

	memset(&addr, 0, serv_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Enter message (120 char):\n");
	scanf("%s", strbuff);

	fd_connect = connect(fd_sock, (struct sockaddr *) &addr, serv_len);
	if(fd_connect == -1){
		perror("Error listen1");
		return EXIT_FAILURE;
	}

	printf("\n Serv port: %d\n", ntohs(addr.sin_port));
	printf("\n Serv addr: %s\n", inet_ntoa(addr.sin_addr));

	num_send = send(fd_sock, strbuff, LEN_BUFF, 0);
	if(num_send == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	num_recv = recv(fd_sock, strbuff_recv, LEN_BUFF + 8, 0);
	if(num_recv == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	printf("\n Message receive: %s\n", strbuff_recv);

	close(fd_sock);
	return 0;
}