#pragma once

//=======================================================================================
// 类型定义
//=======================================================================================

//-------------------------------------
// 会议类型定义
//-------------------------------------
typedef enum _MMS_ROOM_TYPE
{
	MRT_ADVANCE			= 1,	//高级会议
	MRT_TEMPORARY		= 2,	//标准会议
	MRT_MONITOR			= 3,	//监控会议
}MMS_ROOM_TYPE;

//-------------------------------------
// 会议成员类型定义
//-------------------------------------
typedef enum _MMS_MEMBER_TYPE
{
	MMT_OWNER			= 1,	//会议所有者(只针对临时会议类型有效)
	MMT_PRESIDER		= 2,	//主持人
	MMT_PRESIDERINVITEE	= 3,	//被邀请主持人
	MMT_PRESIDERTEMP	= 4,	//临时主持人
	MMT_ATTENDEE		= 5,	//与会者
	MMT_INVITEE			= 6,	//被邀请与会者
	MMT_CHANNEL			= 7,	//监控通道
	MMT_TVWALL			= 8,	//电视墙
	MMT_TVCTRL			= 9,	//电视墙控制器
	MMT_AUDITOR			= 10,	//旁听者
}MMS_MEMBER_TYPE;

//-------------------------------------
// 会议成员状态定义
//-------------------------------------
typedef enum _MMS_MEMBER_STATUS
{
	MMS_OFFLINE			= 0,	//离线
	MMS_ONLINE			= 1,	//在线
}MMS_MEMBER_STATUS;

//-------------------------------------
// 会议项结构
typedef struct _MMS_ROOM
{
	std::string		domain;						//会议室所在域
	std::string		roomid;						//会议室ID
	std::string		roomname;					//会议室名称
	unsigned short	roomtype;					//会议室类型MMS_ROOM_TYPE定义
	std::string		roomcode;					//会议室CODE
	std::string		password;					//会议室密码
	std::string		limitcode;					//会议室限制位: 仅对临时会议类型有效
	std::string		desc;						//会议室描述
	std::string		adminid;					//会议室管理员帐号,对于临时会议类型adminid为创建者，对于高级会议类型adminid为机构管理者.
	int				membersum;					//会议室中的总人数
	int				onlinesum;					//会议室中的当前在线人数
	std::string		schedule;					//none=无事件安排计划，appointed=指定日期会议(定时会议)，weekly=每周例会，monthly=每月例会，dialy=每日会议，manual=手工会议
	std::string		startdate;					//会议开始日期
	std::string		enddate;					//会议结束日期
	std::string		starttime;					//会议开始时间
	std::string		endtime;					//会议结束时间
	std::string		dayflag;					//日期标志
	_MMS_ROOM()
	{
		roomtype=0;
		membersum=0;
		onlinesum=0;
	};
}MMS_ROOM,*PMMS_ROOM;

typedef std::list<PMMS_ROOM> MMS_ROOM_LST;

//-------------------------------------
// 会议组结构
typedef struct _MMS_GROUP
{
	std::string domain;						//会议室所在域
	std::string	roomid;						//会议室ID
	std::string	groupid;					//会议室组ID
	std::string	groupname;					//会议室组名称
	int			levelid;					//组的层次
	int			orderid;					//组的序号
	std::string	parentid;					//父级组ID
	_MMS_GROUP()
	{
		levelid=0;
		orderid=0;
	};
}MMS_GROUP,*PMMS_GROUP;

typedef std::list<PMMS_GROUP> MMS_GROUP_LST;

//-------------------------------------
// 会议模板项结构
typedef struct _MMS_SCREEN
{
	int		temtype;				//屏模板类型
	int		temid;					//屏模板号
	bool	temshow;				//是否显示屏窗口
	int		temwinnum;			//屏窗口数
	int		temfloatx;				//浮动窗口X
	int		temfloaty;				//浮动窗口Y
	int		temfloatcx;				//浮动窗口CX
	int		temfloatcy;				//浮动窗口CY

	_MMS_SCREEN()
	{
		temtype		= -1;
		temid		= -1;
		temshow		= false;
		temwinnum	= -1;
		temfloatx	= 0;
		temfloaty	= 0;
		temfloatcx	= 0;
		temfloatcy	= 0;
	}
}MMS_SCREEN,*PMMS_SCREEN;

//-------------------------------------
// 会议组详细信息结构
typedef struct _MMS_GROUP_EX : public _MMS_GROUP
{
	int				curscrid;					//当前屏幕号(1号屏/2号屏/3号屏/4号屏)
	
	MMS_SCREEN		screen[4];					//4套屏幕信息

	std::string		flag;						//该组是否允许召开子组会议 "Y": 允许   "N":不允许
	std::string		devid;						//设备ID(空为会议组,非空则为设备)

	int				membernum;					//组中总成员数
	int				onlinenum;					//组中在线成员数

	bool			subnode;					//是否为叶子节点（20081102 为组递归判断增加标记位add by dqs）
	int				subonline;					//在线子节点总数
	int				subtotal;					//子节点总数

	_MMS_GROUP_EX()
	{
		curscrid=0;		

		flag="Y";
		devid="";

		membernum=0;
		onlinenum=0;

		subnode=true;
		subonline=0;
		subtotal=0;
	};
}MMS_GROUP_EX,*PMMS_GROUP_EX;

//-------------------------------------
// 会议成员基础数据结构
typedef struct _MMS_MEMBER
{
	std::string		domain;					//会议室所在域
	std::string		roomid;					//会议室ID
	std::string		groupid;				//会议室组ID
	std::string		memberid;				//成员ID
	std::string		membername;				//成员名称
	unsigned short	membertype;				//成员类型MMS_MEMBER_TYPE定义
	_MMS_MEMBER()
	{
		membertype=0;
	};
}MMS_MEMBER,*PMMS_MEMBER;

//-------------------------------------
// 会议成员扩展数据结构
typedef struct _MMS_MEMBER_EX : public _MMS_MEMBER
{
	std::string		activegroupid;			//活动组
	int				videocount;				//视频数
	int				audiocount;				//音频数
	std::string		operflag;				//操作标志
	std::string		svrid;					//服务器ID
	std::string		svraddr;				//服务器地址
	unsigned short	svrport;				//服务器端口
	std::string		svrtype;				//服务器类型
	std::string		nodeid;					//NODEID
	std::string		nataddr;				//NAT地址
	std::string		localaddr;				//本地地址
	unsigned short	localport;				//本地端口
	std::string		termtype;				//终端类型
	unsigned char	status;					//状态: 0=不在会议中 1=在会议中
	_MMS_MEMBER_EX()
	{
		videocount	= 0;
		audiocount	= 0;
		svrport		= 0;
		localport	= 0;
		status		= 0;
	}
}MMS_MEMBER_EX,*PMMS_MEMBER_EX;

typedef std::map<std::string,PMMS_MEMBER_EX> MMS_MEMBER_MAP;
typedef std::list<PMMS_MEMBER_EX> MMS_MEMBER_LST;

//-------------------------------------
// 会议投票结构
typedef struct _MMS_VOTE
{
	unsigned long	id;
	std::string		name;
	unsigned short	count;
	_MMS_VOTE()
	{
		id=0;
		count=0;
	};
}MMS_VOTE,*PMMS_VOTE;

typedef std::list<PMMS_VOTE> MMS_VOTE_LST;

//-------------------------------------
// 定损结构
typedef struct _MMS_LOSS
{
	std::string		id;			//报案号
	std::string		carid;		//车牌号
	std::string		userid;		//报损员账号
	std::string		factoryid;	//工厂号
	std::string		starttime;	//开始时间
	double			money;		//定损金额
	unsigned short	status;		//定损状态（0：定损中，1：定损结束）
	_MMS_LOSS()
	{
		money=0.00;
	};
}MMS_LOSS,*PMMS_LOSS;
