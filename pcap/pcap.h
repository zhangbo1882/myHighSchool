#ifndef pcaptest_pcap_h
#define pcaptest_pcap_h
typedef unsigned int  bpf_u_int32;
typedef unsigned short  u_short;
typedef unsigned short uint16;
typedef int uint32;
typedef int bpf_int32;
typedef unsigned char uint8;   
typedef int bool;
#define	TRUE	1
#define	FALSE	0	
typedef struct pcap_file_header {
	bpf_u_int32 magic;
	u_short version_major;
	u_short version_minor;
	bpf_int32 thiszone;    
	bpf_u_int32 sigfigs;   
	bpf_u_int32 snaplen;   
	bpf_u_int32 linktype;  
}pcap_file_header;

typedef struct  timestamp{
	bpf_u_int32 timestamp_s;
	bpf_u_int32 timestamp_ms;
}timestamp;
 
typedef struct pcap_header{
 	timestamp ts;
	bpf_u_int32 capture_len;
	bpf_u_int32 len;
				 
 }pcap_header;
 
void printStatics(void); 
void dumpPcapFileHeader(pcap_file_header *pfh);
void dumpPcapHeader(pcap_header *ph);
void dumpPacket(void *data, size_t size, bool verbose);
void dumpHaPacket(void *data, size_t size, bool verbose);
void dumpHaHeartBeat(void *data, size_t size);
void dumpHaFindPeer(void *data, size_t size);
void dumpHaFoundPeer(void *data, size_t size);
void dumpHaCommand(void *data, size_t size);
void dumpHaCommandResult(void *data, size_t size);
void dumpHaConfig(void *data, size_t size);
void dumpHaConfigAck(void *data, size_t size);
void dumpHaFirmware(void *data, size_t size);
void dumpHaFirmwareAck(void *data, size_t size);
void dumpHaUpgrade(void *data, size_t size);
void dumpHaSyncData(void *data, size_t size);
void dumpSvrrpPacket(void *data, size_t size);
void dumpSvrrpHeartBeat(void *data, size_t size);
#endif
