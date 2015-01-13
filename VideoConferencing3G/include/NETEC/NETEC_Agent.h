//NETEC_Agent.h
#ifndef __NETEC_AGENT_H__
#define __NETEC_AGENT_H__

#include "NETEC_Session.h"

//网络应用服务
class NETEC_AgentCallback
{
public:
	NETEC_AgentCallback(void){};
	virtual~NETEC_AgentCallback(void){};
public:
	//网络节点与本网络应用断开连接的回调
	virtual void OnNETEC_AgentNodeDisconnected(const char*cszDomain,const char*cszNodeID,const char*pData,int nLen){};

	//从其它网络应用收到的数据包回调
	virtual void OnNETEC_AgentReceivedFromAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};
	
	//从网络节点收到的数据包回调
	virtual void OnNETEC_AgentReceivedFromNode(const char*cszDomain,const char*cszNodeID,const char* pData,int nLen){};

	//指定的Agent不存在
	virtual void OnNETEC_AgentAgentDisconnected(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};

	//指定的Router不存在
	virtual void OnNETEC_AgentRouterDisconnected(const char*cszDomain){};

	//从网络节点收到的数据包回调
	virtual void OnNETEC_AgentReceivedFromRouter(const char* pData,int nLen){};

	//指定的MCU不存在
	virtual void OnNETEC_AgentMCUDisconnected(const char*cszMCUID){};

	/******************************************************************************
	* OnNETEC_AgentConnectStatusChanged
	*描述：连接状态改变的回调
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_AgentConnectStatusChanged(void){};

	/******************************************************************************
	* OnNETEC_AgentLoginSuccessful
	*描述：登录成功的回调
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual void OnNETEC_AgentLoginSuccessful(void){};
	
	/******************************************************************************
	* OnNETEC_AgentLoginError
	*描述：登录失败的回调
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual void OnNETEC_AgentLoginError(void){};
};

class NETEC_API NETEC_Agent
{
public:
	NETEC_Agent(void){};
	virtual~NETEC_Agent(void){};
public:
	/******************************************************************************
	* SetServerIP
	*描述：设置服务器IP
	*输入：	cszServerIP			-服务器IP
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void SetServerIP(const char*cszServerIP)=0;

	/******************************************************************************
	* SetServerPort
	*描述：设置服务器端口
	*输入：	usServerPort		-服务器端口
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void SetServerPort(unsigned short usServerPort)=0;

	/******************************************************************************
	* SetLocalIP
	*描述：设置本地IP，用于连接服务器
	*输入：	cszLocalIP			-服本地IP
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void SetLocalIP(const char*cszLocalIP)=0;

	/******************************************************************************
	* SetPassword
	*描述：设置到服务器上论证的密码
	*输入：	cszPassword			-密码
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void SetPassword(const char*cszPassword)=0;

	/******************************************************************************
	* SetVersion
	*描述：设置版本
	*输入：	cszVersion			-版本
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void SetVersion(const char*cszVersion)=0;

	/******************************************************************************
	* Start
	*描述：启动
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Start(void)=0;

	/******************************************************************************
	* IsStarted
	*描述：是否已经启动
	*输入：	无
	*输出： 无
	*返回值：如果已经启动，那么返回非0，否则返回0
	*****************************************************************************/
	virtual int IsStarted(void)=0;

	/******************************************************************************
	* Stop
	*描述：停止
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void Stop(void)=0;

	/******************************************************************************
	* SendDataToAgent
	*描述：发送数据给指定的网络应用
	*输入：	cszDomain			-网络应用所在的域
			nAgentID			-网络应用标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	virtual int SendDataToAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen)=0;

	/******************************************************************************
	* SendDataToNode
	*描述：发送数据给指定的网络节点
	*输入：	cszNodeID			-网络节点标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	virtual int SendDataToNode(const char*cszNodeID,const char*pData,int nLen)=0;

	/******************************************************************************
	* GetDomain
	*描述：获取所在的域
	*输入：	无
	*输出： 无
	*返回值：所在的域
	*****************************************************************************/
	virtual const char*GetDomain(void)=0;

	/******************************************************************************
	* GetAgentID
	*描述：获取网络应用标识
	*输入：	无
	*输出： 无
	*返回值：网络应用标识
	*****************************************************************************/
	virtual unsigned int GetAgentID(void)=0;

	/******************************************************************************
	* GetConnectStatus
	*描述：获取连接状态
	*输入：	无
	*输出： 无
	*返回值：连接状态
	*****************************************************************************/
	virtual NETEC_Session::CONNECT_STATUS GetConnectStatus(void)=0;

	/******************************************************************************
	* GetLoginSuccessful
	*描述：获取是否登录成功
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual int GetLoginSuccessful(void)=0;
	
	/******************************************************************************
	* GetLoginError
	*描述：获取是否登录失败
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual int GetLoginError(void)=0;

	/******************************************************************************
	* GetLoginErrorID
	*描述：获取是否由于帐号错误导致登录失败
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual int GetLoginErrorID(void)=0;

	/******************************************************************************
	* GetLoginErrorPassword
	*描述：获取是否由于密码错误导致登录失败
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual int GetLoginErrorPassword(void)=0;

	/******************************************************************************
	* GetLoginErrorDuplication
	*描述：获取是否由于相同帐号已登录导致登录失败
	*输入：	无
	*输出： 无
	*返回值：返回非0为是，否则为否
	*****************************************************************************/
	virtual int GetLoginErrorDuplication(void)=0;

	static NETEC_Agent*Create(NETEC_AgentCallback&rCallback,unsigned int nAgentID);
};

#endif