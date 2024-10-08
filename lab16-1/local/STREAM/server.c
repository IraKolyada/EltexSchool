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
	int fd_sock = -1, fd_cl = -1, num_bind = -1, num_listen = -1;
	int num_recv = -1, num_send = -1;
	char strbuff[128] = {0};
	char plus_str[] = " + Serv";

	fd_sock = socket(AF_LOCAL,SOCK_STREAM,0);
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

	num_listen = listen(fd_sock,BACKLOG);
	if(num_listen == -1){
		perror("Error listen");
		return EXIT_FAILURE;
	}

	printf("Listen...");


	fd_cl = accept(fd_sock, NULL, NULL);
	if(fd_cl == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	num_recv = recv(fd_cl, strbuff, LEN_BUFF, 0);
	if(num_recv == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	printf("\n %s\n",strbuff);
	strcat(strbuff, plus_str);

	num_send = send(fd_cl, strbuff, LEN_BUFF, 0);
	if(num_send == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	close(fd_cl);


	close(fd_sock);
	return 0;
}