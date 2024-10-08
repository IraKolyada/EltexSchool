#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BACKLOG 1
#define LEN_BUFF 128

int main(void)
{
	struct sockaddr_in addr = {0}, client_addr = {0};
	int fd_sock = -1, fd_cl = -1, num_bind = -1, num_listen = -1;
	int num_recv = -1, num_send = -1;
	socklen_t soc_len = 0, client_len = 0;
	char strbuff[128] = {0};
	char plus_str[] = " + Serv";

	soc_len = sizeof(addr);
	client_len = sizeof(client_addr);

	fd_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_sock == -1){
		perror("Error socket");
		return EXIT_FAILURE;
	}

	memset(&addr, 0, soc_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	num_bind = bind(fd_sock, (struct sockaddr *) &addr, soc_len);
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

	fd_cl = accept(fd_sock,(struct sockaddr*)&client_addr, &client_len);
	if(fd_cl == -1){
		perror("Error accept");
		return EXIT_FAILURE;
	}

	printf("\n Client port: %d\n", ntohs(client_addr.sin_port));
	printf("\n Client addr: %s\n", inet_ntoa(client_addr.sin_addr));

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