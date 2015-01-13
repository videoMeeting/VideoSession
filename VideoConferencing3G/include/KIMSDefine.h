#pragma once

//=======================================================================================
// ���Ͷ���
//=======================================================================================

//-------------------------------------------
// ��ϵ����Ϣ�ṹ(������ϵ�˵ĵ�ַ����)
typedef struct _IMS_CONTACT_ITEM
{
	std::string userid;			// �ʻ�ID
	std::string username;		// �ʻ�����
	int         userlevel;		// �û�����
	
	std::string gender;			// �Ա�
	std::string age;			// ����
	std::string country;		// ����
	std::string province;		// ʡ�ݼ���
	std::string city;			// ����
	std::string address;		// ͨѶ��ַ
	std::string postcode;		// �ʱ�
	std::string phone;			// �绰
	std::string email;			// ����
	std::string show;			// public=�������� protected=����ϵ�˿ɼ� private=������

	std::string group;			// ��ϵ��������
	std::string initiator;		// �����ϵ�˵ķ�����
	std::string acceptflag;		// ���ձ�־: true=������ϵ�� false=��δ��Ϊ��ϵ��
	std::string smscode;		// ���˶����ʺ�
	std::string voipcode;		// voip�ʺż�����

	std::string svrid;			// ������ID
	std::string svraddr;		// ��������ַ
	unsigned short svrport;		// �������˿�
	std::string svrtype;		// ����������

	std::string nodeid;			// ��ϵ��NODEID
	std::string nataddr;		// NAT��ַ
	std::string localaddr;		// ���ص�ַ
	unsigned short localport;	// ���ض˿�
	std::string termtype;		// �����ն�����
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
// �����û���Ϣ�ṹ
typedef struct _IMS_ORGUSER_ITEM
{
	std::string userid;			// �ʻ�ID
	std::string username;		// �ʻ�����
	std::string orgid;			// ����ID
	std::string departid;		// ����ID
	std::string nodeid;			// ��ϵ��NODEID
	std::string status;			// ״̬: 0=���� 1=����

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
// ��ʱ��Ϣ��Ϣ�ṹ(��ʱ��Ϣ��ʽ)
typedef struct _XMSG
{
	std::string type;		// ����,��ʹ��
	std::string head;
	std::string body;
	std::string format;
	std::string datetime;
	std::string attachment;
}XMSG,*PXMSG;

//-------------------------------------------
// �豸
 enum IMS_DEVICE
{
	IMS_DEVICE_CAMERA	  = 0,
	IMS_DEVICE_MICROPHONE = 1,
};

//-------------------------------------------
//��ط���
//�����豸����Ϣ
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
//ͨ����Ϣ
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
//���ӵ�ͼ
typedef struct _MAP_BZ_ITEM
{
	std::string strGroupID;  //����ID
	std::string strTreeID; //ͨ��ID
	std::string strBzID;   //�ȵ�ID
}MAP_BZ_ITEM,*PMAP_BZ_ITEM;

typedef std::list<PMAP_BZ_ITEM> MAP_BZ_LST;

//-----------------------------------------------
// AVC������
typedef struct tagAVC_CALL_ITEM
{
	std::string nodeid;
	int			status;
	bool		iscaller;
}AVC_CALL_ITEM,*PAVC_CALL_ITEM;

//-----------------------------------------------
// AVC������MAP
typedef std::map<std::string,PAVC_CALL_ITEM> AVC_CALL_ITEM_MAP;

//-----------------------------------------------
// �װ�ͨѶ��Ϣ�ṹ
typedef struct tagWHB_CALL_ITEM
{
	std::string nodeid;
	int			status;
	bool		iscaller;
}WHB_CALL_ITEM,*PWHB_CALL_ITEM;

//-----------------------------------------------
typedef std::map<std::string,PWHB_CALL_ITEM> WHB_CALL_ITEM_MAP;

//-----------------------------------------------
// SRV��Ļ��ƵͨѶ��Ϣ�ṹ
typedef struct tagSRV_CALL_ITEM
{
	std::string nodeid;
	int			status;
	bool		iscaller;
}SRV_CALL_ITEM,*PSRV_CALL_ITEM;

//-----------------------------------------------
// SRV MAP
typedef std::map<std::string,PSRV_CALL_ITEM> SRV_CALL_ITEM_MAP;
