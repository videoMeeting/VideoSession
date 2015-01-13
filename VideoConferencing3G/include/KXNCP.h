#pragma once

#define AVCON_SERVER_VERSION		"6.2.3.6.1177"
#define AVCON_PROTOCOL_VERSION		6236

//////////////////////////////////////////////////////////////////////////////////////
//									SYS												//
//////////////////////////////////////////////////////////////////////////////////////

#define IO_CONNECT_TYPE_CLIENT_SVC			100
#define IO_CONNECT_TYPE_CLIENT_NFS			103		//¼æÈÝÀÏ°æ±¾
#define IO_CONNECT_TYPE_CLIENT_MGW			104
#define IO_CONNECT_TYPE_CLIENT_VRS			105		//¼à¿ØÂ¼ÏñÉÏ´«

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
// ÎÄ¼þ´«Êä³£Á¿
#define MAX_FILE_PACKET			65536 + 64
#define MAX_FILE_DATA_PACKET	65536
#define MAX_CMD_PACKET			32768 * 3

//////////////////////////////////////////////////////////////////////////////////////
//									MMS												//
//////////////////////////////////////////////////////////////////////////////////////

// È¨ÏÞ
 enum _MMS_RIGHT
{
	MET_RIGHT_SPEACK	= 1,	// ·¢ÑÔ
	MET_RIGHT_RECORD,			// Â¼Ïñ
	MET_RIGHT_TALK,				// ÌÖÂÛ
	MET_RIGHT_CONTROL,			// ¿ØÖÆ
	MET_RIGHT_WHITE,			// °×°å
	MET_RIGHT_FLOAT,			// ¸¡¶¯
	MET_RIGHT_MET,				// »áÒé /*ÌØ±ð´¦Àí*/
	MET_RIGHT_DESK,				// ×ÀÃæ
	MET_RIGHT_PAPER,			// Ð¡Ö½Ìõ
	MET_RIGHT_DOC,
};

// ÁÐ±í
 enum _MMS_LIST
{
	MET_LIST_ROLOCUTOR	= 1,	// ·¢ÑÔ
	MET_LIST_QUESTIONER,		// ÌáÎÊ
};

// ¸½¼þ
 enum _MMS_ANNEX
{
	MET_TOPIC	= 1,	// ±êÌâ
	MET_BULL,			// ¹«¸æ
};

//-------------------------------------
// ¨µÀÀàÐÍ
 enum _MMS_CHLTYPE
{
	MMS_CHLTYPE_VID = 1,	// ÊÓÆµÍ¨µÀ
	MMS_CHLTYPE_AUD,		// ÒôÆµÍ¨µÀ
	MMS_CHLTYPE_DOC,		// ÎÄµµÍ¨µÀ
	MMS_CHLTYPE_CHT,		// ÌÖÂÛÍ¨µÀ
	MMS_CHLTYPE_WHB,		// °×°åÍ¨µÀ
	MMS_CHLTYPE_DTS,		// ÎÄ¼þ´«ÊäÍ¨µÀ
};

//-------------------------------------
// Í¨µÀ½á¹¹
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
// ´íÎó´úÂë
//=======================================================================================
#define	ERR_NO							00000		//ÕýÈ·

//---------------------------------------------------------------------------------------
// ÏµÍ³Àà»òÍøÂçÀà´íÎó´úÂë
//---------------------------------------------------------------------------------------
#define	ERR_SYS_PROTOCOL				10000		//Í¨Ñ¶Ð­Òé°æ±¾²»Æ¥Åä
#define	ERR_SYS_UNKNOWN					10001		//Î´Öª´íÎó
#define	ERR_SYS_COMMAND					10002		//Ð­ÒéÃüÁî´íÎó
#define	ERR_SYS_DATABASE				10003		//Êý¾Ý¿â´íÎó
#define	ERR_SYS_NETWORK					10004		//ÍøÂç¶Ï¿ª(ÍøÂçÍ¨Â·¶Ï¿ª)
#define	ERR_SYS_SERVERTYPE				10005		//·þÎñÆ÷ÀàÐÍ´íÎó,µÇÂ¼µ½´íÎóÀàÐÍµÄ·þÎñÆ÷

//---------------------------------------------------------------------------------------
// ¼´Ê±Í¨Ñ¶Àà´íÎó´úÂë
//---------------------------------------------------------------------------------------
#define	ERR_IMS_PROTOCOL				20000		//Í¨Ñ¶Ð­Òé°æ±¾²»Æ¥Åä
#define	ERR_IMS_INVALIDACCOUNT			20001		//ÎÞÐ§µÄÕË»§(ÏµÍ³Ã»ÓÐ¸ÃÕË»§ID)
#define	ERR_IMS_INVALIDPASSWORD			20002		//ÎÞÐ§µÄÃÜÂë
#define	ERR_IMS_DUPLICATELOGIN			20003		//¸ÃÕË»§ÒÑ¾­µÇÂ¼,²»µÃÖØ¸´µÇÂ¼
#define	ERR_IMS_REQUESTRELOGIN			20004		//·þÎñÆ÷ÒªÇóÊ¹ÓÃ»ñµÃµÄÐÂµØÖ·ÖØÐÂµÇÂ¼
#define	ERR_IMS_KICKOUT					20005		//±»Ìß³ö(¸ÃÕË»§ÔÚÆäËüµØ·½ÒÑµÇÂ¼,Ç¿ÖÆ±¾µØÕÊºÅÍË³ö)
#define ERR_IMS_MODULELIMIT				20006		//·þÎñÆ÷¹¦ÄÜÏÞÖÆ(·þÎñ¶Ë¼´Ê±Í¨Ñ¶Ä£¿éÊÚÈ¨Ã»ÓÐÆôÓÃ)
#define ERR_IMS_CONNECTLIMIT			20007		//Á¬½Ó·þÎñÆ÷µ½´ï×î´óÓÃ»§ÊýÏÞÖÆ
#define ERR_IMS_ACCOUNTLIMIT			20008		//ÓÃ»§µÇÂ¼µ½´ï×î´óÓÃ»§ÕÊºÅÊýÏÞÖÆ
#define ERR_IMS_SERVER					20009		//ÓÃ»§ÕÊºÅÔÚ¸Ã·þÎñÆ÷ÉÏ²»´æÔÚ»ò¸Ã·þÎñÆ÷Ã»ÓÐ¼ÓÔØÕÊºÅÑéÖ¤Ä£¿é
#define ERR_IMS_SERVERLIMIT				20010		//·þÎñÆ÷µØÖ·ÏÞ¶¨,¸ÃÓÃ»§²»ÄÜÔÚ´Ë·þÎñÆ÷ÉÏµÇÂ¼

//---------------------------------------------------------------------------------------
// »áÒéÍ¨Ñ¶Àà´íÎó´úÂë
//---------------------------------------------------------------------------------------
#define ERR_MMS_PROTOCOL				30000		//Í¨Ñ¶Ð­Òé°æ±¾²»Æ¥Åä
#define	ERR_MMS_INVALIDPASSWORD			30001		//ÎÞÐ§µÄ»áÒéÃÜÂë
#define	ERR_MMS_ALREADYLOGIN			30002		//¸ÃÕË»§ÒÑ¾­½øÈë»áÒé
#define	ERR_MMS_WORKGROUPLIMITS			30003		//»áÒéÒÑ¾­³¬¹ýÁùÈËÏÞÖÆ
#define	ERR_MMS_NOMCU					30004		//»áÒéÃ»ÓÐÊÊµ±µÄMCU·þÎñÆ÷
#define	ERR_MMS_OWNERLEAVED				30005		//»áÒéËùÓÐÕßÀë¿ª»áÒé
#define	ERR_MMS_ROOMLOCKED				30006		//»áÒéÒÑ¾­Ëø¶¨
#define	ERR_MMS_INVALIDROOMTYPE			30007		//»áÒéÊÒÀàÐÍ²»Ã÷È·
#define	ERR_MMS_INVALIDMEMBERTYPE		30008		//µÇÂ¼ÕßÀàÐÍ²»Ã÷È·
#define	ERR_MMS_LOSSINVALID				30009		//¶¨Ëð±¨°¸ºÅ²»´æÔÚ
#define	ERR_MMS_LOSSAGAIN				30010		//¶¨Ëð±¨°¸ºÅÒÑ±»ÆäËûÈËµÇ¼Ç
#define	ERR_MMS_LOSSHAVEEND				30011		//¶¨Ëð±¨°¸ºÅÒÑ¾­¶¨Ëð½áÊø
#define ERR_MMS_MODULELIMIT				30012		//·þÎñÆ÷¹¦ÄÜÏÞÖÆ(ÏµÍ³»áÒéÄ£¿éÊÚÈ¨Ã»ÓÐÆôÓÃ)
#define ERR_MMS_CONNECTLIMIT			30013		//ÏµÍ³µ½´ï×î´ó»áÒé³ÉÔ±ÊýÏÞÖÆ
#define ERR_MMS_HAVETV					30014		//µçÊÓÇ½Éè±¸ºÅÒÑ´æÔÚ
#define ERR_MMS_INVALIDTV				30015		//·ÇÓÐÐ§µÄµçÊÓÇ½Éè±¸ºÅ
#define ERR_MMS_HAVETVMATRIX			30016		//µçÊÓÇ½¾ØÕóÉè±¸ºÅÒÑ´æÔÚ
#define ERR_MMS_INVALIDTVMATRIX			30017		//·ÇÓÐÐ§µÄµçÊÓÇ½¾ØÕóÉè±¸ºÅ
#define ERR_MMS_SERVER					30018		//»áÒé·þÎñÆ÷¶Ï¿ªÁ¬½Ó
#define ERR_MMS_AUDITORLIMIT			30019		//»áÒéÅÔÌýÕß×î´óÊýÁ¿ÏÞÖÆ

//---------------------------------------------------------------------------------------
// ¶ÌÐÅÀà´íÎó´úÂë
//---------------------------------------------------------------------------------------
#define ERR_SMS_PROTOCOL				40000		//Í¨Ñ¶Ð­Òé°æ±¾²»Æ¥Åä
#define	ERR_SMS_GATEWAY					40001		//¶ÌÐÅÍø¹Ø·¢ËÍÊ§°Ü
#define	ERR_SMS_INVALIDSEARIALNO		40002		//ÐòÁÐºÅÂëÎª¿Õ»òÎÞÐ§
#define	ERR_SMS_NETWORK					40003		//Á¬½Óµ½¶ÌÐÅÍø¹Ø·¢ÉúÍøÂç¹ÊÕÏ
#define	ERR_SMS_OTHERS					40004		//Á¬½Óµ½¶ÌÐÅÍø¹Ø·¢ÉúÆäËû¹ÊÕÏ
#define	ERR_SMS_ENTRYLIMITS				40005		//ÊÖ»úºÅÂëÎª¿Õ»òÕß³¬¹ý1000¸ö
#define	ERR_SMS_SPLITCHAR				40006		//ÊÖ»úºÅÂë·Ö¸î·ûºÅ²»ÕýÈ·
#define	ERR_SMS_ERRORNUMBER				40007		//²¿·ÖÊÖ»úºÅÂë²»ÕýÈ·£¬ÒÑÉ¾³ý£¬ÆäÓàÊÖ»úºÅÂë±»·¢ËÍ
#define	ERR_SMS_CONTENTOVERFLOW			40008		//¶ÌÐÅÄÚÈÝÎª¿Õ»ò³¬³¤(70¸öºº×Ö)
#define	ERR_SMS_BILLING					40009		//¶ÌÐÅÍø¹Ø¼Æ·ÑÊ§°Ü
#define	ERR_SMS_UNKNOWN					40010		//Î´Öª´íÎó
#define ERR_SMS_MODULELIMIT				40011		//·þÎñÆ÷¹¦ÄÜÏÞÖÆ(ÏµÍ³¶ÌÐÅÄ£¿éÊÚÈ¨Ã»ÓÐÆôÓÃ)
#define ERR_SMS_INVALIDTYPE				40012		//¶ÌÐÅÀàÐÍÎ´¶¨Òå
#define ERR_SMS_EMPTYCODE				40013		//·¢ËÍºÅ»ò½ÓÊÕºÅÎª¿Õ

//---------------------------------------------------------------------------------------
// ¼à¿ØÀàÀà´íÎó´úÂë
//---------------------------------------------------------------------------------------
#define ERR_MON_PROTOCOL				50000		//Í¨Ñ¶Ð­Òé°æ±¾²»Æ¥Åä
#define ERR_MON_REUSESERIAL				50001		//ÐòÁÐºÅÒÑ±»ÆäËûÕÊ»§°ó¶¨
#define	ERR_MON_INVALIDACCOUNT			50002		//ÎÞÐ§µÄ¼à¿ØÉè±¸(»òÍø¹Ø)ÕË»§(ÏµÍ³Ã»ÓÐ¸ÃÕË»§ID)
#define	ERR_MON_INVALIDPASSWORD			50003		//ÎÞÐ§µÄÃÜÂë
#define	ERR_MON_INVALIDSERIAL			50004		//ÎÞÐ§µÄÐòÁÐºÅ
#define	ERR_MON_ALREADYLOGIN			50005		//ÒÑ¾­µÇÂ¼
#define ERR_MON_INVALIDTYPE				50006		//·Ç·¨µÄÖÕ¶ËÀàÐÍ
#define ERR_MON_MODULELIMIT				50007		//·þÎñÆ÷¹¦ÄÜÏÞÖÆ(ÏµÍ³¼à¿ØÄ£¿éÊÚÈ¨Ã»ÓÐÆôÓÃ)
#define ERR_MON_CONNECTLIMIT			50008		//ÏµÍ³µ½´ï×î´óÍ¨µÀÊýÏÞÖÆ
