#include "NETEC_Node.h"
#include "NETEC_Setting.h"
#include "LoginServer.h"
#include "NETEC_Core.h"

#define MAX_TITLE_HEIGHT	62

LoginServer* g_LoginServer = NULL;

//---------------------------------------------------------------------------------------
LoginServer::LoginServer(unsigned long ulMediaId)
:m_bLogin(FALSE)
,m_bIsChairman(false)
,m_uiRoomType(0)
,m_ulRoomId(0)
,m_ulScreenControl(4)
,m_SetInfoStateQueue(true)
,m_ulConnectTime(0)
,m_Connecting(false)
,_voeManager(NULL)
{
    pthread_mutexattr_t attrQueue;
	pthread_mutexattr_init(&attrQueue);
	pthread_mutexattr_settype(&attrQueue, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_pMutexQueue, &attrQueue);
	pthread_mutexattr_destroy(&attrQueue);
    
    pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_pMutex, &attr);
	pthread_mutexattr_destroy(&attr);
    
    //NETEC_Core::Start(0,false,false,true);
    m_IMLoginInfo = nil;
    m_iMGetUserGroupInfo = nil;
    m_iMGetUserFriendInfo = nil;
    //m_imMeetingInfoProtocol = nil;
    m_MMGetRoomControl = nil;
    
    if(ulMediaId == 0)
        m_ulMediaId = XGetTimestamp()+(unsigned long)this;
    else
        m_ulMediaId = ulMediaId;
    
    if(_voeManager == NULL)
    {
        _voeManager = VoeManager::Create();
        _voeManager->Init();
        //_voeManager->SetVideoID(m_ulMediaId);
    }
    
    m_isInRoom = false;
    m_nTimerID = 1;
    StartTimer();
    SetTimerEvent(2,2000);
}

//---------------------------------------------------------------------------------------
LoginServer::~LoginServer()
{
    m_IMLoginInfo = nil;
    m_iMGetUserGroupInfo = nil;
    //m_imMeetingInfoProtocol = nil;
    m_MMGetRoomControl = nil;
    
    if(m_bLogin)
        DoServerDisconnect();
    m_bLogin = FALSE;
    KillTimerEvent(2);
    StopTimer();
    pthread_mutex_destroy(&m_pMutex);
    pthread_mutex_destroy(&m_pMutexQueue);
    //NETEC_Core::Stop();
}

//---------------------------------------------------------------------------------------
LoginServer* LoginServer::OnGetLoginServer(unsigned long ulMediaId)
{
    if(g_LoginServer == NULL)
        g_LoginServer = new LoginServer(ulMediaId);
    
	return g_LoginServer;
}

//---------------------------------------------------------------------------------------
void LoginServer::OnDestroy()
{
	if(g_LoginServer)
        delete g_LoginServer;
    g_LoginServer = NULL;
}

void LoginServer::Run()
{
    SYSSessionRun();
}

//=======================================================================================
// KSYSSession
//=======================================================================================

//---------------------------------------------------------------------------------------
void LoginServer::DoServerConnect(const std::string& strServerAddr,unsigned short usServerPort,const std::string& strUserID,const std::string& strPassword,const std::string& strStatus)
{
	m_strServerAddr = strServerAddr;
	m_usServerPort = usServerPort;
	m_strUserID = strUserID;
	m_strPassword = strPassword;
	m_strStatus = strStatus;

	NETEC_Node::Start();
	NETEC_Node::SetServerIP(strServerAddr.c_str());
	NETEC_Node::SetServerPort(usServerPort);

	if(SYSSessionConnect(this,SERVER_TYPE_MCU_MTS,strUserID)==false)
	{
		//∑˛ŒÒ∆˜¡¨Ω” ß∞‹
		//if(m_pLoginDlg)
		{
		//	m_pLoginDlg->SetMessageText(_T("connect failed."));
		}
		return;
	}
	IMSSessionAddEvent(this);
	MMSSessionAddEvent(this);
    m_ulConnectTime=XGetTimestamp();
    m_Connecting = true;
    
    if(_voeManager != NULL)
    {
        _voeManager->set_server_ip(strServerAddr.c_str());
        _voeManager->set_server_port(usServerPort);
    }
}

//---------------------------------------------------------------------------------------
void LoginServer::DoServerDisconnect(void)
{
	SYSSessionDisconnect(this);
	IMSSessionRelease();
	MMSSessionRelease();
	NETEC_Node::Stop();
    m_bLogin = FALSE;
}

//=======================================================================================
// KSYSSessionEvent
//=======================================================================================

//---------------------------------------------------------------------------------------
void LoginServer::OnServerConnecting(void)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerConnectingInfo:CS_CONNECTING errorid:0];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerReconnected(void)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerConnectingInfo:CS_RECONNECTED errorid:0];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerBusy(void)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerConnectingInfo:CS_BUSY errorid:0];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerFailed(void)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerConnectingInfo:CS_FAILED errorid:0];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerDisconnected(unsigned int nErrCode)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerConnectingInfo:CS_DISCONNECTED errorid:nErrCode];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerConnected(void)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerConnectingInfo:CS_CONNECTED errorid:0];
    
    m_Connecting = false;
	
	GetIMSSession().Login(m_strUserID,m_strPassword,m_strStatus,m_ulMediaId,"");
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerListStart(void)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerList(const std::string& strMCUID,const std::string& strMCUType,
                    unsigned long ulConnections,const std::string& strBandWidth,unsigned long ulActivity,
					const std::string& strIPAddr,unsigned short usIPPort,const std::string& strIPName)
{
	//∑˛ŒÒ∆˜¡–±Ì
}

//---------------------------------------------------------------------------------------
void LoginServer::OnServerListEnd(void)
{

}

//---------------------------------------------------------------------------------------
void LoginServer::OnLogin(int nErrCode,const std::string& strModuleString)
{
	if(nErrCode==0)
	{
		m_bLogin = TRUE;
        /*
		CString csInitStatus = _T("");
		if(m_pLoginDlg)
		{
			m_pLoginDlg->ShowWindow(SW_HIDE);
			csInitStatus = m_pLoginDlg->GetInitStatus();
		}
		std::string strUserID = GetIMSSession().GetUserID();
		std::string strUserName = GetIMSSession().GetUserName();
		CString csUserID = A2U(strUserID);
		CString csUserName = A2U(strUserName);
		CString csUserIDName;
		csUserIDName.Format(_T("%s <%s>"),csUserName,csUserID);
		GetDlgItem(IDC_STATIC_USERID_USERNAME)->SetWindowText(csUserIDName);
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(csInitStatus);*/
        
        if(m_IMLoginInfo!=nil)
            [m_IMLoginInfo OnServerLoginingInfo:CS_LOGINED errorid:0];

		//ªÒ»°¡™œµ»À◊È
		GetIMSSession().FetchGroups();
        if(m_IMLoginInfo!=nil)
            [m_IMLoginInfo OnServerBeginGetUserInfo:CS_GETUSERGROP];
	}
	else
	{
        if(m_IMLoginInfo!=nil)
            [m_IMLoginInfo OnServerLoginingInfo:CS_LOGINFAILED errorid:nErrCode];
	}
}

//---------------------------------------------------------------------------------------
void LoginServer::OnLogout(int nErrCode)
{
	/*if(m_pLoginDlg)
	{
		CString csText;
		csText.Format(_T("logout(errcode=%d)."),nErrCode);
		m_pLoginDlg->SetMessageText(csText);
	}

	PostMessage(WM_DISCONNECT_SERVER);*/
}

std::string LoginServer::GetServerIp() const
{
    return m_strServerAddr;
}

unsigned int LoginServer::GetServerPort() const
{
    return m_usServerPort;
}

bool LoginServer::ISChairman() const
{
    return m_bIsChairman;
}

//---------------------------------------------------------------------------------------
void LoginServer::OnStatus(const std::string& strUserID,const std::string& strStatus,bool bFirst,const std::string& strNodeID,const std::string& strNatAddr,const std::string& strLocalAddr,unsigned short usLocalPort,unsigned long ulMediaId)
{
	if(strUserID==GetIMSSession().GetUserID())
	{
	}
	else
	{
        (void)pthread_mutex_lock(&m_pMutex);
        USERLSRT::iterator iter = m_UserList.find(strUserID);
        if(iter != m_UserList.end())
        {
            iter->second.status = strStatus;
            iter->second.ulMediaId = ulMediaId;
        }
        pthread_mutex_unlock(&m_pMutex);
        
        if(m_iMGetUserFriendInfo!=nil)
        {
            if(strStatus == "online")
            {
                [m_iMGetUserFriendInfo OnFriendOnLine:strUserID];
            }
            else if(strStatus == "offline")
            {
                [m_iMGetUserFriendInfo OnFriendOffline:strUserID];
            }
        }
	}
}

//---------------------------------------------------------------------------------------
void LoginServer::OnGroupItem(const std::string& strGroup,unsigned int nIndex)
{
    if(strGroup.empty())
        return;
    (void)pthread_mutex_lock(&m_pMutex);
    m_UserGrop[nIndex] = strGroup;
    pthread_mutex_unlock(&m_pMutex);
}

//---------------------------------------------------------------------------------------
void LoginServer::OnGroupItemEnd(void)
{
	GetIMSSession().FetchFriends();
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerBeginGetUserInfo:CS_GETFRIEND];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnGroupInsert(const std::string& strGroup,unsigned int nIndex)
{
    (void)pthread_mutex_lock(&m_pMutex);
    m_UserGrop[nIndex] = strGroup;
    pthread_mutex_unlock(&m_pMutex);
    
    if(m_iMGetUserGroupInfo!=nil)
        [m_iMGetUserGroupInfo OnInsertGroup:strGroup nIndex:nIndex];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnGroupUpdateName(const std::string& strOldGroup,const std::string& strNewGroup)
{
    (void)pthread_mutex_lock(&m_pMutex);
    
    USERGROP::iterator iter = m_UserGrop.begin();
    while(iter!=m_UserGrop.end())
    {
        if(iter->second == strOldGroup)
        {
            iter->second = strNewGroup;
            break;
        }
        iter++;
    }
    
    pthread_mutex_unlock(&m_pMutex);
    
    if(m_iMGetUserGroupInfo!=nil)
        [m_iMGetUserGroupInfo OnUpdateGroupName:strOldGroup strNewGroup:strNewGroup];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnGroupUpdateIndex(const std::string& strGroup,unsigned int nIndex)
{
    (void)pthread_mutex_lock(&m_pMutex);
    
    USERGROP::iterator iter = m_UserGrop.begin();
    while(iter!=m_UserGrop.end())
    {
        if(iter->second == strGroup)
        {
            m_UserGrop.erase(iter);
            m_UserGrop[nIndex] = strGroup;
            break;
        }
        iter++;
    }
    
    pthread_mutex_unlock(&m_pMutex);
    
    if(m_iMGetUserGroupInfo!=nil)
        [m_iMGetUserGroupInfo OnUpdateGroupIndex:strGroup nIndex:nIndex];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnGroupDelete(const std::string& strGroup)
{
    (void)pthread_mutex_lock(&m_pMutex);
    
    unsigned int uiCount = 0;
    USERGROP::iterator iter = m_UserGrop.begin();
    while(iter!=m_UserGrop.end())
    {
        if(iter->second == strGroup)
        {
            uiCount = iter->first;
            m_UserGrop.erase(iter);
            break;
        }
        iter++;
    }
    pthread_mutex_unlock(&m_pMutex);
    
    if(m_iMGetUserGroupInfo!=nil)
        [m_iMGetUserGroupInfo OnDeleteGrop:strGroup nIndex:uiCount];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendItem(const IMS_CONTACT_ITEM& item)
{
    if(item.group.empty())
    {
        //assert(false);
        return ;
    }
    (void)pthread_mutex_lock(&m_pMutex);
    USERGROPUSER::iterator iter = m_UserGropUser.find(item.group);
    if(iter!=m_UserGropUser.end())
    {
        bool isfind = false;
        std::vector<std::string>::iterator it = iter->second.begin();
        while (it != iter->second.end())
        {
            if(item.userid == *it)
            {
                isfind = true;
                break;
            }
            it++;
        }
        if(!isfind)
            iter->second.push_back(item.userid);
    }
    else
    {
        std::vector<std::string> UserVector;
        UserVector.push_back(item.userid);
        m_UserGropUser[item.group] = UserVector;
    }
    pthread_mutex_unlock(&m_pMutex);
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendItemEnd(void)
{
	GetIMSSession().FetchOrgs("0000-00-00 00:00:00");
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerBeginGetUserInfo:CS_GETUSERINFO];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendInfo(const std::string& strFriendID)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendApply(const std::string& strFriendID, const std::string& strUserGroup)
{
    //OnFriendAdd
    (void)pthread_mutex_lock(&m_pMutex);
    USERGROPUSER::iterator iter = m_UserGropUser.find(strUserGroup);
    if(iter!=m_UserGropUser.end())
    {
        bool isfind = false;
        std::vector<std::string>::iterator it = iter->second.begin();
        while (it != iter->second.end())
        {
            if(strFriendID == *it)
            {
                isfind = true;
                break;
            }
            it++;
        }
        if(!isfind)
            iter->second.push_back(strFriendID);
    }
    else
    {
        std::vector<std::string> UserVector;
        UserVector.push_back(strFriendID);
        m_UserGropUser[strUserGroup] = UserVector;
    }
    pthread_mutex_unlock(&m_pMutex);
    if(m_iMGetUserFriendInfo!=nil)
        [m_iMGetUserFriendInfo OnFriendAdd:strUserGroup strUserId:strFriendID];
    //GetIMSSession().AdmitFriend(strFriendID);
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendAdmit(const std::string& strFriendID)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendUpdateGroup(const std::string& strFriendID,const std::string& strGroup)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnFriendDelete(const std::string& strUserGroup, const std::string& strFriendID)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERGROPUSER::iterator iter = m_UserGropUser.find(strUserGroup);
    if(iter!=m_UserGropUser.end())
    {
        std::vector<std::string>::iterator it = iter->second.begin();
        while (it != iter->second.end())
        {
            if(strFriendID == *it)
            {
                it = iter->second.erase(it);
            }
            else
                it++;
        }
    }
    pthread_mutex_unlock(&m_pMutex);
    if(m_iMGetUserFriendInfo!=nil)
        [m_iMGetUserFriendInfo OnFriendDelete:strUserGroup strUserId:strFriendID];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgListStart(void)
{
	m_ulTestTimeStamp = GetTimeStamp();
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgItem(const std::string& strOrgID,const std::string& strOrgName)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgItemEnd(void)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgDepartItem(const std::string& strOrgID,const std::string& strDepartID,const std::string& strDepartName,int nLevelID,const std::string& strUpgradeID,int nOrderID)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgDepartItemEnd(void)
{
    bool bIsInRoom = false;
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.find(m_strUserID);
    if(iter!=m_UserList.end())
    {
        bIsInRoom = iter->second.IsEnterRoom;
    }
    pthread_mutex_unlock(&m_pMutex);
    if(!bIsInRoom && m_isInRoom)
    {
        if(m_MMMeetingProtocol!=nil)
            [m_MMMeetingProtocol OnDestructionInterimMeetingInfo:m_strHostID ulRoomID:m_ulRoomId];
    }
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgDepartUserItem(const std::string& strOrgID,const std::string& strDepartID,const IMS_CONTACT_ITEM& item,int nOrderID)
{
    (void)pthread_mutex_lock(&m_pMutex);
    m_UserList[item.userid] = item;
    pthread_mutex_unlock(&m_pMutex);
}
void LoginServer::DeleteUser(const std::string& strUserID)
{
    std::string strUserGroup;
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator itr = m_UserList.find(strUserID);
    if(itr!=m_UserList.end())
    {
        m_UserList.erase(itr);
    }
    
    USERGROPUSER::iterator iter = m_UserGropUser.begin();
    if(iter!=m_UserGropUser.end())
    {
        std::vector<std::string>::iterator it = iter->second.begin();
        while (it != iter->second.end())
        {
            if(strUserID == *it)
            {
                strUserGroup = iter->first;
                it = iter->second.erase(it);
                if(m_iMGetUserFriendInfo!=nil&&!strUserGroup.empty())
                    [m_iMGetUserFriendInfo OnFriendDelete:strUserGroup strUserId:strUserID];

            }
            else
                it++;
        }
    }
    pthread_mutex_unlock(&m_pMutex);
}

std::string LoginServer::GetUserID() const
{
    return m_strUserID;
}

bool LoginServer::GetRoomUserList(std::vector<ROOMUSERINFO>&UserList)
{
    (void)pthread_mutex_lock(&m_pMutex);
    
    ROOMUSERLIST::iterator it= m_RoomUserList.find(this->GetRoomId());
    if(it == m_RoomUserList.end()) {
        //没找到
        pthread_mutex_unlock(&m_pMutex);
        return  false;
    }
    else
    {
        std::vector<ROOMUSERINFO>::iterator iter = it->second.UserList.begin();
        while (iter!=it->second.UserList.end()) {
          
            if(iter->bIsHost)
                UserList.insert(UserList.begin(), *iter);
            else
                UserList.push_back(*iter);
            
            iter++;
        }
        pthread_mutex_unlock(&m_pMutex);
        return true;
    }
}

void LoginServer::GetUserGropList(std::map<unsigned int,std::string>& UserGroup)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERGROP::iterator iter = m_UserGrop.begin();
    while(iter!=m_UserGrop.end())
    {
        UserGroup[iter->first] = iter->second;
        iter++;
    }
    pthread_mutex_unlock(&m_pMutex);
}

void LoginServer::GetUserFriendList(const std::string& strUserGroup, std::vector<std::string>& UserFriend)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERGROPUSER::iterator iter = m_UserGropUser.find(strUserGroup);
    if(iter!=m_UserGropUser.end())
    {
        std::vector<std::string> strUserList = iter->second;
        std::vector<std::string>::iterator it = strUserList.begin();
        while (it!=strUserList.end())
        {
            USERLSRT::iterator ir = m_UserList.find(*it);
            if(ir!=m_UserList.end())
            {
                if(ir->second.status=="online")
                {
                    UserFriend.push_back(*it);
                    it = strUserList.erase(it);
                    continue;
                }
            }
            it++;
        }
        
        it = strUserList.begin();
        while (it!=strUserList.end())
        {
            UserFriend.push_back(*it);
            it++;
        }
    }
    pthread_mutex_unlock(&m_pMutex);
}

unsigned int LoginServer::GetUserGropUserCount(std::string UserGropName)
{
    unsigned int iCount = 0;
    (void)pthread_mutex_lock(&m_pMutex);
    
    USERGROPUSER::iterator iter = m_UserGropUser.find(UserGropName);
    if(iter!=m_UserGropUser.end())
        iCount = iter->second.size();
    pthread_mutex_unlock(&m_pMutex);
    
    return iCount;
}

void LoginServer::GetUserList(std::list<std::string>&UserList)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.begin();
    while(iter!=m_UserList.end())
    {
        if(iter->second.status == "online")
        {
            UserList.push_back(iter->first);
        }
        ++iter;
    }
    pthread_mutex_unlock(&m_pMutex);
}

bool LoginServer::GetUserInfo(const std::string& strUserInfo,IMS_CONTACT_ITEM& mUserInfo)
{
    bool bIsFind = false;
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.find(strUserInfo);
    if(iter!=m_UserList.end())
    {
        mUserInfo = (IMS_CONTACT_ITEM)iter->second;
        bIsFind = true;
    }
    pthread_mutex_unlock(&m_pMutex);
    
    return bIsFind;
}
//---------------------------------------------------------------------------------------
void LoginServer::OnOrgDepartUserItemEnd(void)
{
    if(m_IMLoginInfo!=nil)
        [m_IMLoginInfo OnServerEndGetUserInfo];
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgDeleteItem(const std::string& strOrgID,const std::string& strDepartID,const std::string& strUserID)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgDeleteItemEnd(void)
{
}

//---------------------------------------------------------------------------------------
void LoginServer::OnOrgListEnd(const std::string& strUpdateTime)
{
	GetMMSSession().GetRoomList();
}

//---------------------------------------------------------------------------------------
void LoginServer::OnRoomListEnd(const std::string& strDomain)
{
}

bool LoginServer::AddUserGrop(const std::string& strGroup)
{
    unsigned int uiCount = 1;
    (void)pthread_mutex_lock(&m_pMutex);
    
    if(m_UserGrop.size()>0)
    {
        USERGROP::iterator iter = m_UserGrop.begin();
        while(iter!=m_UserGrop.end())
        {
            if(strGroup == iter->second)
            {
                pthread_mutex_unlock(&m_pMutex);
                return false;
            }
            iter++;
        }
        
        iter=m_UserGrop.end();
        iter--;
        uiCount = iter->first+1;
    }
    pthread_mutex_unlock(&m_pMutex);
    
    GetIMSSession().InsertGroup(strGroup, uiCount);
    return true;
}

bool LoginServer::AddUserFriend(const std::string& strUserGroup, const std::string& strUserFriend)
{
    bool bValue = false;
    (void)pthread_mutex_lock(&m_pMutex);
    USERGROPUSER::iterator iter = m_UserGropUser.find(strUserGroup);
    if(iter!=m_UserGropUser.end())
    {
        std::vector<std::string>::iterator it = iter->second.begin();
        while (it != iter->second.end())
        {
            if(*it == strUserFriend)
            {
                bValue = true;
                break;
            }
            it++;
        }
    }
    pthread_mutex_unlock(&m_pMutex);
    if(!bValue)
    {
        GetIMSSession().ApplyFriend(strUserGroup, strUserFriend);
        return true;
    }
    return false;
}

bool LoginServer::DeleteUserFriend(const std::string& strUserGroup, const std::string& strUserFriend)
{
    GetIMSSession().DeleteFriend(strUserGroup, strUserFriend);
    return true;
}

int LoginServer::UserGropUpdateName(const std::string& strOldGroup, const std::string& strNewGroup)
{
    if(strOldGroup.empty()||strNewGroup.empty())
        return 0;
    
    bool IsFount = false;
    
    (void)pthread_mutex_lock(&m_pMutex);
    if(m_UserGrop.size()>0)
    {
        USERGROP::iterator iter = m_UserGrop.begin();
        while(iter!=m_UserGrop.end())
        {
            if(strOldGroup == iter->second)
            {
                IsFount = true;
                break;
            }
            iter++;
        }
    }
    
    if(!IsFount)
    {
        pthread_mutex_unlock(&m_pMutex);
        return -1;
    }
    
    IsFount = false;
    
    USERGROP::iterator iter = m_UserGrop.begin();
    while(iter!=m_UserGrop.end())
    {
        if(strNewGroup == iter->second)
        {
            IsFount = true;
            break;
        }
        iter++;
    }
    
    if(IsFount)
    {
        pthread_mutex_unlock(&m_pMutex);
        return -2;
    }
    
    USERGROPUSER::iterator it = m_UserGropUser.find(strOldGroup);
    if(it!=m_UserGropUser.end())
    {
        m_UserGropUser[strNewGroup] = it->second;
    }
    
    it = m_UserGropUser.find(strOldGroup);
    if(it!=m_UserGropUser.end())
    {
        m_UserGropUser.erase(it);
    }
    
    pthread_mutex_unlock(&m_pMutex);
    
    GetIMSSession().UpdateGroupName(strOldGroup, strNewGroup);
    
    return 1;
}

bool LoginServer::DeleteUserGrop(const std::string& strGroup)
{
    if(strGroup.empty())
        return false;
    
    GetIMSSession().DeleteGroup(strGroup);
    
    return true;
}

void LoginServer::OnSetMeetingType(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiType)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnSetMeetingType(strUserID, ulRoomID, uiType);
    }
}

void LoginServer::OnInviteUser(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.find(strPeerUserID);
    if(iter != m_UserList.end())
    {
        ROOMUSERLIST::iterator it = m_RoomUserList.find(ulRoomID);
        if(it != m_RoomUserList.end())
        {
            bool isfind = false;
            std::vector<ROOMUSERINFO>::iterator itn = it->second.UserList.begin();
            while (itn != it->second.UserList.end())
            {
                if(strPeerUserID == itn->strUserID)
                {
                    itn->bIsEnterRoom = false;
                    isfind = true;
                    break;
                }
                itn++;
            }
            if(!isfind)
            {
                ROOMUSERINFO mROOMUSERINFO;
                mROOMUSERINFO.strUserID = strPeerUserID;
                mROOMUSERINFO.bIsHost = false;
                mROOMUSERINFO.bIsEnterRoom = false;
                mROOMUSERINFO.bIsInRoom = false;
                it->second.UserList.push_back(mROOMUSERINFO);
            }
        }
        
        GetIMSSession().OnInviteUser(ulRoomID, strPeerUserID);
    }
    pthread_mutex_unlock(&m_pMutex);
}

void LoginServer::OnReplyInviteUser(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID,bool bIsAgree)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.find(strPeerUserID);
    if(iter != m_UserList.end())
    {
        GetIMSSession().OnReplyInviteUser(strPeerUserID, ulRoomID, bIsAgree);
    }
    pthread_mutex_unlock(&m_pMutex);
}

void LoginServer::OnForTheFloor(const std::string& strUserID, unsigned long ulRoomID, const std::string& strHostID)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnForTheFloor(strUserID, ulRoomID, strHostID);
    }
}

void LoginServer::OnPleaseOutTemporaryMeeting(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnPleaseOutTemporaryMeeting(strHostID, ulRoomID, strUserID);
    }
}

void LoginServer::OnPassPrivileges(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnPassPrivileges(strHostID, ulRoomID, strUserID);
    }
}

void LoginServer::OnUserSnedMsg(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, std::string& ulUserMsg, bool bIsBroadcast)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnUserSnedMsg(strUserID, ulRoomID, strPeerUserID, ulUserMsg, bIsBroadcast);
    }
}

void LoginServer::OnOpenPeerUserAudio(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserAudioID, bool bIsBroadcast)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnOpenPeerUserAudio(strUserID, ulRoomID, strPeerUserID, ulUserAudioID, bIsBroadcast);
    }
}

void LoginServer::OnOpenPeerUserVideo(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserVideoID, unsigned int uiScreenControl, bool bIsBroadcast)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        printf("[1]OnOpenPeerUserVideo strUserID=%s ulRoomID =%ld strPeerUserID = %s\n",strUserID.c_str(), ulRoomID,strPeerUserID.c_str());
        GetIMSSession().OnOpenPeerUserVideo(strUserID, ulRoomID, strPeerUserID, ulUserVideoID, uiScreenControl, bIsBroadcast);
    }
}

void LoginServer::OnClosePeerUserAudio(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserAudioID, bool bIsBroadcast)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnClosePeerUserAudio(strUserID, ulRoomID, strPeerUserID, ulUserAudioID, bIsBroadcast);
    }
}

void LoginServer::OnClosePeerUserVideo(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, unsigned long ulUserVideoID, bool bIsBroadcast)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnClosePeerUserVideo(strUserID, ulRoomID, strPeerUserID, ulUserVideoID, bIsBroadcast);
    }
}

void LoginServer::OnInitializationTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount, unsigned int uiVideoType, unsigned int uiAudioType)
{
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnInitializationTemporaryMeeting(strUserID, ulRoomID, uiScreenCount, uiVideoType, uiAudioType);
    }
}

void LoginServer::OnScreenControl(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount)
{
    m_ulScreenControl = uiScreenCount;
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        GetIMSSession().OnScreenControl(strUserID, ulRoomID, uiScreenCount);
    }
}

void LoginServer::QuitTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID)
{
    GetIMSSession().QuitTemporaryMeeting(strUserID, ulRoomID);
    KillTimerEvent(m_nTimerID);
}

void LoginServer::JoinTemporaryMeeting(const std::string& strUserID, const std::string& strPeerUserID, unsigned long ulRoomID)
{
    GetIMSSession().JoinTemporaryMeeting(strUserID, strPeerUserID, ulRoomID);
}

void LoginServer::CreateTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID , unsigned int uiRoomType)
{
    ROOMUSERINFO mROOMUSERINFO;
    mROOMUSERINFO.strUserID = strUserID;
    mROOMUSERINFO.bIsHost = true;
    mROOMUSERINFO.bIsInRoom = true;
    mROOMUSERINFO.bIsEnterRoom = true;
    
    ROOMINFO mROOMINFO;
    mROOMINFO.strHostID = strUserID;
    mROOMINFO.ulRoomId = ulRoomID;
    mROOMINFO.UserList.push_back(mROOMUSERINFO);
    mROOMINFO.uiRoomType = uiRoomType;
    m_uiRoomType = uiRoomType;
    m_ulRoomId = ulRoomID;
    m_RoomUserList[ulRoomID] = mROOMINFO;
    GetIMSSession().OnCreateInterimMeeting(strUserID, ulRoomID, uiRoomType);
}
 void LoginServer::DestructionTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID)
{
    GetIMSSession().OnDestructionInterimMeeting(strUserID, ulRoomID);
}

void LoginServer::CallbackCreateInterimMeeting(const std::string& strHostID, unsigned long ulRoomID , unsigned int uiRoomType)
{
    if(m_strUserID == strHostID)
    {
        m_isInRoom = true;
        m_bIsChairman = true;
    }
    
    m_strHostID = strHostID;
    
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.find(strHostID);
    if(iter!=m_UserList.end())
    {
        iter->second.IsEnterRoom = true;
    }
    pthread_mutex_unlock(&m_pMutex);
    
    ROOMUSERLIST::iterator it = m_RoomUserList.find(ulRoomID);
    if(it==m_RoomUserList.end())
    {
        ROOMUSERINFO mROOMUSERINFO;
        mROOMUSERINFO.strUserID = strHostID;
        mROOMUSERINFO.bIsHost = true;
        mROOMUSERINFO.bIsInRoom = true;
        mROOMUSERINFO.bIsEnterRoom = true;
    
        ROOMINFO mROOMINFO;
        mROOMINFO.strHostID = strHostID;
        mROOMINFO.ulRoomId = ulRoomID;
        mROOMINFO.UserList.push_back(mROOMUSERINFO);
        mROOMINFO.uiRoomType = uiRoomType;
        m_uiRoomType = uiRoomType;
        m_ulRoomId = ulRoomID;
        m_RoomUserList[ulRoomID] = mROOMINFO;
    }
    m_RoomInfoMap.clear();
    m_VideoinfoMap.clear();
    
    m_ulCount = 0;
    SetTimerEvent(m_nTimerID,2000);
    
    if(m_MMMeetingProtocol)
        [m_MMMeetingProtocol OnCreateInterimMeeting:strHostID ulRoomID:ulRoomID uiRoomType:uiRoomType];
}

void LoginServer::CallbackJoinTemporaryMeeting(const std::string& strUserID,  unsigned long ulRoomID)
{
    (void)pthread_mutex_lock(&m_pMutex);
    USERLSRT::iterator iter = m_UserList.find(strUserID);
    if(iter!=m_UserList.end())
    {
        iter->second.IsEnterRoom = true;
    }
    
    ROOMUSERLIST::iterator it = m_RoomUserList.find(ulRoomID);
    if(it != m_RoomUserList.end())
    {
        bool isfind = false;
        std::vector<ROOMUSERINFO>::iterator itn = it->second.UserList.begin();
        while (itn != it->second.UserList.end())
        {
            if(strUserID == itn->strUserID)
            {
                itn->bIsEnterRoom = true;
                itn->bIsInRoom = true;
                isfind = true;
                break;
            }
            itn++;
        }
        if(!isfind)
        {
            ROOMUSERINFO mROOMUSERINFO;
            mROOMUSERINFO.strUserID = strUserID;
            mROOMUSERINFO.bIsHost = false;
            mROOMUSERINFO.bIsEnterRoom = true;
            mROOMUSERINFO.bIsInRoom = true;
            it->second.UserList.push_back(mROOMUSERINFO);
        }
    }
    
    pthread_mutex_unlock(&m_pMutex);
    
    if(m_strUserID == strUserID)
    {
        if(m_bIsChairman)
            return;
        
        m_isInRoom = true;
        m_RoomInfoMap.clear();
        m_VideoinfoMap.clear();
        m_ulCount = 0;
        SetTimerEvent(m_nTimerID,2000);
        if(m_MMMeetingProtocol)
            [m_MMMeetingProtocol OnEnterInterimMeetingInfo:ulRoomID];
    }
    else
    {
        if(m_MMMeetingProtocol)
            [m_MMMeetingProtocol OnJoinTemporaryMeeting:strUserID ulRoomID:ulRoomID];
        if(m_iMGetUserFriendInfo)
            [m_iMGetUserFriendInfo OnFriendEnterInterimMeeting:strUserID ulRoomID:ulRoomID];
    }
}

unsigned int LoginServer::GetRoomType() const
{
    return m_uiRoomType;
}

unsigned long LoginServer::GetRoomId() const
{
    return m_ulRoomId;
}

unsigned long LoginServer::GetLocalVideoId() const
{
    return m_ulMediaId;
}

unsigned long LoginServer::GetLocalAudioId() const
{
    return m_ulMediaId+100;
}

unsigned long LoginServer::GetScreenControl() const
{
    return m_ulScreenControl;
}

unsigned long LoginServer::GetPeerUserVideoId(const std::string strUserId)
{
    unsigned long ulMediaId = 0;
    
    (void)pthread_mutex_lock(&m_pMutex);
    
    USERLSRT::iterator iter = m_UserList.begin();
    
    while(iter!=m_UserList.end())
    {
        if(iter->first == strUserId)
        {
            ulMediaId = iter->second.ulMediaId;
            break;
        }
        ++iter;
    }
    pthread_mutex_unlock(&m_pMutex);
    
    return ulMediaId;
}

unsigned long LoginServer::GetPeerUserAudioId(const std::string strUserId)
{
    unsigned long ulMediaId = 0;
    
    (void)pthread_mutex_lock(&m_pMutex);
    
    USERLSRT::iterator iter = m_UserList.begin();
    
    while(iter!=m_UserList.end())
    {
        if(iter->first == strUserId)
        {
            ulMediaId = iter->second.ulMediaId;
            break;
        }
        ++iter;
    }
    pthread_mutex_unlock(&m_pMutex);
    
    return ulMediaId+100;
}

void LoginServer::CallbackMeetingUserInfo(const std::string& strHostID, unsigned long ulRoomID , unsigned int uiRoomType, std::vector<std::string>& vQuitUser)
{
    m_strHostID = strHostID;
    m_bIsChairman = false;
    
    ROOMINFO mROOMINFO;
    mROOMINFO.strHostID = strHostID;
    mROOMINFO.ulRoomId = ulRoomID;
    
    std::vector<std::string>::iterator iter = vQuitUser.begin();
    while (iter!=vQuitUser.end()) {
        
        ROOMUSERINFO mROOMUSERINFO;
        mROOMUSERINFO.strUserID = *iter;
        if(*iter == strHostID)
            mROOMUSERINFO.bIsHost = true;
        mROOMUSERINFO.bIsEnterRoom = true;
        mROOMUSERINFO.bIsInRoom = true;
        
        mROOMINFO.UserList.push_back(mROOMUSERINFO);
        iter++;
    }
    mROOMINFO.uiRoomType = uiRoomType;
    m_uiRoomType = uiRoomType;
    m_ulRoomId = ulRoomID;
    m_RoomUserList[ulRoomID] = mROOMINFO;
}

void LoginServer::CallbackDestructionInterimMeeting(const std::string& strHostID, unsigned long ulRoomID, std::vector<std::string>& vQuitUser)
{
    std::vector<std::string>::iterator it = vQuitUser.begin();
    while(it != vQuitUser.end())
    {
        std::string strUserID = *it;
        USERLSRT::iterator eit = m_UserList.find(strUserID);
        if(eit != m_UserList.end())
        {
            eit->second.IsEnterRoom = false;
            if(m_iMGetUserFriendInfo)
                [m_iMGetUserFriendInfo OnFriendQuitInterimMeeting:strUserID ulRoomID:ulRoomID];
        }
        it++;
    }
    m_uiRoomType = Room_No;
    m_bIsChairman = false;
    m_ulRoomId = 0;
    m_strHostID = "";
    m_isInRoom = false;
    
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        m_RoomUserList.erase(iter);
    }
    m_RoomInfoMap.clear();
    m_VideoinfoMap.clear();
    m_ulCount = 0;
    KillTimerEvent(m_nTimerID);
    if(m_MMMeetingProtocol!=nil)
        [m_MMMeetingProtocol OnDestructionInterimMeetingInfo:strHostID ulRoomID:ulRoomID];
}

void LoginServer::SetInformationStateQueue(bool b)
{
    m_SetInfoStateQueue = b;
}

void LoginServer::CallbackOpenPeerUserVideo(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserVideoID, unsigned long ulScreeCount)
{
    if(m_MMGetRoomControl!=nil)
    {
        if(!m_SetInfoStateQueue)
        {
            (void)pthread_mutex_lock(&m_pMutexQueue);
            USERROOMINFO mUserRoomInfo;
            mUserRoomInfo.strPeerID = strPeerID;
            mUserRoomInfo.ulRoomID = ulRoomID;
            mUserRoomInfo.ulPeerMediaId = ulPeerUserVideoID;
            mUserRoomInfo.uiScreenCount = ulScreeCount;
            mUserRoomInfo.uiInfoType = ROOM_Info_OpenVideo;
            m_VideoinfoMap[m_ulCount++] = mUserRoomInfo;
            pthread_mutex_unlock(&m_pMutexQueue);
        }
        else
        {
            [m_MMGetRoomControl OnOpenUserVideo:strFromUserID strUserId:strPeerID ulRoomID:ulRoomID ulUserVideoID:ulPeerUserVideoID uiScreenControl:ulScreeCount];
        }
    }
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.strPeerID = strPeerID;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.ulPeerMediaId = ulPeerUserVideoID;
        mUserRoomInfo.uiInfoType = ROOM_Info_OpenVideo;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackClosePeerUserVideo(const std::string& strFromUserID, const std::string& strPeerID, unsigned long ulRoomID,  unsigned long ulPeerUserVideoID)
{
    if(m_MMGetRoomControl!=nil)
    {
        if(!m_SetInfoStateQueue)
        {
            (void)pthread_mutex_lock(&m_pMutexQueue);
            USERROOMINFO mUserRoomInfo;
            mUserRoomInfo.strUserID = strFromUserID;
            mUserRoomInfo.strPeerID = strPeerID;
            mUserRoomInfo.ulRoomID = ulRoomID;
            mUserRoomInfo.ulPeerMediaId = ulPeerUserVideoID;
            mUserRoomInfo.uiInfoType = ROOM_Info_CloseVideo;
            m_VideoinfoMap[m_ulCount++] = mUserRoomInfo;
            pthread_mutex_unlock(&m_pMutexQueue);
        }
        else
        {
            [m_MMGetRoomControl OnCloseUserVideo:strFromUserID strUserId:strPeerID ulRoomID:ulRoomID ulUserVideoID:ulPeerUserVideoID];
        }
    }
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.strUserID = strFromUserID;
        mUserRoomInfo.strPeerID = strPeerID;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.ulPeerMediaId = ulPeerUserVideoID;
        mUserRoomInfo.uiInfoType = ROOM_Info_CloseVideo;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackOpenPeerUserAudio(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserAudioID)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnOpenUserAudio:strFromUserID strUserId:strPeerID ulRoomID:ulRoomID ulUserAudioID:ulPeerUserAudioID];
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.strUserID = strFromUserID;
        mUserRoomInfo.strPeerID = strPeerID;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.ulPeerMediaId = ulPeerUserAudioID;
        mUserRoomInfo.uiInfoType = ROOM_Info_OpenAudio;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackInitializationTemporaryMeeting(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount, unsigned int uiVideoType, unsigned int uiAudioType)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnInitializationTemporaryMeeting:strUserID ulRoomID:ulRoomID uiScreenCount:uiScreenCount uiVideoType:uiVideoType uiAudioType:uiAudioType];
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.strUserID = strUserID;
        mUserRoomInfo.strPeerID = strUserID;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.uiScreenCount = uiScreenCount;
        mUserRoomInfo.uiVideoType = uiVideoType;
        mUserRoomInfo.uiAudioType = uiAudioType;
        mUserRoomInfo.uiInfoType = Room_Info_Initialization;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackClosePeerUserAudio(const std::string& strFromUserID, const std::string& strPeerID,  unsigned long ulRoomID,  unsigned long ulPeerUserAudioID)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnCloseUserAudio:strFromUserID strUserId:strPeerID ulRoomID:ulRoomID ulUserAudioID:ulPeerUserAudioID];
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.strUserID = strFromUserID;
        mUserRoomInfo.strPeerID = strPeerID;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.ulPeerMediaId = ulPeerUserAudioID;
        mUserRoomInfo.uiInfoType = ROOM_Info_CloseAudio;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackSetMeetingType( unsigned long ulRoomID,unsigned int uiType)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnMeetingType:ulRoomID uiType:uiType];
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.uiRoomType = uiType;
        mUserRoomInfo.uiInfoType = ROOM_Info_SetType;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackOnScreenControl(const std::string& strUserID, unsigned long ulRoomID, unsigned int uiScreenCount)
{
    m_ulScreenControl = uiScreenCount;
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnScreenControl:strUserID ulRoomID:ulRoomID uiScreenCount:uiScreenCount];
    else
    {
        (void)pthread_mutex_lock(&m_pMutexQueue);
        USERROOMINFO mUserRoomInfo;
        mUserRoomInfo.strUserID = strUserID;
        mUserRoomInfo.ulRoomID = ulRoomID;
        mUserRoomInfo.uiRoomScreen = uiScreenCount;
        mUserRoomInfo.uiInfoType = ROOM_Info_Screen;
        m_RoomInfoMap[m_ulCount++] = mUserRoomInfo;
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

void LoginServer::CallbackInviteUser(const std::string& strUserID, unsigned long ulRoomID)
{
    if(m_MMMeetingProtocol!=nil)
        [m_MMMeetingProtocol OnHostInviteUser:strUserID ulRoomID:ulRoomID];
}

void LoginServer::CallbackReplyInviteUser(const std::string& strUserID, unsigned long ulRoomID,bool bIsAgree)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnUserReplyInviteUser:strUserID ulRoomID:ulRoomID bIsAgree:bIsAgree];
}

void LoginServer::CallbackForTheFloor(const std::string& strUserID, unsigned long ulRoomID, const std::string& strHostID)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnForTheFloor:strUserID ulRoomID:ulRoomID strHostID:strHostID];
}

void LoginServer::CallbackPleaseOutTemporaryMeeting(const std::string& strHostID, unsigned long ulRoomID, const std::string& strUserID)
{
    USERLSRT::iterator eit = m_UserList.find(strUserID);
    if(eit != m_UserList.end())
    {
        eit->second.IsEnterRoom = false;
    }
    
    if(m_strUserID == strUserID)
    {
        m_strHostID = "";
        m_isInRoom = false;
    }
    
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        std::vector<ROOMUSERINFO>::iterator it = iter->second.UserList.begin();
        while(it!=iter->second.UserList.end())
        {
            if(it->strUserID == strUserID)
            {
                //iter->second.UserList.erase(it);
                it->bIsInRoom = false;
                break;
            }
            it++;
        }
    }
    if(m_MMMeetingProtocol)
    {
        [m_MMMeetingProtocol OnPleaseOutTemporaryMeeting:strHostID ulRoomID:ulRoomID strUserID:strUserID];
        [m_MMMeetingProtocol OnQuitInterimMeetingInfo:strUserID ulRoomID:ulRoomID];

    }
    if(m_iMGetUserFriendInfo)
        [m_iMGetUserFriendInfo OnFriendQuitInterimMeeting:strUserID ulRoomID:ulRoomID];
}

void LoginServer::CallbackPassPrivileges(const std::string& strHostID, unsigned long ulRoomID)
{
    (void)pthread_mutex_lock(&m_pMutex);
    
    m_strHostID = strHostID;
    
    if(strHostID==GetUserID())
    {
        m_bIsChairman = true;
    }
    else
        m_bIsChairman = false;
    
    ROOMUSERLIST::iterator it = m_RoomUserList.find(ulRoomID);
    if(it != m_RoomUserList.end())
    {
        it->second.strHostID = strHostID;
        std::vector<ROOMUSERINFO>::iterator itn = it->second.UserList.begin();
        while (itn != it->second.UserList.end())
        {
            if(strHostID == itn->strUserID)
            {
                itn->bIsHost = true;
            }
            else
            {
                itn->bIsHost = false;
            }
            itn++;
        }
    }
    
    pthread_mutex_unlock(&m_pMutex);
    
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnPassPrivileges:strHostID ulRoomID:ulRoomID];
}

void LoginServer::CallbackUserSnedMsg(const std::string& strUserID, unsigned long ulRoomID, const std::string& strPeerUserID, std::string& ulUserMsg)
{
    if(m_MMGetRoomControl!=nil)
        [m_MMGetRoomControl OnUserSnedMsg:strUserID ulRoomID:ulRoomID strPeerUserID:strPeerUserID ulUserMsg:ulUserMsg];
}

void LoginServer::CallbackQuitTemporaryMeeting(const std::string& strUserID,  unsigned long ulRoomID)
{
    USERLSRT::iterator eit = m_UserList.find(strUserID);
    if(eit != m_UserList.end())
    {
        eit->second.IsEnterRoom = false;
    }
    
    if(m_strUserID == strUserID)
    {
        m_strHostID = "";
        m_isInRoom = false;
    }
    
    ROOMUSERLIST::iterator iter = m_RoomUserList.find(ulRoomID);
    if(iter != m_RoomUserList.end())
    {
        std::vector<ROOMUSERINFO>::iterator it = iter->second.UserList.begin();
        while(it!=iter->second.UserList.end())
        {
            if(it->strUserID == strUserID)
            {
                //iter->second.UserList.erase(it);
                it->bIsInRoom = false;
                break;
            }
            it++;
        }
    }
    if(m_MMMeetingProtocol)
    {
        [m_MMMeetingProtocol OnQuitInterimMeetingInfo:strUserID ulRoomID:ulRoomID];
    }
    if(m_iMGetUserFriendInfo)
        [m_iMGetUserFriendInfo OnFriendQuitInterimMeeting:strUserID ulRoomID:ulRoomID];
}

unsigned long LoginServer::XGetTimestamp()
{
#ifdef WIN32
	return ::timeGetTime();
#else
	struct timeval now;
	gettimeofday(&now,NULL);
	return now.tv_sec*1000+now.tv_usec/1000;
#endif
}

void LoginServer::OnTimerEvent(unsigned int nEventID)
{
    if(nEventID == 2)
    {
        if(m_Connecting && (XGetTimestamp() - m_ulConnectTime > 10000))
        {
            if(m_IMLoginInfo!=nil)
                [m_IMLoginInfo OnServerConnectingOutTime];
            m_Connecting = false;
        }
    }
    else if(nEventID == m_nTimerID)
    {
    
    (void)pthread_mutex_lock(&m_pMutexQueue);
    ROOMINFOMAP::iterator iter = m_RoomInfoMap.begin();
    while(iter != m_RoomInfoMap.end())
    {
        switch (iter->second.uiInfoType) {
                
            case Room_Info_Initialization:
            {
                if(m_MMGetRoomControl!=nil)
                    [m_MMGetRoomControl OnInitializationTemporaryMeeting:iter->second.strUserID ulRoomID:iter->second.ulRoomID uiScreenCount:iter->second.uiScreenCount uiVideoType:iter->second.uiVideoType uiAudioType:iter->second.uiAudioType];
                m_RoomInfoMap.erase(iter);
                iter = m_RoomInfoMap.begin();
                continue;
            }
                break;
            case ROOM_Info_OpenVideo:
            {
                if(m_MMGetRoomControl!=nil)
                {
                    [m_MMGetRoomControl OnOpenUserVideo:iter->second.strUserID strUserId:iter->second.strPeerID ulRoomID:iter->second.ulRoomID ulUserVideoID:iter->second.ulPeerMediaId  uiScreenControl:iter->second.uiScreenCount];
                    m_RoomInfoMap.erase(iter);
                    iter = m_RoomInfoMap.begin();
                    continue;
                }
            }
                break;
            case ROOM_Info_CloseVideo:
            {
                if(m_MMGetRoomControl!=nil)
                {
                    [m_MMGetRoomControl OnCloseUserVideo:iter->second.strUserID strUserId:iter->second.strPeerID ulRoomID:iter->second.ulRoomID ulUserVideoID:iter->second.ulPeerMediaId];
                    m_RoomInfoMap.erase(iter);
                    iter = m_RoomInfoMap.begin();
                    continue;
                }
            }
                break;
            case ROOM_Info_OpenAudio:
            {
                if(m_MMGetRoomControl!=nil)
                {
                    [m_MMGetRoomControl OnOpenUserAudio:iter->second.strUserID strUserId:iter->second.strPeerID ulRoomID:iter->second.ulRoomID ulUserAudioID:iter->second.ulPeerMediaId];
                    m_RoomInfoMap.erase(iter);
                    iter = m_RoomInfoMap.begin();
                    continue;
                }
            }
                break;
            case ROOM_Info_CloseAudio:
            {
                if(m_MMGetRoomControl!=nil)
                {
                    [m_MMGetRoomControl OnCloseUserAudio:iter->second.strUserID strUserId:iter->second.strPeerID ulRoomID:iter->second.ulRoomID ulUserAudioID:iter->second.ulPeerMediaId];
                    m_RoomInfoMap.erase(iter);
                    iter = m_RoomInfoMap.begin();
                    continue;
                }
            }
                break;
            case ROOM_Info_SetType:
            {
                if(m_MMGetRoomControl!=nil)
                {
                    [m_MMGetRoomControl OnMeetingType:iter->second.ulRoomID  uiType:iter->second.uiRoomType];
                    m_RoomInfoMap.erase(iter);
                    iter = m_RoomInfoMap.begin();
                    continue;
                }
            }
            case ROOM_Info_Screen:
            {
                if(m_MMGetRoomControl!=nil)
                {
                    [m_MMGetRoomControl OnScreenControl:iter->second.strUserID ulRoomID:iter->second.ulRoomID uiScreenCount:iter->second.uiRoomScreen];
                    m_RoomInfoMap.erase(iter);
                    iter = m_RoomInfoMap.begin();
                    continue;
                }
            }
                break;
            default:
                break;
        }
        iter++;
    }
    
    ROOMINFOMAP::iterator it = m_VideoinfoMap.begin();
    while (it!=m_VideoinfoMap.end()) {
     
        switch (it->second.uiInfoType)
        {
            case ROOM_Info_OpenVideo:
            {
                if(m_MMGetRoomControl!=nil && m_SetInfoStateQueue)
                {
                    [m_MMGetRoomControl OnOpenUserVideo:it->second.strUserID strUserId:it->second.strPeerID ulRoomID:it->second.ulRoomID ulUserVideoID:it->second.ulPeerMediaId uiScreenControl:it->second.uiScreenCount];
                    m_VideoinfoMap.erase(it);
                    it = m_VideoinfoMap.begin();
                continue;
                }
            }
                break;
            case ROOM_Info_CloseVideo:
            {
                if(m_MMGetRoomControl!=nil && m_SetInfoStateQueue)
                {
                    [m_MMGetRoomControl OnCloseUserVideo:it->second.strUserID strUserId:it->second.strPeerID ulRoomID:it->second.ulRoomID ulUserVideoID:it->second.ulPeerMediaId];
                    m_VideoinfoMap.erase(it);
                    it = m_VideoinfoMap.begin();
                    continue;
                }
            }
                break;
        }
        it++;
    }
    
        pthread_mutex_unlock(&m_pMutexQueue);
    }
}

