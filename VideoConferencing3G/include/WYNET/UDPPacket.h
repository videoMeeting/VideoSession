/**********************************************************
 * Name: UDPPacket.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-11-21
 **********************************************************/

#pragma once

/*
 UDP Data Packet:

 +---------+--------+--------------+-----------------+--------------+-------------------+
 | TYPE(1) | SEQ(4) | TIMESTAMP(4) | SEGMENT FLAG(1) | SEND FLAG(1) | PAYLOAD LENGTH(2) |
 +---------+--------+--------------+-----------------+--------------+-------------------+
 |                                      PAYLOAD DATA(...)                               |
 +--------------------------------------------------------------------------------------+

 User defined UDP Data Packet Header Total Length = 13 Bytes

 TYPE:				        packet's type,data packet or ack packet;
                            0 = DATA
							1 = ACK;
 SEQ:			  			packet's sequence number;
 TIMESTAMP:					send data time stamp;
 SEGMENT FLAG:              sub-packet flag;
							0 = the lastest subpacket;
                            1 = subpacket flag;
 SEND FLAG:					0 = has not been sent;
							1 = has been already sent but not gotten its ACK packet;
							2 = has been gotten the ACK packet and waiting for be deleting;
 PAYLOAD LENGTH:			send payload data length;
*/

#define MAX_UDP_PACKET_SIZE			1024
#define UDP_PACKET_HEADER_SIZE		13			// UDP Packet Header Size

//---------------------------------------------------------------------------------------
// UDP包类
class AFX_EXT_CLASS KUDPPacket
{
public:
	KUDPPacket(void);
	KUDPPacket(KUDPPacket& rUDPPacket);
	KUDPPacket(char* pData,int nLen);
	virtual ~KUDPPacket(void);

	enum{DATA=0,ACK=1};

	void SetType(unsigned char ucType);
	void SetSequence(unsigned long ulSequence);
	void SetTimeStamp(unsigned long ulTimeStamp);
	void SetSegmentFlag(unsigned char ucFlag);
	void SetSendFlag(unsigned char ucFlag);
	void SetPayload(char* pData,int nLen);

	unsigned char GetType(void);
	unsigned long GetSequence(void);
	unsigned long GetTimeStamp(void);
	unsigned char GetSegmentFlag(void);
	unsigned char GetSendFlag(void);
	unsigned short GetPayloadLength(void);
	unsigned char* GetPayloadData(void);

	unsigned char* GetPacketData(void);
	unsigned short GetPacketLength(void);

private:
	unsigned char m_pPacketData[MAX_UDP_PACKET_SIZE];
};

//---------------------------------------------------------------------------------------
//KUDPOutPacket类定义
class AFX_EXT_CLASS KUDPOutPacket
{
public:
	KUDPOutPacket(void);
	KUDPOutPacket(unsigned long ulRemoteIP,unsigned short usRemotePort,char* pData,int nLen);
	virtual ~KUDPOutPacket(void);

	virtual void StorePacket(unsigned long ulRemoteIP,unsigned short usRemotePort,char* pData,int nLen);

	virtual unsigned long GetRemoteIP(void);
	virtual unsigned short GetRemotePort(void);
	virtual char* GetData(void);
	virtual int GetLen(void);

protected:
	unsigned long		m_ulRemoteIP;
	unsigned short		m_usRemotePort;
	char*				m_pData;
	int					m_nLen;
};

//---------------------------------------------------------------------------------------
//KUDPInPacket类定义
class AFX_EXT_CLASS KUDPInPacket
{
public:
	KUDPInPacket(void);
	KUDPInPacket(unsigned long ulRemoteIP,unsigned short usRemotePort,char* pData,int nLen);
	KUDPInPacket(KUDPInPacket* pUDPInPacket);
	virtual ~KUDPInPacket(void);

	void StorePacket(unsigned long ulRemoteIP,unsigned short usRemotePort,char* pData, int nLen);

	unsigned long GetRemoteIP(void);
	unsigned short GetRemotePort(void);

	char* GetData(void);
	int GetLen(void);

protected:
	unsigned long	m_ulRemoteIP;
	unsigned short	m_usRemotePort;

	char*			m_pData;
	int				m_nLen;
};
