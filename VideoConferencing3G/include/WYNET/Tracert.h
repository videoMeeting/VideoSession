#pragma once

#ifdef WIN32

//=======================================================================================
class AFX_EXT_CLASS KTracert : public KThread
{
public:
	KTracert(void);
	virtual ~KTracert(void);

	bool Start(const std::string& strHostAddr,int nDataSize=32,int nTimeOut=3000,int nHopCount=30,int nMaxRetries=3);
	void Stop(void);

	virtual void OnError(const std::string& msg){};
	virtual void OnInformation(const std::string& msg){};
	virtual void OnTrace(const std::string& msg){};
	virtual void OnCompleted(const std::string& msg){};

protected:
	std::string		m_strHostAddr;
	int				m_nDataSize;
	int				m_nTimeOut;
	int				m_nHopCount;
	int				m_nMaxRetries;
	SOCKET			m_hSocket;
	bool			m_bWantToStop;

	void ThreadProcMain(void);

private:
	unsigned short m_usSequence;
	unsigned short m_usProcessID;

	bool ResolveIP (char *pszRemoteHost, char **pszIPAddress);
	unsigned short CalcChecksum (char *pBuffer, int nLen);
	bool ValidateChecksum (char *pBuffer, int nLen);
};

#endif