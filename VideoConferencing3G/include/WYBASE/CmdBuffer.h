/**********************************************************
 * Name: CmdBuffer.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2008-13-14
 **********************************************************/

#pragma once

#include "Buffer.h"
#include <string>

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KCmdBuffer : public KBuffer
{
public:
	KCmdBuffer(void);
	virtual ~KCmdBuffer(void);

	void SetDomain(const std::string& strDomain);
	std::string GetDomain(void);

	void SetDomainID(unsigned int nDomainID);
	unsigned int GetDomainID(void);

	void SetAgentID(unsigned int nAgentID);
	unsigned int GetAgentID(void);

	void SetNodeID(const std::string& strNodeID);
	std::string GetNodeID(void);

	void SetC2SID(unsigned int nC2SID);
	unsigned int GetC2SID(void);

protected:
	std::string		m_strDomain;
	unsigned int	m_nDomainID;
	unsigned int	m_nAgentID;
	std::string		m_strNodeID;
	unsigned int	m_nC2SID;
};
