#pragma once

//=======================================================================================
// MCU测试速度客户端接口类
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
// MCU测试速度接口事件类
//---------------------------------------------------------
class AFX_EXT_CLASS KMCUSessionEvent
{
public:
	KMCUSessionEvent(void){};
	virtual ~KMCUSessionEvent(void){};
	
	/* 连接成功  */
	virtual void OnConnected(void)=0;

	/* 连接断开  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* 测试反馈: ulElapsedTime=平均反馈时间(ms) */
	virtual void OnTest(double dElapsedTime)=0;
};

//---------------------------------------------------------
// MCU测试速度接口类
//---------------------------------------------------------
class AFX_EXT_CLASS KMCUSession
{
public:
	KMCUSession(void){};
	virtual ~KMCUSession(void){};

	/* 连接服务器 */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort,unsigned int nBytes=32)=0;

	/* 断开服务器连接 */
	virtual void Disconnect(void)=0;
};

//=======================================================================================
// MCUSession实例
//=======================================================================================
AFX_EXT_CLASS KMCUSession* CreateMCUSession(KMCUSessionEvent& rMCUSessionEvent);
