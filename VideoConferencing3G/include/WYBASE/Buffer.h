#pragma once

//---------------------------------------------------------------------------------------
// KBuffer缓冲区类定义
class AFX_EXT_CLASS KBuffer  
{
public:
	KBuffer(void);
	virtual ~KBuffer(void);

	/* 设置缓冲区数据 */
	virtual bool SetBuffer(const void* pBufferData,size_t nBufferSize);

	/* 获取缓冲区数据指针 */
	virtual unsigned char* GetBuffer(void);

	/* 获取缓冲区数据大小 */
	virtual size_t GetSize(void);

	/* 缓冲区数据压缩 */
	virtual bool Compress(void);

	/* 缓冲区数据解压缩 */
	virtual bool Decompress(void);

protected:
	unsigned char*	m_pBufferData;	//缓冲区数据指针
	size_t			m_nBufferSize;	//缓冲区有效数据大小	
	size_t			m_nBufferBound;	//缓冲区边界
};

//---------------------------------------------------------------------------------------
// KBufferEx缓冲区类定义
class AFX_EXT_CLASS KBufferEx : public KBuffer
{
public:
	KBufferEx(void){};
	virtual ~KBufferEx(void){};

	/* 设置缓冲区数据 */
	virtual bool SetBuffer(unsigned long ulID,const void* pBufferData,size_t nBufferSize)
	{
		m_ulID = ulID;
		return KBuffer::SetBuffer(pBufferData,nBufferSize);
	}

	virtual unsigned long GetID(void)
	{
		return m_ulID;
	}

protected:
	unsigned long	m_ulID;
};