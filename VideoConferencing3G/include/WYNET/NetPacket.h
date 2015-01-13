/* KNetPacket.h */

#pragma once

#define MAX_NET_PACKET_SIZE			1024*64			//网络原始包总体最大长度(含包头长度)

//---------------------------------------------------------------------------------------
//KNetOutPacket类定义
class AFX_EXT_CLASS KNetOutPacket
{
public:
	KNetOutPacket()
	{
		Reset();
	}

	void Reset()
	{
		m_pCursor = m_pData;
	}

	unsigned char *GetData()
	{
		return m_pData;
	}

	int GetLength()
	{
		int n;
		n=(int)(m_pCursor - m_pData);
		return n;
	}

	void Write16(unsigned short w);
	void Write32(unsigned int dw);
	void Write64(unsigned long lw);
	void WriteData(unsigned char *buf, int n);
	void WriteString(const char *str, int n);

	KNetOutPacket &operator <<(unsigned char b);
	KNetOutPacket &operator <<(unsigned short w);
	KNetOutPacket &operator <<(unsigned int dw);
	KNetOutPacket &operator <<(unsigned long lw);
	KNetOutPacket &operator <<(const char *str);

	unsigned char *Skip(int delta)
	{
		m_pCursor += delta;
		return (m_pCursor - delta);
	}

	unsigned char *SetCursor(unsigned char *pCur)
	{
		unsigned char *pOld = m_pCursor;
		m_pCursor = pCur;
		return pOld;
	}

protected:
	unsigned char m_pData[MAX_NET_PACKET_SIZE];
	unsigned char* m_pCursor;
};


//---------------------------------------------------------------------------------------
// KNetInPacket 类定义
class AFX_EXT_CLASS KNetInPacket
{
public:
	KNetInPacket(char *d, int n)
	{
		m_pCursor = m_pData = (unsigned char *) d;
		m_nDataLen = n;
	}

	KNetInPacket &operator >>(unsigned char &b);
	KNetInPacket &operator >>(unsigned short &w);
	KNetInPacket &operator >>(unsigned int &dw);
	KNetInPacket &operator >>(unsigned long &lw);
	KNetInPacket &operator >>(const char* &str);
	KNetInPacket &operator >>(char* str);

	unsigned int Read64();
	unsigned int Read32();
	unsigned short Read16();
	unsigned char* ReadData(int &n);

	int GetLength(void) {return m_nDataLen;};
	unsigned char* GetCursor(void) {return m_pCursor;};

protected:
	unsigned char *m_pData;
	unsigned char *m_pCursor;
	int m_nDataLen;
};
