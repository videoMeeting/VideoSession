#pragma once

#define AVCON_SERVER_VERSION		"6.2.3.6.1177"
#define AVCON_PROTOCOL_VERSION		6236

//////////////////////////////////////////////////////////////////////////////////////
//									SYS												//
//////////////////////////////////////////////////////////////////////////////////////

#define IO_CONNECT_TYPE_CLIENT_SVC			100
#define IO_CONNECT_TYPE_CLIENT_NFS			103		//�����ϰ汾
#define IO_CONNECT_TYPE_CLIENT_MGW			104
#define IO_CONNECT_TYPE_CLIENT_VRS			105		//���¼���ϴ�

#define IO_CONNECT_TYPE_MCU_ROUTER			200
#define IO_CONNECT_TYPE_NFS_ROUTER			201

#define SERVER_TYPE_MCU						300
#define SERVER_TYPE_MTS						301
#define SERVER_TYPE_MCU_MTS					302

#define IMS_AGENT_ID						400
#define MMS_AGENT_ID						401
#define MON_AGENT_ID						402
#define SMS_AGENT_ID						403
#define FAX_AGENT_ID						404
#define SIP_AGENT_ID						405

//---------------------------------------------------------
// �ļ����䳣��
#define MAX_FILE_PACKET			65536 + 64
#define MAX_FILE_DATA_PACKET	65536
#define MAX_CMD_PACKET			32768 * 3

//////////////////////////////////////////////////////////////////////////////////////
//									MMS												//
//////////////////////////////////////////////////////////////////////////////////////

// Ȩ��
 enum _MMS_RIGHT
{
	MET_RIGHT_SPEACK	= 1,	// ����
	MET_RIGHT_RECORD,			// ¼��
	MET_RIGHT_TALK,				// ����
	MET_RIGHT_CONTROL,			// ����
	MET_RIGHT_WHITE,			// �װ�
	MET_RIGHT_FLOAT,			// ����
	MET_RIGHT_MET,				// ���� /*�ر���*/
	MET_RIGHT_DESK,				// ����
	MET_RIGHT_PAPER,			// Сֽ��
	MET_RIGHT_DOC,
};

// �б�
 enum _MMS_LIST
{
	MET_LIST_ROLOCUTOR	= 1,	// ����
	MET_LIST_QUESTIONER,		// ����
};

// ����
 enum _MMS_ANNEX
{
	MET_TOPIC	= 1,	// ����
	MET_BULL,			// ����
};

//-------------------------------------
// �������
 enum _MMS_CHLTYPE
{
	MMS_CHLTYPE_VID = 1,	// ��Ƶͨ��
	MMS_CHLTYPE_AUD,		// ��Ƶͨ��
	MMS_CHLTYPE_DOC,		// �ĵ�ͨ��
	MMS_CHLTYPE_CHT,		// ����ͨ��
	MMS_CHLTYPE_WHB,		// �װ�ͨ��
	MMS_CHLTYPE_DTS,		// �ļ�����ͨ��
};

//-------------------------------------
// ͨ���ṹ
typedef struct _MMS_CHANNEL
{
	unsigned int	channeltype;
	unsigned long	channelid;
	_MMS_CHANNEL()
	{
		channeltype=0;
		channelid=0;
	};
}MMS_CHANNEL,*PMMS_CHANNEL;

#include <list>
typedef std::list<PMMS_CHANNEL> MMS_CHANNEL_LST;


//=======================================================================================
// �������
//=======================================================================================
#define	ERR_NO							00000		//��ȷ

//---------------------------------------------------------------------------------------
// ϵͳ���������������
//---------------------------------------------------------------------------------------
#define	ERR_SYS_PROTOCOL				10000		//ͨѶЭ��汾��ƥ��
#define	ERR_SYS_UNKNOWN					10001		//δ֪����
#define	ERR_SYS_COMMAND					10002		//Э���������
#define	ERR_SYS_DATABASE				10003		//���ݿ����
#define	ERR_SYS_NETWORK					10004		//����Ͽ�(����ͨ·�Ͽ�)
#define	ERR_SYS_SERVERTYPE				10005		//���������ʹ���,��¼���������͵ķ�����

//---------------------------------------------------------------------------------------
// ��ʱͨѶ��������
//---------------------------------------------------------------------------------------
#define	ERR_IMS_PROTOCOL				20000		//ͨѶЭ��汾��ƥ��
#define	ERR_IMS_INVALIDACCOUNT			20001		//��Ч���˻�(ϵͳû�и��˻�ID)
#define	ERR_IMS_INVALIDPASSWORD			20002		//��Ч������
#define	ERR_IMS_DUPLICATELOGIN			20003		//���˻��Ѿ���¼,�����ظ���¼
#define	ERR_IMS_REQUESTRELOGIN			20004		//������Ҫ��ʹ�û�õ��µ�ַ���µ�¼
#define	ERR_IMS_KICKOUT					20005		//���߳�(���˻��������ط��ѵ�¼,ǿ�Ʊ����ʺ��˳�)
#define ERR_IMS_MODULELIMIT				20006		//��������������(����˼�ʱͨѶģ����Ȩû������)
#define ERR_IMS_CONNECTLIMIT			20007		//���ӷ�������������û�������
#define ERR_IMS_ACCOUNTLIMIT			20008		//�û���¼��������û��ʺ�������
#define ERR_IMS_SERVER					20009		//�û��ʺ��ڸ÷������ϲ����ڻ�÷�����û�м����ʺ���֤ģ��
#define ERR_IMS_SERVERLIMIT				20010		//��������ַ�޶�,���û������ڴ˷������ϵ�¼

//---------------------------------------------------------------------------------------
// ����ͨѶ��������
//---------------------------------------------------------------------------------------
#define ERR_MMS_PROTOCOL				30000		//ͨѶЭ��汾��ƥ��
#define	ERR_MMS_INVALIDPASSWORD			30001		//��Ч�Ļ�������
#define	ERR_MMS_ALREADYLOGIN			30002		//���˻��Ѿ��������
#define	ERR_MMS_WORKGROUPLIMITS			30003		//�����Ѿ�������������
#define	ERR_MMS_NOMCU					30004		//����û���ʵ���MCU������
#define	ERR_MMS_OWNERLEAVED				30005		//�����������뿪����
#define	ERR_MMS_ROOMLOCKED				30006		//�����Ѿ�����
#define	ERR_MMS_INVALIDROOMTYPE			30007		//���������Ͳ���ȷ
#define	ERR_MMS_INVALIDMEMBERTYPE		30008		//��¼�����Ͳ���ȷ
#define	ERR_MMS_LOSSINVALID				30009		//���𱨰��Ų�����
#define	ERR_MMS_LOSSAGAIN				30010		//���𱨰����ѱ������˵Ǽ�
#define	ERR_MMS_LOSSHAVEEND				30011		//���𱨰����Ѿ��������
#define ERR_MMS_MODULELIMIT				30012		//��������������(ϵͳ����ģ����Ȩû������)
#define ERR_MMS_CONNECTLIMIT			30013		//ϵͳ�����������Ա������
#define ERR_MMS_HAVETV					30014		//����ǽ�豸���Ѵ���
#define ERR_MMS_INVALIDTV				30015		//����Ч�ĵ���ǽ�豸��
#define ERR_MMS_HAVETVMATRIX			30016		//����ǽ�����豸���Ѵ���
#define ERR_MMS_INVALIDTVMATRIX			30017		//����Ч�ĵ���ǽ�����豸��
#define ERR_MMS_SERVER					30018		//����������Ͽ�����
#define ERR_MMS_AUDITORLIMIT			30019		//���������������������

//---------------------------------------------------------------------------------------
// ������������
//---------------------------------------------------------------------------------------
#define ERR_SMS_PROTOCOL				40000		//ͨѶЭ��汾��ƥ��
#define	ERR_SMS_GATEWAY					40001		//�������ط���ʧ��
#define	ERR_SMS_INVALIDSEARIALNO		40002		//���к���Ϊ�ջ���Ч
#define	ERR_SMS_NETWORK					40003		//���ӵ��������ط����������
#define	ERR_SMS_OTHERS					40004		//���ӵ��������ط�����������
#define	ERR_SMS_ENTRYLIMITS				40005		//�ֻ�����Ϊ�ջ��߳���1000��
#define	ERR_SMS_SPLITCHAR				40006		//�ֻ�����ָ���Ų���ȷ
#define	ERR_SMS_ERRORNUMBER				40007		//�����ֻ����벻��ȷ����ɾ���������ֻ����뱻����
#define	ERR_SMS_CONTENTOVERFLOW			40008		//��������Ϊ�ջ򳬳�(70������)
#define	ERR_SMS_BILLING					40009		//�������ؼƷ�ʧ��
#define	ERR_SMS_UNKNOWN					40010		//δ֪����
#define ERR_SMS_MODULELIMIT				40011		//��������������(ϵͳ����ģ����Ȩû������)
#define ERR_SMS_INVALIDTYPE				40012		//��������δ����
#define ERR_SMS_EMPTYCODE				40013		//���ͺŻ���պ�Ϊ��

//---------------------------------------------------------------------------------------
// �������������
//---------------------------------------------------------------------------------------
#define ERR_MON_PROTOCOL				50000		//ͨѶЭ��汾��ƥ��
#define ERR_MON_REUSESERIAL				50001		//���к��ѱ������ʻ���
#define	ERR_MON_INVALIDACCOUNT			50002		//��Ч�ļ���豸(������)�˻�(ϵͳû�и��˻�ID)
#define	ERR_MON_INVALIDPASSWORD			50003		//��Ч������
#define	ERR_MON_INVALIDSERIAL			50004		//��Ч�����к�
#define	ERR_MON_ALREADYLOGIN			50005		//�Ѿ���¼
#define ERR_MON_INVALIDTYPE				50006		//�Ƿ����ն�����
#define ERR_MON_MODULELIMIT				50007		//��������������(ϵͳ���ģ����Ȩû������)
#define ERR_MON_CONNECTLIMIT			50008		//ϵͳ�������ͨ��������
