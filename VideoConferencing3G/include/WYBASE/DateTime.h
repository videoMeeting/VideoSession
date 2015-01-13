#pragma once

#include <string>
#include <ctime>

//=======================================================================================
// KFormatDateTime时间格式类定义
class AFX_EXT_CLASS KFormatDateTime
{
public:
	KFormatDateTime();
	~KFormatDateTime();

	void SetYear(int nYear){m_nYear=nYear;};
	void SetMonth(int nMonth){m_nMonth=nMonth;};
	void SetMDay(int nMDay){m_nMDay=nMDay;};
	void SetWDay(int nWDay){m_nWDay=nWDay;};
	void SetHour(int nHour){m_nHour=nHour;};
	void SetMinute(int nMinute){m_nMinute=nMinute;};
	void SetSecond(int nSecond){m_nSecond=nSecond;};

	int GetYear(void){return m_nYear;};
	int GetMonth(void){return m_nMonth;};
	int GetMDay(void){return m_nMDay;};
	int GetWDay(void){return m_nWDay;};
	int GetHour(void){return m_nHour;};
	int GetMinute(void){return m_nMinute;};
	int GetSecond(void){return m_nSecond;};

	void GetJDay(unsigned long& jday);

	void GetDate(std::string& date)
	{
		char szBuffer[128];
		sprintf(szBuffer,"%04d-%02d-%02d",m_nYear,m_nMonth,m_nMDay);
		date = szBuffer;
	};

	void GetDateTime(std::string& datetime)
	{
		char szBuffer[128];
		sprintf(szBuffer,"%04d-%02d-%02d %02d:%02d:%02d",m_nYear,m_nMonth,m_nMDay,m_nHour,m_nMinute,m_nSecond);
		datetime = szBuffer;
	};

protected:
	int m_nYear;
	int m_nMonth;
	int m_nMDay;
	int m_nWDay;
	int m_nHour;
	int m_nMinute;
	int m_nSecond;
};

//=======================================================================================
// KDateTime 类定义
//=======================================================================================
AFX_EXT_CLASS void GetNow(KFormatDateTime& datetime);
AFX_EXT_CLASS void GetFormatDateTime(const std::string& strDateTime,KFormatDateTime& datetime);
AFX_EXT_CLASS bool KYMD2JDay(int year,int month,int day,unsigned long& jday);
AFX_EXT_CLASS void KJDay2YMD(unsigned long jday,KFormatDateTime& datetime);
AFX_EXT_CLASS void KGetWeekDay(int year,int month,int day,int& weekday);

