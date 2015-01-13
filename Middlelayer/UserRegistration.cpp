#include "UserRegistration.h"
#include "WYBASE/MD5.h"

UserRegistration::UserRegistration()
:m_UserID(0)
, m_IsLoginSever(false)
{
}

UserRegistration::~UserRegistration()
{
}

void UserRegistration::StaticConnectSever(const char* czsip, unsigned int uiPort)
{
	assert(czsip);

	m_CmdTCPClient.startClient(czsip,uiPort,this);
}
void UserRegistration::StopConnectSever()
{
	m_CmdTCPClient.stopClient();
}

void UserRegistration::On_SessionConnectStatus(CONNECT_STATUS cs)
{
	char szText[1024]="";
	switch (cs)
	{
	case CS_CONNECTING:
        {
            if(m_RegistrationInfo!=nil)
                [m_RegistrationInfo OnServerConnectingInfo:C_CONNECTING];
            strcpy(szText,"Connecting...");
        }
		break;
	case CS_FAILED:
        {
            if(m_RegistrationInfo!=nil)
                [m_RegistrationInfo OnServerConnectingInfo:C_FAILED];
            strcpy(szText,"Failed");
        }
		break;
	case CS_DISCONNECTED:
		strcpy(szText,"Disconnected");
		break;
	case CS_CONNECTED:
        {
            if(m_RegistrationInfo!=nil)
                [m_RegistrationInfo OnServerConnectingInfo:C_CONNECTED];
            m_IsLoginSever = true;
            strcpy(szText,"Connected");
        }
		break;
	case CS_BUSY:
		strcpy(szText,"Busy");
		break;
	case CS_RECONNECTED:
		strcpy(szText,"Reconnected");
		break;
	case CS_RESTARTED:
		strcpy(szText,"Restarted");
		break;
	default:
		strcpy(szText,"Unkown");
		break;
	}
	printf("%s\n",szText);

	m_ConnectStatus = cs;
}

void UserRegistration::OnDispatchCmd(KCmdPacketEx& pPacket)
{
	std::string strCMD = pPacket.GetCMD();
	std::string strData = pPacket.GetString();
	printf("Get TCP Server Packet packet Value = '%s'\n" ,strData.c_str());

	if(strCMD=="ADDUSER")
	{
        int ulErrorType = pPacket.GetAttrib("ERRORTYPE").AsUnsignedLong();
        switch (ulErrorType)
        {
            case C_ADDUSERExist:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnAddUserInfo:C_ADDUSERExist];
            }
                break;
            case C_ADDUSEROK:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnAddUserInfo:C_ADDUSEROK];
            }
                break;
            case C_DATAERR:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnDeleteUserInfo:C_DATAERR];
            }
                break;
        }
	}
	else if(strCMD=="DELETEUSER")
	{
		int ulErrorType = pPacket.GetAttrib("ERRORTYPE").AsUnsignedLong();
        switch (ulErrorType)
        {
            case C_DELETEUSERNTExist:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnDeleteUserInfo:C_DELETEUSERNTExist];
            }
                break;
            case C_DELETEUserPasswordErro:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnDeleteUserInfo:C_DELETEUserPasswordErro];
            }
                break;
            case C_DELETEUSEROK:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnDeleteUserInfo:C_DELETEUSEROK];
            }
                break;
            case C_DATAERR:
            {
                if(m_RegistrationInfo!=nil)
                    [m_RegistrationInfo OnDeleteUserInfo:C_DATAERR];
            }
                break;
        }
	}
}

bool UserRegistration::AddUser(std::string strUserName, std::string strPassword, std::string strNickname, std::string strPhone, std::string strRemark)
{
    if(!m_IsLoginSever)
        return false;
    
    std::string strLogin = "AddUser";
    KCmdPacketEx rPacket(strLogin.c_str(),(int)strLogin.length()+1);
    std::string strCMD = "ADDUSER";
    rPacket.SetCMD(strCMD);
    rPacket.SetAttrib("userid",strUserName);
    rPacket.SetAttrib("password",KMD5::GetStringMD5(strPassword));
    rPacket.SetAttrib("nickname",strNickname);
    rPacket.SetAttrib("phone",strPhone);
    rPacket.SetAttrib("remark",strRemark);
    m_CmdTCPClient.sendData(rPacket);
    return true;
}

bool UserRegistration::DeleteUser(std::string strUserName, std::string strPassword)
{
    if(!m_IsLoginSever)
        return false;
    
    std::string strLogin = "DeleteUser";
    KCmdPacketEx rPacket(strLogin.c_str(),(int)strLogin.length()+1);
    std::string strCMD = "DELETEUSER";
    rPacket.SetCMD(strCMD);
    rPacket.SetAttrib("userid",strUserName);
    rPacket.SetAttrib("password",KMD5::GetStringMD5(strPassword));
    m_CmdTCPClient.sendData(rPacket);
    return true;
}
