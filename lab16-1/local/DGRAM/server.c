#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SOCK_F_NAME "socket1"
#define BACKLOG 1
#define LEN_BUFF 20

int main(void)
{
	struct sockaddr_un addr = {0}, clienta_addr = {0};
	int fd_sock = -1, num_bind = -1;
	int num_recv = -1, num_send = -1;
	socklen_t client_len = 0;
	char strbuff[128] = {0};
	char plus_str[] = " + Serv";

	fd_sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(fd_sock == -1){
		perror("Error socket");
		return EXIT_FAILURE;
	}

	if((remove(SOCK_F_NAME) == -1) && (errno != ENOENT)){
		printf("Error: remove %s", SOCK_F_NAME);
	}
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_LOCAL;
	strncpy(addr.sun_path, SOCK_F_NAME, sizeof(addr.sun_path) - 1);

	num_bind = bind(fd_sock, (struct sockaddr *) &addr, (sizeof(struct sockaddr_un) -1));
	if(num_bind== -1){
		perror("Error bind");
		return EXIT_FAILURE;
	}

	client_len = sizeof(struct sockaddr_un);

	num_recv = recvfrom(fd_sock, strbuff, LEN_BUFF, 0, (struct sockaddr *) &clienta_addr, &client_len);
	if(num_recv == -1){
		perror("Error recvfrom");
		return EXIT_FAILURE;
	}

	printf("\n Message received: %s\n",strbuff);
	printf("\n Client sun_path: %s\n", clienta_addr.sun_path);
	strcat(strbuff, plus_str);

	num_send = sendto(fd_sock, strbuff, LEN_BUFF, 0, (struct sockaddr *) &clienta_addr, client_len);
	if(num_send != 20){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	close(fd_sock);
	return 0;
}