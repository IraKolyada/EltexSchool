#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

#define LEN_BUFF 1024
#define DGR_SIZE 4096

typedef struct udp_header
{
	uint16_t src_port; //source port
	uint16_t dst_port; //destinanion port
	uint16_t len;      //lenght header
	uint16_t checksum;
}udp_header_t;

void halt(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(void){
	struct sockaddr_in addr = {0};
	udp_header_t udp_head = {0};
	int fd_rawsock = -1;
	int num_send = -1;
	socklen_t soc_len = 0;
	uint16_t dgr_len;
	char strbuff[LEN_BUFF] = {0};
	char dgrbuff[DGR_SIZE] = {0};

	soc_len = sizeof(struct sockaddr_in);

	fd_rawsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(fd_rawsock == -1){
		halt("Error socket");
	}

	memset(&addr, 0, soc_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5566);
	inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));

	strcpy(strbuff, "Raw dgram");

	//Total lenght of the package
	dgr_len = sizeof(udp_header_t) + strlen(strbuff);

	//UDP header

	udp_head.src_port = htons(6655);
	udp_head.dst_port = htons(5566);
	udp_head.len = htons(dgr_len);
	udp_head.src_port = 0;

	memcpy((void *) dgrbuff, (void *) &udp_head, sizeof(udp_header_t));
	memcpy((void *) dgrbuff + sizeof(udp_header_t),(void *) &strbuff, strlen(strbuff));

	num_send = sendto(fd_rawsock, dgrbuff, dgr_len, 0, (struct sockaddr *) &addr, soc_len);
	if(num_send == -1){
		halt("Error sendto");
	}

	if(close(fd_rawsock) == -1)
		halt("Error close");

	return 0;
}
