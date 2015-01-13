#pragma once

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KDataOutPacket
{
public:
	KDataOutPacket(bool bAutoDelete=true,int nBufferLength=1024)
		:m_pBuffer(NULL)
		,m_nBufferLength(nBufferLength)
		,m_bAutoDelete(bAutoDelete)
	{
		m_pBuffer=(unsigned char*)malloc(m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
		}
		Reset();
	}

	virtual~KDataOutPacket(void)
	{
		if (m_pBuffer && m_bAutoDelete)
		{
			free(m_pBuffer);
			m_pBuffer=NULL;
		}
	}

	void Reset()
	{
		m_pCursor = m_pBuffer;
	}

	unsigned char *GetData()
	{
		return m_pBuffer;
	}

	int GetLength()
	{
		int n;
		n=(int)(m_pCursor - m_pBuffer);
		return n;
	}

	void Write16(unsigned short w);
	void Write32(unsigned int dw);
	void Write64(unsigned long lw);
	void WriteData(unsigned char *buf, unsigned int n);
	void WriteString(const char *str, unsigned int n);

	KDataOutPacket &operator <<(unsigned char b);
	KDataOutPacket &operator <<(unsigned short w);
	KDataOutPacket &operator <<(unsigned int dw);
	KDataOutPacket &operator <<(unsigned long lw);
	KDataOutPacket &operator <<(const char *str);

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
	unsigned char*	m_pBuffer;
	unsigned int	m_nBufferLength;
	unsigned char*	m_pCursor;
	bool			m_bAutoDelete;
};

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KDataInPacket
{
public:
	KDataInPacket(char *d, int n)
	{
		m_pCursor = m_pData = (unsigned char *) d;
		m_nDataLen = n;
	}

	KDataInPacket &operator >>(unsigned char &b);
	KDataInPacket &operator >>(unsigned short &w);
	KDataInPacket &operator >>(unsigned int &dw);
	KDataInPacket &operator >>(unsigned long &lw);
	KDataInPacket &operator >>(const char* &str);
	KDataInPacket &operator >>(char* str);

	unsigned int Read64();
	unsigned int Read32();
	unsigned short Read16();
	unsigned char *ReadData(int &n);

	int GetLength()
	{
		return m_nDataLen;
	}

	unsigned char* GetCursor(void)
	{
		return m_pCursor;
	};

protected:
	unsigned char *m_pData;
	unsigned char *m_pCursor;
	int m_nDataLen;
};

