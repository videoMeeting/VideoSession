#pragma once

//=======================================================================================
// 类型定义
//=======================================================================================

//-------------------------------------------
// 联系人信息结构(记载联系人的地址资料)
typedef struct _IMS_CONTACT_ITEM
{
	std::string userid;			// 帐户ID
	std::string username;		// 帐户名称
	int         userlevel;		// 用户级别
	
	std::string gender;			// 性别
	std::string age;			// 年龄
	std::string country;		// 国家
	std::string province;		// 省份及州
	std::string city;			// 城市
	std::string address;		// 通讯地址
	std::string postcode;		// 邮编
	std::string phone;			// 电话
	std::string email;			// 电邮
	std::string show;			// public=公开资料 protected=仅联系人可见 private=不公开

	std::string group;			// 联系人所属组
	std::string initiator;		// 添加联系人的发起人
	std::string acceptflag;		// 接收标志: true=已是联系人 false=还未成为联系人
	std::string smscode;		// 个人短信帐号
	std::string voipcode;		// voip帐号及密码

	std::string svrid;			// 服务器ID
	std::string svraddr;		// 服务器地址
	unsigned short svrport;		// 服务器端口
	std::string svrtype;		// 服务器类型

	std::string nodeid;			// 联系人NODEID
	std::string nataddr;		// NAT地址
	std::string localaddr;		// 本地地址
	unsigned short localport;	// 本地端口
	std::string termtype;		// 所在终端类型
	std::string status;			// online offline busy away
    bool        IsEnterRoom;
    unsigned long  ulMediaId;

	_IMS_CONTACT_ITEM()
	{
		userid		= "";
		username	= "";
		userlevel	= 0;
		
		gender		= "";
		age			= "";
		country		= "";
		province	= "";
		city		= "";
		address		= "";
		postcode	= "";
		phone		= "";
		email		= "";
		show		= "private";

		group		= "";
		initiator	= "";
		acceptflag	= "false";
		voipcode	= "";

		svrid		= "";
		svraddr		= "";
		svrport		= 0;
		svrtype		= "";

		nodeid		= "";
		nataddr		= "";
		localaddr	= "";
		localport	= 0;
		termtype	= "";
		status		= "offline";
        IsEnterRoom = false;
        ulMediaId   = 0;
	};
}IMS_CONTACT_ITEM,*PIMS_CONTACT_ITEM;

typedef std::map<std::string,PIMS_CONTACT_ITEM> IMS_CONTACT_ITEM_MAP;

//-------------------------------------------
// 机构用户信息结构
typedef struct _IMS_ORGUSER_ITEM
{
	std::string userid;			// 帐户ID
	std::string username;		// 帐户名称
	std::string orgid;			// 机构ID
	std::string departid;		// 部门ID
	std::string nodeid;			// 联系人NODEID
	std::string status;			// 状态: 0=离线 1=在线

	_IMS_ORGUSER_ITEM()
	{
		userid		= "";
		username	= "";
		orgid		= "";
		departid	= "";
		nodeid		= "";
		status		= "offline";
	};
}IMS_ORGUSER_ITEM,*PIMS_ORGUSER_ITEM;

typedef std::map<std::string,PIMS_ORGUSER_ITEM> IMS_ORGUSER_ITEM_MAP;

//-------------------------------------------
// 即时消息信息结构(及时消息格式)
typedef struct _XMSG
{
	std::string type;		// 保留,不使用
	std::string head;
	std::string body;
	std::string format;
	std::string datetime;
	std::string attachment;
}XMSG,*PXMSG;

//-------------------------------------------
// 设备
 enum IMS_DEVICE
{
	IMS_DEVICE_CAMERA	  = 0,
	IMS_DEVICE_MICROPHONE = 1,
};

//-------------------------------------------
//监控分区
//区域（设备）信息
typedef struct _MONGROUP
{
	unsigned long	groupid;
	std::string		groupname;
	std::string		devid;
	unsigned long	parentid;
	_MONGROUP()
	{
		groupid=0;
		parentid=0;
	};
}MONGROUP,*PMONGROUP;

//-------------------------------------------
//通道信息
typedef struct _MONCHANNEL
{
	std::string channelid;
	std::string channelname;
	std::string devid;
	std::string devinfo;
	std::string nodeid;
	unsigned long groupid;
	std::string mcuid;
	std::string mcuaddr;
	unsigned short mcuport;
	std::string nataddr;
	std::string localaddr;
	unsigned short localport;
	std::string termtype;
	unsigned long videocid;
	unsigned long audiocid;
	unsigned short status;
	unsigned char controlflag;
	_MONCHANNEL()
	{
		groupid=0;
		mcuport=0;
		localport=0;
		videocid=0;
		audiocid=0;
		status=0;
		controlflag=0;
	}
}MONCHANNEL,*PMONCHANNEL;

//-----------------------------------------------
//电子地图
typedef struct _MAP_BZ_ITEM
{
	std::string strGroupID;  //区域ID
	std::string strTreeID; //通道ID
	std::string strBzID;   //热点ID
}MAP_BZ_ITEM,*PMAP_BZ_ITEM;

typedef std::list<PMAP_BZ_ITEM> MAP_BZ_LST;

//-----------------------------------------------
// AVC呼叫项
typedef struct tagAVC_CALL_ITEM
{
	std::string nodeid;
	int			status;
	bool		iscaller;
}AVC_CALL_ITEM,*PAVC_CALL_ITEM;

//-----------------------------------------------
// AVC呼叫项MAP
typedef std::map<std::string,PAVC_CALL_ITEM> AVC_CALL_ITEM_MAP;

//-----------------------------------------------
// 白板通讯信息结构
typedef struct tagWHB_CALL_ITEM
{
	std::string nodeid;
	int			status;
	bool		iscaller;
}WHB_CALL_ITEM,*PWHB_CALL_ITEM;

//-----------------------------------------------
typedef std::map<std::string,PWHB_CALL_ITEM> WHB_CALL_ITEM_MAP;

//-----------------------------------------------
// SRV屏幕视频通讯信息结构
typedef struct tagSRV_CALL_ITEM
{
	std::string nodeid;
	int			status;
	bool		iscaller;
}SRV_CALL_ITEM,*PSRV_CALL_ITEM;

//-----------------------------------------------
// SRV MAP
typedef std::map<std::string,PSRV_CALL_ITEM> SRV_CALL_ITEM_MAP;
