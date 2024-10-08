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
#define LEN_BUFF 20

int main(void)
{
	struct sockaddr_in addr = {0}, clienta_addr = {0};
	int fd_sock = -1, num_bind = -1;
	int num_recv = -1, num_send = -1;
	socklen_t soc_len = 0, client_len = 0;
	char strbuff[128] = {0};
	char plus_str[] = " + Serv";

	soc_len = sizeof(struct sockaddr_in);
	client_len = sizeof(clienta_addr);

	fd_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd_sock == -1){
		perror("Error socket");
		return EXIT_FAILURE;
	}

	memset(&addr, 0, soc_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	num_bind = bind(fd_sock, (struct sockaddr *) &addr, (soc_len));
	if(num_bind== -1){
		perror("Error bind");
		return EXIT_FAILURE;
	}

	printf("Listening...\n\n");

	num_recv = recvfrom(fd_sock, strbuff, LEN_BUFF, 0, (struct sockaddr *) &clienta_addr, &client_len);
	if(num_recv == -1){
		perror("Error recvfrom");
		return EXIT_FAILURE;
	}

	printf("\n Message received: %s\n",strbuff);
	printf("\n Client port: %d\n", ntohs(clienta_addr.sin_port));
	printf("\n Client addr: %s\n", inet_ntoa(clienta_addr.sin_addr));
	strcat(strbuff, plus_str);

	num_send = sendto(fd_sock, strbuff, LEN_BUFF, 0, (struct sockaddr *) &clienta_addr, client_len);
	if(num_send != 20){
		perror("Error sendto");
		return EXIT_FAILURE;
	}

	close(fd_sock);
	return 0;
}