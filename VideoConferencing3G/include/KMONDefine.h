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
#define  MON_KEY_TALKTYPE       "TALKTYPE"  //0:为正常对讲 1:对讲测试

//REQ20080325001
#define  MON_KEY_YT_TYPE		"YTTYPE:"
#define  MON_KEY_YT_COM			"YTCOM:"
#define  MON_KEY_YT_NO			"YTNO:"		//云台编号
#define  MON_KEY_PRESET_NO		"PRESETNO:"	//预置点编号
#define  MON_KEY_PRESET_NAME	"PRESETNAME:"	//预置点名称
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
// 网络代理信息
typedef struct _XPROXY_INFO
{
    unsigned int	proxytype;		// 代理类型: 0=direct 1=http proxy 2=socks5 3=http tunnel
    std::string		proxyhost;		// 代理服务器地址
    unsigned short	proxyport;		// 代理服务器端口
    std::string		proxyuser;		// 代理账户
    std::string		proxypass;		// 代理密码
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
//房间状态
enum _ROOM_STATUS
{
	ROOM_STATUS_NONE = 0,	//未进入
	ROOM_STATUS_MET,		//会议
	ROOM_STATUS_MON,		//监控
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
	unsigned short nChannelNum;	//通道号
	std::string strPresetNO;	//所有预置点的编号，如“1,3,5”，用','分隔开
	std::string strPresetName;	//所有预置点的名称，如“前门,后院,边门”，用','分隔开，与编号相对应！
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
	MONERR_CH_INVALID,   // 无效通道
	MONERR_OFFLINE,
	MONERR_CH_UPDATE_FAIL,
	MONERR_UNKNOW,
}MON_ERR_CODE;

//-------------------------------------
// 录像结构
typedef struct _MON_RECORD
{
	std::string filename;	//文件名
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
	MONERR_DEVCHECK_OLDSERIALNO_ISEMPTY,	//现有设备序列号为空
	MONERR_DEVCHECK_SERIALNO_ISNOTSAME,		//现有设备帐号和新设备帐号相同,但是序列号不同
	MONERR_DEVCHECK_DEVID_ISNOTSAME,		//现有设备帐号和新设备帐号不同,但是序列号相同
	MONERR_DEVCHECK_NEWDEVID_ISNOTEXIST,	//新设备帐号不存在
	MONERR_DEVCHECK_NEWDEVID_SERIALNO,		//新设备帐号已经绑定了序列号
	MONERR_DEVCHECK_NEWDEVID_LOGIN,			//新设备帐号已经登录
	MONERR_DEVCHECK_NEWSERIALNO_USED,		//新设备序列号已经被使用
}MONERR_DEVCHECK;