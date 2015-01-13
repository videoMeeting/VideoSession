//RTOU.h
#ifndef __RTOU_H__
#define __RTOU_H__

#include <NETEC/NETEC_Export.h>


#define RTOU_MTU	1248

#ifdef _WIN32
#include <winsock2.h>
#ifndef __INLINE__
#define __INLINE__ _inline
#endif
#else
#ifndef SOCKET
#define SOCKET int
#endif
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#ifndef __INLINE__
#define __INLINE__ inline
#endif
#endif

typedef struct tagRTOUADDR
{
	SOCKET			hSocket;
	unsigned long	ulIP;
	unsigned short	usPort;

	tagRTOUADDR(void)
		: hSocket(INVALID_SOCKET)
		, ulIP(0)
		, usPort(0)
	{
	};
	tagRTOUADDR(SOCKET _hSocket,unsigned long _ulIP,unsigned short _usPort)
		: hSocket(_hSocket)
		, ulIP(_ulIP)
		, usPort(_usPort)
	{
	};
}RTOUADDR,*PRTOUADDR;


//RTOU_Core 每个进程只允许一个实例

class RTOU_CoreCallback
{
public:
	RTOU_CoreCallback(void){};
	virtual~RTOU_CoreCallback(void){};
public:
	//有数据要发送到指定的IP地址，包含外部数据头
	virtual void OnRTOU_CoreCallbackSendingPacket(const RTOUADDR&rRTOUAddr,unsigned char*pPacketData,int nPacketLen)=0;
};

class NETEC_API RTOU_Core
{
public:
	RTOU_Core(void){};
	virtual~RTOU_Core(void){};
public:
	//打开
	virtual int Open(void)=0;
	//关闭
	virtual void Close(void)=0;

	//处理从远程RTOU_Core发回的数据包
	virtual int ProcessRecvdPacket(const RTOUADDR&rRTOUAddr,unsigned char*pPacketData,int nPacketLen)=0;

	//驱动内部循环
	virtual bool DoTick(void)=0;

	virtual void UpdateRTOUAddr(const RTOUADDR&rRTOUAddr)=0;

	//创建RTOU_Core,如果这个进程中已经有一个实例，那么它将返回NULL
	static RTOU_Core*Create(RTOU_CoreCallback&rCallback,int nHeaderMargin=0);
	
	//取本机到指定IP地址的往返时间
	static unsigned long GetRTT(const RTOUADDR&rRTOUAddr);
	//取本机到指定IP地址的丢包率
	static int GetTXPacketLossRate(const RTOUADDR&rRTOUAddr);
	//取指定IP地址到本机的丢包率
	static int GetRXPacketLossRate(const RTOUADDR&rRTOUAddr);
	//取本机到指定IP地址的包重传率
	static int GetTXPacketRetransferRate(const RTOUADDR&rRTOUAddr);
	//取指定IP地址到本机的包重传率
	static int GetRXPacketRetransferRate(const RTOUADDR&rRTOUAddr);
	//取本机到指定IP地址的延时抖动
	static unsigned long GetTXDelayVariation(const RTOUADDR&rRTOUAddr);
	//取指定IP地址到本机的延时抖动
	static unsigned long GetRXDelayVariation(const RTOUADDR&rRTOUAddr);

	static SOCKET GetBestSocketHandle(unsigned long ulIP,unsigned short usPort);
};


class RTOU_RTSPSessionCallback
{
public:
	RTOU_RTSPSessionCallback(void){};
	virtual~RTOU_RTSPSessionCallback(void){};
public:
	//有数据包要发送
	virtual void OnRTOU_RTSPSessionCallbackSendingPacket(unsigned char*pPacketData,int nPacketLen)=0;
	//收到完成的数据帧
	virtual void OnRTOU_RTSPSessionCallbackRecvdFrame(unsigned char*pFrameData,int nFrameLen)=0;
};

class NETEC_API RTOU_RTSPSession
{
public:
	RTOU_RTSPSession(void){};
	virtual~RTOU_RTSPSession(void){};
public:
	//打开
	virtual int Open(void)=0;
	//关闭
	virtual void Close(void)=0;

	virtual bool DoTick(void)=0;
	//是否可以写
	virtual bool IsWritable(void)=0;
	//写数据帧
	virtual int WriteFrame(unsigned char*pFrameData,int nFrameLen)=0;
	//处理收到的数据包
	virtual int ProcessRecvdPacket(unsigned char*pPacketData,int nPacketLen)=0;
	//设置带宽
	virtual int SetMaxBandwidth(int nMaxBandwidth)=0;
	//更新RTT
	virtual void UpdateRTT(unsigned long nRTT)=0;
	//更新发送丢包率
	virtual void UpdateTXPacketLossRate(int nTXPacketLossRate)=0;

	//创建RTSPSessuion
	static RTOU_RTSPSession*Create(RTOU_RTSPSessionCallback&rCallback,const RTOUADDR&rRTOUAddr,int nMaxBandwidth,int nMTU=RTOU_MTU,int nHeaderMargin=0);
};


class RTOU_JitterBufferCallback
{
public:
	RTOU_JitterBufferCallback(void){};
	virtual~RTOU_JitterBufferCallback(void){};
public:
	virtual void OnRTOU_JitterBufferCallbackRecvdPacket(unsigned short usSeq,unsigned long ulRTPTimeMS,const unsigned char*pPacketData,int nPacketLen)=0;
};

class NETEC_API RTOU_JitterBuffer
{
public:
	RTOU_JitterBuffer(void){};
	virtual~RTOU_JitterBuffer(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;

	virtual int ProcessRecvdPacket(unsigned short usSeq,unsigned long ulRTPTimeMS,const unsigned char*pPacketData,int nPacketLen)=0;
	virtual bool DoTick(void)=0;

	virtual int GetTXPacketLossRate(void)=0;
	virtual unsigned long GetRXLostPacketCount(void)=0;

	//创建RTPSessuion
	static RTOU_JitterBuffer*Create(RTOU_JitterBufferCallback&rCallback,const RTOUADDR&rRTOUAddr);
};


#endif