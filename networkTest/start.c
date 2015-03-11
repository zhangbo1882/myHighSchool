#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <linux/if_ether.h>
#define IFNAMESIZE 32
#define SRVPORT 10000
#define DST "10.10.10.10"
int main(int argc, char* argv[])
{
	char ifName[IFNAMESIZE] = "tun_1";
	int sockFd;
	int i;
	struct sockaddr_in dst;
	char buf[32]="Hello,world!";
	int len = sizeof(dst);
	int dstIp = inet_aton(DST,&dstIp);
	sockFd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockFd < 0)
	{
		fprintf(stderr,"Can create socket\n");
		exit(1);
	}
	dst.sin_family = AF_INET;
	dst.sin_port = SRVPORT;
	for(i = 0; i < 100; i++)
	{	
		dst.sin_addr.s_addr = dstIp++;
		if(sendto(sockFd, buf, 32, 0, &dst, len) == -1)
		{
			fprintf(stderr, "send fail\n");
			exit(1);
		}
	}

	return 1;
}
