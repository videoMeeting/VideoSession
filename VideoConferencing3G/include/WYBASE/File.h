#pragma once

#include <string>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef WIN32
#define _stat stat
#endif 

//---------------------------------------------------------------------------------------
// 函数定义
AFX_EXT_CLASS size_t KGetFileSize(const std::string& strFileFullPath);
AFX_EXT_CLASS time_t KGetFileLastModifiedTime(const std::string& strFileFullPath);
AFX_EXT_CLASS bool IsFileExist(const std::string& strFileFullPath);
AFX_EXT_CLASS bool IsDirExist(const std::string& strDirFullPath);
AFX_EXT_CLASS void SplitFilePath(const std::string& strFileFullPath,std::string& strDriver,std::string& strDirectory,std::string& strFileName,std::string& strExtension);
AFX_EXT_CLASS std::string TrimRightPath(const std::string& strPath);
AFX_EXT_CLASS std::string TrimLeftPath(const std::string& strPath);
AFX_EXT_CLASS std::string TrimAllPath(const std::string& strPath);
AFX_EXT_CLASS bool MakeDir(const std::string& strPath);

//---------------------------------------------------------------------------------------
// KFile类定义
class AFX_EXT_CLASS KFile
{
public:
	KFile(void);
	virtual ~KFile(void);

	bool Open(const std::string& strFileFullPath,const std::string& strFileOpenMode);
	void Close();

	size_t Read(void* pData, unsigned long ulBlockSize, unsigned long ulBlockCount);
	size_t Write(const void* pData, unsigned long ulBlockSize, unsigned long ulBlockCount);

	/************************************************************************************
	 * 文件定位
	 *  ulPos: SEEK_CUR - Current position of file pointer. 
     *         SEEK_END - End of file. 
     *         SEEK_SET - Beginning of file. 
	 ***********************************************************************************/
	long Seek(long lPos,int nOffSet);

	/************************************************************************************
	 * Flush returns 0 if the buffer was successfully flushed. 
     * The value 0 is also returned in cases in which the specified stream has no buffer or is 
     * open for reading only. A return value of EOF indicates an error.
     ***********************************************************************************/
	int Flush();
	unsigned long GetCurPos();
	char* GetString(char* pData, int nLen);
	void Printf(const char* cszFormat, ...);

	off_t Size();
	bool Eof();
	bool IsOpened(void);

private:
	FILE*		m_pFilePtr;
	std::string m_strFileFullPath;
	std::string m_strFileOpenMode;
};
