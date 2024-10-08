#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SOCK_F_NAME "socket1"
#define BACKLOG 1
#define LEN_BUFF 120

int main(void)
{
	struct sockaddr_un addr = {0}, client_addr = {0};
	int fd_sock = -1, fd_connect = -1;
	int num_bind = -1, num_send = -1, num_recv = -1;
	socklen_t serv_len = 0;
	char strbuff[120] = {0};
	char strbuff_recv[128] = {0};

	fd_sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(fd_sock == -1){
		perror("Error socket");
		return EXIT_FAILURE;
	}

	serv_len = sizeof(struct sockaddr_un);

	memset(&client_addr, 0, serv_len);
	client_addr.sun_family = AF_LOCAL;
	snprintf(client_addr.sun_path,serv_len,"socket1.%ld",(long)getpid());


	num_bind = bind(fd_sock, (struct sockaddr *) &client_addr, (sizeof(struct sockaddr_un) -1));
	if(num_bind== -1){
		perror("Error bind");
		return EXIT_FAILURE;
	}


	memset(&addr, 0, serv_len);
	addr.sun_family = AF_LOCAL;
	strncpy(addr.sun_path, SOCK_F_NAME, sizeof(addr.sun_path) - 1);

	fd_connect = connect(fd_sock, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));
	if(fd_connect == -1){
		perror("Error listen1");
		return EXIT_FAILURE;
	}

	printf("Enter message (120 char):\n");
	scanf("%s", strbuff);

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

	/*num_send = sendto(fd_sock, strbuff, LEN_BUFF, 0, (struct sockaddr *) &addr, serv_len);
	if(num_send == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	num_recv = recvfrom(fd_sock, strbuff_recv, LEN_BUFF + 50, 0, (struct sockaddr *) &addr, &serv_len);
	if(num_recv == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}*/


	printf("\n Message receive: %s\n", strbuff_recv);
	printf("\n Server sun_path: %s\n", addr.sun_path);


	close(fd_sock);
	//remove();
	return 0;
}