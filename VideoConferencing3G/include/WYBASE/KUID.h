#pragma once

#include <string>
#include "Utils.h"

//=======================================================================================
// KUID定义
class AFX_EXT_CLASS KUID
{
public:
	KUID(const std::string& strUID);
	KUID(const std::string& strUserID,const std::string& strDomain);
	~KUID();

	std::string GetUserID(void);
	std::string GetDomain(void);
	std::string GetUID(void);

private:
	std::string m_strUserID;
	std::string m_strDomain;
	std::string m_strUID;
};

//=======================================================================================
// KDomain定义
class AFX_EXT_CLASS KDomain
{
public:
	KDomain(const std::string& strLocalDomain);
	~KDomain();

	std::string GetParentDomain(void);
	int GetParentDomainLevel(void);
	std::string GetLocalDomain(void);
	int GetLocalDomainLevel(void);
	STRING_MAP& GetFullDomain(void);

private:
	std::string m_strParentDomain;
	std::string m_strLocalDomain;
	int m_nParentDomainLevel;
	int m_nLocalDomainLevel;
	STRING_MAP m_mapFullDomain;
};

//=======================================================================================
AFX_EXT_CLASS std::string GetUserDomain(const std::string& strUserID);
AFX_EXT_CLASS std::string GetUserIDWithDomain(const std::string& strUserID,const std::string& strDomain);