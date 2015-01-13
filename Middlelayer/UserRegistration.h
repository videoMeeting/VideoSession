#pragma once
#include "cmdtcpclient.h"

typedef enum{
	C_CONNECTING=1,           //登陆服务器
	C_FAILED,		    //正在登陆服务器
	C_CONNECTED,			//无法登陆服务器
	C_ADDUSERExist,
    C_ADDUSEROK,
    C_DELETEUSERNTExist,
    C_DELETEUserPasswordErro,
    C_DELETEUSEROK,
    C_DATAERR,
}LOGINSEVER_STATUS;

typedef struct _CLIENTUSERINFOLIST
{
	std::string strUserName;
	unsigned long ulUserId;
	unsigned long ulUertVideoID;

}CLIENTUSERINFOLIST;

typedef std::map<std::string, CLIENTUSERINFOLIST> CLIENTUSERINFOLIST_MAP;

@protocol RegistrationInfo
-(void) OnServerConnectingInfo:(unsigned int)errorid;
-(void) OnAddUserInfo:(unsigned int)errorid;
-(void) OnDeleteUserInfo:(unsigned int)errorid;
@end

class UserRegistration
	: public CmdTCPClientCallback
{
public:
	UserRegistration();	// 标准构造函数
	virtual ~UserRegistration();
public:
	virtual void On_SessionConnectStatus(CONNECT_STATUS cs);
	virtual void OnDispatchCmd(KCmdPacketEx& pPacket);
public:
	void StaticConnectSever(const char* czsip, unsigned int uiPort);
	void StopConnectSever();
public:
    bool AddUser(std::string strUserName, std::string strPassword, std::string strNickname, std::string strPhone, std::string strRemark);
    bool DeleteUser(std::string strUserName, std::string strPassword);
private:
	CmdTCPClient        m_CmdTCPClient;
	CONNECT_STATUS      m_ConnectStatus;
	LOGINSEVER_STATUS   m_LoginSever;
	bool                m_IsLoginSever;
	unsigned long       m_SetTimerID;
	CLIENTUSERINFOLIST_MAP m_UserInfoList;
	unsigned long       m_UserID;
	std::string         m_LocalUserName;
public:
    id<RegistrationInfo>  m_RegistrationInfo;
};
