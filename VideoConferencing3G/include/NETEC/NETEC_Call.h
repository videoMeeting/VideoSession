//NETEC_Call.h
#ifndef __NETEC_CALL_H__
#define __NETEC_CALL_H__

#include <NETEC/NETEC.h>

class NETEC_API NETEC_Call
{
public:
	NETEC_Call(void);
	virtual~NETEC_Call(void);
public:
	virtual int Start(void);
	virtual void Stop(void);
	
	virtual const char* MakeCall(const char*cszPeerUserID,const char*cszCallType,const char*cszLocalSDP);
	virtual int HangupCall(const char*cszCallID);
	virtual int AcceptCall(const char*cszCallID,const char*cszLocalSDP);

	virtual const char*GetCallPeerNodeID(const char*cszCallID);
	virtual const char*GetCallPeerNATIP(const char*cszCallID);
	virtual const char*GetCallPeerLocalIP(const char*cszCallID);
	virtual unsigned short GetCallPeerLocalPort(const char*cszCallID);
	
	virtual void OnNETEC_CallRingOut(const char*cszPeerUserID,const char*cszPeerUserName,const char*cszCallID,const char*cszCallType)=0;
	virtual void OnNETEC_CallRingIn(const char*cszPeerUserID,const char*cszPeerUserName,const char*cszPeerSDP,const char*cszCallID,const char*cszCallType)=0;
	virtual void OnNETEC_CallEstablished(const char*cszPeerUserID,const char*cszPeerUserName,const char*cszPeerSDP,const char*cszCallID,const char*cszCallType)=0;
	virtual void OnNETEC_CallDestroyed(const char*cszPeerUserID,const char*cszPeerUserName,const char*cszCallID,const char*cszCallType)=0;
};

#endif
