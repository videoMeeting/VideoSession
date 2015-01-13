#pragma once

#include "string"
#include "WYSYSClient.h"
#include "Middlelayer.h"
#include <vector>
#include "WYBASE/Timer.h"
#include "VoeManager.h"

typedef struct _ROOMUSERINFO
{
    _ROOMUSERINFO()
    {
        bIsOpenVideo = false;
        uiScreenNum = 0;
        bIsOpenAudio = false;
        strUserID = "";
        bIsHost = false;
        bIsInRoom = false;
        bIsEnterRoom = false;
        bIsUpRoom = true;
    }
    bool          bIsOpenVideo;
    unsigned int  uiScreenNum;
    bool          bIsOpenAudio;
    std::string   strUserID;
    bool          bIsHost;
    bool          bIsInRoom;
    bool          bIsUpRoom;
    bool          bIsEnterRoom;
}ROOMUSERINFO;

typedef struct _ROOMINFO
{
    _ROOMINFO()
    {
        ulRoomId = 0;
        strHostID = "";
        uiRoomType = 0;
        UserList.clear();
    }
    unsigned long ulRoomId;
    std::string   strHostID;
    unsigned int  uiRoomType;
    std::vector<ROOMUSERINFO> UserList;
    
}ROOMINFO;

typedef enum _ROOM_TYPE
{
    Room_No=0,
    Room_VIDEO,
    Room_AUDIO
}ROOM_TYPE;

typedef enum _ROOM_VIDEOANDAUDIOSET
{
    ROOM_SET_NO=0,
    ROOM_VIDEO_PUSH,
    ROOM_VIDEO_ROOM,
    ROOM_AUDIO_SPEAK,
    ROOM_AUDIO_DISCUSS
}ROOM_VIDEOANDAUDIOSET;

typedef enum  _ROOM_INFO_TYPE
{
    ROOM_Info_No=0,
    Room_Info_Initialization,
    ROOM_Info_OpenVideo,
    ROOM_Info_CloseVideo,
    ROOM_Info_OpenAudio,
    ROOM_Info_CloseAudio,
    ROOM_Info_SetType,
    ROOM_Info_Screen
}ROOM_INFO_TYPE;

typedef struct _USERROOMINFO
{
    std::string strUserID;
    std::string strPeerID;
    unsigned long ulRoomID;
    unsigned long ulPeerMediaId;
    unsigned int uiRoomType;
    unsigned int uiRoomScreen;
    unsigned int uiVideoType;
    unsigned int uiAudioType;
    unsigned int uiInfoType;
    unsigned int uiScreenCount;
}USERROOMINFO;

typedef std::map<unsigned int,std::string> USERGROP;
typedef std::map<std::string,std::vector<std::string> > USERGROPUSER;

typedef std::map<unsigned long, ROOMINFO> ROOMUSERLIST;
typedef std::map<std::string,IMS_CONTACT_ITEM> USERLSRT;
typedef std::map<unsigned int, USERROOMINFO> ROOMINFOMAP;

//=======================================================================================
class LoginServer : public KSYSSessionEvent
                  , public KIMSSessionEvent
			      , public KMMSSessionEvent
                  , public KTimer
{
public:
	LoginServer(unsigned long ulMediaId = 0);
	virtual ~LoginServer();
    
private:
	BOOL	        m_bLogin;
	unsigned long	m_ulTestTimeStamp;
    USERLSRT        m_UserList;
    ROOMUSERLIST    m_RoomUserList;
    pthread_mutex_t m_pMutex;
    pthread_mutex_t m_pMutexQueue;
    unsigned long   m_ulRoomId;
    unsigned int    m_uiRoomType;
    unsigned long   m_ulMediaId;
    unsigned long   m_ulScreenControl;
    ROOMINFOMAP     m_RoomInfoMap;
    ROOMINFOMAP     m_VideoinfoMap;
    unsigned long   m_ulCount;
    unsigned int    m_nTimerID;
    bool            m_isInRoom;
private:
    USERGROP        m_UserGrop;
    USERGROPUSER    m_UserGropUser;
    unsigned long   m_ulConnectTime;
    bool            m_Connecting;
public:
    id<IMLoginInfo>         m_IMLoginInfo;
    id<IMGetUserGroupInfo>  m_iMGetUserGroupInfo;
    id<IMGetUserFriendInfo> m_iMGetUserFriendInfo;
    id<MMMeetingProtocol>   m_MMMeetingProtocol;
    id<MMGetRoomControl>    m_MMGetRoomControl;
public:
	void DoServerConnect(const std::string& strServerAddr,unsigned short usServerPort,const std::string& strUserID,const std::string& strPassword,const std::string& strStatus);
	void DoServerDisconnect(void);
    
    virtual void OnTimerEvent(unsigned int nEventID);
public:
    std::string   GetServerIp() const;
    unsigned int  GetServerPort() const;
    bool ISChairman() const;
    unsigned int  GetRoomType() const;
    unsigned long GetRoomId() const;
    unsigned long GetLocalVideoId() const;
    unsigned long GetLocalAudioId() const;
    unsigned long GetScreenControl() const;
    unsigned long GetPeerUserVideoId(const std::string strUserId);
    unsigned long GetPeerUserAudioId(const std::string strUserId);
    unsigned long XGetTimestamp();
    std::string   GetHostID(){return m_strHostID;}
    bool          GetIsInRoom(){return m_isInRoom;}
    void          SetInformationStateQueue(bool b);
    VoeManager *voe_manager() { return _voeManager; }
protected:
	std::string	m_strServerAddr;
	unsigned short m_usServerPort;
	std::string m_strUserID;
	std::string m_strPassword;
	std::string m_strStatus;
    std::string m_strHostID;
    bool        m_bIsChairman;
    bool        m_SetInfoStateQueue;
    VoeManager                  *_voeManager;
	//-----------------------------------------------------
	// KSYSSessionEvent
	//-----------------------------------------------------
	virtual void OnServerConnecting(void);
	virtual void OnServerReconnected(void);
	virtual void OnServerBusy(void);
	virtual void OnServerFailed(void);
	virtual void OnServerDisconnected(unsigned int nErrCode);
	virtual void OnServerConnected(void);
	virtual void OnServerListStart(void);
	virtual void OnServerList(const std::string& strMCUID,const std::string& strMCUType,
		                      unsigned long ulConnections,const std::string& strBandWidth,unsigned long ulActivity,
							  const std::string& strIPAddr,unsigned short usIPPort,const std::string& strIPName);
	virtual void OnServerListEnd(void);
	virtual void OnServerRealTime(const std::string& strServerTime){};
	virtual void OnClientVersion(const std::string& strProduct,const std::string& strVersion,bool bForce){};

	//-----------------------------------------------------
	// KIMSSessionEvent
	//-----------------------------------------------------
	virtual void OnLogin(int nErrCode,const std::string& strModuleString);
	virtual void OnLogout(int nErrCode);
	virtual void OnAllUserCount(unsigned long ulCount){};
	virtual void OnOnlineUserCount(unsigned long ulCount){};
	virtual void OnMyName(const std::string& strUserName){};
	virtual void OnMyInfo(const IMS_CONTACT_ITEM& ui){};
	virtual void OnMyPriv(unsigned long ulPrivCode){};
	virtual void OnImage(const std::string& strUserID,const std::string& strImgType,const std::string& strImgData){};
	virtual void OnStatus(const std::string& strUserID,const std::string& strStatus,bool bFirst,const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,unsigned long ulMediaId);

	virtual void OnGroupItem(const std::string& strGroup,unsigned int nIndex);
	virtual void OnGroupItemEnd(void);
	virtual void OnGroupInsert(const std::string& strGroup,unsigned int nIndex);
	virtual void OnGroupUpdateName(const std::string& strOldGroup,const std::string& strNewGroup);
	virtual void OnGroupUpdateIndex(const std::string& strGroup,unsigned int nIndex);
	virtual void OnGroupDelete(const std::string& strGroup);

	virtual void OnFriendItem(const IMS_CONTACT_ITEM& item);
	virtual void OnFriendItemEnd(void);
	virtual void OnFriendInfo(const std::string& strFriendID);
	virtual void OnFriendApply(const std::string& strFriendID, const std::string& strUserGroup);
	virtual void OnFriendApplyError(const std::string& strFriendID){};
	virtual void OnFriendAdmit(const std::string& strFriendID);
	virtual void OnFriendUpdateGroup(const std::string& strFriendID,const std::string& strGroup);
	virtual void OnFriendDelete(const std::string& strUserGroup, const std::string& strFriendID);
	virtual void OnFriendSearch(const IMS_CONTACT_ITEM& item){};

	virtual void OnOrgListStart(void);
	virtual void OnOrgItem(const std::string& strOrgID,const std::string& strOrgName);
	virtual void OnOrgItemEnd(void);
	virtual void OnOrgDepartItem(const std::string& strOrgID,const std::string& strDepartID,const std::string& strDepartName,int nLevelID,const std::string& strUpgradeID,int nOrderID);
	virtual void OnOrgDepartItemEnd(void);
	virtual void OnOrgDepartUserItem(const std::string& strOrgID,const std::string& strDepartID,const IMS_CONTACT_ITEM& item,int nOrderID);
	virtual void OnOrgDepartUserItemEnd(void);
    virtual void DeleteUser(const std::string& strUserID);
	virtual void OnOrgDeleteItem(const std::string& strOrgID,const std::string& strDepartID,const std::string& strUserID);
	virtual void OnOrgDeleteItemEnd(void);
	virtual void OnOrgListEnd(const std::string& strUpdateTime);

	virtual void OnOnlineMessage(const std::string& strUserID,const std::string& strUserName,const std::string& strNodeID,const XMSG& xmsg){};
	virtual void OnOfflineMessage(const std::string& strUserID,const XMSG& xmsg){};
	virtual void OnSystemMessage(const std::string& strAdminName,const XMSG& xmsg){};
	virtual void OnSystemMessageEnd(void){};
	virtual void OnOrgMessage(const std::string& strOrgID,const std::string& strOrgName,
		                      const std::string& strDepartID,const std::string& strDepartName,
							  const std::string& strUserID,const std::string& strUserName,const XMSG& xmsg){};
	virtual void OnUserData(KCmdUserDataPacket& packet){};
	virtual void OnWEBServer(const std::string& strHost,unsigned short usPort){};
	virtual void OnPBXServer(const std::string& strHost){};
	virtual void OnFAXServer(const std::string& strHost,unsigned short usPort){};
	virtual void OnGetURLItem(const std::string& strName,const std::string& strURL){};
	virtual void OnGetURLListEnd(){};
	virtual void OnGetFAXCount(unsigned int nCount){};	
	virtual void OnMapInfo(const std::string& strGroupID, const std::string& strMapMD5){};
	virtual void OnBzIDInfo(const std::string& strGroupID, MAP_BZ_LST listMAPBZ){};
	virtual void OnMonUpdateTime(const std::string& strUpdateTime){};
	virtual void OnGroupInfo(const MONGROUP& item){};
	virtual void OnChannelInfo(const MONCHANNEL& item){};
	virtual void OnGetGroupInfoEnd(){};
	virtual void OnChannelInfoEnd(){};
	virtual void OnMonAlert(const std::string& strChannelID,unsigned short usType,unsigned short usSubtype){};			
	virtual void OnDEVAddMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName){};
	virtual void OnDEVDelMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName){};
	virtual void OnDEVRenameMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName){};
	virtual void OnDEVAddMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid){};
	virtual void OnDEVDelMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid){};
	virtual void OnDEVGetMyGroup(const std::string& strTmpGrpID,std::string& strAdminID, std::string& strTmpGrpName){};
	virtual void OnDEVGetMyGroupMember(const std::string& strTmpGrpID,std::string& strMemberID, int nDid){};
	virtual void OnUpdateDevName(const std::string& strDevID,const std::string& strName, unsigned long ulGroupID){};
	virtual void OnUpdateChannelName(const std::string& strChannelID,const std::string& strName,unsigned long ulGroupID){};

	//-----------------------------------------------------
	// KMMSSessionEvent
	//-----------------------------------------------------
	//add by wanggj
public:
    std::string GetUserID() const;
public:
    virtual void GetUserGropList(std::map<unsigned int,std::string>& UserGrop);
    virtual void GetUserFriendList(const std::string& strUserGroup, std::vector<std::string>& UserFriend);
    virtual unsigned int GetUserGropUserCount(std::string UserGropName);
    virtual void GetUserList(std::list<std::string>&UserList);
    virtual bool GetUserInfo(const std::string& strUser,IMS_CONTACT_ITEM& mUserInfo);
    virtual bool GetRoomUserList(std::vector<ROOMUSERINFO>&UserList);
public:
    void Run();//主线程定时调用
    
    virtual bool AddUserGrop(const std::string& strGroup);
    virtual int  UserGropUpdateName(const std::string& strOldGroup, const std::string& strNewGroup);
    virtual bool DeleteUserGrop(const std::string& strGroup);
    
    virtual bool AddUserFriend(const std::string& strUserGroup, const std::string& strUserFriend);
    virtual bool DeleteUserFriend(const std::string& strUserGroup, const std::string& strUserFriend);
    
	virtual void CreateTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID , unsigned int uiRoomType);
    
	virtual void DestructionTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID);
    
    virtual void QuitTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID);
    virtual void JoinTemporaryMeeting(const std::string& strUserID, const std::string& strPeerUserID, unsigned long ulRoomID);
    
    virtual void OnInitializationTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount, unsigned int uiVideoType, unsigned int uiAudioType);
    
	virtual void OnOpenPeerUserVideo(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserVideoID, unsigned int uiScreenControl, bool bIsBroadcast=true);
	virtual void OnClosePeerUserVideo(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserVideoID, bool bIsBroadcast=true);

	virtual void OnOpenPeerUserAudio(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserAudioID, bool bIsBroadcast=true); 
	virtual void OnClosePeerUserAudio(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserAudioID, bool bIsBroadcast=true);
    
    virtual void OnScreenControl(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount);

	virtual void OnSetMeetingType(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiType);
    
    virtual void OnInviteUser(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID);
    virtual void OnReplyInviteUser(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID,bool bIsAgree);
    
    virtual void OnForTheFloor(const std::string& strUserID, unsigned long ulRoomID, const std::string& strHostID);
	virtual void OnPleaseOutTemporaryMeeting(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID);
	virtual void OnPassPrivileges(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID);
	virtual void OnUserSnedMsg(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, std::string& ulUserMsg, bool bIsBroadcast=false);
public:
    virtual void CallbackCreateInterimMeeting(const std::string& strHostID, unsigned long ulRoomID , unsigned int uiRoomType);
    virtual void CallbackDestructionInterimMeeting(const std::string& strHostID, unsigned long ulRoomID,   std::vector<std::string>& vQuitUser);
    virtual void CallbackJoinTemporaryMeeting(const std::string& strUserID,  unsigned long ulRoomID);
    
    virtual void CallbackMeetingUserInfo(const std::string& strHostID, unsigned long ulRoomID, unsigned int uiRoomType, std::vector<std::string>& vQuitUser);
    
    virtual void CallbackQuitTemporaryMeeting(const std::string& strUserID,  unsigned long ulRoomID);
    
    virtual void CallbackInitializationTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount, unsigned int uiVideoType, unsigned int uiAudioType);
    
    virtual void CallbackOpenPeerUserVideo(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserVideoID, unsigned long ulScreeCount);
    
    virtual void CallbackClosePeerUserVideo(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserVideoID);
    
    virtual void CallbackOpenPeerUserAudio(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserAudioID);
    
    virtual void CallbackClosePeerUserAudio(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserAudioID);
    
    virtual void CallbackSetMeetingType(unsigned long ulRoomID, unsigned int uiType);
    
    virtual void CallbackOnScreenControl(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount);
    
    virtual void CallbackInviteUser(const std::string& strUserID, unsigned long ulRoomID);
    virtual void CallbackReplyInviteUser(const std::string& strUserID, unsigned long ulRoomID,bool bIsAgree);
    
    virtual void CallbackForTheFloor(const std::string& strUserID, unsigned long ulRoomID, const std::string& strHostID);
	virtual void CallbackPleaseOutTemporaryMeeting(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID);
	virtual void CallbackPassPrivileges(const std::string& strHostID, unsigned long ulRoomID);
	virtual void CallbackUserSnedMsg(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, std::string& ulUserMsg);
	//endif

protected:
	virtual void OnTempGroupItem(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strGroupName,bool bDefault){};
	virtual void OnTempGroupUpdateName(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strGroupName){};
	virtual void OnTempGroupDelete(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID){};
	virtual void OnTempMemberItem(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strMemberID,const std::string& strMemberName){};
	virtual void OnTempMemberDelete(const std::string& strDomain,unsigned long ulRoomID,unsigned long ulGroupID,const std::string& strMemberID){};

	virtual void OnRoomListEnd(const std::string& strDomain);

	virtual void OnLogin(unsigned int nErrCode,const std::string& strDomainID,const std::string& strRoomID,const std::string& strRoomName,unsigned short usRoomType,
		const std::string& strRootGroupID,const std::string& strGroupID,const std::string& strActiveGroupID,
        const std::string& strMemberID,unsigned short usMemberType,bool bAllowVideo){};
	virtual void OnLogout(unsigned int nErrCode){};
	virtual void OnRoomGroupItem(MMS_GROUP_EX& item){};
	virtual void OnRoomGroupListEnd(const std::string& strUpdateTime){};
	virtual void OnRoomMemberItem(MMS_MEMBER_EX& item){};
	virtual void OnRoomMemberListEnd(void){};
	virtual void OnReady(void){};
	virtual void OnStatus(const std::string& strGroupID,const std::string& strMemberID,unsigned short usMemberType,
		                  const std::string& strSvrID,const std::string& strSvrAddr,unsigned short usSvrPort,const std::string& strSvrType,
						  const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,
						  const std::string& strTermType,unsigned char ucStatus){};
	virtual void OnInvite(const std::string& strRoomDomain,const std::string& strRoomID,const std::string& strGroupID,
		                  const std::string& strRoomName,const std::string& strInviterNodeID,const std::string& strInviterID,
						  const std::string& strInviterName,const std::string& strPassword,bool bPresider){};
	virtual void OnReject(const std::string& strDomain,const std::string& strRoomID,const std::string& strInviteeID,const std::string& strInviteeName){};
	virtual void OnMessage(const std::string& strMemberID,const std::string& strHead,const std::string& strBody,const std::string& strFormat){};
	virtual void OnUserData(KCmdUserDataPacket& packet,unsigned char ucObject){};
	virtual void OnSetActiveGroupID(const std::string& strGroupID){};
	virtual void OnSetCurrentScreenID(const std::string& strOwnerID,const std::string& strGroupID,int nCurScrID,int nPrevTM){};
	virtual void OnCardItem(const std::string& strGroupID,const std::string& strMemberID,int nCardIndex,const std::string& strCardName,
		                    unsigned int nChannelType,unsigned long ulChannnelID,
							const std::string& strMCUID,const std::string& strMCUAddr,unsigned short usMCUPort,
							const std::string& strDevInfo){};
	virtual void OnCardListEnd(void){};
	virtual void OnCardAudioItem(const std::string& strGroupID,const std::string& strMemberID,int nCardIndex,unsigned long ulAudioID){};
	virtual void OnSetCardName(const std::string& strGroupID,const std::string& strMemberID,int nCardIndex,const std::string& strCardName){};
	virtual void OnGroupSynInfoEnd(void){};
	virtual void OnSetRight(int usRightType,unsigned char ucRight,const std::string& strMemberID){};
	virtual void OnSetProlocutor(const std::string& strMemberID,bool bRequest){};
	virtual void OnEnableProlocutor(const std::string& strMemberID,bool bEnable){};
	virtual void OnSetQuestioner(const std::string& strMemberID,bool bRequest){};
	virtual void OnEnableQuestioner(const std::string& strMemberID,bool bEnable){};
	virtual void OnSetAnnexData(int usAnnexType,const std::string& strData,const std::string& strFormat){};
	virtual void OnEnableAnnex(int usAnnexType,bool bEnable){};
	virtual void OnUnlocked(void){};
	virtual void OnBroadcastCard(const std::string& strOwnerID,const std::string& strGroupID,int nScreenID,int nWindowID,
		                         const std::string& strMemberID,int nCardIndex,int nChannelType,unsigned long ulChannelID,
								 const std::string& strMCUID,const std::string& strMCUAddr,unsigned short usMCUPort,
								 const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,
								 const std::string& strTag){};
	virtual void OnCloseBroadcastCard(const std::string& strOwnerID,const std::string& strGroupID,
		                              const std::string& strMemberID,int nCardIndex,int nChannelType){};
	virtual void OnDragWindow(const std::string& strOwnerID,int nFromScreenID,int nFromWindowID,int nToScreenID,int nToWindowID){};
	virtual void OnSetTemplet(const std::string& strOwnerID,int nScreenID,int nTemType,int nTemID,bool bTemShow,int nWinNumber){};
	virtual void OnSetFloatWindow(const std::string& strOwnerID,int nScreenID,int nX,int nY,int nCX,int nCY){};	
	virtual void OnInviteInRoomBroadcast(const std::string& strRoomDomain,const std::string& strRoomID,const std::string& strGroupID,
		                                 const std::string& strMemberID,const std::string& strMeetingName,const std::string& strMeetingPass,
										 const std::string& strMemberName){};
	virtual void OnSetTempPresider(std::string& strMemberID,bool bSet){};
	virtual void OnPrepVote(const std::string& strMemberID,const std::string& strVoteID,bool bAllow){};
	virtual void OnStartVote(const std::string& strVoteID,const std::string& strTopic,bool bType,unsigned long ulTime,bool bMulti,MMS_VOTE_LST& strItems){};
	virtual void OnStopVote(const std::string& strVoteID,const std::string& strEndType,int nSum,int nAnswer,MMS_VOTE_LST& strItems){};
	virtual void OnStartHandle(unsigned long ulID,unsigned long ulTime){};
	virtual void OnStopHandle(unsigned long ulID,unsigned short usTotal,unsigned short usCount){};
	virtual void OnAllowSubMeet(const std::string& strGroupID){};
	virtual void OnSync(const std::string& strGroupID){};
	virtual void OnCalling(const std::string& strMemberID,unsigned int usTime){};
	virtual void OnCloseCalling(const std::string& strMemberID){};

	virtual void OnMonUserData(KCmdUserDataPacket& packet){};
	virtual void OnMonP2PData(const std::string& strDevID,KCmdUserDataPacket& packet){};
	virtual void OnLoss(MMS_LOSS& loss, unsigned short usErrorCode){};
	virtual void OnInsertTVMonitor(unsigned short usIndex,unsigned short usErrorCode){};
	virtual void OnUpdateTVMonitor(unsigned short usIndex,unsigned short usErrorCode){};
	virtual void OnInsertTVMatrix(unsigned short usIndex,unsigned short usErrorCode){};
	virtual void OnUpdateTVMatrix(unsigned short usIndex,unsigned short usErrorCode){};
	virtual void OnTVServerItem(const std::string& strTV,const std::string& strTVName,const std::string& strStatus){};
	virtual void OnTVMonitorItem(unsigned short usIndex,const std::string& strData){};
	virtual void OnTVMatrixItem(unsigned short usIndex,const std::string& strData){};
	virtual void OnTVListEnd(void){};

public:
	//CMeetingDlg			m_dlgMeetingPage;
public:
    static LoginServer* OnGetLoginServer(unsigned long ulMediaId = 0);
    static void OnDestroy();
};

