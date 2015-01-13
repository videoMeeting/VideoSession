#pragma once

#include "KXMLElement.h"
#include "WYBASE.h"

class KXMLPacket;

//---------------------------------------------------------------------------------------
// 类型定义
typedef std::list<KXMLPacket*> XMLPACKET_LIST;

//---------------------------------------------------------------------------------------
// KXMLPacket类定义
class AFX_EXT_CLASS KXMLPacket : public KXMLElement
{
public:
	KXMLPacket(const std::string& xns,const std::string& cmd,const std::string& userid="",const std::string& fromid="",const std::string& toid="",unsigned long rsid=0,unsigned long csid=0);
	KXMLPacket(KXMLElement& rXMLElement):KXMLElement(rXMLElement){};
	virtual ~KXMLPacket(void){};

	void SetCMD(const std::string& cmd);
	void SetUserID(const std::string& userid);
	void SetFromID(const std::string& fromid);
	void SetToID(const std::string& toid);
	void SetRSID(unsigned long rsid);
	void SetCSID(unsigned long csid);

	std::string GetCMD(void);
	std::string GetUserID(void);
	std::string GetFromID(void);
	std::string GetToID(void);
	unsigned long GetRSID(void);
	unsigned long GetCSID(void);
};

//=======================================================================================
// KXMLUserDataPacket 类定义
class AFX_EXT_CLASS KXMLUserDataPacket :	public KXMLPacket
{
public:
	KXMLUserDataPacket(const std::string& fromid,const std::string& toid,unsigned long rsid=0)
		:KXMLPacket("","","",fromid,toid,rsid){};
	KXMLUserDataPacket(KXMLElement& rXMLElement):KXMLPacket(rXMLElement){};
	virtual ~KXMLUserDataPacket(void){};
};


//=======================================================================================
// KXMLSIDPacket 类定义
class AFX_EXT_CLASS KXMLSIDPacket
{
public:
        KXMLSIDPacket(unsigned long ulCSID,KXMLPacket& rXMLPacket)
                :m_ulCSID(ulCSID)
                ,m_XMLPacket(rXMLPacket){};
        virtual ~KXMLSIDPacket(void){};

        unsigned long GetCSID(void){return m_ulCSID;};
        KXMLPacket& GetXMLPacket(void){return m_XMLPacket;};

protected:
        unsigned long   m_ulCSID;
        KXMLPacket		m_XMLPacket;
};
