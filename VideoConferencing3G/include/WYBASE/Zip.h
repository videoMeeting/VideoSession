#pragma once

#ifdef WIN32
 
#include "zlib/zlib.h"
 
//---------------------------------------------------------------------------------------
// KZip 类定义
class AFX_EXT_CLASS KZip  
{
public:
	KZip();
	virtual ~KZip();

public:	
	void Flash();
	bool Open(DWORD dwLen);
	void Close();
	bool Write(PBYTE pData,DWORD dwLength);

	DWORD	GetLength(){return m_dwBufferLength;};
	DWORD	GetSize(){	return m_dwBufferSize;};
	PBYTE	GetBuffer(){return m_pbBuffer;};

private:
	PBYTE		m_pbBuffer;
	DWORD		m_dwBufferSize;
	DWORD		m_dwBufferLength;

	CPtrList	m_list;
	z_stream	m_ZIPStream;
	uLong		m_crc32;
public:
	static void myfree(void* opaque, void* address);
	static void* myalloc(void* opaque, UINT items, UINT size);
};

//---------------------------------------------------------------------------------------
// KUnZip 类定义
class AFX_EXT_CLASS KUnZip  
{
public:
	KUnZip();
	~KUnZip();
public:
	void Close();
	int Read(void* buf, UINT len);
	bool Open(void* pData,int nLen,int nUnCompressed);
	DWORD	GetPos(){return m_dwReadPos;};
private:
	PBYTE		m_pbBuffer;
	DWORD		m_dwBufferSize;
	DWORD		m_dwReadPos;

	z_stream	m_ZIPStream;
	uLong		m_crc32;
	CPtrList	m_list;
	int			m_nLengthOfUnCompressed;
	TCHAR*		m_pReadBuffer;
};

#endif