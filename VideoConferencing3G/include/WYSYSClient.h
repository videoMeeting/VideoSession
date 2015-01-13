#pragma once

//=======================================================================================
// ����������
// ����: ������ͨѶ����SESSION,����ͨѶ����Ҫ��������
//=======================================================================================
#include "KXNCP.h"
#include "WYBASE/CmdPacket.h"
#include <vector>
typedef std::vector<std::string> ENTERMEETINGUSER;

class AFX_EXT_CLASS KSYSSession
{
public:
	KSYSSession(void){};
	virtual ~KSYSSession(void){};

	/* ����ʱ�����¼� 
	 * �Է�WIN32��ϵͳ��Ϊ��ʹ��ʱ����,��Ҫ�ⲿѭ�����øú����Դ����ѽ��ܵ������ݰ� */
	virtual void ProcessTimerEvent(void)=0;

	/****************************************************************
	 * ��ȡ���ز���(���ӳɹ������)
	 ****************************************************************/

	/* ������ӵķ�����ID */
	virtual std::string GetServerID(void)=0;

	/* ��÷���������: SERVER_TYPE_MCU | SERVER_TYPE_MTS | SERVER_TYPE_MCU_MTS */
	virtual unsigned short GetServerType(void)=0;

	/* ��÷�������¼ʱ�� */
	virtual std::string GetServerTime(void)=0;

	/* ���NAT��ַ */
	virtual std::string GetNatAddr(void)=0;

	/* ���LOCAL��ַ */
	virtual std::string GetLocalAddr(void)=0;

	/* ���LOCAL�˿� */
	virtual unsigned short GetLocalPort(void)=0;

	/****************************************************************
	 * ����Э�麯��
	 ****************************************************************/

	/* ��÷������б�,���͵���������ȡ�������б�(MCU/MTS/MCU+MTS)
	   �����¼�:OnServerListStart/OnServerList/OnServerListEnd. */
	virtual void GetServerList(void)=0;

	/* ��÷�����ʵʱʱ�� */
	virtual void GetServerRealTime(void)=0;

	/* ������������
	 * usType: 0=���� 1=��Ƶ 2=��Ƶ 3=���Ӱװ� 4=��Ļ��Ƶ 5=... 
	 * ulUpStream: �ϴ���������KB
	 * ulDownStream: �ϴ���������KB
	 * strStartTime: ��ʼͳ�Ƶ�ʱ��,��ʽ:YYYY-MM-DD HH:NN:SS
	 * strEditTime:  ����ͳ�Ƶ�ʱ��,��ʽ:YYYY-MM-DD HH:NN:SS	 */
	virtual void SetTraffic(unsigned short usType,unsigned long ulUpStream,unsigned long ulDownStream,
                            const std::string& strStartTime,const std::string& strEndTime,
							unsigned long ulRoomID=0)=0;

	/****************************************************************
	 * �ڲ�ģ�����
	 ****************************************************************/

	/* ���͵�NODE */
	virtual void SetUserID(const std::string& strUserID)=0;

	/* ���͵�NODE */
	virtual void SendPacketToNode(const std::string& strNodeID,KCmdPacket& rCmdPacket)=0;

	/* ���͵�IMS AGENT */
	virtual void SendPacketToIMSAgent(KCmdPacket& rCmdPacket,const std::string& strDomain="")=0;

	/* ���͵�MMS AGENT */
	virtual void SendPacketToMMSAgent(KCmdPacket& rCmdPacket,const std::string& strDomain="")=0;

	/* ���͵�MON AGENT */
	virtual void SendPacketToMONAgent(KCmdPacket& rCmdPacket,const std::string& strDomain="")=0;

	/* ���͵�SMS AGENT */
	virtual void SendPacketToSMSAgent(KCmdPacket& rCmdPacket,const std::string& strDomain="")=0;
};

//=======================================================================================
// ���������¼���
//=======================================================================================
class AFX_EXT_CLASS KSYSSessionEvent
{
public:
	KSYSSessionEvent(void){};
	virtual ~KSYSSessionEvent(void){};

public:
	/* �������ӷ�����...... */
	virtual void OnServerConnecting(void)=0;

	/* ���������ӵ������� */
	virtual void OnServerReconnected(void)=0;

	/* ����������æ */
	virtual void OnServerBusy(void)=0;

	/* δ���ӵ������� */
	virtual void OnServerFailed(void)=0;

	/* ������������������ѶϿ�
	 * nErrCode: ERR_SYS_NETWORK=��������Ͽ�; ERR_SYS_SERVERTYPE=��¼���������͵ķ����� */
	virtual void OnServerDisconnected(unsigned int nErrCode)=0;

	/* �����ӵ������� */
	virtual void OnServerConnected(void)=0;

	/* �յ��������б�ʼ */
	virtual void OnServerListStart(void)=0;

	/* �յ��������б�
	 * strMCUID:		������ID
	 * strMCUType:		����������(MCU/MTS/MCU+MTS)
	 * ulConnections:	������������
	 * strBandWidth:	���������۴���
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

	/* �յ�������ʵʱʱ�� */
	virtual void OnServerRealTime(const std::string& strServerTime)=0;

	/* �յ��������ͻ��˰汾�б�(�����յ�������¼)
	 * strProduct:	��Ʒ��,ÿһ���ͻ���Ψһ����,�ɿͻ��˺�WEB��ͳһȷ��
	 * strVersion:	��Ʒ�汾��
	 * bForce:		�Ƿ�ǿ�Ƹ��� */
	virtual void OnClientVersion(const std::string& strProduct,const std::string& strVersion,bool bForce)=0;
};

//=======================================================================================
// SYSʵ��
//=======================================================================================

/* ���ӷ�����
 * strServerType: ����������SERVER_TYPE_MCU/SERVER_TYPE_MTS/SERVER_TYPE_MCU_MTS
 * strUserID:     �û��ʺ�(���ڻ�ȡ������������ʺŵķ������б�,
 *                ��strUserIDΪ��ʱϵͳ���Զ�Ϊ����ѡ���·������б�,�ʺŴ�������Ϊ��¼���� */
AFX_EXT_CLASS bool SYSSessionConnect(KSYSSessionEvent* pSYSSessionEvent,unsigned short usServerType,const std::string& strUserID);

AFX_EXT_CLASS void SYSSessionRun();

/* �Ͽ����������� */
AFX_EXT_CLASS void SYSSessionDisconnect(KSYSSessionEvent* pSYSSessionEvent);

/* ���SYSSessionʵ�� */
AFX_EXT_CLASS KSYSSession& GetSYSSession(void);

//=======================================================================================
// IMSģ����
//=======================================================================================
#include "KIMSDefine.h"

class AFX_EXT_CLASS KIMSSession
{
public:
	KIMSSession(void){};
	virtual ~KIMSSession(void){};

	/* SYS����ģ����û�ȡ�û�NODEID */
	virtual int OnGetUserNodeID(const std::string& strUserID,std::string& strNodeID)=0;

	/* SYS����ģ����ô�������� */
	virtual void OnDispatchCmd(KCmdPacket& t)=0;

public:
	/****************************************************************
	 * ���غ���
	 ****************************************************************/

	/* ��ձ������� */
	virtual void ClearLocalData(void)=0;

	/* ��ñ����û��ʺ� */
	virtual std::string GetUserID(void)=0;

	/* ��ñ����û��� */
	virtual std::string GetUserName(void)=0;

	/* ��ñ����û����� */
	virtual int GetUserLevel(void)=0;

	/* ��ñ�����ϵ���б� */
	virtual IMS_CONTACT_ITEM_MAP& GetFriendItemMap(void)=0;

	/* ��ñ�����ϵ���� */
	virtual PIMS_CONTACT_ITEM GetFriendItem(const std::string& strFriendID)=0;

	/* ���ͳ�ʼ��¼���� */
	virtual void SendLoginCommand(void)=0;

	/****************************************************************
	 * ���ܺ���(��Login�������¼����ܲ���)
	 ****************************************************************/

	/* �û���¼
	 * strStatus:   �û���¼��ʼ״̬ 
	 * strTermType: �ն����� */
	virtual void Login(const std::string& strUserID,const std::string& strPassword,const std::string& strStatus,const unsigned long ulMediaId,const std::string& strTermType="" )=0;

	/* �û�ע�� */
	virtual void Logout(void)=0;

	/* ��ȡע���û��� */
	virtual void GetAllUserCount(void)=0;

	/* ��ȡ�����û��� */
	virtual void GetOnlineUserCount(void)=0;

	/* �����ҵ����� */
	virtual void SetMyPassword(const std::string& strPassword)=0;

	/* �����ҵ����� */
	virtual void SetMyName(const std::string& strMyName)=0;

	/* �����ҵ���Ϣ */
	virtual void SetMyInfo(IMS_CONTACT_ITEM& item)=0;

	/* ��ȡ�ҵ���Ϣ */
	virtual void GetMyInfo(void)=0;

	/* ��ȡȨ�� */
	virtual void GetMyPriv(void)=0;

	/* ����ͷ�� */
	virtual void SetImage(const std::string& strImgType,const std::string& strImgFile)=0;

	/* ��ȡͷ�� */
	virtual void GetImage(const std::string& strFriendid)=0;

	/* ���õ�¼�û�״̬ */
	virtual void SetStatus(const std::string& strStatus)=0;

	/****************************************************************
	 * ��ϵ�����ຯ��
	 ****************************************************************/

	/* ��ȡ�������б� */
	virtual void FetchGroups(void)=0;

	/* ��Ӻ����� */
	virtual void InsertGroup(const std::string& strGroup,unsigned int nIndex)=0;

	/* ���ĺ��������� */
	virtual void UpdateGroupName(const std::string& strOldGroup,const std::string& strNewGroup)=0;

	/* ���ĺ������������� */
	virtual void UpdateGroupIndex(const std::string& strGroup,unsigned int nIndex)=0;

	/* ɾ�������� */
	virtual void DeleteGroup(const std::string& strGroup)=0;

	/****************************************************************
	 * ��ϵ���ຯ��
	 ****************************************************************/

	/* ��ȡ�����б� */
	virtual void FetchFriends(void)=0;

	/* ��ȡ��ϵ���� */
	virtual void FetchFriend(const std::string& strFriendID)=0;

	/* ��ȡ��ϵ����Ϣ */
	virtual void GetFriendInfo(const std::string& strFriendID)=0;

	/* �����ϵ�� */
	virtual void ApplyFriend(const std::string& strUserGroup, const std::string& strFriendID)=0;

	/* ������ϵ�� */
	virtual void AdmitFriend(const std::string& strFriendID)=0;

	/* ���ĺ��������� */
	virtual void UpdateFriendGroup(const std::string& strFriendID,const std::string& group)=0;

	/* ɾ������ */
	virtual void DeleteFriend(const std::string& DeleteFriend, const std::string& strFriendID)=0;

	/* �������� */
	virtual void SearchFriend(const IMS_CONTACT_ITEM& item,int nStartID=0,int nEndID=0,bool bOnlineOnly=false)=0;
    
    //room create and OnDestruction
    virtual void OnCreateInterimMeeting(std::string strHostId,unsigned long ulRoomID, unsigned int uiRoomType)=0;
    virtual void OnDestructionInterimMeeting(std::string strHostId, unsigned long ulRoomID)=0;
    
    virtual void QuitTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID)=0;
    virtual void JoinTemporaryMeeting(const std::string& strUserID, const std::string& strPeerUserID, unsigned long ulRoomID)=0;
    //
    
    virtual void OnInitializationTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount, unsigned int uiVideoType, unsigned int uiAudioType)=0;
    
    //video and audio
    virtual void OnOpenPeerUserVideo(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserVideoID, unsigned int uiScreenControl, bool bIsBroadcast)=0;
	virtual void OnClosePeerUserVideo(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserVideoID, bool bIsBroadcast)=0;
    virtual void OnOpenPeerUserAudio(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserAudioID, bool bIsBroadcast)=0;
	virtual void OnClosePeerUserAudio(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserAudioID, bool bIsBroadcast)=0;
    //end
    
    //room info
    virtual void OnScreenControl(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount)=0;
    virtual void OnInviteUser(unsigned long ulRoomID, const std::string& strPeerUserID)=0;
    virtual void OnReplyInviteUser(const std::string& strPeerUserID, unsigned long ulRoomID,bool bIsAgree)=0;
	virtual void OnSetMeetingType(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiType)=0;
    
    virtual void OnForTheFloor(const std::string& strUserID, unsigned long ulRoomID, const std::string& strHostID)=0;
	virtual void OnPleaseOutTemporaryMeeting(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID)=0;
	virtual void OnPassPrivileges(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID)=0;
	virtual void OnUserSnedMsg(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, std::string& ulUserMsg, bool bIsBroadcast)=0;
    //end

	/****************************************************************
	 * ��������
	 ****************************************************************/

	/* ��ȡ�����б�
	 * strUpdateTime: �ϴθ��»����б��ʱ�� */
	virtual void FetchOrgs(const std::string& strUpdateTime)=0;

	/****************************************************************
	 * ��Ϣ����
	 ****************************************************************/

	/* ���ͼ�ʱ��Ϣ */
	virtual void SendOnlineMessage(const std::string& strNodeID,XMSG& xmsg)=0;

	/* ����������Ϣ */
	virtual void SendOfflineMessage(const std::string& strToID,XMSG& xmsg)=0;

	/* ���ͻ�����Ϣ,ָ�������Ͳ��ŷ���,���strDepartIDΪ������������г�Ա���� */
	virtual void SendOrgMessage(const std::string& strOrgID,const std::string& strDepartID,XMSG& xmsg)=0;

	/* ��ȡ������Ϣ */
	virtual void GetOfflineMessage(void)=0;

	/* ��ȡϵͳ��Ϣ */
	virtual void GetSystemMessage(void)=0;

	/****************************************************************
	 * �Զ��庯��
	 ****************************************************************/

    /* �����û����ݵ�ָ���Է� */
	virtual void SendUserData(const std::string& strNodeID,KCmdPacket& packet)=0;

	/****************************************************************
	 * �칫�ຯ��
	 ****************************************************************/

	/* ��ȡURL�б� */
	virtual void FetchURLs()=0;

	/****************************************************************
	 * ��ͼ�ຯ��
	 ****************************************************************/

	/* ���ӵ�ͼ��Ϣ */
	virtual void AddMapInfo(const std::string& strGroupID,const std::string& strMapMD5)=0;

	/* ���µ�ͼ��Ϣ */
	virtual void UpdateMapInfo(const std::string& strGroupID,const std::string& strMapMD5)=0;

	/* ɾ����ͼ��Ϣ */
	virtual void DeleteMapInfo(const std::string& strGroupID)=0;

	/* �������ڵ�ID�õ���Ӧ�ĵ�ͼID���ڵ�ͼ�Ƚ� */
	virtual void GetMapInfo(const std::string& strGroupID)=0;

	/****************************************************************
	 * �ȵ��ຯ��
	 ****************************************************************/

	/* �����ȵ���Ϣ
	   strGroupID: ����ID
	   strTreeID:  �����������ͨ��ID */
	virtual void AddBzInfo(const std::string& strGroupID,const std::string& strTreeID,const std::string& strBzID)=0;

	/* ɾ�����ڵ�Ĺ�������Ϣ
	   strGroupID ������ID
	   strTreeID  �������������ͨ��ID ��strTreeID  Ϊ��ʱ��ɾ�������ȵ���Ϣ	*/
	virtual void DeleteBzInfo(const std::string& strGroupID,const std::string& strTreeID)=0;

	/* ��������ID�õ��������ȵ�ID */
	virtual void GetBzInfo(const std::string& strGroupID)=0; 

	/****************************************************************
	 * ��ط�������
	 ****************************************************************/
	virtual void GetMonGroupInfo(const std::string strUpdateTime)=0;
	virtual void DEV_AddMyGroup(std::string& strTmpGrpName)=0;
	virtual void DEV_DelMyGroup(const std::string& strTmpGrpID, std::string& strTmpGrpName)=0;
	virtual void DEV_RenameMyGroup(const std::string& strTmpGrpID, std::string& strTmpGrpName)=0;
	virtual void DEV_AddMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid)=0;
	virtual void DEV_DelMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid)=0;
	virtual void DEV_GetMyGroup(void)=0;
	virtual void DEV_GetMyGroupMember(const std::string& strTmpGrpID)=0;
};

//=======================================================================================
// IMSģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KIMSSessionEvent
{
public:
	KIMSSessionEvent(void){};
	virtual ~KIMSSessionEvent(void){};

public:
	/* ��¼
	 * nErrCode: ��¼���ش�����,0=��¼�ɹ�,
	 * strModuleString: ϵͳģ���ַ���: IMS+MMS+MON+SMS or IMS+MMS  */
	virtual void OnLogin(int nErrCode,const std::string& strModuleString)=0;

	/* ע�� 
	 * nErrCode:ע�����ش�����,0=����ע�� */
	virtual void OnLogout(int nErrCode)=0;

	/* �յ�ע���û����� */
	virtual void OnAllUserCount(unsigned long ulCount)=0;

	/* �յ������û����� */
	virtual void OnOnlineUserCount(unsigned long ulCount)=0;

	/* �յ��ҵ������¼� */
	virtual void OnMyName(const std::string& strUserName)=0;

	/* �յ��ҵ���Ϣ�¼� */
	virtual void OnMyInfo(const IMS_CONTACT_ITEM& ui)=0;

	/* �յ�Ȩ���� */
	virtual void OnMyPriv(unsigned long ulPrivCode)=0;

	/* �յ�ͷ���¼� */
	virtual void OnImage(const std::string& strUserID,const std::string& strImgType,const std::string& strImgData)=0;

	/* �յ�״̬�¼�,bFirst��ʾ�Ƿ��һ��״̬���� */
	virtual void OnStatus(const std::string& strUserID,const std::string& strStatus,bool bFirst,const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,unsigned long ulMediaId)=0;
    //add by wanggj
    virtual void CallbackCreateInterimMeeting(const std::string& strHostID, unsigned long ulRoomID , unsigned int uiRoomType) = 0;
    
    virtual void CallbackDestructionInterimMeeting(const std::string& strHostID, unsigned long ulRoomID, std::vector<std::string>& vQuitUser)=0;
    
    virtual void CallbackQuitTemporaryMeeting(const std::string& strUserID,  unsigned long ulRoomID)=0;
    
    virtual void CallbackJoinTemporaryMeeting(const std::string& strUserID,  unsigned long ulRoomID)=0;
    
    virtual void CallbackInitializationTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount, unsigned int uiVideoType, unsigned int uiAudioType) = 0;
    
    virtual void CallbackMeetingUserInfo(const std::string& strHostID, unsigned long ulRoomID , unsigned int uiRoomType, std::vector<std::string>& vQuitUser) = 0;
    
    virtual void CallbackOpenPeerUserVideo(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserVideoID, unsigned long ulScreeCount)=0;
    
    virtual void CallbackClosePeerUserVideo(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserVideoID)=0;
    
    virtual void CallbackOpenPeerUserAudio(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserAudioID)=0;
    
    virtual void CallbackClosePeerUserAudio(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserAudioID)=0;
    
    virtual void CallbackSetMeetingType( unsigned long ulRoomID,unsigned int uiType)=0;
    
    virtual void CallbackOnScreenControl(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount)=0;
    virtual void CallbackInviteUser(const std::string& strUserID, unsigned long ulRoomID)=0;
    virtual void CallbackReplyInviteUser(const std::string& strUserID, unsigned long ulRoomID,bool bIsAgree)=0;
    
    virtual void CallbackForTheFloor(const std::string& strUserID, unsigned long ulRoomID, const std::string& strHostID)=0;
	virtual void CallbackPleaseOutTemporaryMeeting(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID)=0;
	virtual void CallbackPassPrivileges(const std::string& strHostID, unsigned long ulRoomID)=0;
	virtual void CallbackUserSnedMsg(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, std::string& ulUserMsg)=0;

	/****************************************************************
	 * ��ϵ�������¼�
	 ****************************************************************/

	/* �յ���ϵ������ */
	virtual void OnGroupItem(const std::string& strGroup,unsigned int nIndex)=0;

	/* �յ���ϵ�������б���� */
	virtual void OnGroupItemEnd(void)=0;

	/* �յ�������ϵ�����¼�  */
	virtual void OnGroupInsert(const std::string& strGroup,unsigned int nIndex)=0;

	/* �յ���ϵ��������¼� */
	virtual void OnGroupUpdateName(const std::string& strOldGroup,const std::string& strNewGroup)=0;

	/* �յ���ϵ��������������¼� */
	virtual void OnGroupUpdateIndex(const std::string& strGroup,unsigned int nIndex)=0;

	/* �յ�ɾ����ϵ�����¼� */
	virtual void OnGroupDelete(const std::string& strGroup)=0;

	/****************************************************************
	 * ��ϵ�����¼�
	 ****************************************************************/

	/* �յ���ϵ���� */
	virtual void OnFriendItem(const IMS_CONTACT_ITEM& item)=0;

	/* �յ���ϵ�����б�����¼� */
	virtual void OnFriendItemEnd(void)=0;

	/* �յ���ϵ����Ϣ�¼� */
	virtual void OnFriendInfo(const std::string& strFriendID)=0;

	/* �յ���ϵ����������¼� */
	virtual void OnFriendApply(const std::string& strFriendID, const std::string& strUserGroup)=0;

	/* �յ������ϵ�˴����¼� */
	virtual void OnFriendApplyError(const std::string& strFriendID)=0;

	/* �յ���ϵ�˽��������¼� */
	virtual void OnFriendAdmit(const std::string& strFriendID)=0;

	/* �յ���ϵ�˸������¼� */
	virtual void OnFriendUpdateGroup(const std::string& strFriendID,const std::string& strGroup)=0;

	/* �յ�ɾ����ϵ���¼� */
	virtual void OnFriendDelete(const std::string& strUserGroup, const std::string& strFriendID)=0;

	/* �յ�������ϵ�˽���¼� */
	virtual void OnFriendSearch(const IMS_CONTACT_ITEM& item)=0;

	/****************************************************************
	 * �������¼�
	 ****************************************************************/

	/* �յ������б�ʼ�� */
	virtual void OnOrgListStart(void)=0;

	/* �յ������� */
	virtual void OnOrgItem(const std::string& strOrgID,const std::string& strOrgName)=0;

	/* �յ���������� */
	virtual void OnOrgItemEnd(void)=0;

	/* �յ����������� */
	virtual void OnOrgDepartItem(const std::string& strOrgID,const std::string& strDepartID,const std::string& strDepartName,int nLevelID,const std::string& strUpgradeID,int nOrderID)=0;

	/* �յ�������������� */
	virtual void OnOrgDepartItemEnd(void)=0;

	/* �յ����������û��� */
	virtual void OnOrgDepartUserItem(const std::string& strOrgID,const std::string& strDepartID,const IMS_CONTACT_ITEM& item,int nOrderID)=0;
    
    virtual void DeleteUser(const std::string& strUserID)=0;

	/* �յ����������û������ */
	virtual void OnOrgDepartUserItemEnd(void)=0;

	/* �յ�����/����/�û�ɾ���� */
	virtual void OnOrgDeleteItem(const std::string& strOrgID,const std::string& strDepartID,const std::string& strUserID)=0;

	/* �յ�����/����/�û�ɾ������� */
	virtual void OnOrgDeleteItemEnd(void)=0;

	/* �յ��ṹ�б���� */
	virtual void OnOrgListEnd(const std::string& strUpdateTime)=0;

	/****************************************************************
	 * ��Ϣ���¼�
	 ****************************************************************/

	/* �յ�������Ϣ�¼� */
	virtual void OnOnlineMessage(const std::string& strUserID,const std::string& strUserName,const std::string& strNodeID,const XMSG& xmsg)=0;

	/* �յ�������Ϣ�¼� */
	virtual void OnOfflineMessage(const std::string& strUserID,const XMSG& xmsg)=0;

	/* �յ�ϵͳ��Ϣ�¼� */
	virtual void OnSystemMessage(const std::string& strAdminName,const XMSG& xmsg)=0;

	/* �յ�ϵͳ��Ϣ�����¼� */
	virtual void OnSystemMessageEnd(void)=0;

	/* �յ�������Ϣ�¼� */
	virtual void OnOrgMessage(const std::string& strOrgID,const std::string& strOrgName,
		                      const std::string& strDepartID,const std::string& strDepartName,
							  const std::string& strUserID,const std::string& strUserName,const XMSG& xmsg)=0;

	/****************************************************************
	 * �Զ����¼�
	 ****************************************************************/

	/* �յ��û��Զ��������¼� */
	virtual void OnUserData(KCmdUserDataPacket& packet)=0;

	/****************************************************************
	 * �������б��¼�
	 ****************************************************************/

	/* ����WEB��������ַ�Ͷ˿� */
	virtual void OnWEBServer(const std::string& strHost,unsigned short usPort)=0;

	/* ����PBX��������ַ,�ַ�����ʽӦ�ú�WEB��ӵ����ݿ��еĸ�ʽһ�� */
	virtual void OnPBXServer(const std::string& strHost)=0;

	/* �յ�FAX���� */
	virtual void OnFAXServer(const std::string& strHost,unsigned short usPort)=0;

	/****************************************************************
	 * �칫���¼�
	 ****************************************************************/

	/* �յ�URL�б��� */
	virtual void OnGetURLItem(const std::string& strName,const std::string& strURL)=0;

	/* �յ�URL�б������ */
	virtual void OnGetURLListEnd()=0;

	/* �յ��´������ */
	virtual void OnGetFAXCount(unsigned int nCount)=0;	

	/****************************************************************
	 * ��ͼ���¼�
	 ****************************************************************/

	/* �յ��ص���ͼ��Ϣ
	   strGroupID������ID
	   strMapMD5 ����ͼMD5ֵ	*/
	virtual void OnMapInfo(const std::string& strGroupID, const std::string& strMapMD5)=0;

	/****************************************************************
	 * �ȵ����¼�
	 ****************************************************************/

	/* �������ڵ�ID�õ��������ȵ�ID
	   strGroupID������ID
	   listMAPBZ �������������ȵ�list */
	virtual void OnBzIDInfo(const std::string& strGroupID, MAP_BZ_LST listMAPBZ)=0;

	/****************************************************************
	 * ��ط����¼�
	 ****************************************************************/

	virtual void OnMonUpdateTime(const std::string& strUpdateTime)=0;
	virtual void OnGroupInfo(const MONGROUP& item)=0;
	virtual void OnChannelInfo(const MONCHANNEL& item)=0;
	virtual void OnGetGroupInfoEnd()=0;
	virtual void OnChannelInfoEnd()=0;
	virtual void OnMonAlert(const std::string& strChannelID,unsigned short usType,unsigned short usSubtype)=0;			

	/* ���Ӽ���豸�������ص� */
	virtual void OnDEVAddMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName)=0;
	virtual void OnDEVDelMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName)=0;
	virtual void OnDEVRenameMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName)=0;
	virtual void OnDEVAddMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid)=0;
	virtual void OnDEVDelMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid)=0;
	virtual void OnDEVGetMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName)=0;
	virtual void OnDEVGetMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid)=0;

	/* �յ�����豸���� */
	virtual void OnUpdateDevName(const std::string& strDevID,const std::string& strName, unsigned long ulGroupID)=0;

	/* �յ����ͨ������ */
	virtual void OnUpdateChannelName(const std::string& strChannelID,const std::string& strName,unsigned long ulGroupID)=0;
};

//=======================================================================================
// IMSʵ��
//=======================================================================================
AFX_EXT_CLASS bool IMSSessionAddEvent(KIMSSessionEvent* pIMSSessionEvent);
AFX_EXT_CLASS void IMSSessionRemoveEvent(KIMSSessionEvent* pIMSSessionEvent);
AFX_EXT_CLASS void IMSSessionRelease(void);
AFX_EXT_CLASS KIMSSession& GetIMSSession(void);

#include "KMMSDefine.h"

class AFX_EXT_CLASS KMMSSessionEvent;
//=======================================================================================
// MMSģ����
//=======================================================================================
class AFX_EXT_CLASS KMMSSession
{
public:
	KMMSSession(void){};
	virtual ~KMMSSession(void){};

	/* SYS����ģ����û�ȡ�û�NODEID */
	virtual int OnGetUserNodeID(const std::string& strUserID,std::string& strNodeID)=0;
	virtual void OnDispatchCmd(KCmdPacket& t)=0;
	virtual void ClearLocalData(void)=0;

	virtual void SetUserID(const std::string& strUserID)=0;
	virtual std::string GetUserID(void)=0;
	virtual void SetUserName(const std::string& strUserName)=0;
	virtual std::string GetUserName(void)=0;

	/****************************************************************
	 * ��ȡ���ػ������б���
	 ****************************************************************/
	virtual MMS_ROOM_LST& GetLocalRoomList(void)=0;
	virtual MMS_GROUP_LST& GetLocalGroupList(void)=0;
	virtual MMS_MEMBER_LST& GetLocalMemberList(void)=0;

	virtual PMMS_ROOM GetLocalRoomItem(const std::string& strDomain,const std::string& strRoomID)=0;
	virtual PMMS_GROUP GetLocalGroupItem(const std::string& strDomain,const std::string& strRoomID,const std::string& strGroupID)=0;
	virtual PMMS_MEMBER_EX GetLocalMemberItem(const std::string& strDomain,const std::string& strRoomID,const std::string& strMemberID)=0;

	/* ���ͳ�ʼ��¼���� */
	virtual void SendLoginCommand(void)=0;

	/****************************************************************
	 * �������б���
	 ****************************************************************/

	/* ��û����б�
	 * bAllRoomType=true: ��ȡ���л�����/��/��Ա
	 * bAllRoomType=false:ֻȡ������ͱ�׼������+��+��Ա+�߼������� */
	virtual void GetRoomList(bool bAllRoomType=false)=0;

	/****************************************************************
	 * ��ʱ�����ҷ���
	 ****************************************************************/

	/* �����ʱ������
	 * strGroupName: ��ʱ���������� */
	virtual void InsertTempGroup(const std::string& strGroupName)=0;

	/* �޸���ʱ����������
	 * ulGroupID: ��ʱ������ID
	 * strGroupName: ��ʱ���������� */
	virtual void UpdateTempGroupName(unsigned ulGroupID,const std::string& strGroupName)=0;

	/* ɾ����ʱ������
	 * ulGroupID: ��ʱ������ID */
	virtual void DeleteTempGroup(unsigned ulGroupID)=0;

	/* �����ʱ�����Ա */
	virtual void InsertTempMember(unsigned ulGroupID,const std::string& strMemberID,const std::string& strMemberName)=0;

	/* ɾ����ʱ�����Ա */
	virtual void DeleteTempMember(unsigned ulGroupID,const std::string& strMemberID)=0;

	/****************************************************************
	 * ���鹦�ܺ���
	 ****************************************************************/

	/* ��¼������
	 * strDomain:			������������
	 * strRoomID:			������ID
	 * strPassword:			��ҪMD5����
	 * strInviteeGroupID:	����������ID
	 * bPresider:			���Ϊ��������,����Ҫȷ�����������Ƿ�Ϊ������
	 * strUpdateTime:		������Ϣ����ʱ��,�͵��������ж��Ƿ�һ��,�����һ�·����������س�Ա�б�
	 * strTermType:			�ն����� */
	virtual void Login(const std::string& strDomain,const std::string& strRoomID,const std::string& strPassword,
		               const std::string& strMemberID,const std::string& strMemberName,
					   const std::string& strInviteeGroupID,bool bPresider=false,
					   const std::string& strUpdateTime="",const std::string& strTermType="",bool bHasVideo=false)=0;

	/* �˳������� */
	virtual void Logout(void)=0;

	/* �����Ա���
	 * strNodeID:			�������ߵ�NODEID
	 * strPassword:			��������
	 * bPresider:			�Ƿ�����Ϊ������,true=�����������,false=���������� */
	virtual void Invite(const std::string& strInviteeNodeID,const std::string& strPassword,bool bPresider)=0;

	/* �ܾ�������� */
	virtual void Reject(const std::string& strDomain,const std::string& strRoomID,const std::string& strInviterNodeID)=0;

	/* �߳����� */
	virtual void Kickout(const std::string& strMemberID)=0;

	/* ���ͻ�����Ϣ */
	virtual void SendMessage(const std::string& strHead,const std::string& strBody,const std::string& strFormat)=0;

	/* �����û��Զ�������(�����͵����鵱�еĳ�Ա)
	 * ucObject����: 
	 *   0=���������������(�������Լ�)��������
	 *   1=��������г�Ա��������
	 *   ��0��1�����������=��packet�е�toid�������� */
	virtual void SendUserData(KCmdUserDataPacket& packet,unsigned char ucObject=0)=0;

	/****************************************************************
	 * �����������
	 ****************************************************************/

	/* ��������鲢�㲥 */
	virtual void InviteInRoomBroadcast(const std::string& strMemberName,const std::string& strMeetingName,const std::string& strMeetingPass)=0;

	/* ���û������ID */
	virtual void SetActiveGroupID(const std::string& strActiveGroupID)=0;

	/* ���û����鵱ǰ��Ļ�� */
	virtual void SetCurrentScreenID(const std::string& strGroupID,int nCurScrID,int nPrevTM)=0;

	/* ��ȡ��Աͨ�����б�(VID/AUD/DOC) */
	virtual void GetCardList(void)=0;

	/* ����ͨ������,���㲥�������� */
	virtual void SetCardItem(int nCardIndex,const std::string& strCardName,MMS_CHANNEL_LST& lstChannel)=0;

	/* ������Ƶͨ������,���㲥�������� */
	virtual void SetCardAudioItem(int nCardIndex,unsigned long ulAudioChannelID)=0;

	/* ����ͨ��������(ֻ�����ñ����û���) */
	virtual void SetCardName(int nCardIndex,const std::string& strCardName)=0;

	/* �㲥��Ա��(nChannelTypeȡֵ:MMS_CHLTYPE_VID / MMS_CHLTYPE_SVD / MMS_CHLTYPE_AUD / MMS_CHLTYPE_CHT / MMS_CHLTYPE_WHB / MMS_CHLTYPE_DTS) */
	virtual void BroadcastCard(int nScreenID,int nWindowID,const std::string& strMemberID,int nCardIndex,int nChannelType,const std::string& strTag)=0;

	/* �رչ㲥��Ա��(nChannelTypeȡֵ:MMS_CHLTYPE_VID / MMS_CHLTYPE_SVD / MMS_CHLTYPE_AUD / MMS_CHLTYPE_CHT / MMS_CHLTYPE_WHB / MMS_CHLTYPE_DTS) */
	virtual void CloseBroadcastCard(const std::string& strMemberID,int nCardIndex,int nChannelType)=0;

	/* �л����� */
	virtual void DragWindow(int nFromScreenID,int nFromWindowID,int nToScreenID,int nToWindowID)=0;

	/* ���û���ģ�� */
	virtual bool SetTemplet(int nScreenID,int nTemType,int nTemID,bool bTemShow,int nWinNumber)=0;

	/* ���ø�������λ��
	 * x = ���ر��� * 100
	 * y = ���ر��� * 100
	 * cx= ��ȱ��� * 100
	 * cy= �߶ȱ��� * 100 */
	virtual bool SetFloatWindow(int nScreenID,int nX,int nY,int nCX,int nCY)=0;	

	/* ���ø��˻����Ȩ�� */
	virtual void SetRight(int usRightType,unsigned char ucRight,const std::string& strMemberID="")=0;

	/* ��ȡ��ͬ����Ϣ */
	virtual void GetGroupSynInfo(const std::string& strGroupID)=0;

	/* ����strGroupID���ٿ�������� */
	virtual void AllowSubMeet(const std::string& strGroupID,const std::string& strMemberID)=0;

	/* Ҫ��strGroupID�鼰������������strGroupID��ͬ�� */
	virtual void Sync(const std::string& strGroupID,const std::string& strMemberID)=0;
	
	/* ������ʱ������ */
	virtual void SetTempPresider(std::string& strMemberID,bool bSet)=0;

	/* �����ɾ�������� */
	virtual void SetProlocutor(const std::string& strMemberID="")=0;

	/* �㲥��ȡ���㲥������ */
	virtual void EnableProlocutor(const std::string& strMemberID,bool bEnable)=0;

	/* �����ɾ�������� */
	virtual void SetQuestioner(const std::string& strMemberID="")=0;

	/* ���ӻ�ȡ������������*/
	virtual void EnableQuestioner(const std::string& strMemberID,bool bEnable)=0; 

	/* �������� */
	virtual void SetAnnexData(int usAnnexType,const std::string& strData,const std::string& strFormat)=0;

	/* ���� */
	virtual void EnableAnnex(int usAnnexType,bool bEnable=true)=0;

	/****************************************************************
	 * ����ͶƱ����
	 ****************************************************************/

	/* ֻ��λ��root��������˲ſ��Է���ͶƱ,��������в��ܷ���
	 * ԤͶƱ
	 * strMemberID:	����ͶƱ�������� */
	virtual void PrepVote(const std::string& strMemberID)=0;

	/* ����ͶƱ 
	voteid:		ͶƱ��ʶID
	topic:		ͶƱ����
	type:		ͶƱ���ͣ������򲻼�����"public"��"anonymous"��
	desc:		����������Ϣ */
	virtual void StartVote(const std::string& strVoteID,const std::string& strTopic,bool bType,unsigned long ulTime,bool bMulti,MMS_VOTE_LST& strItems)=0;

	/* ����ͶƱ 
	endtype:	ͶƱ������ʽ���ֶ����Զ���"hand" �� "auto"��*/
	virtual void StopVote(const std::string& strVoteID,const std::string& strEndType)=0;

	/* ͶƱ
	result:		ͬ�⡢���Ի���Ȩ��"agree"��"disagree"��"abstain"��
	strMemberID:	ͶƱ�ߵ�ID�����ڲ�����ͶƱ��Ϊ��("")
	desc:		��ע */
	virtual void Vote(const std::string& strMemberID,const std::string& strVoteID,MMS_VOTE_LST& strItems)=0;

	/****************************************************************
	 * ������ֺ���
	 ****************************************************************/

	/* ��ʼ����:�����˵��� */
	virtual void StartHandle(unsigned long ulTime)=0;

	/* ����:�����˵��� */
	virtual void Handle(unsigned long ulID,bool bAgree)=0;

	/* ֹͣ����:�����˵��� */
	virtual void StopHandle(unsigned long ulID)=0;

	/****************************************************************
	 * �����������
	 ****************************************************************/
	virtual void Calling(unsigned int usTime)=0;
	virtual void CloseCalling()=0;
	virtual void CallingInConference(const std::string& strFile)=0;

	/****************************************************************
	 * �����غ���
	 ****************************************************************/

	//���ͼ������
	virtual void MonUserData(KCmdUserDataPacket& packet)=0;

	//���P2P
	virtual void MonP2P(const std::string strChannelID, KCmdUserDataPacket& packet)=0;

	/****************************************************************
	 * ������
	 ****************************************************************/
	virtual void Loss(MMS_LOSS& loss, bool bStart=true)=0;

	/****************************************************************
	 * ����ǽ����
	 ****************************************************************/
	virtual void InsertTVMonitor(unsigned short usIndex,const std::string& strData)=0;
	virtual void UpdateTVMonitor(unsigned short usIndex,const std::string& strData)=0;
	virtual void DeleteTVMonitor(unsigned short usIndex)=0;
	virtual void InsertTVMatrix(unsigned short usIndex,const std::string& strData)=0;
	virtual void UpdateTVMatrix(unsigned short usIndex,const std::string& strData)=0;
	virtual void DeleteTVMatrix(unsigned short usIndex)=0;
	virtual void GetTVList(void)=0;
};

//=======================================================================================
// MMSģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KMMSSessionEvent
{
public:
	KMMSSessionEvent(void){};
	virtual ~KMMSSessionEvent(void){};

public:
	/****************************************************************
	 * ��ʱ�����¼�
	 ****************************************************************/

	virtual void OnTempGroupItem(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strGroupName,bool bDefault)=0;
	virtual void OnTempGroupUpdateName(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strGroupName)=0;
	virtual void OnTempGroupDelete(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID)=0;
	virtual void OnTempMemberItem(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strMemberID,const std::string& strMemberName)=0;
	virtual void OnTempMemberDelete(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strMemberID)=0;

	/****************************************************************
	 * �����б��¼�
	 ****************************************************************/
	virtual void OnRoomListEnd(const std::string& strDomain)=0;

	/****************************************************************
	 * �����¼�
	 ****************************************************************/

	/* �յ���¼�������¼�
	 * errcode���ص�¼���ֵ
	 * 0: �ɹ���¼������
	 * 1: ������֤ʧ��
	 * 2: �û��Ѿ��������
	 * 3: �����Ѿ�������������
	 * 4: ����û���ʵ���MCU������
	 * 5: �����������뿪����
	 * 6: ��¼�����Ͳ���ȷ
	 * 7: �����Ѿ�����
	 * 8: �������Ͳ���ȷ
	 *99: �����ڲ��������� */
	virtual void OnLogin(unsigned int nErrCode,const std::string& strDomainID,const std::string& strRoomID,const std::string& strRoomName,unsigned short usRoomType,
		const std::string& strRootGroupID,const std::string& strGroupID,const std::string& strActiveGroupID,
        const std::string& strMemberID,unsigned short usMemberType,bool bAllowVideo)=0;

	/* �յ��˳��������¼�
	 * errcode���ص�¼���ֵ
	 * 0: ��ʾ�����˳�������
	 * 1: ��ʾ�������˳�������
	 * 2: ��ʾ���߳�������
	 * 3: �����Ա�ʺ��ڸ÷������ϲ����ڻ�÷�����û�м��ػ���ģ�� */
	virtual void OnLogout(unsigned int nErrCode)=0;

	/* �յ��������� */
	virtual void OnRoomGroupItem(MMS_GROUP_EX& item)=0;

	/* �յ������������ */
	virtual void OnRoomGroupListEnd(const std::string& strUpdateTime)=0;

	/* �յ������Ա�� */
	virtual void OnRoomMemberItem(MMS_MEMBER_EX& item)=0;

	/* �յ������Ա����� */
	virtual void OnRoomMemberListEnd(void)=0;

	/* �յ�����������׼��,�յ�����Ϣ��ʾ�����¼�ɹ����յ�����ʵʱ���� */
	virtual void OnReady(void)=0;

	/* �յ���Ա״̬ */
	virtual void OnStatus(const std::string& strGroupID,const std::string& strMemberID,unsigned short usMemberType,
		                  const std::string& strSvrID,const std::string& strSvrAddr,unsigned short usSvrPort,const std::string& strSvrType,
						  const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,
						  const std::string& strTermType,unsigned char ucStatus)=0;

	/* �յ��������� */
	virtual void OnInvite(const std::string& strRoomDomain,const std::string& strRoomID,const std::string& strGroupID,
		                  const std::string& strRoomName,const std::string& strInviterNodeID,const std::string& strInviterID,
						  const std::string& strInviterName,const std::string& strPassword,bool bPresider)=0;

	/* �յ��ܾ����� */
	virtual void OnReject(const std::string& strDomain,const std::string& strRoomID,const std::string& strInviteeID,const std::string& strInviteeName)=0;

	/* �յ�������Ϣ */
	virtual void OnMessage(const std::string& strMemberID,const std::string& strHead,const std::string& strBody,const std::string& strFormat)=0;

	/* �յ��û���������
     * ucObject����: 
	 *   0=�յ��������˷��͵�����
	 *   1=�յ��㲥����
	 *   ��0��1��=�յ��㵽������ */
	virtual void OnUserData(KCmdUserDataPacket& packet,unsigned char ucObject)=0;

	/* ���ü����� */
	virtual void OnSetActiveGroupID(const std::string& strGroupID)=0;

	/* ���õ�ǰ��Ļ�� */
	virtual void OnSetCurrentScreenID(const std::string& strOwnerID,const std::string& strGroupID,int nCurScrID,int nPrevTM)=0;

	/* �յ�ͨ���� */
	virtual void OnCardItem(const std::string& strGroupID,const std::string& strMemberID,int nCardIndex,const std::string& strCardName,
		                    unsigned int nChannelType,unsigned long ulChannnelID,
							const std::string& strMCUID,const std::string& strMCUAddr,unsigned short usMCUPort,
							const std::string& strDevInfo)=0;

	/* ͨ�����б���� */
	virtual void OnCardListEnd(void)=0;

	/* �յ���Ƶͨ���� */
	virtual void OnCardAudioItem(const std::string& strGroupID,const std::string& strMemberID,int nCardIndex,unsigned long ulAudioID)=0;

	/* ����ͨ������ */
	virtual void OnSetCardName(const std::string& strGroupID,const std::string& strMemberID,int nCardIndex,const std::string& strCardName)=0;

	/* ��ͬ����Ϣ��ȡ��� */
	virtual void OnGroupSynInfoEnd(void)=0;

	/* ���ø��˻����Ȩ�� */
	virtual void OnSetRight(int usRightType,unsigned char ucRight,const std::string& strMemberID)=0;

	/* �����ɾ�������� */
	virtual void OnSetProlocutor(const std::string& strMemberID,bool bRequest)=0;

	/* �㲥��ȡ���㲥������ */
	virtual void OnEnableProlocutor(const std::string& strMemberID,bool bEnable)=0;

	/* �����ɾ�������� */
	virtual void OnSetQuestioner(const std::string& strMemberID,bool bRequest)=0;

	/* ���ӻ�ȡ������������ */
	virtual void OnEnableQuestioner(const std::string& strMemberID,bool bEnable)=0;

	/* ���ù������� */
	virtual void OnSetAnnexData(int usAnnexType,const std::string& strData,const std::string& strFormat)=0;

	/* ���ù������� */
	virtual void OnEnableAnnex(int usAnnexType,bool bEnable)=0;

	/* ������� */
	virtual void OnUnlocked(void)=0;

	/* �㲥�� */
	virtual void OnBroadcastCard(const std::string& strOwnerID,const std::string& strGroupID,int nScreenID,int nWindowID,
		                         const std::string& strMemberID,int nCardIndex,int nChannelType,unsigned long ulChannelID,
								 const std::string& strMCUID,const std::string& strMCUAddr,unsigned short usMCUPort,
                                 const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,
								 const std::string& strTag)=0;

	/* �رչ㲥�� */
	virtual void OnCloseBroadcastCard(const std::string& strOwnerID,const std::string& strGroupID,const std::string& strMemberID,
		                              int nCardIndex,int nChannelType)=0;

	/* �϶����� */
	virtual void OnDragWindow(const std::string& strOwnerID,int nFromScreenID,int nFromWindowID,int nToScreenID,int nToWindowID)=0;

	/* �ı�ģ�� */
	virtual void OnSetTemplet(const std::string& strOwnerID,int nScreenID,int nTemType,int nTemID,bool bTemShow,int nWinNumber)=0;

	/* �������� */
	virtual void OnSetFloatWindow(const std::string& strOwnerID,int nScreenID,int nX,int nY,int nCX,int nCY)=0;	

	/* ���뵽�����Ҳ��㲥 */
	virtual void OnInviteInRoomBroadcast(const std::string& strRoomDomain,const std::string& strRoomID,const std::string& strGroupID,
		                                 const std::string& strMemberID,const std::string& strMeetingName,const std::string& strMeetingPass,
										 const std::string& strMemberName)=0;

	/* ������ʱ������
	 * bSet: true=����;false=ȡ�� */
	virtual void OnSetTempPresider(std::string& strMemberID,bool bSet)=0;

	/* ͶƱ */
	virtual void OnPrepVote(const std::string& strMemberID,const std::string& strVoteID,bool bAllow)=0;
	virtual void OnStartVote(const std::string& strVoteID,const std::string& strTopic,bool bType,unsigned long ulTime,bool bMulti,MMS_VOTE_LST& strItems)=0;
	virtual void OnStopVote(const std::string& strVoteID,const std::string& strEndType,int nSum,int nAnswer,MMS_VOTE_LST& strItems)=0;

	/* ���� */
	virtual void OnStartHandle(unsigned long ulID,unsigned long ulTime)=0;
	virtual void OnStopHandle(unsigned long ulID,unsigned short usTotal,unsigned short usCount)=0;

	virtual void OnAllowSubMeet(const std::string& strGroupID)=0;
	virtual void OnSync(const std::string& strGroupID)=0;

	/* ���� */
	virtual void OnCalling(const std::string& strMemberID,unsigned int usTime)=0;
	virtual void OnCloseCalling(const std::string& strMemberID)=0;

	/* ���ؼ������ */
	virtual void OnMonUserData(KCmdUserDataPacket& packet)=0;

	/* ���ؼ��P2P */
	virtual void OnMonP2PData(const std::string& strDevID,KCmdUserDataPacket& packet)=0;
    
	/* ���� */
	virtual void OnLoss(MMS_LOSS& loss, unsigned short usErrorCode)=0;

	/* ����ǽ */
	virtual void OnInsertTVMonitor(unsigned short usIndex,unsigned short usErrorCode)=0;
	virtual void OnUpdateTVMonitor(unsigned short usIndex,unsigned short usErrorCode)=0;

	/* ����ǽ������ */
	virtual void OnInsertTVMatrix(unsigned short usIndex,unsigned short usErrorCode)=0;
	virtual void OnUpdateTVMatrix(unsigned short usIndex,unsigned short usErrorCode)=0;
	virtual void OnTVServerItem(const std::string& strTV,const std::string& strTVName,const std::string& strStatus)=0;
	virtual void OnTVMonitorItem(unsigned short usIndex,const std::string& strData)=0;
	virtual void OnTVMatrixItem(unsigned short usIndex,const std::string& strData)=0;
	virtual void OnTVListEnd(void)=0;
};

//=======================================================================================
// MMSʵ��
//=======================================================================================
AFX_EXT_CLASS bool MMSSessionAddEvent(KMMSSessionEvent* pMMSSessionEvent);
AFX_EXT_CLASS void MMSSessionRemoveEvent(KMMSSessionEvent* pMMSSessionEvent);
AFX_EXT_CLASS void MMSSessionRelease(void);
AFX_EXT_CLASS KMMSSession& GetMMSSession(void);


#include "KMONDefine.h"

class AFX_EXT_CLASS KMONSessionEvent;
//=======================================================================================
// MMSģ����
//=======================================================================================
class AFX_EXT_CLASS KMONSession
{
public:
	KMONSession(void){};
	virtual ~KMONSession(void){};

	virtual void OnDispatchCmd(KCmdPacket& t)=0;
	virtual void ClearLocalData(void)=0;

	/* ���ͳ�ʼ��¼���� */
	virtual void SendLoginCommand(void)=0;

	/* ��¼
	 * usClientType(�ͻ�������): "SYS" "MON" "OCX" */
	virtual void Login(const std::string& strUserID,const std::string& strPassword,const std::string& strClientType,const std::string& strName,const std::string& strSerialno,const std::string& strTermType="")=0;

	/* ע�� */
	virtual void Logout(void)=0;

	/* ���Ͷ��� */
	virtual void SendSMS(const std::string& strMobilNumber,const std::string& strMessage)=0;

	/* �豸���� */
	virtual void DeviceOnline(const std::string &strDevType, const std::string &strDevID,const std::string &strPwd,const std::string &strMask,const std::string &strName)=0;

	/* �豸���� */
	virtual void DeviceOffline(const std::string &strDevID)=0;

	/* ��֤�豸���ʺź����кŵİ󶨹�ϵ
	 * strDevID: Ϊ�����豸�ʺ�
	 * strNewDevID: Ϊ�µ��豸�ʺ�
	 * strSerialNo: Ϊ�豸�����к� */
	virtual void DeviceCheck(const std::string &strDevID,const std::string &strNewDevID,const std::string &strSerialNo)=0;

	/* �޸��豸���� */
	virtual void UpdateDeviceName(const std::string &strDevID,const std::string &strName)=0;

	/* ����DVRͨ��������Ϣ */
	virtual void ChannelOnline(const DEV_CHANNEL_ITEM &channelItem)=0;

	/* ����DVRͨ��ע������ nCHNum=-1 ����ͨ��ע�� */
	virtual void ChannelOffline(const std::string &strDevID,unsigned short nCHNum)=0; 

	/* �޸�ͨ������ */
	virtual void UpdateChannelName(const std::string &strChannelID,const std::string &strName)=0;
	
	/* ��ȡ������Ϣ */
	virtual void GetDeviceBasicInfo(const std::string &strDevID)=0;

	/* ����Խ� */
	virtual void A2AInvite( const std::string &strCALLID,const DEV_CHANNEL_ITEM &channelItem,const std::string &strSDPData )=0;

	/* ��Ӧ�Խ� */
	virtual void A2ARespond( const std::string &strCALLID,const DEV_CHANNEL_ITEM &channelItem,const std::string &strSDPData )=0;

	/* �ж϶Խ� */
	virtual void A2ABye( const std::string &strCALLID )=0;

	/* ���� */
	virtual void Alert( const std::string &strDevID,unsigned short nCHNum,unsigned short nLevel,unsigned short nsubLevel = 0 )=0;
	
	/* ��̨���� */
	virtual int YTControl(const std::string &strDevID,unsigned short nCHNum,unsigned short nYTCmd, unsigned short nSpeed, unsigned short nPresetNO,const std::string &strPresetName )=0;// ��̨����

	/* ������ȡ��̨���Ʋ������� */
	virtual void GetYTControlParameters(const std::string &strDevID, unsigned short nCHNum)=0;

	/* ������ȡ��̨���Ӳ������� */
	virtual void GetYTConnectionParameters(const std::string &strDevID, unsigned short nCHNum)=0;

	/* ������̨���Ʋ��� */
	virtual void SetYTControlParameters(const std::string &strDevID,const std::string &strToID, const YT_CONTROL_PARAMETERS & YTParam)=0;

	/* ������̨���Ӳ��� */
	virtual void SetYTConnectionParameters(const std::string &strDevID,const std::string &strToID, unsigned short nChannelNum, const std::string &strType, unsigned short nCom,  unsigned short  nSerialNo)=0;

	/* ����P2P */
	virtual void P2P(const std::string strUserID, KCmdUserDataPacket& packet)=0;

	/* ��ȡ������������� */
	virtual void GetRegion(void)=0;
	virtual void GetRegion(const std::string &strUserID)=0;
	virtual bool GetRegion(const std::string strRegionID,unsigned short nNodeType)=0;

	/* ��ȡ¼���������ַ */
	virtual void GetVRSServer(void)=0;
};

//=======================================================================================
// MONģ���¼���
//=======================================================================================
class KMONSessionEvent
{
public:
	KMONSessionEvent(void){};
	virtual ~KMONSessionEvent(void){};
	
public:
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

	/* �豸��� */
	virtual void OnDeviceCheck(KCmdPacket& rCmdPacket)=0;

	/* �յ�ͨ������ (DEVID,CHNUM,ERRCODE) */
	virtual void OnChannelOnline(KCmdPacket& rCmdPacket)=0;

	/* �յ�ͨ������ */
	virtual void OnChannelOffline(KCmdPacket& rCmdPacket)=0;

	/* ��ȡ������Ϣ */
	virtual void OnDeviceBasicInfo(KCmdPacket& rCmdPacket)=0;

	/* ���� */
	virtual void OnAlert(KCmdPacket& rCmdPacket)=0;

	/* ����Խ� */
	virtual void OnA2A(KCmdPacket& rCmdPacket)=0;

	/* ����Խ� */
	virtual void OnA2ABye(KCmdPacket& rCmdPacket)=0;

	/* ������̨�������� */
	virtual void OnYTControl(KCmdPacket& rCmdPacket)=0;

	/* ��ȡ��̨���Ӳ������� */
	virtual void OnGetYTConnectionParameters(KCmdPacket& rCmdPacket)=0;

	/* ��ȡ��̨���Ʋ������� */
	virtual void OnGetYTControlParameters(KCmdPacket& rCmdPacket)=0;

	/* ������̨���Ӳ��� */
	virtual void OnSetYTConnectionParameters(KCmdPacket& rCmdPacket)=0;

	/* ������̨���Ʋ��� */
	virtual void OnSetYTControlParameters(KCmdPacket& rCmdPacket)=0;

	/* ���ػ���P2P */
	virtual void OnP2P(const std::string& strUserID,KCmdUserDataPacket& packet)=0;

	/* ������� */
	virtual void OnRegion(KCmdItem& rCmdPacket)=0;

	/* ���VRS������VRSID,VRSADDR */
	virtual void OnVRSServer(KCmdPacket& rCmdPacket)=0;
};

//=======================================================================================
// MONʵ��
//=======================================================================================
AFX_EXT_CLASS bool MONSessionAddEvent(KMONSessionEvent* pMONSessionEvent);
AFX_EXT_CLASS void MONSessionRemoveEvent(KMONSessionEvent* pMONSessionEvent);
AFX_EXT_CLASS void MONSessionRelease(void);
AFX_EXT_CLASS KMONSession& GetMONSession(void);

//=======================================================================================
// AVCģ����
//=======================================================================================
class AFX_EXT_CLASS KAVCSession
{
public:
	KAVCSession(void){};
	virtual ~KAVCSession(void){};

	enum{CALLINGOUT,CALLINGIN,TALKING};

public:
	//-------------------------------------------
	// ����¼�
	virtual void OnDispatchCmd(KCmdPacket& t)=0;

	virtual AVC_CALL_ITEM_MAP& GetCallItemMap(void)=0;
	virtual PAVC_CALL_ITEM GetCallItem(const std::string& toid)=0;
	virtual std::string GetUserID(void)=0;

	virtual bool Call(const std::string& strNodeID,const std::string& strUserName,const std::string& strData)=0;
	virtual void Hangup(const std::string& strNodeID,const std::string& strData)=0;
	virtual void Pickup(const std::string& strNodeID,const std::string& strData)=0; 
	virtual void SendUserData(const std::string& strNodeID,KCmdPacket& packet)=0;
};

//=======================================================================================
// AVCģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KAVCSessionEvent
{
public:
	KAVCSessionEvent(void){};
	virtual ~KAVCSessionEvent(void){};

public:
	virtual void OnCall(const std::string& strUserID,const std::string& strUserName,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnHangup(const std::string& strUserID,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnPickup(const std::string& strUserID,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnUserData(KCmdPacket& packet)=0;
};

//=======================================================================================
// AVCʵ��
//=======================================================================================
AFX_EXT_CLASS bool AVCSessionAddEvent(KAVCSessionEvent* pAVCSessionEvent);
AFX_EXT_CLASS void AVCSessionRemoveEvent(KAVCSessionEvent* pAVCSessionEvent);
AFX_EXT_CLASS void AVCSessionRelease(void);
AFX_EXT_CLASS KAVCSession& GetAVCSession(void);

//=======================================================================================
// WHBģ����
//=======================================================================================
class AFX_EXT_CLASS KWHBSession
{
public:
	KWHBSession(void){};
	virtual ~KWHBSession(void){};
	
	/* ����SESSION */
	virtual void Close()=0;	

	enum{CALLINGOUT,CALLINGIN,TALKING};

	//-------------------------------------------
	// ����¼�
	virtual void OnDispatchCmd(KCmdPacket& t)=0;

	virtual WHB_CALL_ITEM_MAP& GetCallItemMap(void)=0;
	virtual PWHB_CALL_ITEM GetCallItem(const std::string& strNodeID)=0;
	virtual std::string GetUserID(void)=0;

	virtual bool Call(const std::string& strNodeID,const std::string& strUserName,const std::string& strData)=0;
	virtual void Hangup(const std::string& strNodeID,const std::string& strData)=0;
	virtual void Pickup(const std::string& strNodeID,const std::string& strData)=0; 
	virtual void SendUserData(const std::string& strNodeID,KCmdPacket& packet)=0;
};

//=======================================================================================
// WHBģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KWHBSessionEvent
{
public:
	KWHBSessionEvent(void){};
	virtual ~KWHBSessionEvent(void){};

public:
	virtual void OnCall(const std::string& strUserID,const std::string& strUserName,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnHangup(const std::string& strUserID,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnPickup(const std::string& strUserID,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnUserData(KCmdPacket& packet)=0;
};

//=======================================================================================
// WHBʵ��
//=======================================================================================
AFX_EXT_CLASS bool WHBSessionAddEvent(KWHBSessionEvent* pWHBSessionEvent);
AFX_EXT_CLASS void WHBSessionRemoveEvent(KWHBSessionEvent* pWHBSessionEvent);
AFX_EXT_CLASS void WHBSessionRelease(void);
AFX_EXT_CLASS KWHBSession& GetWHBSession(void);

//=======================================================================================
// SVRģ����
//=======================================================================================
class AFX_EXT_CLASS KSRVSession
{
public:
	KSRVSession(void){};
	virtual ~KSRVSession(void){};
	
	/* ����SESSION */
	virtual void Close()=0;

	enum{CALLINGOUT,CALLINGIN,TALKING};

public:
	//-------------------------------------------
	// ����¼�
	virtual void OnDispatchCmd(KCmdPacket& t)=0;

	virtual SRV_CALL_ITEM_MAP& GetCallItemMap(void)=0;
	virtual PSRV_CALL_ITEM GetCallItem(const std::string& toid)=0;
	virtual std::string GetUserID(void)=0;

	virtual bool Call(const std::string& strNodeID,const std::string& strUserName,const std::string& strData)=0;
	virtual void Hangup(const std::string& strNodeID,const std::string& strData)=0;
	virtual void Pickup(const std::string& strNodeID,const std::string& strData)=0; 
	virtual void SendUserData(const std::string& strNodeID,KCmdPacket& packet)=0;
};

//=======================================================================================
// SVRģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KSRVSessionEvent
{
public:
	KSRVSessionEvent(void){};
	virtual ~KSRVSessionEvent(void){};

public:
	virtual void OnCall(const std::string& strUserID,const std::string& strUserName,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnHangup(const std::string& strUserID,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnPickup(const std::string& strUserID,const std::string& strNodeID,const std::string& strData)=0;
	virtual void OnUserData(KCmdPacket& packet)=0;
};

//=======================================================================================
// SRVʵ��
//=======================================================================================
AFX_EXT_CLASS bool SRVSessionAddEvent(KSRVSessionEvent* pSRVSessionEvent);
AFX_EXT_CLASS void SRVSessionRemoveEvent(KSRVSessionEvent* pSRVSessionEvent);
AFX_EXT_CLASS void SRVSessionRelease(void);
AFX_EXT_CLASS KSRVSession& GetSRVSession(void);

//=======================================================================================
// FILģ����
//=======================================================================================
class AFX_EXT_CLASS KFILSession
{
public:
	KFILSession(void){};
	virtual ~KFILSession(void){};
	
	/* ����SESSION */
	virtual void Close()=0;

public:
	//-------------------------------------------
	// ����¼�
	virtual void OnDispatchCmd(KCmdPacket& t)=0;

	virtual std::string GetUserID(void)=0;

	virtual void Call(const std::string& strNodeID,const std::string& strUserName,const std::string& strFileName,unsigned long ulFileSize)=0;
	virtual void Hangup(const std::string& strNodeID,const std::string& strFileName)=0;
	virtual void SendUserData(const std::string& strNodeID,KCmdPacket& packet)=0;
};

//=======================================================================================
// FILģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KFILSessionEvent
{
public:
	KFILSessionEvent(void){};
	virtual ~KFILSessionEvent(void){};

public:
	virtual void OnCall(const std::string& strUserID,const std::string& strUserName,const std::string& strNodeID,const std::string& strFileName,unsigned long ulFileSize)=0;
	virtual void OnHangup(const std::string& strUserID,const std::string& strNodeID,const std::string& strFileName)=0;
	virtual void OnUserData(KCmdPacket& packet)=0;
};

//=======================================================================================
// FILʵ��
//=======================================================================================
AFX_EXT_CLASS bool FILSessionAddEvent(KFILSessionEvent* pFILSessionEvent);
AFX_EXT_CLASS void FILSessionRemoveEvent(KFILSessionEvent* pFILSessionEvent);
AFX_EXT_CLASS void FILSessionRelease(void);
AFX_EXT_CLASS KFILSession& GetFILSession(void);

//=======================================================================================
// SMSģ����
//=======================================================================================
class AFX_EXT_CLASS KSMSSession
{
public:
	KSMSSession(void){};
	virtual ~KSMSSession(void){};

	/* ����SESSION */
	virtual void Close()=0;

public:
	virtual void OnDispatchCmd(KCmdPacket& t)=0;

	/* ���͸��˶���
	 * strReceiverCode: �������ֻ�����,֧�ֶ������,�÷ֺ�(;)���� */
	virtual void Send(const std::string& strReceiverCode,const std::string& strContent)=0;

	/* ������ҵ����
	 * strOrgID:        ����ID
	 * strDepartID;		����ID,�����û������������û�������strDepartID��Ϊ�� */
	virtual void Send(const std::string& strOrgID,const std::string& strDepartID,const std::string& strContent)=0;
};

//=======================================================================================
// SMSģ���¼���
//=======================================================================================
class AFX_EXT_CLASS KSMSSessionEvent
{
public:
	KSMSSessionEvent(void){};
	virtual ~KSMSSessionEvent(void){};

public:
	/* ���ŷ��ͺ�ķ�����Ϣ
	 * nType: 0=���˶��� 1=��ҵ���� */
	virtual void OnSend(unsigned short nType,bool bSuccess,const std::string& strErrText,const std::string& strRecvCode,const std::string& strContent)=0;

	/* �յ�����
	 * nType: 0=���˶��� 1=��ҵ���� */
	virtual void OnReceive(unsigned short nType,const std::string& strUserID,const std::string& strSenderCode,const std::string& strContent,const std::string& strRecvTime)=0;
};

//=======================================================================================
// SMSʵ��
//=======================================================================================
AFX_EXT_CLASS bool SMSSessionAddEvent(KSMSSessionEvent* pSMSSessionEvent);
AFX_EXT_CLASS void SMSSessionRemoveEvent(KSMSSessionEvent* pSMSSessionEvent);
AFX_EXT_CLASS void SMSSessionRelease(void);
AFX_EXT_CLASS KSMSSession& GetSMSSession(void);


//=======================================================================================
// �����ļ�ģ����
//=======================================================================================
#include "KNFSDefine.h"

class AFX_EXT_CLASS KNFSSession
{
public:
	KNFSSession(void);
	virtual ~KNFSSession(void);

	static bool Start(void);
	static void Stop(void);
};

//---------------------------------------------------------
// KNFSUploadSessionEvent �¼��ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSUploadSessionEvent
{
public:
	KNFSUploadSessionEvent(void){};
	virtual ~KNFSUploadSessionEvent(void){};
	
	/* ���ӳɹ�  */
	virtual void OnConnected(void)=0;

	/* ���ӶϿ�  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* �ϴ����� */
	virtual void OnUploadError(int nErrCode)=0;

	/* �ϴ����� */
	virtual void OnUploadProgress(double dPercent,double dSpeed)=0;

	/* �ϴ����� */
	virtual void OnUploadEnd(void)=0;

	/* ɾ�� */
	virtual void OnDelete(int nErrCode)=0;
};

//---------------------------------------------------------
// KNFSUploadSession �ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSUploadSession
{
public:
	KNFSUploadSession(void){};
	virtual ~KNFSUploadSession(void){};

	/* ���ӷ����� */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort)=0;

	/* �Ͽ����������� */
	virtual void Disconnect(void)=0;

	/* �ϴ��ļ�:
	 * strLocalFileFullName:  �����ϴ��ļ�ȫ·����(�����ļ���)
	 * strUploadFilePath:     �ϴ��ļ�·��(���������·��):/emaps/part01
	 * strUploadFileName:     �ϴ��ļ�����: map0001.jpg
     * ˵��:���浽�������ϵ��ļ�λ��: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Upload(const std::string& strLocalFileFullName,const std::string& strUploadFilePath,const std::string& strUploadFileName)=0;

	/* ɾ���ļ�
	 * strUploadFilePath:     �ϴ��ļ�·��(���������·��):/emaps/part01
	 * strUploadFileName:     �ϴ��ļ�����: map0001.jpg
     * ˵��:���浽�������ϵ��ļ�λ��: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Delete(const std::string& strDeleteFilePath,const std::string& strDeleteFileName)=0;
};

//---------------------------------------------------------
// KNFSDownloadSessionEvent �¼��ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSDownloadSessionEvent
{
public:
	KNFSDownloadSessionEvent(void){};
	virtual ~KNFSDownloadSessionEvent(void){};
	
	/* ���ӳɹ�  */
	virtual void OnConnected(void)=0;

	/* ���ӶϿ�  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* ���ؿ�ʼ */
	virtual void OnDownloadStart(unsigned long ulFileSize)=0;

	/* ���ش��� */
	virtual void OnDownloadError(int nErrCode)=0;

	/* ���ؽ��� */
	virtual void OnDownloadProgress(double dPercent,double dSpeed)=0;

	/* ���ؽ��� */
	virtual void OnDownloadEnd(void)=0;

	/* ɾ�� */
	virtual void OnDelete(int nErrCode)=0;
};

//---------------------------------------------------------
// KNFSDownloadSession �ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSDownloadSession
{
public:
	KNFSDownloadSession(void){};
	virtual ~KNFSDownloadSession(void){};

	/* ���ӷ����� */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort)=0;

	/* �Ͽ����������� */
	virtual void Disconnect(void)=0;

	/* �ϴ��ļ�:
	 * strLocalFileFullName: �����ļ�ȫ·��
	 * strDownloadFilePath:  �����ļ�·��(���������·��):/emaps/part01
	 * strDownloadFileName:  �����ļ�����: map0001.jpg
     * ˵��:�ӷ������������ļ�/usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Download(const std::string& strLocalFileFullName,const std::string& strDownloadFilePath,const std::string& strDownloadFileName)=0;

	/* ɾ���ļ�
	 * strUploadFilePath:     �ϴ��ļ�·��(���������·��):/emaps/part01
	 * strUploadFileName:     �ϴ��ļ�����: map0001.jpg
     * ˵��:���浽�������ϵ��ļ�λ��: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Delete(const std::string& strDeleteFilePath,const std::string& strDeleteFileName)=0;
};

//---------------------------------------------------------
// �����ϴ�SESSION
//---------------------------------------------------------
AFX_EXT_CLASS KNFSUploadSession* CreateNFSUploadSession(KNFSUploadSessionEvent& rNFSUploadSessionEvent);

//---------------------------------------------------------
// ��������SESSION
//---------------------------------------------------------
AFX_EXT_CLASS KNFSDownloadSession* CreateNFSDownloadSession(KNFSDownloadSessionEvent& rNFSDownloadSessionEvent);

