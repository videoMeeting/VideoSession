#pragma once

#include <string>

class KXMLNode;

//---------------------------------------------------------------------------------------
// KXMLAccumulator¿‡∂®“Â
class AFX_EXT_CLASS KXMLAccumulator
{
public:
	KXMLAccumulator(std::string& s);
	void operator()(KXMLNode* n);
	void operator()(std::pair<const std::string, std::string> p);
	template <class T>	KXMLAccumulator& operator<<(T data)
	{
		m_result += data; return *this;
	}
private:
	std::string& m_result;
};

//---------------------------------------------------------------------------------------
// Utility routines
AFX_EXT_CLASS void XMLUnEscape(const char* src, unsigned int srcLen, std::string& dest, bool append = false);  
AFX_EXT_CLASS std::string XMLEscape(const std::string& src);