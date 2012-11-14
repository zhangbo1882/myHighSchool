#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pcap.h"
#include "sonicHA.h"
#define ETH_DST_OFFSIZE 0
#define ETH_SRC_OFFSIZE 6
#define ETH_TYPE_OFFSIZE 12
#define ETHER_HDR_SIZE 14
#define MACFORMAT	"%02x:%02x:%02x:%02x:%02x:%02x"
#define MACPARAM(x)	(unsigned char)(x)[0],(unsigned char)(x)[1],(unsigned char)(x)[2],(unsigned char)(x)[3],(unsigned char)(x)[4],(unsigned char)(x)[5]		


char *haTypeMap[20]={
		"None",
		"HeartBeat",
		"FindPeer",
		"FoundPeer",
		"Command",
		"ComRest",
		"Config",
		"ConfigAck",
		"Firmware",
		"FirmwareAck",
		"Upgrade",
		"Sync",
		"SvrrpHeartBeat",
		"SvrrpFindPeer",
		"SvrrpFoundPeer",
};

char *haStateMap[10]={
		"sleepState",
		"electionState",
		"idleState",
		"activeState",
		"errorState",
		"rebootState",
		"syncState",
		"haMaxState",
};



void dumpPcapFileHeader(pcap_file_header *pfh)
{
	if(pfh == NULL)
	{
		return;	
	}
	printf("====================\n"
		"Magic:	0x%0x\n"
		"Version_major:	%u\n"
		"Version_minor:	%u\n"
		"Thiszone:	%u\n"
		"Sigfigs:	%u\n"
		"Snaplen:	%u\n"
		"LinkType:	%u\n"
		"====================\n",
		ntohl(pfh->magic),
		ntohs(pfh->version_major),
		ntohs(pfh->version_minor),
		ntohl(pfh->thiszone),
		ntohl(pfh->sigfigs),
		ntohl(pfh->snaplen),
		ntohl(pfh->linktype));
}

void dumpPcapHeader(pcap_header *ph)
{
	printf("====================\n"
		"ts.timeStamp_s:	%u\n"
		"tstimeeStamp_ms:	%u\n"
		"capture_len:	%u\n"
		"len:	%u\n"
		"====================\n",
		ntohl(ph->ts.timestamp_s),
		ntohl(ph->ts.timestamp_ms),
		ntohl(ph->capture_len),
		ntohl(ph->len));
	
}

void dumpHex(uint8 *data, size_t size)
{
	int i = 0;
	printf("0x");
	for(i; i < size; i++)
	{
		printf("%02x", *data);
		data++;
	}
	printf("\n");
}
void dumpPacket(void *data, size_t size)
{
	int i = 0;
	char *p = (char *)data;
	char *type = NULL;
	char *ha = p + ETHER_HDR_SIZE; 
	uint16 ethType = ntohs(*((uint16 *)(p + ETH_TYPE_OFFSIZE)));
	switch(ethType)
	{
		case HA_TYPE:
			type = "HA Control Packet";
			break;
		case HA_SYNC_TYPE:
			type = "HA Stateful Sync Packet";
			break;
		case HA_SVRRP_TYPE:
			type = "HA SVRRP Control Packet";
			break;
		default:
			type = "Unknow HA Packet";
			break;
	}
	printf("\tDestination Mac:" MACFORMAT "\n", MACPARAM(p + ETH_DST_OFFSIZE));
	printf("\tSource Mac:" MACFORMAT "\n", MACPARAM(p + ETH_SRC_OFFSIZE));
	printf("\tEther Type: %s(0x%04x)\n", type, ethType);
	if(ethType != HA_TYPE && ethType != HA_SYNC_TYPE && ethType != HA_SVRRP_TYPE)
	{
		printf("\tNone HA packet\n");
		return ;
	}
	switch(ethType)
	{
		case HA_TYPE:
			dumpHaPacket(ha,size - ETHER_HDR_SIZE);
			break;
		case HA_SYNC_TYPE:
			break;
		case HA_SVRRP_TYPE:
			break;
		default:
			printf("None HA Packet\n");
	}
}

void dumpHaPacket(void *data, size_t size)
{
	uint8 *ha = (char *)data;
	uint8 *auth = ha + SHAP_AUTHDATA_OFFSET;
	uint8 type = *(ha + SHAP_TYPE_OFFSET);
	assert(type < MAX_HA_TYPE);
	printf("\t%-20s\n","[HA Header]");
	printf("\t\t%-20s:	%u\n", "auth version", *(ha + SHAP_VERSION_OFFSET));
	printf("\t\t%-20s:	%s(%u)\n", "type", haTypeMap[type], type);
	printf("\t\t%-20s:	%u\n", "version", *(ha + SHAP_VERSION_OFFSET));
	printf("\t\t%-20s:	%u\n", "svrrpNodeId", *(ha + SHAP_SVRRP_NODEID_OFFSET));
	printf("\t\t%-20s:	%u\n", "length", ntohs(*(uint16 *)(ha + SHAP_LENGTH_OFFSET)));
	printf("\t\t%-20s:	0x%04x\n", "checksum", ntohs(*(uint16 *)(ha + SHAP_CHECKSUM_OFFSET)));
	printf("\t\t%-20s:	", "authdata");
	dumpHex(auth, SHAP_AUTHDATA_SIZE);
	switch(type)
	{
		case SHAP_TYPE_HEARTBEAT:
			dumpHaHeartBeat(data + SHAP_HEADER_SIZE, size);
			break;
		case SHAP_TYPE_FIND_PEER:
			break;
		case SHAP_TYPE_FOUND_PEER:
			break;
		case SHAP_TYPE_COMMAND:
			break;
		case SHAP_TYPE_COM_REST:
			break;
		case SHAP_TYPE_CONFIG:
			break;
		case SHAP_TYPE_CONFIG_ACK:
			break;
		case SHAP_TYPE_FIRMWARE:
			break;
		case SHAP_TYPE_FIRMWARE_ACK:
			break;
		case SHAP_TYPE_UPGRADE:
			break;
		case SHAP_TYPE_SYNC_DATA:
			break;
		case SHAP_TYPE_SVRRP_HEARTBEAT:
			break;
		case SHAP_TYPE_SVRRP_FIND_PEER:
			break;
		case SHAP_TYPE_SVRRP_FOUND_PEER:
			break;

		default:
			printf("Unknow HA type\n");
			break;

	}

}

void dumpHaHeartBeat(void *data, size_t size)
{
	uint8 *hb = (uint8 *)data;
	uint8 state = *(hb + SHAP_HB_STATE_OFFSET);
	assert(state < MAX_HA_STATE);
	printf("\t\t%-20s\n", "[HeartBeat Header]");
	printf("\t\t\t%-20s:	%u\n", "priority", *(hb + SHAP_HB_PRIORITY_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "minor version",*(hb + SHAP_HB_MINORVERSION_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "hwModle",*(hb + SHAP_HB_HWMODULEINFO_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "vendor id",*(hb + SHAP_HB_VENDORID_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "link change status",*(hb + SHAP_HB_LINKCHG_STATUS_INFO_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "link change if",*(hb + SHAP_HB_LINKCHG_IFNUM_OFFSET));
	printf("\t\t\t%-20s:	0x%08x\n", "firmware",ntohl(*(uint32 *)(hb + SHAP_HB_FIRMWARE_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "high timestamp",ntohl(*(uint32 *)(hb + SHAP_HB_HIGHTIMESTAMP_OFFSET)));
	printf("\t\t\t%-20s:	%s(%u)\n", "state", haStateMap[state], state);
	printf("\t\t\t%-20s:	%u\n", "number TLV",*(hb + SHAP_HB_NUMTLVS_OFFSET));
	printf("\t\t\t%-20s:	0x%08x\n", "flag",ntohl(*(uint32 *)(hb + SHAP_HB_HAGROUP_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "stable link weight",ntohl(*(uint32 *)(hb + SHAP_HB_STATUS_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "timestamp",ntohl(*(uint32 *)(hb + SHAP_HB_TIMESTAMP_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "ha group",ntohl(*(uint32 *)(hb + SHAP_HB_HAGROUP_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "unstable link weight",ntohl(*(uint32 *)(hb + SHAP_HB_UNSTABLE_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "random number",ntohl(*(uint32 *)(hb + SHAP_HB_RANDOMNUM_OFFSET)));

	printf("\t\t\t%-20s\n", "[HeartBeat]");
	



}
