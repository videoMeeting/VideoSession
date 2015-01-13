/**********************************************************
 * Name: KCmdLine.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2008-03-07
 **********************************************************/

#pragma once

#include "Utils.h"

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KCmdLine
{
public:
#ifdef WIN32
	KCmdLine(int argc, TCHAR* argv[]);
#else
	KCmdLine(int argc, char* argv[]);
#endif
	virtual ~KCmdLine(void);

	int GetParamCount(void);
	std::string GetParamValue(int nIndex);
	std::string GetOptionParamValue(const std::string& strOptionParamName);
	bool IsExistParam(const std::string& strOptionParamName);

private:
	STRING_MAP	m_mapCmdLine;
};
