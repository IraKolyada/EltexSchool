#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
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
	struct sockaddr_in addr_client = {0};
	struct sockaddr_in addr_srv = {0};
	char str[BUFF_LEN] = {0};
	socklen_t addr_size = 0; 

	fd_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd_sock == -1){
		halt("socket");
	}

	/*
	* The client is waiting for a broadcast, then he needs fixed port and corresponding address
	*/
	addr_size = sizeof(addr_client);
	addr_client.sin_family = AF_INET;
	addr_client.sin_port = htons(CLT_PORT);
	addr_client.sin_addr.s_addr = inet_addr(CLT_ADDR);
	if (bind(fd_sock, (struct sockaddr *)&addr_client, addr_size) == -1){
		close(fd_sock);
		halt("bind");
	}

	// Wait broadcast
	while (1){
		if (recvfrom(fd_sock, str, BUFF_LEN, 0, (struct sockaddr *)&addr_srv, &addr_size) == -1){
			perror("recvfrom");            
			break;
		}
		if (!strcmp(str, "disconnect"))
			break;
		printf("Received from server: %s\n", str);
	}

	if(close(fd_sock) == -1)
		halt("Error close");

	return 0;
}
