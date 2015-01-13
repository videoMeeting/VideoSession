#pragma once

/****************************************************************************************
 * 文件版本: 2008-06-06 17:45
 ****************************************************************************************/

#include <string>
#include <map>
#include "String.h"

//=======================================================================================
// 命令字符串编解码
//=======================================================================================

// 转义字符串编码
void CommandStringEncode(const std::string& in,std::string& out);

// 转义字符串解码
void CommandStringDecode(const std::string& in,std::string& out);

//=======================================================================================
typedef std::map<std::string,std::string> CMD_ATTRIB_MAP;

//=======================================================================================
// 命令子项类定义
//=======================================================================================
class AFX_EXT_CLASS KCmdItem
{
public:
	KCmdItem(void);
	KCmdItem(const std::string& data);
	KCmdItem(KCmdItem& rCmdItem);
	virtual ~KCmdItem(void);

	// 设置属性
	void SetAttrib(const std::string& name,const std::string& value);
	void SetAttribUL(const std::string& name,unsigned long value);
	void SetAttribUN(const std::string& name,unsigned int value);
	void SetAttribUS(const std::string& name,unsigned short value);
	void SetAttribUC(const std::string& name,unsigned char value);
	void SetAttribBL(const std::string& name,bool value);

	// 获取属性
	KString GetAttrib(const std::string& name);

	// 获取字符串
	std::string GetString(void);

protected:
	CMD_ATTRIB_MAP	m_mapAttribs;
};

//=======================================================================================
typedef std::list<std::string> CMD_ITEM_LST;

//=======================================================================================
// 命令包类定义
//=======================================================================================
class AFX_EXT_CLASS KCmdPacket
{
public:
	KCmdPacket(const std::string& xns,const std::string& cmd,const std::string& userid="");
	KCmdPacket(const char* pData,int nLen);
	KCmdPacket(KCmdPacket& rCmdElement);
	virtual ~KCmdPacket(void);

	void SetXNS(const std::string& xns);
	void SetCMD(const std::string& cmd);
	void SetUserID(const std::string& userid);

	std::string GetXNS(void);
	std::string GetCMD(void);
	std::string GetUserID(void);

	// 命令子项方法
	void SetItem(const std::string& item);
	std::string GetItemString(void);
	CMD_ITEM_LST& GetItemList(void);
	void ClearAllItems(void);

	// 设置属性
	void SetAttrib(const std::string& name,const std::string& value);
	void SetAttribUL(const std::string& name,unsigned long value);
	void SetAttribUN(const std::string& name,unsigned int value);
	void SetAttribUS(const std::string& name,unsigned short value);
	void SetAttribUC(const std::string& name,unsigned char value);
	void SetAttribBL(const std::string& name,bool value);

	// 获取属性
	KString GetAttrib(const std::string& name);

	// 获取构造的字符串
	std::string GetString(void);

protected:
	std::string		m_strXNS;
	std::string		m_strCMD;
	std::string		m_strUserID;
	CMD_ATTRIB_MAP	m_mapAttribs;
	std::string		m_strItems;
	CMD_ITEM_LST	m_lstItems;
};

//=======================================================================================
// KCmdUserDataPacket 类定义
//=======================================================================================
class AFX_EXT_CLASS KCmdUserDataPacket : public KCmdPacket
{
public:
	KCmdUserDataPacket()
		:KCmdPacket("",""){};
	KCmdUserDataPacket(KCmdPacket& rCmdPacket):KCmdPacket(rCmdPacket){};
	virtual ~KCmdUserDataPacket(void){};
};


//=======================================================================================
// KCmdPacketEx 类定义
// m_ucSourceType: 0=NODE,1=C2S,2=AGENT
//=======================================================================================
class AFX_EXT_CLASS KCmdPacketEx : public KCmdPacket
{
public:
	//-----------------------------------------------------
	KCmdPacketEx(const std::string& xns,const std::string& cmd,const std::string& userid="")
	:KCmdPacket(xns,cmd,userid)
	,m_strDomain("")
	,m_ucSourceType(0)
	,m_strSourceID("")
	{
	};

	//-----------------------------------------------------
	KCmdPacketEx(const char* pData,int nLen)
	:KCmdPacket(pData,nLen)
	,m_strDomain("")
	,m_ucSourceType(0)
	,m_strSourceID("")
	{
	};

	//-----------------------------------------------------
	KCmdPacketEx(KCmdPacket& rCmdElement)
	:KCmdPacket(rCmdElement)
	,m_strDomain("")
	,m_ucSourceType(0)
	,m_strSourceID("")
	{
	};

	virtual ~KCmdPacketEx(void){};

	void SetDomain(const std::string& strDomain){m_strDomain=strDomain;};
	void SetSourceType(unsigned char ucSourceType){m_ucSourceType=ucSourceType;};
	void SetSourceID(const std::string& strSourceID){m_strSourceID=strSourceID;};

	std::string GetDomain(void){return m_strDomain;};
	unsigned char GetSourceType(void){return m_ucSourceType;};
	std::string GetSourceID(void){return m_strSourceID;};

protected:
	std::string		m_strDomain;
	unsigned char   m_ucSourceType;
	std::string		m_strSourceID;
};
