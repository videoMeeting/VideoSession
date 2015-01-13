#pragma once

#ifdef WIN32

typedef struct _PING_STATISTICS
{
	unsigned long  MinElapsed;
	unsigned long  MaxElapsed;
	unsigned long  AvgElapsed;
	unsigned long  SentPacketCount;
	unsigned long  RecvPacketCount;
	unsigned int   LostPercent;
}PING_STATISTICS,*PPING_STATISTICS;

//=======================================================================================
class AFX_EXT_CLASS KPing : public KThread
{
public:
	KPing(void);
	virtual ~KPing(void);
	bool Start(const std::string& strHostAddr,unsigned int nDataSize=32);
	void Stop(void);

	void GetStatistics(PING_STATISTICS& ps);

	virtual void OnPong(const std::string& msg){};

protected:
	struct sockaddr_in	m_saHostAddr;
	SOCKET				m_hSocket;
	bool				m_bWantToStop;

	void ThreadProcMain(void);

private:
	unsigned short m_usSequence;
	unsigned short m_usProcessID;
	
	unsigned long  m_ulMinElapsed;
	unsigned long  m_ulMaxElapsed;
	unsigned long  m_ulAvgElapsed;
	unsigned long  m_ulSentPacketCount;
	unsigned long  m_ulRecvPacketCount;

	int SendEchoRequest(SOCKET hSocket,sockaddr_in* pToAddr);
	int WaitForEchoReply(SOCKET hSocket);
	int RecvEchoReply(SOCKET hSocket,sockaddr_in* pFromAddr,unsigned short* pSeq,unsigned long* pTimeStamp,unsigned char* pTTL);
	unsigned short CalcCheckSum(unsigned short* buffer,int size);
	bool ValidateChecksum(char *pBuffer,int nLen);
};

#endif