#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pcap.h"
#include "ha.h"
#define ETH_DST_OFFSIZE 0
#define ETH_SRC_OFFSIZE 6
#define ETH_TYPE_OFFSIZE 12
#define ETHER_HDR_SIZE 14
#define MACFORMAT	"%02x:%02x:%02x:%02x:%02x:%02x"
#define MACPARAM(x)	(unsigned char)(x)[0],(unsigned char)(x)[1],(unsigned char)(x)[2],(unsigned char)(x)[3],(unsigned char)(x)[4],(unsigned char)(x)[5]		
#define IPFORMAT "%u.%u.%u.%u"
#define IPPARAM(x) (x >> 24), ((x & 0x00ff0000) >> 16), ((x & 0x0000ff00) >> 8) , (x & 0x000000ff)

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

char *haConfigTypeMap[5]={
		"None",
		"Preference",
		"Http Post",
		"Record",
};

char *haConfigAckTypeMap[5]={
		"None",
		"Preference",
		"Http Post",
		"Ack",
		"Record",
};

char *haCommandTypeMap[10]={
		"None",
		"get login",
		"stateful flush",
		"stateful synced",
		"stateful now allowed",
		"send heartbeat",
		"send VPN information",
		"send SVRRP LLB",
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
void dumpPacket(void *data, size_t size, bool verbose)
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
	printf("\t%-20s:	"MACFORMAT"\n", "destination mac", MACPARAM(p + ETH_DST_OFFSIZE));
	printf("\t%-20s:	"MACFORMAT"\n", "source mac",  MACPARAM(p + ETH_SRC_OFFSIZE));
	printf("\t%-20s:	%s(0x%04x)\n", "ethtype",  type, ethType);
	if(ethType != HA_TYPE && ethType != HA_SYNC_TYPE && ethType != HA_SVRRP_TYPE)
	{
		printf("\tNone HA packet\n");
		return ;
	}
	switch(ethType)
	{
		case HA_TYPE:
			dumpHaPacket(ha,size - ETHER_HDR_SIZE, verbose);
			break;
		case HA_SYNC_TYPE:
			break;
		case HA_SVRRP_TYPE:
			break;
		default:
			printf("None HA Packet\n");
	}
}

void dumpHaPacket(void *data, size_t size, bool verbose)
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
	if(!verbose)
		return;
	switch(type)
	{
		case SHAP_TYPE_HEARTBEAT:
			dumpHaHeartBeat(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_FIND_PEER:
			dumpHaFindPeer(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_FOUND_PEER:
			dumpHaFoundPeer(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_COMMAND:
			dumpHaCommand(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_COM_REST:
			dumpHaCommandResult(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_CONFIG:
			dumpHaConfig(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_CONFIG_ACK:
			dumpHaConfigAck(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_FIRMWARE:
			dumpHaFirmware(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_FIRMWARE_ACK:
			dumpHaFirmwareAck(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
			break;
		case SHAP_TYPE_UPGRADE:
			dumpHaUpgrade(data + SHAP_HEADER_SIZE, size - SHAP_HEADER_SIZE);
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
	uint8 *hbPkt = hb + SHAP_HEARTBEAT_SIZE;
	uint16 tlvType = 0; 
	uint16 tlvLen  = 0;
	uint32 leftLen = size - SHAP_HEARTBEAT_SIZE;
	
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
	while(leftLen > 0)
	{

		tlvType = ntohs(*(uint16 *)hbPkt);
		tlvLen = ntohs(*(uint16 *)(hbPkt + sizeof(tlvType)));

		switch(tlvType)
		{
			case HA_TLV_TYPE_LICENSE_INFO:
				printf("\t\t\t\t%-20s:	%s\n", "tlv type", "License");
				printf("\t\t\t\t%-20s:	%u\n", "tlv len", tlvLen);
				printf("\t\t\t\t%-20s:	", "data");
				dumpHex(hbPkt + sizeof(tlvType) + sizeof(tlvLen), tlvLen);
				break;
			case HA_TLV_TYPE_CORE_UTIL:
				printf("\t\t\t\t%-20s:	%s\n", "tlv type", "Core Util");
				printf("\t\t\t\t%-20s:	%u\n", "tlv len", tlvLen);
				printf("\t\t\t\t%-20s:	", "data");
				dumpHex(hbPkt + sizeof(tlvType) + sizeof(tlvLen), tlvLen);
				break;
			case HA_TLV_TYPE_SVRRP_INFO:
				printf("\t\t\t\t%-20s:	%s\n", "tlv type", "Svrrp Info");
				printf("\t\t\t\t%-20s:	%u\n", "tlv len", tlvLen);
				break;
	
			default:
				printf("\t\t\t\t%-20s:	%u\n","Unknow TLV type", tlvType);
			break;
		}
		leftLen = leftLen - sizeof(tlvType) - sizeof(tlvLen) -  tlvLen;
		hbPkt = hbPkt + sizeof(tlvType) + sizeof(tlvLen) + tlvLen;
	}
	


}

void dumpHaFindPeer(void *data, size_t size)
{

	uint8 *fp = (uint8 *)data;
	printf("\t\t%-20s\n", "[Find Peer]");
	printf("\t\t\t%-20s:	"MACFORMAT"\n","my mac address", MACPARAM(fp + SHAP_FP_MY_MAC_OFFSET));
	printf("\t\t\t%-20s:	"MACFORMAT"\n","peer mac address", MACPARAM(fp + SHAP_FP_PEER_MAC_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "hardware id", *(fp + SHAP_FP_HARDWAREID_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "module info", *(fp + SHAP_FP_HWMODULEINFO_OFFSET));
	printf("\t\t\t%-20s:	0x%08x\n", "firmware", ntohl(*(uint32 *)(fp + SHAP_FP_FIRMWARE_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "ha group", ntohl(*(uint32 *)(fp + SHAP_FP_HAGROUP_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "primary", *(fp + SHAP_FP_ISPRIMARY_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "interface number", ntohl(*(uint32 *)(fp + SHAP_FP_IFNUM_OFFSET)));
	printf("\t\t\t%-20s:	%02x%02x%02x%02x%02x%02x\n", "my serial number", MACPARAM(fp + SHAP_FP_MY_SERIAL_OFFSET));
	printf("\t\t\t%-20s:	%02x%02x%02x%02x%02x%02x\n", "peer serial number", MACPARAM(fp + SHAP_FP_PEER_SERIAL_OFFSET));


}

void dumpHaFoundPeer(void *data, size_t size)
{
	uint8 *fo = (uint8 *)data;
	printf("\t\t%-20s\n", "[Found Peer]");
	printf("\t\t\t%-20s:	"MACFORMAT"\n","my mac address", MACPARAM(fo + SHAP_FO_MY_MAC_OFFSET));
	printf("\t\t\t%-20s:	"IPFORMAT"\n","my ip address", IPPARAM(ntohl(*(uint32 *)(fo + SHAP_FO_MY_IP_OFFSET))));
	printf("\t\t\t%-20s:	%u\n", "hardware id", *(fo + SHAP_FO_HARDWAREID_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "vendor id", *(fo + SHAP_FO_VENDORID_OFFSET));
	printf("\t\t\t%-20s:	0x%08x\n", "firmware", ntohl(*(uint32 *)(fo + SHAP_FO_FIRMWARE_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "timestamp", ntohl(*(uint32 *)(fo + SHAP_FO_TIMESTAMP_OFFSET)));
	printf("\t\t\t%-20s:	%u\n", "ha group", ntohl(*(uint32 *)(fo + SHAP_FO_HAGROUP_OFFSET)));

}

void dumpHaCommand(void *data, size_t size)
{
	uint8 *cm = (uint8 *)data;
	uint32 type = ntohl(*(uint32 *)(cm + SHAP_CM_TYPE_OFFSET));
	assert(type < 8);
	printf("\t\t%-20s\n", "[Command]");
	printf("\t\t\t%-20s:	%s(%u)\n", "type", haCommandTypeMap[type], type);


}

void dumpHaCommandResult(void *data, size_t size)
{
	uint8 *cr = (uint8 *)data;
	uint32 type = ntohl(*(uint32 *)(cr + SHAP_CR_TYPE_OFFSET));
	uint16 len = ntohs(*(uint16 *)(cr + SHAP_CR_DATA_LEN_OFFSET));
	assert(type < 8);
	printf("\t\t%-20s\n", "[Command Result]");
	printf("\t\t\t%-20s:	%s(%u)\n", "type", haCommandTypeMap[type], type);
	printf("\t\t\t%-20s:	%u\n", "data len", len);
	printf("\t\t\t%-20s\n", "[Data]");
	switch(type)
	{
		case SHAP_CM_GET_LOGIN:
			printf("\t\t\t%-20s:	", "random number");
			dumpHex(cr + SHAP_CR_DATA_OFFSET, HA_RANDOMSTRING_SIZE);
			printf("\t\t\t%-20s:	", "auth seed");
			dumpHex(cr + SHAP_CR_DATA_OFFSET + HA_RANDOMSTRING_SIZE, HA_RANDOMSTRING_SIZE);
			printf("\t\t\t%-20s:	", "admin name");
			dumpHex(cr + SHAP_CR_DATA_OFFSET + HA_RANDOMSTRING_SIZE + HA_RANDOMSTRING_SIZE, HA_ADMIN_NAME_SIZE);
			printf("\t\t\t%-20s:	", "password");
			dumpHex(cr + SHAP_CR_DATA_OFFSET + HA_RANDOMSTRING_SIZE + HA_RANDOMSTRING_SIZE + HA_ADMIN_NAME_SIZE, HA_ADMIN_PASSWORD_SIZE);
			break;
		default:
		dumpHex(cr + SHAP_CR_DATA_OFFSET, len);
		break;
		
	}
}

void dumpHaConfig(void *data, size_t size)
{
	uint8 *cf = (uint8 *)data;
	uint16 type = ntohs(*(uint16 *)(cf + SHAP_CF_TYPE_OFFSET)); 
	assert(type < 4);
	printf("\t\t%-20s\n", "[Config]");
	printf("\t\t\t%-20s:	%s(%u)\n", "type", haConfigTypeMap[type], type);
	printf("\t\t\t%-20s:	%u\n", "left block number", ntohs(*(uint16 *)(cf + SHAP_CF_LEFT_BNUM_OFFSET)));
}

void dumpHaConfigAck(void *data, size_t size)
{
	uint8 *ca = (uint8 *)data;
	uint16 type = ntohs(*(uint16 *)(ca + SHAP_CA_TYPE_OFFSET));
	assert(type< 5);
	printf("\t\t%-20s\n", "[Config Ack]");
	printf("\t\t\t%-20s:	%s(%u)\n", "type", haConfigAckTypeMap[type], type);
	printf("\t\t\t%-20s:	%u\n", "error code", ntohl(*(uint32 *)(ca + SHAP_CA_ERROR_CODE_OFFSET)));
	printf("\t\t\t%-20s:	", "data");
	dumpHex(ca + SHAP_CA_DATA_OFFSET, 4);
}

void dumpHaFirmware(void *data, size_t size)
{
	uint8 *fw = (uint8 *)data;
	printf("\t\t%-20s\n", "[Firmware]");
	printf("\t\t\t%-20s:	%u\n", "left block number", ntohl(*(uint32 *)(fw + SHAP_FW_LEFT_BNUM_OFFSET)));
	printf("\t\t\t%-20s:	\n", "data");
}

void dumpHaFirmwareAck(void *data, size_t size)
{
	uint8 *fa = (uint8 *)data;
	printf("\t\t%-20s\n", "[Firmware Ack]");
	printf("\t\t\t%-20s:	%u\n", "type",*(fa + SHAP_FA_TYPE_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "error code",*(fa + SHAP_FA_FW_STATUS_OFFSET));
	printf("\t\t\t%-20s:	%u\n", "block number", ntohl(*(uint32 *)(fa + SHAP_FA_BLOCK_NUM_OFFSET)));
	
}

void dumpHaUpgrade(void *data, size_t size)
{
	uint8 *up = (uint8 *)data;
	uint16 type = ntohs(*(uint16 *)(up + SHAP_UP_TYPE_OFFSET));
	printf("\t\t%-20s\n", "[Upgrade]");
	printf("\t\t\t%-20s:	%u\n", "type", type);
	if(size - sizeof(type) > 0)
	{
		printf("\t\t\t%-20s:	", "data");
		dumpHex(up + SHAP_UP_DATA_OFFSET, size - sizeof(type));
	}
}
