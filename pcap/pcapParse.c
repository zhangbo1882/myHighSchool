#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include "pcap.h"
#define MAX_ETH_FRAME 1514
int main(int argc, char *argv[])
{
	pcap_file_header pfh;
	pcap_header ph;
	int count = 1;
	void *buff = NULL;
	char *pcapFile = argv[1];
	int readSize = 0;
//	int pos = 0;
	int captureLen = 0;
	if(argv[1] == NULL)
	{
		printf("Please input the .pcap file name\n");
		return 0;
	}
	printf("pcapFile: %s\n", pcapFile);
		
	FILE *fp = fopen(pcapFile, "rw");
	if(!fp)
	{
		printf("File (%s) does not exist\n", pcapFile);
		return -1;
	}
	fread(&pfh, sizeof(pcap_file_header), 1, fp);
//	dumpPcapFileHeader(&pfh);
//	pos = ftell(fp);
//	printf("Current Pos: %d\n", pos);
	buff = (void *)malloc(MAX_ETH_FRAME);
	if(!buff)
	{
		printf("Can not malloc memory\n");
		return -1;
	}
	while(count++)
	{
		memset(buff, 0, MAX_ETH_FRAME);
		fread(&ph, sizeof(pcap_header), 1, fp);
		if(feof(fp))
		{
			printf("End of File\n");
			break;
		}
//		dumpPcapHeader(&ph);
//		pos = ftell(fp);
//		printf("CUrrent Pos: %d\n", pos);
		captureLen = ntohl(ph.capture_len);
		fread(buff, captureLen, 1,fp);
		if(feof(fp))
		{
			printf("Read Error\n");
			break;
		}
		printf("Packet Number %d\n",count-1);
		dumpPacket(buff, captureLen);
		printf("\n");
//		pos = ftell(fp);
//		printf("Current Pos: %d\n", pos);
	}
	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}
	return 0;
	
}
