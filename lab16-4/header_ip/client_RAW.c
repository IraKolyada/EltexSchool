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

#define BACKLOG 1
#define LEN_BUFF 1024
#define DGR_SIZE 4096

typedef struct udp_header
{
	uint16_t src_port; //source port
	uint16_t dst_port; //destinanion port
	uint16_t len;      //lenght header
	uint16_t checksum;
}udp_header_t;

typedef struct ip_header
{
	uint16_t ihl:4;       //lenght header ip packege
	uint16_t version:4;   //version of the protocol ip
	u_char ds;          //type serves
	uint16_t len;       //total lenght header
	uint16_t id;        //id packege
	uint16_t offset;    //
	u_char ttl;         //total time life
	u_char protocol;    //type protocol
	uint16_t checksum;
	uint32_t src_ip;    //source ip addr
	uint32_t dst_ip;    //destinanion ip addr
}ip_header_t;

void halt(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(void){
	struct sockaddr_in addr = {0};
	udp_header_t udp_head = {0};
	ip_header_t ip_head = {0};
	int fd_rawsock = -1;
	int num_send = -1;
	int op_val;
	socklen_t soc_len = 0;
	uint16_t dgr_len;
	uint16_t ip_len;
	char strbuff[LEN_BUFF] = {0};
	char dgrbuff[DGR_SIZE] = {0};

	soc_len = sizeof(struct sockaddr_in);

	fd_rawsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(fd_rawsock == -1){
		halt("Error socket");
	}

	if(setsockopt(fd_rawsock, IPPROTO_IP, IP_HDRINCL, &op_val, sizeof(op_val) < 0)){
		halt("Error setsockopt");
	}

	memset(&addr, 0, soc_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5566);
	inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));

	strcpy(strbuff, "Raw dgram");

	printf("GO\n");

	//Total lenght of the package
	dgr_len = sizeof(udp_header_t) + strlen(strbuff);
	ip_len = sizeof(udp_header_t) + sizeof(ip_header_t) + strlen(strbuff);

	//IP header
	ip_head.ihl = 5;
	ip_head.version = 4;
	ip_head.ds = 0;
	ip_head.len = 0;
	ip_head.offset = 0;
	ip_head.ttl = 255;
	ip_head.protocol = IPPROTO_UDP;
	ip_head.checksum = 0;
	//inet_pton(AF_INET, "127.0.0.1", &(ip_head.src_ip));
	inet_pton(AF_INET, "127.0.0.1", &(ip_head.dst_ip));

	//UDP header
	udp_head.src_port = htons(6655);
	udp_head.dst_port = htons(5566);
	udp_head.len = htons(dgr_len);
	udp_head.src_port = 0;

	memcpy(dgrbuff, &ip_head, sizeof(ip_header_t));
	memcpy(dgrbuff + sizeof(ip_header_t), (void *) &udp_head, sizeof(udp_header_t));
	memcpy(dgrbuff + sizeof(ip_header_t) + sizeof(udp_header_t),(void *) &strbuff, strlen(strbuff));

	num_send = sendto(fd_rawsock, dgrbuff, ip_len, 0, (struct sockaddr *) &addr, soc_len);
	if(num_send == -1){
		halt("Error sendto");
	}

	if(close(fd_rawsock) == -1)
		halt("Error close");

	return 0;
}
