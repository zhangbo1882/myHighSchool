#ifndef __SONICHA__H__
#define __SONICHA__H__

#define SHAP_AUTHDATA_SIZE	16

typedef struct HaShapHeader
{
	uint8 	headerVersion:4,
		authType:4;
	uint8	type;
	uint8	version; /* This is same as Heartbeat version refered in the code*/
	uint8	svrrpNodeId;
	uint16	length;
	uint16	checksum;
	uint8	authenticationData[SHAP_AUTHDATA_SIZE];
}__attribute__((packed)) HaShapHeader;

typedef struct HaShapHeartbeatBase
{
	uint8	priority;
	uint8 	minorHbVersion;
	uint8 	hwModuleInfo; /*hardwareId is stale now*/
	uint8	blankVendorId; /*This needs to be blank , for interoperability with hb version 4.0*/
	/*uint16	blank2;	*/	/*Reserver for other usage*/
	uint8	lastLinkChgStatusInfo;
	uint8	lastLinkChgIfNum;
	uint32	firmware;
	uint32	prefsTimeStampHigh;
	uint8	state;
	uint8 	numTlvs;
	uint32	haFlags;
	uint32	stableLinkWeight;
	uint32	prefsTimeStampLow;
	uint32	haGroup;
	uint32	unstableLinkWeight; /*BR: Added Unstable link weight in the heartbeat message */
	uint32	randomNum;
}__attribute__((packed)) HaShapHeartbeatBase;


#define HA_TYPE	0xA156
#define HA_SYNC_TYPE	0xA159
#define HA_SVRRP_TYPE	0xA154
#define MAX_HA_TYPE	20
#define MAX_HA_STATE	7


#define SHAP_HEADER_SIZE	24

#define SHAP_TYPE_HEARTBEAT	1
#define SHAP_TYPE_FIND_PEER	2
#define SHAP_TYPE_FOUND_PEER	3
#define SHAP_TYPE_COMMAND	4
#define SHAP_TYPE_COM_REST	5
#define SHAP_TYPE_CONFIG	6
#define SHAP_TYPE_CONFIG_ACK	7
#define SHAP_TYPE_FIRMWARE	8
#define SHAP_TYPE_FIRMWARE_ACK	9
#define SHAP_TYPE_UPGRADE	10
#define SHAP_TYPE_SYNC_DATA	11
#define SHAP_TYPE_SVRRP_HEARTBEAT	12
#define SHAP_TYPE_SVRRP_FIND_PEER	13
#define SHAP_TYPE_SVRRP_FOUND_PEER	14




/* SHAP packet header: offsets are from the beginning of the SHAP packet */
#define SHAP_VERS_AUTH_OFFSET		0
#define SHAP_TYPE_OFFSET			1
#define SHAP_VERSION_OFFSET			2
#define SHAP_SVRRP_NODEID_OFFSET		3
#define SHAP_LENGTH_OFFSET			4
#define SHAP_CHECKSUM_OFFSET		6
#define SHAP_AUTHDATA_OFFSET		8

/* SHAP heartbeat packet: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_HB_PRIORITY_OFFSET				0
#define SHAP_HB_MINORVERSION_OFFSET			1
#define SHAP_HB_HWMODULEINFO_OFFSET			2
#define SHAP_HB_VENDORID_OFFSET				3
#define SHAP_HB_LINKCHG_STATUS_INFO_OFFSET		4
#define SHAP_HB_LINKCHG_IFNUM_OFFSET			5
#define SHAP_HB_FIRMWARE_OFFSET				6
#define SHAP_HB_HIGHTIMESTAMP_OFFSET				10
#define SHAP_HB_STATE_OFFSET				14
#define SHAP_HB_NUMTLVS_OFFSET				15
#define SHAP_HB_HA_FLAGS_OFFSET				16
#define SHAP_HB_STATUS_OFFSET				20
#define SHAP_HB_TIMESTAMP_OFFSET			24
#define SHAP_HB_HAGROUP_OFFSET				28
#define SHAP_HB_UNSTABLE_OFFSET				32
#define SHAP_HB_RANDOMNUM_OFFSET			36











#endif
