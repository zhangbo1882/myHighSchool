#ifndef pcaptest_pcap_h
#define pcaptest_pcap_h
typedef unsigned int  bpf_u_int32;
typedef unsigned short  u_short;
typedef unsigned short uint16;
typedef int uint32;
typedef int bpf_int32;
typedef unsigned char uint8;   
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
 
 
void dumpPcapFileHeader(pcap_file_header *pfh);
void dumpPcapHeader(pcap_header *ph);
void dumpPacket(void *data, size_t size);
void dumpHaPacket(void *data, size_t size);
void dumpHaHeartBeat(void *data, size_t size);
void dumpSvrrpPacket(void *data, size_t size);
void dumpSvrrpHeartBeat(void *data, size_t size);
#endif
