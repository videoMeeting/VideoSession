#pragma once

//=========================================================
// 扩展网络通讯协议定义
//=========================================================

//---------------------------------------------------------------------------------------
// IO连接类型(内部调用)
#define IO_CONNECT_TYPE_MON					1		// CLIENT到C2S
#define IO_CONNECT_TYPE_OCX					2		// Client到Server

//---------------------------------------------------------
// 协议命令
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
	IMS_USER_PROFILE = 1000,		//	C:获得用户资料				S:返回用户资料
	IMS_USER_STATUS,				//	C:设置用户状态				S:返回用户状态
	IMS_USER_IMAGE_SET,				//	C:设置用户头像				S:-
	IMS_USER_IMAGE_GET,			
	IMS_USER_IMAGE,		

	IMS_GROUP_LIST_GET,				//  C:获得组列表				S:-
	IMS_GROUP_LIST_ITEM,			//	C:-							S:返回组列表项
	IMS_GROUP_LIST_END,				//	C:-							S:返回组列表项结束
	IMS_GROUP_ITEM,					//  C:-							S:返回组项
	IMS_GROUP_ITEM_INSERT,			//	C:添加组项					S:返回添加组项
	IMS_GROUP_ITEM_DELETE,			//	C:删除组项					S:返回删除组项
	IMS_GROUP_NAME_UPDATE,			//	C:组更名					S:返回组更名
	IMS_GROUP_INDEX_UPDATE,			//	C:组更改索引				S:返回组更改索引

	IMS_FRIEND_LIST_GET,			//  C:获得好友列表				S:-
	IMS_FRIEND_LIST_ITEM,			//	C:-							S:返回好友列表项
	IMS_FRIEND_LIST_END,			//	C:-							S:返回好友列表项结束
	IMS_FRIEND_ITEM,				//	C:-							S:返回好友项
	IMS_FRIEND_ITEM_DELETE,			//	C:删除好友项				S:返回删除好友项
	IMS_FRIEND_ITEM_SEARCH,			//	C:搜索好友项				S:返回搜索好友项
	IMS_FRIEND_APPLY,				//	C:申请他人为好友			S:被他人加为好友
	IMS_FRIEND_ADMIT,				//	C:同意他人申请成为好友	S:他人已同意为好友
	IMS_FRIEND_NICKNAME_UPDATE,		//	C:更改好友的昵称			S:返回更改好友的昵称
	IMS_FRIEND_GROUP_UPDATE,		//	C:更改好友的组				S:返回更改好友的组

	IMS_ORG_ROOTITEM,				//  C:获得机构根项				S:返回机构列表根项
	IMS_ORG_ROOTITEM_INSERT,		//	C:添加机构根项				S:返回添加机构根项
	IMS_ORG_ROOTITEM_DELETE,		//	C:删除机构根项				S:返回删除机构根项
	IMS_ORG_ROOTITEM_SEARCH,		//	C:搜索机构根项				S:返回搜索机构根项
	IMS_ORG_SUBITEM,				//  C:获得机构子项				S:返回机构子项
	IMS_ORG_USERITEM,			//	C:获取机构用户项			S:返回机构用户项
	IMS_ORG_SERVICEID,				//	C:获取机构呼叫号			S:返回机构呼叫号

	MMS_ROOM_LIST_GET = 2000,		//	C:获得会议列表				S:-
	MMS_ROOM_LIST_ITEM,				//	C:-							S:返回会议列表项
	MMS_ROOM_LIST_END,				//	C:-							S:返回会议列表结束

	// MON XCMD START:------------------------------------------------------

	MON_DEV_ONLINE,                   // MON C:DEV上线                     S:-
	MON_DEV_OFFLINE,                  // MON C:DEV下线                     S:-

    MON_DEVCH_ONLINE,                 //  MON C:DEV通道上线                   S:-
	MON_DEVCH_OFFLINE,				  //  MON C:DEV通道下线                   S:-

	MON_GET_BASICINFO,                // MON C:请求MCU                      S:-
	MON_SET_BASICINFO,                // MON 设置 MCU                       C:-

	MON_GET_FRIEND,                    // C:获取监控列表
	MON_SET_FRIEND,                    // C:设置监控列表

	MON_P2P_INVITE,                  //  C:打洞请求                          S:P2P信息
	MON_P2P_RSP,					 //  MON:C 打洞响应
	MON_P2P_BYE,                     //  C:结束

	MON_AV_INVITE,                   //  C:音视频请求
	MON_AV_RSP,                       
	MON_AV_BYE,                      //  C: 结束音视频

	MON_A2A_INVITE,					 //  C:对讲请求
	MON_A2A_RSP,
	MON_A2A_BYE,                     //  C:结束对讲

	MON_DEVCH_ALERT,                    //  MON C:报警                       S:-

	MON_GET_REGION,
	MON_SET_REGION,
	MON_GET_SUBREGION,
	MON_DEVCH_CONTROL,                  //  C:云台控制

	MON_DEV_SET,
	MON_DEV_GET,
	MON_TRANSLATE_DATA,
	MON_SRVINFO,

	MON_GET_YT_CTRL,
	MON_GET_YT_CONN,
	MON_SET_YT_CTRL,					//云台控制参数
	MON_SET_YT_CONN,					//云台连接参数

	//AV参数设置 REQ20080520001
	MON_SEND_AUDIO,					//发送Audio参数到远程
	MON_SEND_VIDEO,					//发送Video参数到远程

	MON_GET_AV,						//接收到远程获取AV参数请求
	MON_SET_AV,						//接收到远程新的AV参数

	MON_ERROR,                        //  MON S: 错误信息                      MON:C
	// MON XCMD END:-------------------------------------------------------
};

//---------------------------------------------------------
// SESSOIN信息结构
typedef struct _XSESSIONID
{
	unsigned long csid;
	unsigned long rsid;
	//std::string   nataddr;
}XSESSIONID,*PXSESSIONID;

typedef std::list<PXSESSIONID> XSESSIONID_LIST;
//---------------------------------------------------------
// 网络代理信息
typedef struct _XPROXY_INFO
{
    unsigned int	proxytype;		// 代理类型: 0=direct 1=http proxy 2=socks5 3=http tunnel
    std::string		proxyhost;		// 代理服务器地址
    unsigned short	proxyport;		// 代理服务器端口
    std::string		proxyuser;		// 代理账户
    std::string		proxypass;		// 代理密码
}XPROXY_INFO,*PXPROXY_INFO;

//---------------------------------------------------------
// 网络断开错误码
typedef enum _XDISCONNECT_ERROR_CODE
{
	ERR_NETWORK_FAILURE	= 0,		//网络连接失败
	ERR_NETEORK_BROKEN,				//网络连接被断开
	ERR_NETWORK_TIMEOUT,			//网络连接超时
	ERR_INVALID_ADDRESS,			//NameServer寻址失败(没有获得正确的CommServer服务器地址)
	ERR_INVALID_ACCOUNT,			//无效的用户名
	ERR_INVALID_PASSWORD,			//无效的密码
	ERR_KICKOUT,					//同帐户的用户在其它地方登录,被踢出
	ERR_UNKNOWN,					//未知错误
};

//---------------------------------------------------------
// CommServer连接地址
typedef struct _XCOMM_SERVER_ADDRESS
{
	std::string		csid;		//CommServer's ID
	unsigned short	csport;		//CommServer Port
	std::string		csaddr0;	//CommServer Address0
	std::string		csaddr1;	//CommServer Address1
	std::string		csaddr2;	//CommServer Address2
}XCOMM_SERVER_ADDRESS;

//---------------------------------------------------------
// MESG类型定义
//---------------------------------------------------------

//-----------------------------------------------
// MCU信息结构
typedef struct _XMCU_ITEM
{
	std::string		mcuid;
	std::string		mcutype;	// MCU网络线路类型(国内C、国外T)
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
// GROUP信息结构
typedef struct _XGROUP_ITEM
{
	std::string		groupid;
	unsigned int	index;
}XGROUP_ITEM,*PXGROUP_ITEM;

typedef std::list<PXGROUP_ITEM> XGROUP_LIST;
typedef std::map<std::string,PXGROUP_ITEM> XGROUP_MAP;

//---------------------------------------------------------
// 用户的信息结构(含本人)
typedef struct _XUSER_ITEM
{
	std::string		userid;		//用户ID
	std::string		username;	//用户姓名
	std::string		nickname;	//好友昵称(本地用户为好友取得昵称)
	std::string		groupid;	//所属组
	std::string		initiator;	//发起人ID: 如果为本地用户ID，则为本地发起，否则为对方发起
	bool			accepted;	//接收标志: true=已是联系人 false=还未成为联系人
	unsigned int	level;		//用户级别:最低0级
	unsigned long	csid;		//CSID
	unsigned long	rsid;		//RSID
	std::string		nataddr;	//NATADDR
	std::string		nattype;	//NATTYPE
	std::string		callid;		//呼叫号
	unsigned short	status;		//好友状态
	unsigned short	camstatus;	//摄像机状态
	unsigned short	micstatus;	//麦克风状态

	std::string		gender;		//性别
	std::string		age;		//年龄
	std::string		country;	//国家
	std::string		province;	//省份/州
	std::string		city;		//城市
	std::string		address;	//地址
	std::string		postcode;	//邮编
	std::string		phone;		//电话
	std::string		email;		//电子邮件
	std::string		url;		//URL
	std::string		imgtype;	//头像类型
	std::string		imgdata;	//头像数据
	unsigned int	showflag;	//显示标志: 0=不公开资料 1=向好友公开 2=向所有人公开
}XUSER_ITEM,*PXUSER_ITEM;

typedef std::list<PXUSER_ITEM> XUSER_LIST;
typedef std::map<std::string,PXUSER_ITEM> XUSER_MAP;

//-----------------------------------------------
// MESSAGE信息结构
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
// 机构信息结构
typedef struct _XORG_ITEM
{
	unsigned long	orgid;			// 机构ID
	std::string		orgname;		// 机构名称
	std::string		orgtype;		// 机构类型
	unsigned int	levelid;		// 部门层次级别
	unsigned long	upgradeid;		// 上级ORGID
	unsigned int	orderid;		// 排序号
	unsigned long	rootid;			// 根机构ID
	unsigned long	usercount;		// 用户总数
	std::string		desc;			// 描述
}XORG_ITEM,*PXORG_ITEM;

typedef std::list<PXORG_ITEM> XORG_LIST;
typedef std::map<unsigned long,PXORG_ITEM> XORG_MAP;

//---------------------------------------------------------
// 机构用户的信息结构
typedef struct _XORG_USER_ITEM
{
	unsigned long	orgid;		//机构ID
	std::string		userid;		//用户姓名
	std::string		username;	//用户姓名
	unsigned int	level;		//用户级别:最低0级
	unsigned long	csid;		//CSID
	unsigned long	rsid;		//RSID
	std::string		nataddr;	//NATADDR
	std::string		nattype;	//NATTYPE
	std::string		callid;		//呼叫号
	unsigned short	status;		//好友状态
	unsigned short	camstatus;	//摄像机状态
	unsigned short	micstatus;	//麦克风状态

	std::string		gender;		//性别
	std::string		age;		//年龄
	std::string		country;	//国家
	std::string		province;	//省份/州
	std::string		city;		//城市
	std::string		address;	//地址
	std::string		postcode;	//邮编
	std::string		phone;		//电话
	std::string		email;		//电子邮件
	std::string		url;		//URL
	std::string		imgtype;	//头像类型
	std::string		imgdata;	//头像数据
	unsigned int	showflag;	//显示标志: 0=不公开资料 1=向好友公开 2=向所有人公开
}XORG_USER_ITEM,*PXORG_USER_ITEM;

typedef std::list<PXORG_USER_ITEM> XORG_USER_LIST;
typedef std::map<std::string,PXORG_USER_ITEM> XORG_USER_MAP;

//-------------------------------------------
// 会议信息结构
typedef struct _XMEETING_ITEM
{
	unsigned long	meetingid;		// 会议ID
	std::string		meetingname;	// 会议名称
	unsigned short	meetingtype;	// 会议类型
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
#define  MON_KEY_YT_NO			"YTNO:"		//云台编号
#define  MON_KEY_PRESET_NO		"PRESETNO:"	//预置点编号
#define  MON_KEY_PRESET_NAME	"PRESETNAME:"	//预置点名称
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
	unsigned short nChannelNum;	//通道号
	//unsigned short nPresetNum;
	std::string strPresetNO;	//所有预置点的编号，如“1,3,5”，用','分隔开
	std::string strPresetName;	//所有预置点的名称，如“前门,后院,边门”，用','分隔开，与编号相对应！
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
	MONERR_CH_INVALID,   // 无效通道
	MONERR_OFFLINE,
	MONERR_CH_UPDATE_FAIL,
	MONERR_UNKNOW,
}MON_ERR_CODE;

typedef unsigned char BYTE;
typedef unsigned long ULONG;
typedef unsigned long DWORD;

//压缩参数
typedef struct{
	BYTE byStreamType;		//码流类型0-视频流,1-复合流
	BYTE byResolution;  	//分辨率0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
	BYTE byBitrateType;		//码率类型0:变码率，1:定码率
	BYTE  byPicQuality;		//图象质量 0-最好 1-次好 2-较好 3-一般 4-较差 5-差	
	DWORD dwVideoBitrate; 	//视频码率 0-保留 1-保留 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
				// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
				//最高位(31位)置成1表示是自定义码流, 0-30位表示码流值(MIN-16K MAX-8192K)。
	DWORD dwVideoFrameRate;	//帧率 0-全部; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
}NET_DVR_COMPRESSION_INFO,*LPNET_DVR_COMPRESSION_INFO;

typedef struct{
	DWORD dwSize;
	NET_DVR_COMPRESSION_INFO struRecordPara; //录像
	NET_DVR_COMPRESSION_INFO struNetPara;	//网传
}NET_DVR_COMPRESSIONCFG,*LPNET_DVR_COMPRESSIONCFG;



#define CMD_CHANNEL_GETVIDEOINFO		"cmd_channel_getvideoinfo"	// 视频信息
/*#define ATTRIB_ENCODER_ID				"eid"						// 编码器*/
/*#define ATTRIB_CHANNEL_ID				"cid"						// 通道号*/
#define ATTRIB_VIDEO_DEVICE				"video_device"				// 设备
#define ATTRIB_VIDEO_DENOISE			"video_denoise"				// 图像去噪

#define ATTRIB_VIDEO_CODEC				"video_codec"				// 编码方式
#define ATTRIB_VIDEO_RESOLUTION			"video_resolution"			// 分辨率
#define ATTRIB_VIDEO_FRAMERATE			"video_framerate"			// 视频帧率
#define ATTRIB_VIDEO_FRAMETYPE			"video_frametype"			// 视频模式
#define ATTRIB_VIDEO_QUALITY			"video_quality"				// 视频码流
#define ATTRIB_VIDEO_AUTOQUALITY		"video_autoquality"			// 图像质量自动控制

#define ATTRIB_VIDEO_CODEC_SUB			"video_codec_sub"			// 子流编码方式
#define ATTRIB_VIDEO_RESOLUTION_SUB		"video_resolution_sub"		// 子流分辨率
#define ATTRIB_VIDEO_FRAMERATE_SUB		"video_framerate_sub"		// 子流帧率
#define ATTRIB_VIDEO_FRAMETYPE_SUB		"video_frametype_sub"		// 子流模式
#define ATTRIB_VIDEO_QUALITY_SUB		"video_quality_sub"			// 子流码流
#define ATTRIB_VIDEO_AUTOQUALITY_SUB	"video_autoquality_sub"		// 子流图像质量自动控制

#define ATTRIB_VIDEO_QUARTERSIZE_SUB	"video_quartersize_sub"		// 	1/4尺寸


#define ATTRIB_NDCI_BITRATETYPE			"ndci_bitratetype"			//码率类型0:变码率，1:定码率
#define ATTRIB_NDCI_STREAMTYPE			"ndci_streamtype"			//码流类型0-视频流,1-复合流
#define ATTRIB_NDCI_RESOLUTION			"ndci_resolution"			//分辨率0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
#define ATTRIB_NDCI_PICQUALITY			"ndci_picquality"			//图象质量 0-最好 1-次好 2-较好 3-一般 4-较差 5-差	
#define ATTRIB_NDCI_VIDEOFRAMERATE		"ndci_videoframerate"		//帧率 0-全部; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
#define ATTRIB_NDCI_VIDEOBITRATE		"ndci_videobitrate"			//视频码率 0-保留 1-保留 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 
//11-256K 12-320K 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 
//21-1536K 22-1792K 23-2048K
//最高位(31位)置成1表示是自定义码流, 0-30位表示码流值(MIN-16K MAX-8192K)

#define ATTRIB_NDCI_BITRATETYPE_SUB		"ndci_bitratetype_sub"		//码率类型0:变码率，1:定码率
#define ATTRIB_NDCI_STREAMTYPE_SUB		"ndci_streamtype_sub"		//码流类型0-视频流,1-复合流
#define ATTRIB_NDCI_RESOLUTION_SUB		"ndci_resolution_sub"		//分辨率0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
#define ATTRIB_NDCI_PICQUALITY_SUB		"ndci_picquality_sub"		//图象质量 0-最好 1-次好 2-较好 3-一般 4-较差 5-差	
#define ATTRIB_NDCI_VIDEOFRAMERATE_SUB	"ndci_videoframerate_sub"	//帧率 0-全部; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
#define ATTRIB_NDCI_VIDEOBITRATE_SUB	"ndci_videobitrate_sub"		//视频码率 0-保留 1-保留 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 
//11-256K 12-320K 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 
//21-1536K 22-1792K 23-2048K
//最高位(31位)置成1表示是自定义码流, 0-30位表示码流值(MIN-16K MAX-8192K)

typedef struct tagVIDEO_INFO// 视频信息
{
	std::string	eid;			// 编码器
	ULONG	cid;			// 通道
	std::string	encodername;	
	std::string	channelname;	

	//dvr
	int		device;			// 设备
	int     denoise;		// 图像去噪

	int		codec;			// 编码方式
	int		resolution;		// 分辨率
	int		framerate;		// 视频帧率
	int		frametype;		// 视频模式
	int		quality;		// 视频码流
	int		autoquality;	// 图像质量自动控制

	int		codec_sub;		// 子流编码方式
	int		resolution_sub;	// 子分辨率
	int		framerate_sub;	// 子流帧率
	int		frametype_sub;	// 子流模式
	int		quality_sub;	// 子流码流
	int		autoquality_sub;// 图像质量自动控制

	int     quartersize_sub;// 1/4尺寸

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


#define CMD_CHANNEL_GETAUDIOINFO  "cmd_channel_getaudioinfo"// 音频信息
#define ATTRIB_AUDIO_DEVICE		  "audio_device"			// 设备
#define ATTRIB_AUDIO_CODEC		  "audio_codec"				// 编码方式
#define	ATTRIB_AUDIO_VAD		  "audio_vad"				// 静音检测
#define ATTRIB_AUDIO_AGC		  "audio_agc"				// 自动增益
#define ATTRIB_AUDIO_AEC		  "audio_aec"				// 回音消除
#define ATTRIB_AUDIO_CAPTURE_CARD "audio_capture_card"		// 采集音频卡
#define ATTRIB_AUDIO_CAPTURE_MODE "audio_capture_mode"		// 采集模式：0:MIC，1:LINE_IN，2:WAVE_OUT_MIXER
#define ATTRIB_AUDIO_LABIAL_SYNC  "audio_labial_sync"		// 唇音同步
#define ATTRIB_COPY_TO_A2A		  "copy_to_a2a"				// 复制到对讲通道
typedef struct tagAUDIO_INFO// 音频信息
{
	std::string	eid;			// 编码器
	ULONG	cid;			// 通道
	string	encodername;		
	string	channelname;		

	int		device;			// 设备
	int		codec;			// 编码方式
	int		agc;			// 自动增益
	int		aec;			// 回音消除
	int		vad;			// 静音检测
	int		capture_card;	// 采集音频卡
	int		capture_mode;	// 采集模式：0:MIC，1:LINE_IN，2:WAVE_OUT_MIXER

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