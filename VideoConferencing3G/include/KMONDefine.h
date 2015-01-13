#pragma once

//=======================================================================================
#define  MON_KEY_ID             "LOGID:"
#define  MON_KEY_PASSWORD       "PASSWORD:"
#define  MON_KEY_FROM           "FROM:"
#define  MON_KEY_TO             "TO:"
#define  MON_KEY_ATTR           "ATTR:"
#define  MON_KEY_OPERATE        "OPERATE:"
#define  MON_KEY_REFID          "REFID:"
#define  MON_KEY_EERCODE        "ERRCODE:"
#define  MON_KEY_USERID         "USERID:"
#define  MON_KEY_CHNAME			"CHANNELNAME:"
#define  MON_KEY_DEVTYPE        "DEVTYPE:"
#define  MON_KEY_DEVID          "DEVID"
#define  MON_KEY_DEVNAME        "DEVNAME"
#define  MON_KEY_CHSTATUS       "STATUS:"
#define  MON_KEY_MCUID			"MCUID:"
#define  MON_KEY_MCUADDR		"MCUADDR:"
#define  MON_KEY_MCUPORT		"MCUPORT:"
#define  MON_KEY_VIDEOCID       "VIDEOCID:"
#define  MON_KEY_AUDIOCID       "AUDIOCID:"
#define  MON_KEY_CHNUM          "CHANNELNUM:"
#define  MON_KEY_CHCNT          "CHANNELCOUNT:"
#define  MON_KEY_M_E_C_ID       "M_E_C_ID:"
#define  MON_KEY_SDPDATA        "SDPDATA:"
#define  MON_KEY_NODEID         "NODEID:"
#define  MON_KEY_NATADDR        "NATADDR:"
#define  MON_KEY_LOCALADDR      "LOCALADDR:"
#define  MON_KEY_LOCALPORT      "LOCALPORT:"
#define  MON_KEY_TERMTYPE       "TERMTYPE:"
#define  MON_KEY_CALLID         "CALLID:"
#define  MON_KEY_CTRLINFO       "CTRLINFO:"
#define  MON_KEY_ALERTLEVEL     "ALERTLEVEL:"
#define  MON_KEY_TREENAME       "TREENAME:"
#define  MON_KEY_TREEID         "TREEID:"
#define  MON_KEY_TREEPID        "TREEPARENTID:"
#define  MON_KEY_TREENODETYPE   "TREENODETYPE:"
#define  MON_KEY_RSSADDR        "RSSADDR:"
#define  MON_KEY_RSSPORT        "RSSPORT:"
#define  MON_KEY_VODIP          "VODIP:"
#define  MON_KEY_TYPE           "TYPE:"
#define  MON_KEY_DATA           "DATA:"
#define  MON_KEY_RSPCODE        "RSPCODE:"
#define  MON_KEY_MASK	        "MASK:"
#define  MON_KEY_ALERT_SUBLEVEL	"ALERT_SUBLEVEL:"
#define  MON_KEY_SRVADDR        "SRVADDR:"
#define  MON_KEY_FROMNODE       "FROMNODE:"
#define  MON_KEY_TALKTYPE       "TALKTYPE"  //0:Ϊ�����Խ� 1:�Խ�����

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

//=======================================================================================
#define  MON_AV_EID			    "EID"
#define  MON_AV_CID			    "CID"
#define  MON_AV_ENAME		    "ENAME"
#define  MON_AV_CHNAME		    "CH_NAME"
#define  MON_AV_HDDEVICE	    "MON_AV_HDDEVICE"

//=======================================================================================
// ���������Ϣ
typedef struct _XPROXY_INFO
{
    unsigned int	proxytype;		// ��������: 0=direct 1=http proxy 2=socks5 3=http tunnel
    std::string		proxyhost;		// �����������ַ
    unsigned short	proxyport;		// ����������˿�
    std::string		proxyuser;		// �����˻�
    std::string		proxypass;		// ��������
}XPROXY_INFO,*PXPROXY_INFO;

#define ERRNO_INVALID_ACCOUNT		301
#define ERRNO_INVALID_PASSWORD		302
#define ERRNO_DUPLICATE_LOGIN		304
#define ERRNO_DATABASE				305
#define ERRNO_UNKNOWN				306

//=======================================================================================
enum _MON_TREENODE_TYPE
{
	MON_TREENODE_REGION = 0,
	MON_TREENODE_DEV,
	MON_TREENODE_DEVCH,
	MON_TREENODE_DEVCH_UPDATE
};

//=======================================================================================
//����״̬
enum _ROOM_STATUS
{
	ROOM_STATUS_NONE = 0,	//δ����
	ROOM_STATUS_MET,		//����
	ROOM_STATUS_MON,		//���
};

//=======================================================================================
typedef struct _DEV_CHANNEL_ITEM
{
public:
	_DEV_CHANNEL_ITEM()
	{
		channelid = "";
		channelnum = 0;
		channelname = "";
		devname = "";
		devid = "";
		sptype = 0;
		status = 0;
		mcuid = "";
		mcuaddr = "";
		mcuport = 0;
		videocid = 0;
		audiocid = 0;
		devinfo = "";
	}
	_DEV_CHANNEL_ITEM& operator=(const _DEV_CHANNEL_ITEM& rChannelItem)
	{
		channelid = rChannelItem.channelid;
		channelnum = rChannelItem.channelnum;
		channelname = rChannelItem.channelname;
		devname = rChannelItem.devname;
		devid  = rChannelItem.devid;
		sptype = rChannelItem.sptype;
		status = rChannelItem.status;
		mcuid	= rChannelItem.mcuid;
		mcuaddr	= rChannelItem.mcuaddr;
		mcuport	= rChannelItem.mcuport;
		videocid = rChannelItem.videocid;
		audiocid = rChannelItem.audiocid;
		devinfo = rChannelItem.devinfo;
		return *this;
	}
public:
	std::string		channelid;
	unsigned short  channelnum;
	std::string		channelname;
	std::string		devname;
	std::string     devid;
	unsigned short  sptype;
	unsigned short  status;
	std::string		mcuid;
	std::string		mcuaddr;
	unsigned short	mcuport;
	unsigned long	videocid;
	unsigned long	audiocid;
	std::string		devinfo;
}DEV_CHANNEL_ITEM;

//=======================================================================================
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
	std::string strPresetNO;	//����Ԥ�õ�ı�ţ��硰1,3,5������','�ָ���
	std::string strPresetName;	//����Ԥ�õ�����ƣ��硰ǰ��,��Ժ,���š�����','�ָ������������Ӧ��
	unsigned short nSpeed;

}YT_CONTROL_PARAMETERS;

//=======================================================================================
typedef enum _MON_DVR_ATTR
{
	MON_DVR_DEVICE = 0,
	MON_DVR_MEET,
	MON_DVR_VIEWER,
}MON_DVR_ATTR;

//=======================================================================================
typedef enum _MONERR_CODE 
{
	MONERR_PACKET=0,
	MONERR_DB,
	MONERR_CH_INVALID,   // ��Чͨ��
	MONERR_OFFLINE,
	MONERR_CH_UPDATE_FAIL,
	MONERR_UNKNOW,
}MON_ERR_CODE;

//-------------------------------------
// ¼��ṹ
typedef struct _MON_RECORD
{
	std::string filename;	//�ļ���
	std::string writedate;
	std::string completedate;
	unsigned long filesize;
	std::string dvrid;
	unsigned short channelid;
	unsigned short filetype;
	std::string filestarttime;
	std::string fileendtime;
	std::string serverip0;
	std::string serverip1;
	std::string serverip2;
}MON_RECORD,*PMON_RECORD;

//=======================================================================================
typedef enum _MONERR_DEVCHECK
{
	MONERR_DEVCHECK_NONE=0,
	MONERR_DEVCHECK_OLDSERIALNO_ISEMPTY,	//�����豸���к�Ϊ��
	MONERR_DEVCHECK_SERIALNO_ISNOTSAME,		//�����豸�ʺź����豸�ʺ���ͬ,�������кŲ�ͬ
	MONERR_DEVCHECK_DEVID_ISNOTSAME,		//�����豸�ʺź����豸�ʺŲ�ͬ,�������к���ͬ
	MONERR_DEVCHECK_NEWDEVID_ISNOTEXIST,	//���豸�ʺŲ�����
	MONERR_DEVCHECK_NEWDEVID_SERIALNO,		//���豸�ʺ��Ѿ��������к�
	MONERR_DEVCHECK_NEWDEVID_LOGIN,			//���豸�ʺ��Ѿ���¼
	MONERR_DEVCHECK_NEWSERIALNO_USED,		//���豸���к��Ѿ���ʹ��
}MONERR_DEVCHECK;