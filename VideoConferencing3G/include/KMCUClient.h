#pragma once

//=======================================================================================
// MCU�����ٶȿͻ��˽ӿ���
//=======================================================================================
class AFX_EXT_CLASS KMCUClient
{
public:
	KMCUClient(void);
	virtual ~KMCUClient(void);

	static bool Start(void);
	static void Stop(void);
};

//---------------------------------------------------------
// MCU�����ٶȽӿ��¼���
//---------------------------------------------------------
class AFX_EXT_CLASS KMCUSessionEvent
{
public:
	KMCUSessionEvent(void){};
	virtual ~KMCUSessionEvent(void){};
	
	/* ���ӳɹ�  */
	virtual void OnConnected(void)=0;

	/* ���ӶϿ�  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* ���Է���: ulElapsedTime=ƽ������ʱ��(ms) */
	virtual void OnTest(double dElapsedTime)=0;
};

//---------------------------------------------------------
// MCU�����ٶȽӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KMCUSession
{
public:
	KMCUSession(void){};
	virtual ~KMCUSession(void){};

	/* ���ӷ����� */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort,unsigned int nBytes=32)=0;

	/* �Ͽ����������� */
	virtual void Disconnect(void)=0;
};

//=======================================================================================
// MCUSessionʵ��
//=======================================================================================
AFX_EXT_CLASS KMCUSession* CreateMCUSession(KMCUSessionEvent& rMCUSessionEvent);
