//NETEC_Session.h
#ifndef __NETEC_SESSION_H__
#define __NETEC_SESSION_H__

#include "NETEC/NETEC_Export.h"

//Õ¯¬Áª·ª∞
class NETEC_API NETEC_Session
{
public:
	NETEC_Session(void){};
	virtual~NETEC_Session(void){};
public:
	typedef enum{
		CS_CONNECTING=0,		//’˝‘⁄¡¨Ω”
		CS_FAILED,				//Œﬁ∑®¡¨Ω”
		CS_CONNECTED,			//“—æ≠¡¨Ω”
		CS_DISCONNECTED,		//∂œø™¡¨Ω”
		CS_BUSY,				//Õ¯¬Á√¶(“—∂œø™’˝÷ÿ¡¨)
		CS_RECONNECTED,			//÷ÿ¡¨≥…π¶
		CS_IDLE,				//ø’œ–
		CS_RESTARTED,			//¡¨Ω”÷ÿ÷√¡À°æ¡¨Ω”∂œø™¡À£¨≤¢«“”÷÷ÿ–¬¡¨Ω”…œ¡À£¨µ´ «ªª¡À“ª∏ˆ–¬¡¨Ω”°ø
	}CONNECT_STATUS;
public:
	//¡¨Ω”∑˛ŒÒ∆˜
	virtual int Connect(const char*cszIP,unsigned short usPort,const char*cszInterface)=0;
	//∂œø™¡¨Ω”
	virtual void Disconnect(void)=0;
	// ’µΩ¡¨Ω”◊¥Ã¨
	virtual void OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0)=0;
};

#endif