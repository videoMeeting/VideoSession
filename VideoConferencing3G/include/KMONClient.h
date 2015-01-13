#pragma once

#include "KMONDefine.h"

//---------------------------------------------------------------------------------------
// KMONSessionEvent事件接口类
class KMONSessionEvent
{
public:
	KMONSessionEvent(void){};
	virtual ~KMONSessionEvent(void){};
	
public:
	/* 正在连接服务器...... */
	virtual void OnConnecting(void)=0;

	/* 已重新连接到服务器 */
	virtual void OnReconnected(void)=0;

	/* 服务器网络忙 */
	virtual void OnBusy(void)=0;

	/* 未连接到服务器 */
	virtual void OnFailed(void)=0;

	/* 与服务器的网络连接已断开
	 * nErrCode: ERR_SYS_NETWORK=正常网络断开; ERR_SYS_SERVERTYPE=登录到错误类型的服务器 */
	virtual void OnDisconnected(unsigned int nErrCode)=0;

	/* 已连接到服务器 */
	virtual void OnConnected(void)=0;

	/* 收到服务器列表
	 * strMCUID:		服务器ID
	 * strMCUType:		服务器类型(MCU/MTS/MCU+MTS)
	 * ulConnections:	服务器连接数
	 * ulBandWidth:		服务器理论带宽
	 * ulActivity:		服务器活跃度
	 * strIPAddr:		服务器IP地址
	 * usIPPort:		服务器IP端口
	 * strIPType:		服务器IP类型
	 * strIPName:		服务器IP名称 */
	virtual void OnServerList(const std::string& strMCUID,const std::string& strMCUType,
		                      unsigned long ulConnections,const std::string& strBandWidth,unsigned long ulActivity,
							  const std::string& strIPAddr,unsigned short usIPPort,const std::string& strIPName)=0;

	/* 收到服务器列表结束 */
	virtual void OnServerListEnd(void)=0;

	/* 登录返回码nErrCode: 
	 * 0=登录成功
	 * 1=用户账号不存在
	 * 2=用户密码无效
	 * 3=用户已登录
	 * 99=系统错误 */
	virtual void OnLogin(int nErrCode)=0;

	/* 注销返回码nErrCode: 
	 * 0=登录成功
	 * 1=系统断开
	 * 99=系统错误 */
	virtual void OnLogout(int nErrCode)=0;

	/* 设备上线 */
	virtual void OnDeviceOnline(KCmdPacket& rCmdPacket)=0;

	/* 设备下线 */
	virtual void OnDeviceOffline(KCmdPacket& rCmdPacket)=0;

	/* 收到通道上线 (DEVID,CHNUM,ERRCODE) */
	virtual void OnChannelOnline(KCmdPacket& rCmdPacket)=0;

	/* 收到通道下线 */
	virtual void OnChannelOffline(KCmdPacket& rCmdPacket)=0;

	virtual void OnMonDispatchRegionInfo(KCmdItem& rCmdPacket)=0;				// 区域
	virtual void OnMonDispatchAlert(KCmdPacket& rCmdPacket)=0;					// 报警

	virtual void OnMonDispatchA2A(KCmdPacket& rCmdPacket){};					// 处理对讲
	virtual void OnMonDispatchA2ABye(KCmdPacket& rCmdPacket){};					// 处理对讲
	virtual void OnMonDispatchDevCHCtrl(KCmdPacket& rCmdPacket){};				// 处理云台控制请求
	virtual void OnMonDispatchSrvInfo(KCmdPacket& rCmdPacket){};				// 处理 MCU 信息
	virtual void OnMonDispatchBasicInfo(KCmdPacket& rCmdPacket){};				// 获取基本信息

	virtual void OnMonDispatchGetYTConnectionParameters(KCmdPacket& rCmdPacket){};	// 获取云台连接参数请求
	virtual void OnMonDispatchGetYTControlParameters(KCmdPacket& rCmdPacket){};		// 获取云台控制参数请求
	virtual void OnMonDispatchSetYTConnectionParameters(KCmdPacket& rCmdPacket){};	// 设置云台连接参数
	virtual void OnMonDispatchSetYTControlParameters(KCmdPacket& rCmdPacket){};		// 设置云台控制参数

	// AV参数设置
	virtual void OnMonDispatchGetAVParameters(KCmdPacket& rCmdPacket){};
	virtual void OnMonDispatchSetAVParameters(KCmdPacket& rCmdPacket){};	

	//返回会议P2P
	virtual void OnMonP2P(const std::string& strUserID, KCmdUserDataPacket& packet)=0;
};

//---------------------------------------------------------------------------------------
// KMONSession接口类
class AFX_EXT_CLASS KMONSession
{
public:
	KMONSession(void){};
	virtual ~KMONSession(void){};

	/* 非WIN32调用，当没有消息循环时调用DoCheck进行命令缓冲处理检查 */
	virtual bool ProcessTimerEvent(void)=0;

	/****************************************************************
	 * 获取本地参数(连接成功后调用)
	 ****************************************************************/

	/* 获得连接的服务器ID */
	virtual std::string GetServerID(void)=0;

	/* 获得服务器地址 */
	virtual std::string GetServerAddr(void)=0;

	/* 获得服务器端口 */
	virtual unsigned short GetServerPort(void)=0;

	/* 获得服务器类型: SERVER_TYPE_MCU | SERVER_TYPE_MCU_MTS */
	virtual unsigned int GetServerType(void)=0;

	/* 获得服务器时间 */
	virtual std::string GetServerTime(void)=0;

	/* 获得NAT地址 */
	virtual std::string GetNatAddr(void)=0;

	/* 获得LOCAL地址 */
	virtual std::string GetLocalAddr(void)=0;

	/* 获得LOCAL端口 */
	virtual unsigned short GetLocalPort(void)=0;

	/* 获得服务器列表 */
	virtual void GetServerList(void)=0;

	/****************************************************************
	 * 发送命令(连接成功后调用)
	 ****************************************************************/

	/* 登录
	 * usClientType(客户端类型): "SYS" "MON" "OCX" */
	virtual void Login(const std::string& strUserID,const std::string& strPassword,const std::string& strClientType,const std::string& strName,const std::string& strSerialno,const std::string& strTermType="")=0;

	/* 注销 */
	virtual void Logout(void)=0;

	/* 发送短信 */
	virtual void SendSMS(const std::string& strMobilNumber,const std::string& strMessage)=0;

	/* 设备上线 */
	virtual void DeviceOnline(const std::string &strDevType, const std::string &strDevID,const std::string &strPwd,const std::string &strMask,const std::string &strName)=0;

	/* 修改设备名称 */
	virtual void UpdateDeviceName(const std::string &strDevID,const std::string &strName)=0;

	/* 设备下线 */
	virtual void DeviceOffline(const std::string &strDevID)=0;

	/* 发送DVR通道上线信息 */
	virtual void MON_DevCHOnline( const DEV_CHANNEL_ITEM &channelItem )=0;

	/* 修改通道名称 */
	virtual void UpdateChannelName(const std::string &strChannelID,const std::string &strName)=0;

	/* 发送DVR通道注销请求 chanelNum = -1 所有通道注销 */
	virtual void MON_DevCHOffline( const std::string &strDevID,unsigned short nCHNum )=0; 
	
	/* 获取基础信息 */
	virtual void MON_GetBasicInfo( const std::string &strDevID )=0;

	virtual int  MON_GetRegion()=0;
	virtual int  MON_GetRegion( const std::string &strUserID )=0;
	virtual int  MON_GetSubRegion( const std::string strRegionID,unsigned short nNodeType )=0;              // 获取子区域
	
	/* 发送对讲 */
	virtual void MON_A2AInvite( const std::string &strCALLID,const DEV_CHANNEL_ITEM &channelItem,const std::string &strSDPData )=0;
	virtual void MON_A2ARsp( const std::string &strCALLID,const DEV_CHANNEL_ITEM &channelItem,const std::string &strSDPData )=0;
	virtual void MON_A2ABye( const std::string &strCALLID )=0;

	virtual int  MON_DevCHCtrl(const std::string &strDevID,unsigned short nCHNum,unsigned short nYTCmd, unsigned short nSpeed, unsigned short nPresetNO,const std::string &strPresetName )=0;// 云台控制

	/* 报警 */
	virtual void MON_Alert( const std::string &strDevID,unsigned short nCHNum,unsigned short nLevel,unsigned short nsubLevel = 0 )=0;
	
	/* 发出获取云台控制参数请求 */
	virtual void MON_GetYTControlParameters(const std::string &strDevID, unsigned short nCHNum)=0;

	/* 发出获取云台连接参数请求 */
	virtual void MON_GetYTConnectionParameters(const std::string &strDevID, unsigned short nCHNum)=0;

	/* 发送云台控制参数 */
	virtual void MON_SendYTControlParameters(const std::string &strDevID,const std::string &strToID, const YT_CONTROL_PARAMETERS & YTParam)=0;

	/* 发送云台连接参数 */
	virtual void MON_SendYTConnectionParameters(const std::string &strDevID,const std::string &strToID, unsigned short nChannelNum, const std::string &strType, unsigned short nCom,  unsigned short  nSerialNo)=0;

	/* 音频参数设置 */
	virtual void MON_SendAudioParameters(unsigned short unDevType, const std::string &strToID, const AUDIO_INFO & ai)=0;

	/* 视频参数设置 */
	virtual void MON_SendVideoParameters(unsigned short unDevType, const std::string &strToID, const VIDEO_INFO & vi)=0;

	//会议P2P
	virtual void MonP2P(const std::string strUserID, KCmdUserDataPacket& packet)=0;
};

//---------------------------------------------------------------------------------------

/* 网络连接
 * nProxyType: 0=没有代理; 1=HTTP代理; 2=SOCK5代理; 3=TUNNEL隧道 */
AFX_EXT_CLASS bool MONSessionConnect(KMONSessionEvent* pMONSessionEvent,const std::string& strServerAddr,unsigned short usServerPort,const std::string& strLoginDomain);
AFX_EXT_CLASS void MONSessionDisconnect(void);
AFX_EXT_CLASS KMONSession& GetMONSession(void);
