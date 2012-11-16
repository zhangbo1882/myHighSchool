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

typedef enum HaHbTlVType
{
	HA_TLV_TYPE_LICENSE_INFO = 1,
	HA_TLV_TYPE_CORE_UTIL,
	HA_TLV_TYPE_SVRRP_INFO

} HaHbTlvType;

#define HA_TYPE	0xA156
#define HA_SYNC_TYPE	0xA159
#define HA_SVRRP_TYPE	0xA154
#define MAX_HA_TYPE	20
#define MAX_HA_STATE	7


#define SHAP_HEADER_SIZE	24
#define SHAP_HEARTBEAT_SIZE	sizeof(HaShapHeartbeatBase)
#define SHAP_HEARTBEAT_BASESIZE		(SHAP_HEADER_SIZE + SHAP_HEARTBEAT_BASESIZE)
#define SVRRP_HEARTBEAT_BASESIZE	(SHAP_HEADER_SIZE + sizeof(SvrrpHeartbeatBase)) 
#define SVRRP_FIND_PEER_SIZE			(SHAP_HEADER_SIZE + sizeof(SvrrpFindPeer)) 
#define SVRRP_FOUND_PEER_SIZE			(SHAP_HEADER_SIZE + sizeof(SvrrpFoundPeer)) 
#define SHAP_FIND_PEER_SIZE			(SHAP_HEADER_SIZE + 39)
#define SHAP_FOUND_PEER_SIZE		(SHAP_HEADER_SIZE + 24)
#define SHAP_COMMAND_SIZE			(SHAP_HEADER_SIZE + 4)
#define SHAP_COM_REST_SIZE			ETHERMTU
#define SHAP_CONFIG_SIZE			ETHERMTU
#define SHAP_CONFIG_ACK_SIZE		(SHAP_HEADER_SIZE + 10)
#define SHAP_FIRMWARE_SIZE			ETHERMTU
#define SHAP_FIRMWARE_ACK_SIZE		(SHAP_HEADER_SIZE + 6)
#define SHAP_UPGRADE_SIZE			(SHAP_HEADER_SIZE + 20)		/* reserve space */

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


/* SHAP find peer packet: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_FP_MY_MAC_OFFSET				0
#define SHAP_FP_PEER_MAC_OFFSET				6
#define SHAP_FP_HARDWAREID_OFFSET			12
#define SHAP_FP_HWMODULEINFO_OFFSET				13
#define SHAP_FP_FIRMWARE_OFFSET				14
#define SHAP_FP_HAGROUP_OFFSET				18
#define SHAP_FP_ISPRIMARY_OFFSET			22
#define SHAP_FP_IFNUM_OFFSET				23
#define SHAP_FP_MY_SERIAL_OFFSET			27
#define SHAP_FP_PEER_SERIAL_OFFSET			33

/* SHAP found peer: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_FO_MY_MAC_OFFSET				0
#define SHAP_FO_MY_IP_OFFSET				6
#define SHAP_FO_HARDWAREID_OFFSET			10
#define SHAP_FO_VENDORID_OFFSET				11
#define SHAP_FO_FIRMWARE_OFFSET				12
#define SHAP_FO_TIMESTAMP_OFFSET			16
#define SHAP_FO_HAGROUP_OFFSET				20

/* SHAP command: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_CM_TYPE_OFFSET					0

#define SHAP_CM_GET_LOGIN					1
#define SHAP_CM_STATEFUL_FLUSH				2
#define SHAP_CM_STATEFUL_SYNCED				3
#define SHAP_CM_STATEFUL_NOT_ALLOWED		4
#define SHAP_CM_SEND_HEARTBEAT				5
#define SHAP_CM_SEND_VPNINFO				6
#define SHAP_CM_SVRRP_LLB_SYNC					7

/* SHAP command result: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_CR_TYPE_OFFSET			0
#define SHAP_CR_DATA_LEN_OFFSET		4
#define SHAP_CR_DATA_OFFSET			6

#define SHAP_CR_DATA_SIZE			(SHAP_COM_REST_SIZE - SHAP_HEADER_SIZE - 6)
#define SHAP_CR_HEADER_SIZE			(SHAP_HEADER_SIZE + 6)

#define HA_RANDOMSTRING_SIZE 33 
#define HA_ADMIN_NAME_SIZE 33
#define HA_ADMIN_PASSWORD_SIZE 64  

/* SHAP config: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_CF_TYPE_OFFSET			0
#define SHAP_CF_LEFT_BNUM_OFFSET	2
#define SHAP_CF_DATA_OFFSET			4

#define SHAP_CF_DATA_SIZE			(SHAP_CONFIG_SIZE - SHAP_HEADER_SIZE - 4)
#define SHAP_CF_HEADER_SIZE			(SHAP_HEADER_SIZE + 4)

#define SHAP_CF_TYPE_PREFERENCES	1
#define SHAP_CF_TYPE_HTTP_POST		2
#define SHAP_CF_TYPE_SYNC_RECORD	3

#define SHAP_CF_NUM_PACKET_ACK		5
#define SHAP_CF_ACK_PACKET_NUM		1

#define SHAP_CF_BLOCK_APP			0x00000001
#define SHAP_CF_FREE_BUFFER			0x00000002
#define SHAP_CF_SYNC_STATE			0x00000004
#define SHAP_CF_PREFERENCES			0x00000008


/* SHAP config ack: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_CA_TYPE_OFFSET				0
#define SHAP_CA_ERROR_CODE_OFFSET		2
#define SHAP_CA_DATA_OFFSET				6
#define SHAP_CA_RESULT_CODE_OFFSET		SHAP_CA_DATA_OFFSET
#define SHAP_CA_BLOCK_NUM_OFFSET		SHAP_CA_DATA_OFFSET

#define SHAP_CA_TYPE_PREFERENCES	1
#define SHAP_CA_TYPE_HTTP_POST		2
#define SHAP_CA_TYPE_ACK			3
#define SHAP_CA_TYPE_SYNC_RECORD	4

/* SHAP firmware: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_FW_LEFT_BNUM_OFFSET		0
#define SHAP_FW_DATA_OFFSET				4

#define SHAP_FW_DATA_SIZE			(SHAP_FIRMWARE_SIZE - SHAP_HEADER_SIZE - 4)
#define SHAP_FW_HEADER_SIZE			(SHAP_HEADER_SIZE + 4)

#define SHAP_FW_TYPE_FIRMWARE		1		

#define SHAP_FW_NUM_PACKET_ACK		5
#define SHAP_FW_ACK_PACKET_NUM		1

/* SHAP firmware ack: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_FA_TYPE_OFFSET			0
#define SHAP_FA_FW_STATUS_OFFSET	1
#define SHAP_FA_BLOCK_NUM_OFFSET	2

#define SHAP_FA_TYPE_FIRMWARE		1
#define SHAP_FA_TYPE_ACK			2

/* SHAP upgrade: offsets are from the beginning of the SHAP payload(after header) */
#define SHAP_UP_TYPE_OFFSET			0
#define SHAP_UP_DATA_OFFSET			2

#define SHAP_UP_TYPE_REBOOT_PEER		1
#define SHAP_UP_TYPE_REBOOTING			2
#define SHAP_UP_TYPE_REBOOT_STATUS		3
#define SHAP_UP_TYPE_REBOOT_SUCCESS		4
#define SHAP_UP_TYPE_REBOOT_FAILURE		5
#define SHAP_UP_TYPE_SVRRP_BOOT_PEER		6
#define SHAP_UP_TYPE_SVRRP_BOOT_PEER_ACK1		7
#define SHAP_UP_TYPE_SVRRP_BOOT_PEER_ACK2		8
#define SHAP_UP_TYPE_SVRRP_BOOT_STATUS	9
#define SHAP_UP_TYPE_SVRRP_BOOT_SUCCESS 	10
#define SHAP_UP_TYPE_SVRRP_BOOT_FAILURE 	11

#define SHAP_UP_STATUS_OLD_SUCCESS		1
#define SHAP_UP_STATUS_NEW_FAILURE		2
#define SHAP_UP_STATUS_OLD_DEFAULT		3
#define SHAP_UP_STATUS_FW_WRONG			4

#define SHAP_UP_FW_TYPE_NEW				1
#define SHAP_UP_FW_TYPE_BACKUP			2
#define SHAP_UP_FW_TYPE_CURRENT			3

#define SHAP_UP_FW_PREF_NORMAL			0
#define SHAP_UP_FW_PREF_DEFAULT			1
#define SHAP_UP_FW_PREF_BACKUP			2











#endif
