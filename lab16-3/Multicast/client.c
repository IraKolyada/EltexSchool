#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define CLT_PORT 33333
#define CLT_ADDR "127.0.0.1"
#define GRP_ADDR "239.0.0.34"
#define LEN_BUFF 64

void halt(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main()
{
	int fd_sock;
	struct sockaddr_in addr_clt;
	struct sockaddr_in addr_srv;
	struct ip_mreqn mreq; // Registration on multicast
	char str[LEN_BUFF];
	socklen_t addr_size;

	// Create socket
	fd_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd_sock == -1){
		halt("socket");
	}
	addr_size = sizeof(addr_clt);
	addr_clt.sin_family = AF_INET;
	addr_clt.sin_port = htons(CLT_PORT);
	addr_clt.sin_addr.s_addr = inet_addr(CLT_ADDR);
	if (bind(fd_sock, (struct sockaddr *)&addr_clt, addr_size) == -1){
		close(fd_sock);
		halt("bind");
	}

	// Registration on multicast
	//htonl(INADDR_ANY);
	//inet_addr(CLT_ADDR);
	mreq.imr_multiaddr.s_addr = inet_addr(GRP_ADDR);
	mreq.imr_address.s_addr = inet_addr(CLT_ADDR);
	if (setsockopt(fd_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0){
		perror("setsockopt");
		exit(1);
	}

	// Wait multicast
	while (1){
		if (recvfrom(fd_sock, str, LEN_BUFF, 0, (struct sockaddr *)&addr_srv, &addr_size) == -1)
			halt("recvfrom");
		if (!strcmp(str, "disconnect"))
			break;
		printf("Received from server: %s\n", str);
	}

	if(close(fd_sock) == -1)
		halt("Error close");

	return 0;
}
