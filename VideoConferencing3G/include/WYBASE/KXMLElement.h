#pragma once

#include "KXMLNode.h"
#include "KXMLCData.h"
#include "Utils.h"

#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef std::list<KXMLNode*> XMLELEMENT_CHILD_LIST;
typedef std::map<std::string,std::string> XMLELEMENT_ATTRIB_MAP;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KXMLElement: public KXMLNode
{
public:
	KXMLElement(const std::string& xns, const char** attribs = NULL);
	KXMLElement(KXMLElement& e);
	~KXMLElement();

	KXMLElement& operator=(KXMLElement& e);

	KXMLElement* AddElement(const std::string& xns, const char** attribs = NULL);
	KXMLElement* AddElement(const std::string& xns, const std::string& cdata, bool escaped = false);
	KXMLCData* AddCDATA(const char* data, int datasz, bool escaped = false);	

	KXMLElement* FindElement(const std::string& xns);
	void EraseElement(const std::string& xns);
	void ClearElement(void);

	bool HasAttrib(const std::string& xns);
	void DelAttrib(const std::string& xns);
	bool CmpAttrib(const std::string& xns, const std::string& value);

	void PutAttrib(const std::string& xns,const std::string& value);
	void PutAttribUL(const std::string& xns,unsigned long value);
	void PutAttribUN(const std::string& xns,unsigned int value);
	void PutAttribUS(const std::string& xns,unsigned short value);
	void PutAttribUC(const std::string& xns,unsigned char value);
	void PutAttribBL(const std::string& xns,bool value);

	std::string GetAttrib(const std::string& xns);
	unsigned long GetAttribUL(const std::string& xns);
	unsigned int GetAttribUN(const std::string& xns);
	unsigned short GetAttribUS(const std::string& xns);
	unsigned char GetAttribUC(const std::string& xns);
	bool GetAttribBL(const std::string& xns);
	
	XMLELEMENT_ATTRIB_MAP GetAttribMap();
	XMLELEMENT_CHILD_LIST GetChildrenList();

	void AppendChild(KXMLNode* child);
	std::string GetCDATA();
	std::string GetChildCDATA(const std::string& xns);
	int         GetChildCDATA(const std::string& xns, int defaultvalue);

	std::string XMLString();
	std::string XMLStringEx(bool recursive = false, bool closetag = false);

	void Accumulate(KXMLAccumulator& acc);

protected:
	XMLELEMENT_CHILD_LIST	m_listChildren;
	XMLELEMENT_ATTRIB_MAP	m_mapAttribs;
};
