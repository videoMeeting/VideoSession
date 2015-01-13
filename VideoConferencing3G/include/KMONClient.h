#pragma once

#include "KMONDefine.h"

//---------------------------------------------------------------------------------------
// KMONSessionEvent�¼��ӿ���
class KMONSessionEvent
{
public:
	KMONSessionEvent(void){};
	virtual ~KMONSessionEvent(void){};
	
public:
	/* �������ӷ�����...... */
	virtual void OnConnecting(void)=0;

	/* ���������ӵ������� */
	virtual void OnReconnected(void)=0;

	/* ����������æ */
	virtual void OnBusy(void)=0;

	/* δ���ӵ������� */
	virtual void OnFailed(void)=0;

	/* ������������������ѶϿ�
	 * nErrCode: ERR_SYS_NETWORK=��������Ͽ�; ERR_SYS_SERVERTYPE=��¼���������͵ķ����� */
	virtual void OnDisconnected(unsigned int nErrCode)=0;

	/* �����ӵ������� */
	virtual void OnConnected(void)=0;

	/* �յ��������б�
	 * strMCUID:		������ID
	 * strMCUType:		����������(MCU/MTS/MCU+MTS)
	 * ulConnections:	������������
	 * ulBandWidth:		���������۴���
	 * ulActivity:		��������Ծ��
	 * strIPAddr:		������IP��ַ
	 * usIPPort:		������IP�˿�
	 * strIPType:		������IP����
	 * strIPName:		������IP���� */
	virtual void OnServerList(const std::string& strMCUID,const std::string& strMCUType,
		                      unsigned long ulConnections,const std::string& strBandWidth,unsigned long ulActivity,
							  const std::string& strIPAddr,unsigned short usIPPort,const std::string& strIPName)=0;

	/* �յ��������б���� */
	virtual void OnServerListEnd(void)=0;

	/* ��¼������nErrCode: 
	 * 0=��¼�ɹ�
	 * 1=�û��˺Ų�����
	 * 2=�û�������Ч
	 * 3=�û��ѵ�¼
	 * 99=ϵͳ���� */
	virtual void OnLogin(int nErrCode)=0;

	/* ע��������nErrCode: 
	 * 0=��¼�ɹ�
	 * 1=ϵͳ�Ͽ�
	 * 99=ϵͳ���� */
	virtual void OnLogout(int nErrCode)=0;

	/* �豸���� */
	virtual void OnDeviceOnline(KCmdPacket& rCmdPacket)=0;

	/* �豸���� */
	virtual void OnDeviceOffline(KCmdPacket& rCmdPacket)=0;

	/* �յ�ͨ������ (DEVID,CHNUM,ERRCODE) */
	virtual void OnChannelOnline(KCmdPacket& rCmdPacket)=0;

	/* �յ�ͨ������ */
	virtual void OnChannelOffline(KCmdPacket& rCmdPacket)=0;

	virtual void OnMonDispatchRegionInfo(KCmdItem& rCmdPacket)=0;				// ����
	virtual void OnMonDispatchAlert(KCmdPacket& rCmdPacket)=0;					// ����

	virtual void OnMonDispatchA2A(KCmdPacket& rCmdPacket){};					// ����Խ�
	virtual void OnMonDispatchA2ABye(KCmdPacket& rCmdPacket){};					// ����Խ�
	virtual void OnMonDispatchDevCHCtrl(KCmdPacket& rCmdPacket){};				// ������̨��������
	virtual void OnMonDispatchSrvInfo(KCmdPacket& rCmdPacket){};				// ���� MCU ��Ϣ
	virtual void OnMonDispatchBasicInfo(KCmdPacket& rCmdPacket){};				// ��ȡ������Ϣ

	virtual void OnMonDispatchGetYTConnectionParameters(KCmdPacket& rCmdPacket){};	// ��ȡ��̨���Ӳ�������
	virtual void OnMonDispatchGetYTControlParameters(KCmdPacket& rCmdPacket){};		// ��ȡ��̨���Ʋ�������
	virtual void OnMonDispatchSetYTConnectionParameters(KCmdPacket& rCmdPacket){};	// ������̨���Ӳ���
	virtual void OnMonDispatchSetYTControlParameters(KCmdPacket& rCmdPacket){};		// ������̨���Ʋ���

	// AV��������
	virtual void OnMonDispatchGetAVParameters(KCmdPacket& rCmdPacket){};
	virtual void OnMonDispatchSetAVParameters(KCmdPacket& rCmdPacket){};	

	//���ػ���P2P
	virtual void OnMonP2P(const std::string& strUserID, KCmdUserDataPacket& packet)=0;
};

//---------------------------------------------------------------------------------------
// KMONSession�ӿ���
class AFX_EXT_CLASS KMONSession
{
public:
	KMONSession(void){};
	virtual ~KMONSession(void){};

	/* ��WIN32���ã���û����Ϣѭ��ʱ����DoCheck��������崦���� */
	virtual bool ProcessTimerEvent(void)=0;

	/****************************************************************
	 * ��ȡ���ز���(���ӳɹ������)
	 ****************************************************************/

	/* ������ӵķ�����ID */
	virtual std::string GetServerID(void)=0;

	/* ��÷�������ַ */
	virtual std::string GetServerAddr(void)=0;

	/* ��÷������˿� */
	virtual unsigned short GetServerPort(void)=0;

	/* ��÷���������: SERVER_TYPE_MCU | SERVER_TYPE_MCU_MTS */
	virtual unsigned int GetServerType(void)=0;

	/* ��÷�����ʱ�� */
	virtual std::string GetServerTime(void)=0;

	/* ���NAT��ַ */
	virtual std::string GetNatAddr(void)=0;

	/* ���LOCAL��ַ */
	virtual std::string GetLocalAddr(void)=0;

	/* ���LOCAL�˿� */
	virtual unsigned short GetLocalPort(void)=0;

	/* ��÷������б� */
	virtual void GetServerList(void)=0;

	/****************************************************************
	 * ��������(���ӳɹ������)
	 ****************************************************************/

	/* ��¼
	 * usClientType(�ͻ�������): "SYS" "MON" "OCX" */
	virtual void Login(const std::string& strUserID,const std::string& strPassword,const std::string& strClientType,const std::string& strName,const std::string& strSerialno,const std::string& strTermType="")=0;

	/* ע�� */
	virtual void Logout(void)=0;

	/* ���Ͷ��� */
	virtual void SendSMS(const std::string& strMobilNumber,const std::string& strMessage)=0;

	/* �豸���� */
	virtual void DeviceOnline(const std::string &strDevType, const std::string &strDevID,const std::string &strPwd,const std::string &strMask,const std::string &strName)=0;

	/* �޸��豸���� */
	virtual void UpdateDeviceName(const std::string &strDevID,const std::string &strName)=0;

	/* �豸���� */
	virtual void DeviceOffline(const std::string &strDevID)=0;

	/* ����DVRͨ��������Ϣ */
	virtual void MON_DevCHOnline( const DEV_CHANNEL_ITEM &channelItem )=0;

	/* �޸�ͨ������ */
	virtual void UpdateChannelName(const std::string &strChannelID,const std::string &strName)=0;

	/* ����DVRͨ��ע������ chanelNum = -1 ����ͨ��ע�� */
	virtual void MON_DevCHOffline( const std::string &strDevID,unsigned short nCHNum )=0; 
	
	/* ��ȡ������Ϣ */
	virtual void MON_GetBasicInfo( const std::string &strDevID )=0;

	virtual int  MON_GetRegion()=0;
	virtual int  MON_GetRegion( const std::string &strUserID )=0;
	virtual int  MON_GetSubRegion( const std::string strRegionID,unsigned short nNodeType )=0;              // ��ȡ������
	
	/* ���ͶԽ� */
	virtual void MON_A2AInvite( const std::string &strCALLID,const DEV_CHANNEL_ITEM &channelItem,const std::string &strSDPData )=0;
	virtual void MON_A2ARsp( const std::string &strCALLID,const DEV_CHANNEL_ITEM &channelItem,const std::string &strSDPData )=0;
	virtual void MON_A2ABye( const std::string &strCALLID )=0;

	virtual int  MON_DevCHCtrl(const std::string &strDevID,unsigned short nCHNum,unsigned short nYTCmd, unsigned short nSpeed, unsigned short nPresetNO,const std::string &strPresetName )=0;// ��̨����

	/* ���� */
	virtual void MON_Alert( const std::string &strDevID,unsigned short nCHNum,unsigned short nLevel,unsigned short nsubLevel = 0 )=0;
	
	/* ������ȡ��̨���Ʋ������� */
	virtual void MON_GetYTControlParameters(const std::string &strDevID, unsigned short nCHNum)=0;

	/* ������ȡ��̨���Ӳ������� */
	virtual void MON_GetYTConnectionParameters(const std::string &strDevID, unsigned short nCHNum)=0;

	/* ������̨���Ʋ��� */
	virtual void MON_SendYTControlParameters(const std::string &strDevID,const std::string &strToID, const YT_CONTROL_PARAMETERS & YTParam)=0;

	/* ������̨���Ӳ��� */
	virtual void MON_SendYTConnectionParameters(const std::string &strDevID,const std::string &strToID, unsigned short nChannelNum, const std::string &strType, unsigned short nCom,  unsigned short  nSerialNo)=0;

	/* ��Ƶ�������� */
	virtual void MON_SendAudioParameters(unsigned short unDevType, const std::string &strToID, const AUDIO_INFO & ai)=0;

	/* ��Ƶ�������� */
	virtual void MON_SendVideoParameters(unsigned short unDevType, const std::string &strToID, const VIDEO_INFO & vi)=0;

	//����P2P
	virtual void MonP2P(const std::string strUserID, KCmdUserDataPacket& packet)=0;
};

//---------------------------------------------------------------------------------------

/* ��������
 * nProxyType: 0=û�д���; 1=HTTP����; 2=SOCK5����; 3=TUNNEL��� */
AFX_EXT_CLASS bool MONSessionConnect(KMONSessionEvent* pMONSessionEvent,const std::string& strServerAddr,unsigned short usServerPort,const std::string& strLoginDomain);
AFX_EXT_CLASS void MONSessionDisconnect(void);
AFX_EXT_CLASS KMONSession& GetMONSession(void);
