#pragma once

//=========================================================
// ��չ����ͨѶЭ�鶨��
//=========================================================

//---------------------------------------------------------------------------------------
// IO��������(�ڲ�����)
#define IO_CONNECT_TYPE_MON					1		// CLIENT��C2S
#define IO_CONNECT_TYPE_OCX					2		// Client��Server

//---------------------------------------------------------
// Э������
typedef enum _XCOMD
{
	STREAM_START = 0,
	SERVER_CONNECT = 100,
	SERVER_DISCONNECT,
	SERVER_CONNCOUNT,
	CLIENT_CONNECT,
	CLIENT_DISCONNECT,
	CLIENT_FETCH_C2S,
	IMS_MCU_LIST_GET = 200,
	IMS_MCU_LIST_ITEM,
	IMS_MCU_LIST_END,
	IMS_USER_PROFILE = 1000,		//	C:����û�����				S:�����û�����
	IMS_USER_STATUS,				//	C:�����û�״̬				S:�����û�״̬
	IMS_USER_IMAGE_SET,				//	C:�����û�ͷ��				S:-
	IMS_USER_IMAGE_GET,			
	IMS_USER_IMAGE,		

	IMS_GROUP_LIST_GET,				//  C:������б�				S:-
	IMS_GROUP_LIST_ITEM,			//	C:-							S:�������б���
	IMS_GROUP_LIST_END,				//	C:-							S:�������б������
	IMS_GROUP_ITEM,					//  C:-							S:��������
	IMS_GROUP_ITEM_INSERT,			//	C:�������					S:�����������
	IMS_GROUP_ITEM_DELETE,			//	C:ɾ������					S:����ɾ������
	IMS_GROUP_NAME_UPDATE,			//	C:�����					S:���������
	IMS_GROUP_INDEX_UPDATE,			//	C:���������				S:�������������

	IMS_FRIEND_LIST_GET,			//  C:��ú����б�				S:-
	IMS_FRIEND_LIST_ITEM,			//	C:-							S:���غ����б���
	IMS_FRIEND_LIST_END,			//	C:-							S:���غ����б������
	IMS_FRIEND_ITEM,				//	C:-							S:���غ�����
	IMS_FRIEND_ITEM_DELETE,			//	C:ɾ��������				S:����ɾ��������
	IMS_FRIEND_ITEM_SEARCH,			//	C:����������				S:��������������
	IMS_FRIEND_APPLY,				//	C:��������Ϊ����			S:�����˼�Ϊ����
	IMS_FRIEND_ADMIT,				//	C:ͬ�����������Ϊ����	S:������ͬ��Ϊ����
	IMS_FRIEND_NICKNAME_UPDATE,		//	C:���ĺ��ѵ��ǳ�			S:���ظ��ĺ��ѵ��ǳ�
	IMS_FRIEND_GROUP_UPDATE,		//	C:���ĺ��ѵ���				S:���ظ��ĺ��ѵ���

	IMS_ORG_ROOTITEM,				//  C:��û�������				S:���ػ����б����
	IMS_ORG_ROOTITEM_INSERT,		//	C:��ӻ�������				S:������ӻ�������
	IMS_ORG_ROOTITEM_DELETE,		//	C:ɾ����������				S:����ɾ����������
	IMS_ORG_ROOTITEM_SEARCH,		//	C:������������				S:����������������
	IMS_ORG_SUBITEM,				//  C:��û�������				S:���ػ�������
	IMS_ORG_USERITEM,			//	C:��ȡ�����û���			S:���ػ����û���
	IMS_ORG_SERVICEID,				//	C:��ȡ�������к�			S:���ػ������к�

	MMS_ROOM_LIST_GET = 2000,		//	C:��û����б�				S:-
	MMS_ROOM_LIST_ITEM,				//	C:-							S:���ػ����б���
	MMS_ROOM_LIST_END,				//	C:-							S:���ػ����б����

	// MON XCMD START:------------------------------------------------------

	MON_DEV_ONLINE,                   // MON C:DEV����                     S:-
	MON_DEV_OFFLINE,                  // MON C:DEV����                     S:-

    MON_DEVCH_ONLINE,                 //  MON C:DEVͨ������                   S:-
	MON_DEVCH_OFFLINE,				  //  MON C:DEVͨ������                   S:-

	MON_GET_BASICINFO,                // MON C:����MCU                      S:-
	MON_SET_BASICINFO,                // MON ���� MCU                       C:-

	MON_GET_FRIEND,                    // C:��ȡ����б�
	MON_SET_FRIEND,                    // C:���ü���б�

	MON_P2P_INVITE,                  //  C:������                          S:P2P��Ϣ
	MON_P2P_RSP,					 //  MON:C ����Ӧ
	MON_P2P_BYE,                     //  C:����

	MON_AV_INVITE,                   //  C:����Ƶ����
	MON_AV_RSP,                       
	MON_AV_BYE,                      //  C: ��������Ƶ

	MON_A2A_INVITE,					 //  C:�Խ�����
	MON_A2A_RSP,
	MON_A2A_BYE,                     //  C:�����Խ�

	MON_DEVCH_ALERT,                    //  MON C:����                       S:-

	MON_GET_REGION,
	MON_SET_REGION,
	MON_GET_SUBREGION,
	MON_DEVCH_CONTROL,                  //  C:��̨����

	MON_DEV_SET,
	MON_DEV_GET,
	MON_TRANSLATE_DATA,
	MON_SRVINFO,

	MON_GET_YT_CTRL,
	MON_GET_YT_CONN,
	MON_SET_YT_CTRL,					//��̨���Ʋ���
	MON_SET_YT_CONN,					//��̨���Ӳ���

	//AV�������� REQ20080520001
	MON_SEND_AUDIO,					//����Audio������Զ��
	MON_SEND_VIDEO,					//����Video������Զ��

	MON_GET_AV,						//���յ�Զ�̻�ȡAV��������
	MON_SET_AV,						//���յ�Զ���µ�AV����

	MON_ERROR,                        //  MON S: ������Ϣ                      MON:C
	// MON XCMD END:-------------------------------------------------------
};

//---------------------------------------------------------
// SESSOIN��Ϣ�ṹ
typedef struct _XSESSIONID
{
	unsigned long csid;
	unsigned long rsid;
	//std::string   nataddr;
}XSESSIONID,*PXSESSIONID;

typedef std::list<PXSESSIONID> XSESSIONID_LIST;
//---------------------------------------------------------
// ���������Ϣ
typedef struct _XPROXY_INFO
{
    unsigned int	proxytype;		// ��������: 0=direct 1=http proxy 2=socks5 3=http tunnel
    std::string		proxyhost;		// �����������ַ
    unsigned short	proxyport;		// ����������˿�
    std::string		proxyuser;		// �����˻�
    std::string		proxypass;		// ��������
}XPROXY_INFO,*PXPROXY_INFO;

//---------------------------------------------------------
// ����Ͽ�������
typedef enum _XDISCONNECT_ERROR_CODE
{
	ERR_NETWORK_FAILURE	= 0,		//��������ʧ��
	ERR_NETEORK_BROKEN,				//�������ӱ��Ͽ�
	ERR_NETWORK_TIMEOUT,			//�������ӳ�ʱ
	ERR_INVALID_ADDRESS,			//NameServerѰַʧ��(û�л����ȷ��CommServer��������ַ)
	ERR_INVALID_ACCOUNT,			//��Ч���û���
	ERR_INVALID_PASSWORD,			//��Ч������
	ERR_KICKOUT,					//ͬ�ʻ����û��������ط���¼,���߳�
	ERR_UNKNOWN,					//δ֪����
};

//---------------------------------------------------------
// CommServer���ӵ�ַ
typedef struct _XCOMM_SERVER_ADDRESS
{
	std::string		csid;		//CommServer's ID
	unsigned short	csport;		//CommServer Port
	std::string		csaddr0;	//CommServer Address0
	std::string		csaddr1;	//CommServer Address1
	std::string		csaddr2;	//CommServer Address2
}XCOMM_SERVER_ADDRESS;

//---------------------------------------------------------
// MESG���Ͷ���
//---------------------------------------------------------

//-----------------------------------------------
// MCU��Ϣ�ṹ
typedef struct _XMCU_ITEM
{
	std::string		mcuid;
	std::string		mcutype;	// MCU������·����(����C������T)
	std::string		addr0;
	std::string		addr1;
	std::string		addr2;
	std::string		type0;
	std::string		type1;
	std::string		type2;
}XMCU_ITEM,*PXMCU_ITEM;

typedef std::list<PXMCU_ITEM>	XMCU_LIST;
typedef std::map<std::string,PXMCU_ITEM> XMCU_MAP;

//-----------------------------------------------
// GROUP��Ϣ�ṹ
typedef struct _XGROUP_ITEM
{
	std::string		groupid;
	unsigned int	index;
}XGROUP_ITEM,*PXGROUP_ITEM;

typedef std::list<PXGROUP_ITEM> XGROUP_LIST;
typedef std::map<std::string,PXGROUP_ITEM> XGROUP_MAP;

//---------------------------------------------------------
// �û�����Ϣ�ṹ(������)
typedef struct _XUSER_ITEM
{
	std::string		userid;		//�û�ID
	std::string		username;	//�û�����
	std::string		nickname;	//�����ǳ�(�����û�Ϊ����ȡ���ǳ�)
	std::string		groupid;	//������
	std::string		initiator;	//������ID: ���Ϊ�����û�ID����Ϊ���ط��𣬷���Ϊ�Է�����
	bool			accepted;	//���ձ�־: true=������ϵ�� false=��δ��Ϊ��ϵ��
	unsigned int	level;		//�û�����:���0��
	unsigned long	csid;		//CSID
	unsigned long	rsid;		//RSID
	std::string		nataddr;	//NATADDR
	std::string		nattype;	//NATTYPE
	std::string		callid;		//���к�
	unsigned short	status;		//����״̬
	unsigned short	camstatus;	//�����״̬
	unsigned short	micstatus;	//��˷�״̬

	std::string		gender;		//�Ա�
	std::string		age;		//����
	std::string		country;	//����
	std::string		province;	//ʡ��/��
	std::string		city;		//����
	std::string		address;	//��ַ
	std::string		postcode;	//�ʱ�
	std::string		phone;		//�绰
	std::string		email;		//�����ʼ�
	std::string		url;		//URL
	std::string		imgtype;	//ͷ������
	std::string		imgdata;	//ͷ������
	unsigned int	showflag;	//��ʾ��־: 0=���������� 1=����ѹ��� 2=�������˹���
}XUSER_ITEM,*PXUSER_ITEM;

typedef std::list<PXUSER_ITEM> XUSER_LIST;
typedef std::map<std::string,PXUSER_ITEM> XUSER_MAP;

//-----------------------------------------------
// MESSAGE��Ϣ�ṹ
typedef struct _XMESSAGE_ITEM
{
	std::string	friendid;
	std::string	content;
	std::string format;
	unsigned short type;
	std::string stime;
}XMESSAGE_ITEM,*PXMESSAGE_ITEM;

typedef std::list<PXMESSAGE_ITEM> XMESSAGE_LIST;

//-------------------------------------------
// ������Ϣ�ṹ
typedef struct _XORG_ITEM
{
	unsigned long	orgid;			// ����ID
	std::string		orgname;		// ��������
	std::string		orgtype;		// ��������
	unsigned int	levelid;		// ���Ų�μ���
	unsigned long	upgradeid;		// �ϼ�ORGID
	unsigned int	orderid;		// �����
	unsigned long	rootid;			// ������ID
	unsigned long	usercount;		// �û�����
	std::string		desc;			// ����
}XORG_ITEM,*PXORG_ITEM;

typedef std::list<PXORG_ITEM> XORG_LIST;
typedef std::map<unsigned long,PXORG_ITEM> XORG_MAP;

//---------------------------------------------------------
// �����û�����Ϣ�ṹ
typedef struct _XORG_USER_ITEM
{
	unsigned long	orgid;		//����ID
	std::string		userid;		//�û�����
	std::string		username;	//�û�����
	unsigned int	level;		//�û�����:���0��
	unsigned long	csid;		//CSID
	unsigned long	rsid;		//RSID
	std::string		nataddr;	//NATADDR
	std::string		nattype;	//NATTYPE
	std::string		callid;		//���к�
	unsigned short	status;		//����״̬
	unsigned short	camstatus;	//�����״̬
	unsigned short	micstatus;	//��˷�״̬

	std::string		gender;		//�Ա�
	std::string		age;		//����
	std::string		country;	//����
	std::string		province;	//ʡ��/��
	std::string		city;		//����
	std::string		address;	//��ַ
	std::string		postcode;	//�ʱ�
	std::string		phone;		//�绰
	std::string		email;		//�����ʼ�
	std::string		url;		//URL
	std::string		imgtype;	//ͷ������
	std::string		imgdata;	//ͷ������
	unsigned int	showflag;	//��ʾ��־: 0=���������� 1=����ѹ��� 2=�������˹���
}XORG_USER_ITEM,*PXORG_USER_ITEM;

typedef std::list<PXORG_USER_ITEM> XORG_USER_LIST;
typedef std::map<std::string,PXORG_USER_ITEM> XORG_USER_MAP;

//-------------------------------------------
// ������Ϣ�ṹ
typedef struct _XMEETING_ITEM
{
	unsigned long	meetingid;		// ����ID
	std::string		meetingname;	// ��������
	unsigned short	meetingtype;	// ��������
}XMEETING_ITEM,*PXMEETING_ITEM;

typedef std::list<PXMEETING_ITEM> XMEETING_LIST;
typedef std::map<unsigned long,PXMEETING_ITEM> XMEETING_MAP;

//=======================================================================================
#define  MON_KEY_ID            "LOGID:"
#define  MON_KEY_PASSWORD      "PASSWORD:"
#define  MON_KEY_FROM          "FROM:"
#define  MON_KEY_TO            "TO:"
#define  MON_KEY_ATTR          "ATTR:"
#define  MON_KEY_OPERATE       "OPERATE:"
#define  MON_KEY_REFID         "REFID:"
#define  MON_KEY_EERCODE       "ERRCODE:"
#define  MON_KEY_USERID        "USERID:"
#define  MON_KEY_CHID          "CHANNELID:"
#define  MON_KEY_CHALIAS       "CHANNELALIAS:"
#define  MON_KEY_DEVTYPE		"DEVTYPE:"
#define  MON_KEY_DEVID         "DEVID"
#define  MON_KEY_CHSTATUS      "STATUS:"
#define  MON_KEY_AUDIOID       "AUDIOID:"
#define  MON_KEY_AUDIOIP0      "AUDIOIP0:"
#define  MON_KEY_AUDIOIP1      "AUDIOIP1:"
#define  MON_KEY_AUDIOIP2      "AUDIOIP2:"
#define  MON_KEY_VIDEOID       "VIDEOID:"
#define  MON_KEY_VIDEOIP0      "VIDEOIP0:"
#define  MON_KEY_VIDEOIP1      "VIDEOIP1:"
#define  MON_KEY_VIDEOIP2      "VIDEOIP2:"
#define  MON_KEY_SUBVIDEOID    "SUBVIDEOID:"
#define  MON_KEY_SUBVIDEOIP0   "SUBVIDEOIP0:"
#define  MON_KEY_SUBVIDEOIP1   "SUBVIDEOIP1:"
#define  MON_KEY_SUBVIDEOIP2   "SUBVIDEOIP2:"
#define  MON_KEY_CHNUM         "CHANNELNUM:"
#define  MON_KEY_CHCNT         "CHANNELCOUNT:"
#define  MON_KEY_M_E_C_ID      "M_E_C_ID:"
#define  MON_KEY_SDPDATA       "SDPDATA:"
#define  MON_KEY_NATADDR       "NATADDR:"
#define  MON_KEY_CALLID        "CALLID:"
#define  MON_KEY_CTRLINFO      "CTRLINFO:"
#define  MON_KEY_ALERTLEVEL    "ALERTLEVEL:"
#define  MON_KEY_TREENAME      "TREENAME:"
#define  MON_KEY_TREEID        "TREEID:"
#define  MON_KEY_TREEPID      "TREEPARENTID:"
#define  MON_KEY_TREENODETYPE "TREENODETYPE:"
#define  MON_KEY_MCUIP0       "MCUIP0:"
#define  MON_KEY_MCUIP1       "MCUIP1:"
#define  MON_KEY_MCUIP2       "MCUIP2:"
#define  MON_KEY_RSSIP0       "RSSIP0:"
#define  MON_KEY_RSSIP1       "RSSIP1:"
#define  MON_KEY_RSSIP2       "RSSIP2:"
#define  MON_KEY_RSSPORT      "RSSPORT:"
#define  MON_KEY_VODIP        "VODIP:"
#define  MON_KEY_TYPE         "TYPE:"
#define  MON_KEY_DATA         "DATA:"
#define  MON_KEY_RSPCODE      "RSPCODE:"
#define  MON_KEY_MASK	       "MASK:"
#define  MON_KEY_ALERT_SUBLEVEL  "ALERT_SUBLEVEL:"
#define  MON_KEY_SRVADDR         "SRVADDR:"
#define  MON_KEY_FROMNODE        "FROMNODE:"

//REQ20080325001
#define  MON_KEY_YT_TYPE		"YTTYPE:"
#define  MON_KEY_YT_COM			"YTCOM:"
#define  MON_KEY_YT_NO			"YTNO:"		//��̨���
#define  MON_KEY_PRESET_NO		"PRESETNO:"	//Ԥ�õ���
#define  MON_KEY_PRESET_NAME	"PRESETNAME:"	//Ԥ�õ�����
#define  MON_KEY_YT_SPEED		"YTSPEED:"
#define  MON_KEY_YT_CMD			"YTCMD:"
#define  MON_KEY_PTYPE			"PTYPE:"
#define  MON_CONTROL_TYPE		"CTRLTYPE:"

enum _MON_TREENODE_TYPE
{
	MON_TREENODE_REGION = 0,
	MON_TREENODE_DEV,
	MON_TREENODE_DEVCH,
	MON_TREENODE_DEVCH_UPDATE
};

typedef struct _DEV_CHANNEL_ITEM
{
public:
	_DEV_CHANNEL_ITEM()
	{
		channelkey = 0;
		channelnum = 0;
		channelalias = "";
		devchname;
		devid = "";
		sptype = 0;
		status = 0;
		audioid = 0;
		audioip0 = "";
		audioip1 = "";
		audioip2 = "";
		videoid = 0;
		videoip0 = "";
		videoip1 = "";
		videoip2 = "";
		subvideoid = 0;
		subvideoip0 = "";
		subvideoip1 = "";
		subvideoip2 = "";
	}
	_DEV_CHANNEL_ITEM& operator=(const _DEV_CHANNEL_ITEM& rChannelItem)
	{
		devchname = rChannelItem.devchname;
		channelkey = rChannelItem.channelkey;
		channelnum = rChannelItem.channelnum;
		channelalias = rChannelItem.channelalias;
		devid  = rChannelItem.devid;
		sptype = rChannelItem.sptype;
		status = rChannelItem.status;
		audioid = rChannelItem.audioid;
		audioip0 = rChannelItem.audioip0;
		audioip1 = rChannelItem.audioip1;
		audioip2 = rChannelItem.audioip2;
		videoid = rChannelItem.videoid;
		videoip0 = rChannelItem.videoip0;
		videoip1 = rChannelItem.videoip1;
		videoip2 = rChannelItem.videoip2;
		subvideoid = rChannelItem.subvideoid;
		subvideoip0 = rChannelItem.subvideoip0;
		subvideoip1 = rChannelItem.subvideoip1;
		subvideoip2 = rChannelItem.subvideoip2;
		return *this;
	}
public:
	unsigned long   channelkey;
	std::string     devchname;
	unsigned short  channelnum;
	std::string		channelalias;
	std::string     devid;
	unsigned short  sptype;
	unsigned short  status;
	unsigned long	audioid;
	std::string		audioip0;
	std::string		audioip1;
	std::string		audioip2;
	unsigned long	videoid;
	std::string		videoip0;
	std::string		videoip1;
	std::string		videoip2;
	unsigned long	subvideoid;
	std::string		subvideoip0;
	std::string		subvideoip1;
	std::string		subvideoip2;

}DEV_CHANNEL_ITEM;

typedef struct _YT_Control_Parameters
{
public:
	_YT_Control_Parameters()
	{
		nChannelNum = -1;
		strPresetNO = "";
		strPresetName= "";
		nSpeed = 50;
	}

	_YT_Control_Parameters& operator=(const _YT_Control_Parameters& rChannelItem)
	{
		nChannelNum = rChannelItem.nChannelNum;
		strPresetNO = rChannelItem.strPresetNO;
		strPresetName = rChannelItem.strPresetName;
		nSpeed = rChannelItem.nSpeed;

		return *this;
	}

public:
	unsigned short nChannelNum;	//ͨ����
	//unsigned short nPresetNum;
	std::string strPresetNO;	//����Ԥ�õ�ı�ţ��硰1,3,5������','�ָ���
	std::string strPresetName;	//����Ԥ�õ�����ƣ��硰ǰ��,��Ժ,���š�����','�ָ������������Ӧ��
	unsigned short nSpeed;

}YT_CONTROL_PARAMETERS;

typedef enum _MON_DVR_ATTR
{
	MON_DVR_DEVICE = 0,
	MON_DVR_MEET,
	MON_DVR_VIEWER,
}MON_DVR_ATTR;

typedef enum _MONERR_CODE 
{
	MONERR_PACKET=0,
	MONERR_DB,
	MONERR_CH_INVALID,   // ��Чͨ��
	MONERR_OFFLINE,
	MONERR_CH_UPDATE_FAIL,
	MONERR_UNKNOW,
}MON_ERR_CODE;

typedef unsigned char BYTE;
typedef unsigned long ULONG;
typedef unsigned long DWORD;

//ѹ������
typedef struct{
	BYTE byStreamType;		//��������0-��Ƶ��,1-������
	BYTE byResolution;  	//�ֱ���0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
	BYTE byBitrateType;		//��������0:�����ʣ�1:������
	BYTE  byPicQuality;		//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-��	
	DWORD dwVideoBitrate; 	//��Ƶ���� 0-���� 1-���� 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
				// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
				//���λ(31λ)�ó�1��ʾ���Զ�������, 0-30λ��ʾ����ֵ(MIN-16K MAX-8192K)��
	DWORD dwVideoFrameRate;	//֡�� 0-ȫ��; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
}NET_DVR_COMPRESSION_INFO,*LPNET_DVR_COMPRESSION_INFO;

typedef struct{
	DWORD dwSize;
	NET_DVR_COMPRESSION_INFO struRecordPara; //¼��
	NET_DVR_COMPRESSION_INFO struNetPara;	//����
}NET_DVR_COMPRESSIONCFG,*LPNET_DVR_COMPRESSIONCFG;



#define CMD_CHANNEL_GETVIDEOINFO		"cmd_channel_getvideoinfo"	// ��Ƶ��Ϣ
/*#define ATTRIB_ENCODER_ID				"eid"						// ������*/
/*#define ATTRIB_CHANNEL_ID				"cid"						// ͨ����*/
#define ATTRIB_VIDEO_DEVICE				"video_device"				// �豸
#define ATTRIB_VIDEO_DENOISE			"video_denoise"				// ͼ��ȥ��

#define ATTRIB_VIDEO_CODEC				"video_codec"				// ���뷽ʽ
#define ATTRIB_VIDEO_RESOLUTION			"video_resolution"			// �ֱ���
#define ATTRIB_VIDEO_FRAMERATE			"video_framerate"			// ��Ƶ֡��
#define ATTRIB_VIDEO_FRAMETYPE			"video_frametype"			// ��Ƶģʽ
#define ATTRIB_VIDEO_QUALITY			"video_quality"				// ��Ƶ����
#define ATTRIB_VIDEO_AUTOQUALITY		"video_autoquality"			// ͼ�������Զ�����

#define ATTRIB_VIDEO_CODEC_SUB			"video_codec_sub"			// �������뷽ʽ
#define ATTRIB_VIDEO_RESOLUTION_SUB		"video_resolution_sub"		// �����ֱ���
#define ATTRIB_VIDEO_FRAMERATE_SUB		"video_framerate_sub"		// ����֡��
#define ATTRIB_VIDEO_FRAMETYPE_SUB		"video_frametype_sub"		// ����ģʽ
#define ATTRIB_VIDEO_QUALITY_SUB		"video_quality_sub"			// ��������
#define ATTRIB_VIDEO_AUTOQUALITY_SUB	"video_autoquality_sub"		// ����ͼ�������Զ�����

#define ATTRIB_VIDEO_QUARTERSIZE_SUB	"video_quartersize_sub"		// 	1/4�ߴ�


#define ATTRIB_NDCI_BITRATETYPE			"ndci_bitratetype"			//��������0:�����ʣ�1:������
#define ATTRIB_NDCI_STREAMTYPE			"ndci_streamtype"			//��������0-��Ƶ��,1-������
#define ATTRIB_NDCI_RESOLUTION			"ndci_resolution"			//�ֱ���0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
#define ATTRIB_NDCI_PICQUALITY			"ndci_picquality"			//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-��	
#define ATTRIB_NDCI_VIDEOFRAMERATE		"ndci_videoframerate"		//֡�� 0-ȫ��; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
#define ATTRIB_NDCI_VIDEOBITRATE		"ndci_videobitrate"			//��Ƶ���� 0-���� 1-���� 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 
//11-256K 12-320K 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 
//21-1536K 22-1792K 23-2048K
//���λ(31λ)�ó�1��ʾ���Զ�������, 0-30λ��ʾ����ֵ(MIN-16K MAX-8192K)

#define ATTRIB_NDCI_BITRATETYPE_SUB		"ndci_bitratetype_sub"		//��������0:�����ʣ�1:������
#define ATTRIB_NDCI_STREAMTYPE_SUB		"ndci_streamtype_sub"		//��������0-��Ƶ��,1-������
#define ATTRIB_NDCI_RESOLUTION_SUB		"ndci_resolution_sub"		//�ֱ���0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
#define ATTRIB_NDCI_PICQUALITY_SUB		"ndci_picquality_sub"		//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-��	
#define ATTRIB_NDCI_VIDEOFRAMERATE_SUB	"ndci_videoframerate_sub"	//֡�� 0-ȫ��; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
#define ATTRIB_NDCI_VIDEOBITRATE_SUB	"ndci_videobitrate_sub"		//��Ƶ���� 0-���� 1-���� 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 
//11-256K 12-320K 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 
//21-1536K 22-1792K 23-2048K
//���λ(31λ)�ó�1��ʾ���Զ�������, 0-30λ��ʾ����ֵ(MIN-16K MAX-8192K)

typedef struct tagVIDEO_INFO// ��Ƶ��Ϣ
{
	std::string	eid;			// ������
	ULONG	cid;			// ͨ��
	std::string	encodername;	
	std::string	channelname;	

	//dvr
	int		device;			// �豸
	int     denoise;		// ͼ��ȥ��

	int		codec;			// ���뷽ʽ
	int		resolution;		// �ֱ���
	int		framerate;		// ��Ƶ֡��
	int		frametype;		// ��Ƶģʽ
	int		quality;		// ��Ƶ����
	int		autoquality;	// ͼ�������Զ�����

	int		codec_sub;		// �������뷽ʽ
	int		resolution_sub;	// �ӷֱ���
	int		framerate_sub;	// ����֡��
	int		frametype_sub;	// ����ģʽ
	int		quality_sub;	// ��������
	int		autoquality_sub;// ͼ�������Զ�����

	int     quartersize_sub;// 1/4�ߴ�

	//nvs
	NET_DVR_COMPRESSION_INFO ndci;
	NET_DVR_COMPRESSION_INFO ndci_sub;

	tagVIDEO_INFO()
	{
		eid = "";
		cid = 0; 
		encodername = "";
		channelname = "";
		device = 0;
		denoise = 0;
		autoquality = 0; 
		codec = 0; 
		resolution = 0; 
		framerate = 0; 
		quality = 0; 
		frametype = 0; 
		codec_sub = 0; 
		resolution_sub = 0; 
		framerate_sub = 0; 
		quality_sub = 0; 
		frametype_sub = 0; 
		autoquality_sub = 0;
		quartersize_sub = 0;

		ndci.byBitrateType = 0;
		ndci.byPicQuality = 2;
		ndci.byResolution = 1;
		ndci.byStreamType = 1;
		ndci.dwVideoBitrate = 11;
		ndci.dwVideoFrameRate = 10;
		ndci_sub.byBitrateType = 0;
		ndci_sub.byPicQuality = 2;
		ndci_sub.byResolution = 1;
		ndci_sub.byStreamType = 1;
		ndci_sub.dwVideoBitrate = 11;
		ndci_sub.dwVideoFrameRate = 10;
	}

	tagVIDEO_INFO& operator=(const tagVIDEO_INFO& vi)
	{
		eid = vi.eid;     
		cid = vi.cid;     
		encodername = vi.encodername;   
		channelname = vi.channelname;
		device = vi.device;
		denoise = vi.denoise;
		codec = vi.codec;    
		resolution = vi.resolution;     
		autoquality = vi.autoquality;   
		framerate = vi.framerate;     
		quality = vi.quality;     
		frametype = vi.frametype;    
		codec_sub = vi.codec_sub; 
		resolution_sub = vi.resolution_sub;  
		framerate_sub = vi.framerate_sub;  
		quality_sub = vi.quality_sub;  
		frametype_sub = vi.frametype_sub; 
		autoquality_sub = vi.autoquality_sub;
		quartersize_sub = vi.quartersize_sub;

		ndci.byBitrateType = vi.ndci.byBitrateType;
		ndci.byPicQuality = vi.ndci.byPicQuality;
		ndci.byResolution = vi.ndci.byResolution;
		ndci.byStreamType = vi.ndci.byStreamType;
		ndci.dwVideoBitrate = vi.ndci.dwVideoBitrate;
		ndci.dwVideoFrameRate = vi.ndci.dwVideoFrameRate;
		ndci_sub.byBitrateType = vi.ndci_sub.byBitrateType;
		ndci_sub.byPicQuality = vi.ndci_sub.byPicQuality;
		ndci_sub.byResolution = vi.ndci_sub.byResolution;
		ndci_sub.byStreamType = vi.ndci_sub.byStreamType;
		ndci_sub.dwVideoBitrate = vi.ndci_sub.dwVideoBitrate;
		ndci_sub.dwVideoFrameRate = vi.ndci_sub.dwVideoFrameRate;
		return *this; 
	}
}VIDEO_INFO, *LPVIDEO_INFO;
typedef vector<VIDEO_INFO>				VIDEO_INFO_LIST;
typedef VIDEO_INFO_LIST::iterator		VIDEO_INFO_LIST_IT;


#define CMD_CHANNEL_GETAUDIOINFO  "cmd_channel_getaudioinfo"// ��Ƶ��Ϣ
#define ATTRIB_AUDIO_DEVICE		  "audio_device"			// �豸
#define ATTRIB_AUDIO_CODEC		  "audio_codec"				// ���뷽ʽ
#define	ATTRIB_AUDIO_VAD		  "audio_vad"				// �������
#define ATTRIB_AUDIO_AGC		  "audio_agc"				// �Զ�����
#define ATTRIB_AUDIO_AEC		  "audio_aec"				// ��������
#define ATTRIB_AUDIO_CAPTURE_CARD "audio_capture_card"		// �ɼ���Ƶ��
#define ATTRIB_AUDIO_CAPTURE_MODE "audio_capture_mode"		// �ɼ�ģʽ��0:MIC��1:LINE_IN��2:WAVE_OUT_MIXER
#define ATTRIB_AUDIO_LABIAL_SYNC  "audio_labial_sync"		// ����ͬ��
#define ATTRIB_COPY_TO_A2A		  "copy_to_a2a"				// ���Ƶ��Խ�ͨ��
typedef struct tagAUDIO_INFO// ��Ƶ��Ϣ
{
	std::string	eid;			// ������
	ULONG	cid;			// ͨ��
	string	encodername;		
	string	channelname;		

	int		device;			// �豸
	int		codec;			// ���뷽ʽ
	int		agc;			// �Զ�����
	int		aec;			// ��������
	int		vad;			// �������
	int		capture_card;	// �ɼ���Ƶ��
	int		capture_mode;	// �ɼ�ģʽ��0:MIC��1:LINE_IN��2:WAVE_OUT_MIXER

	tagAUDIO_INFO()
	{
		eid = "";
		cid = 0; 
		encodername = "";
		channelname = "";
		device = 0;
		codec = 0; 
		agc = 0; 
		aec = 0; 
		vad = 0; 
		capture_card = 0; 
		capture_mode = 0; 
	}

	tagAUDIO_INFO& operator=(const tagAUDIO_INFO& ai)
	{
		eid	= ai.eid;	 
		cid = ai.cid;    
		encodername = ai.encodername;  
		channelname = ai.channelname;  
		device = ai.device;
		codec = ai.codec;   
		agc = ai.agc;          
		aec = ai.aec;          
		vad = ai.vad;          
		capture_card = ai.capture_card; 
		capture_mode = ai.capture_mode;          
		return *this; 
	}

public:
}AUDIO_INFO, *LPAUDIO_INFO;
typedef vector<AUDIO_INFO>				AUDIO_INFO_LIST;
typedef AUDIO_INFO_LIST::iterator		AUDIO_INFO_LIST_IT;

#define  MON_AV_EID			"EID"
#define  MON_AV_CID			"CID"
#define  MON_AV_ENAME		"ENAME"
#define  MON_AV_CHNAME		"CH_NAME"

typedef unsigned short USHORT;