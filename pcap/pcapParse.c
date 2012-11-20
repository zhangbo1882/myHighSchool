#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include "pcap.h"
#define MAX_ETH_FRAME 1514
#define MAX_HA_TYPE	20
#define PCAP_FILE_MAGIC 0xa1b2c3d4
extern int statics[MAX_HA_TYPE];
void printHelp(void)
{
	printf("Usage: hadump  -v -h -c -s number -b beginNumber1 -e endNumber2 fileName\n");
	printf("-v: display the packet in detail.\n"
		"-h: help.\n"
		"-c: display the total packet number.\n"
		"-s number: display the specify number packet.\n"
		"-b beginNumber1: display the packet from the number beginNumber1.\n"
		"-e endNumber2: display the packet upto the number endNumber.2\n");
}
int main(int argc, char *argv[])
{
	pcap_file_header pfh;
	pcap_header ph;
	int count = 0;
	void *buff = NULL;
	char *pcapFile = argv[argc - 1];
	const char *optstring = "vhcb:e:s:";
	char option;
	bool verbose = FALSE;
	bool onlyTotal = FALSE;
	int begin = 0;
	int end = 0;
	int readSize = 0;
/*	int pos = 0; */
	int captureLen = 0;
	if(argc < 2)
	{
		printHelp();
		return 0;
	}
	while((option = getopt(argc, argv, optstring)) != -1)
	{
		switch(option)
		{
			case 'v':
				verbose = TRUE;
				break;
			case 'h':
				printHelp();
				return 0;
			case 'c':
				onlyTotal = TRUE;		
				break;
			case 's':
				if(optarg == NULL)
				{
					printHelp();
					return 0;
				}
				begin = atoi(optarg);
				end = begin;
				break;
			case 'b':
				if(optarg == NULL)
				{
					printHelp();
					return 0;
				}
				begin = atoi(optarg);
				break;
			case 'e':
				if(optarg == NULL)
				{
					printHelp();
					return 0;
				}
				end = atoi(optarg);
				break;
			
		}
		
	}
	FILE *fp = fopen(pcapFile, "rw");
	if(!fp)
	{
		printf("File (%s) does not exist\n", pcapFile);
		return -1;
	}
	fread(&pfh, sizeof(pcap_file_header), 1, fp);
	if(ntohl(pfh.magic) != PCAP_FILE_MAGIC)
	{
		printf("Unsupported file type, please use pcap file\n");
		return 0;
	}
#if 0
	dumpPcapFileHeader(&pfh);
	pos = ftell(fp);
	printf("Current Pos: %d\n", pos);
#endif
	buff = (void *)malloc(MAX_ETH_FRAME);
	if(!buff)
	{
		printf("Can not malloc memory\n");
		return -1;
	}
	while(++count)
	{
		memset(buff, 0, MAX_ETH_FRAME);
		fread(&ph, sizeof(pcap_header), 1, fp);
		if(feof(fp))
		{
			break;
		}
#if 0		
		dumpPcapHeader(&ph);
		pos = ftell(fp);
		printf("CUrrent Pos: %d\n", pos);
#endif
		captureLen = ntohl(ph.capture_len);
		fread(buff, captureLen, 1,fp);
		if(feof(fp))
		{
			printf("Read Error\n");
			break;
		}
		if(!onlyTotal &&  begin <= count  && ( end ? count <= end : 1))
		{	
			printf("Packet Number %d\n",count);
			dumpPacket(buff, captureLen, verbose);
			printf("\n");
		}
#if 0
		pos = ftell(fp);
		printf("Current Pos: %d\n", pos);
#endif
	}
	if(onlyTotal)
	{
		printf("There are %u packets\n", count - 1);
	}
	else
	{
		printStatics();
	}
	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}
	return 0;
	
}
