/**********************************************************
 * Name: KUtils.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-03-15
 **********************************************************/

#pragma once
#define AFX_EXT_CLASS  
#include <string>
#include <algorithm>
#include <map>
#include <list>

#ifdef WIN32
#include <process.h>
typedef long pid_t;
#define getpid	_getpid
#define unlink	_unlink
#else
#include <unistd.h>
#endif

/* 按照指定序号(整形int)保存字符串 */
typedef std::map<int,std::string> STRING_MAP;
typedef std::map<std::string,std::string> STRING_MAP_EX;

/* 按照先进先出顺序保存字符串 */
typedef std::list<std::string> STRING_LIST;

/* 随机初始化函数,在获取所有随机数之前调用此函数进行初始化 */
AFX_EXT_CLASS void InitRandom(void);

/* 获取随机数
 * nNumber: 随机数范围最大值 */
AFX_EXT_CLASS int Random(int nNumber);

/* 获取当前时戳(毫秒millisecond) */
AFX_EXT_CLASS unsigned long GetTimeStamp(void);

/* 获取当前时戳(微秒microsecond) */
AFX_EXT_CLASS unsigned long GetMicroTimeStamp(void);

/* 暂停(毫秒):将阻塞程序 */
AFX_EXT_CLASS void Pause(unsigned long ulMS);

/* BASE64编码 */
AFX_EXT_CLASS void Base64Encode(const std::string& InBuffer,std::string& OutBuffer);

/* BASE64解码 */
AFX_EXT_CLASS void Base64Decode(const std::string& InBuffer,std::string& OutBuffer);

/* 将整个文件进行BASE64编码 */
AFX_EXT_CLASS size_t Base64EncodeFromFile(const std::string& filename,std::string& encodedstr);

/* 将字符串BASE64解码保存到文件中 */
AFX_EXT_CLASS void Base64DecodeToFile(const std::string& encodedstr,const std::string& filename);

/* 字符串大写转换 */
AFX_EXT_CLASS std::string UPPERCASE(const std::string& source);

/* 字符串小写转换 */
AFX_EXT_CLASS std::string LOWERCASE(const std::string& source);

/* 清除字符串左边所有空格 */
AFX_EXT_CLASS std::string TRIMLEFT(const std::string& source, const char* chars2remove);

/* 清除字符串右边所有空格 */
AFX_EXT_CLASS std::string TRIMRIGHT(const std::string& source, const char* chars2remove);

/* 清除字符串两边所有空格 */
AFX_EXT_CLASS std::string TRIMSPACE(const std::string& source);

/* 类型转换 */
AFX_EXT_CLASS std::string LONG2STR(long value);
AFX_EXT_CLASS std::string ULONG2STR(unsigned long value);
AFX_EXT_CLASS std::string INT2STR(int value);
AFX_EXT_CLASS std::string UINT2STR(unsigned int value);
AFX_EXT_CLASS std::string SHORT2STR(short value);
AFX_EXT_CLASS std::string USHORT2STR(unsigned short value);
AFX_EXT_CLASS std::string BYTE2STR(unsigned char value);
AFX_EXT_CLASS std::string BOOL2STR(bool value);
AFX_EXT_CLASS std::string DOUBLE2STR(double value);

AFX_EXT_CLASS long STR2LONG(const std::string& value);
AFX_EXT_CLASS unsigned long STR2ULONG(const std::string& value);
AFX_EXT_CLASS int STR2INT(const std::string& value);
AFX_EXT_CLASS unsigned int STR2UINT(const std::string& value);
AFX_EXT_CLASS short STR2SHORT(const std::string& value);
AFX_EXT_CLASS unsigned short STR2USHORT(const std::string& value);
AFX_EXT_CLASS unsigned char STR2BYTE(const std::string& value);
AFX_EXT_CLASS bool STR2BOOL(const std::string& value);
AFX_EXT_CLASS double STR2DOUBLE(const std::string& value);

AFX_EXT_CLASS unsigned short BOOL2USHORT(bool value);
AFX_EXT_CLASS bool USHORT2BOOL(unsigned short value);

AFX_EXT_CLASS std::string ULONG2HEX(unsigned long value);
AFX_EXT_CLASS unsigned long HEX2ULONG(const std::string& value);

AFX_EXT_CLASS std::string NONULLSTR(const char* value);

/* 字符串分割 */
AFX_EXT_CLASS STRING_MAP StrSplit(const std::string& data,const std::string& token);
AFX_EXT_CLASS STRING_MAP_EX StrSplitEx(const std::string& data,const std::string& token);
AFX_EXT_CLASS bool URLSplit(const std::string& url,std::string& protocol,std::string& serveraddr,unsigned short& serverport,std::string& filepath);

/* 获取文件大小 */
AFX_EXT_CLASS unsigned long GetFileSize(const std::string& strFileFullPath);

/* 删除文件 */
AFX_EXT_CLASS bool DeleteFile(const std::string& strFileFullPath);

/* 获得本进程ID */
AFX_EXT_CLASS pid_t GetProcessID(void);

/* 压缩字符串 */
AFX_EXT_CLASS bool Compress(const char* pSourceData,int nSourceLen,char* pDestData,int& nDestLen);

/* 解压字符串 */
AFX_EXT_CLASS bool UnCompress(const char* pSourceData,int nSourceLen,char* pDestData,int& nDestLen);

#ifdef WIN32
/********************************************************************
 * 将通用字符串编码成UTF8字符串
 ********************************************************************/
AFX_EXT_CLASS std::string U2A(CString csUnicodeString);

/********************************************************************
 * 将UTF8字符串解码成通用字符串
 ********************************************************************/
AFX_EXT_CLASS CString A2U(const std::string& strAnsiString);
#endif

/* 获得IP的掩码 nBit取32/16/12/8... */
AFX_EXT_CLASS unsigned long GetBitMask(unsigned int nBit);

/********************************************************************
 * 权限码操作
 * 权限码以长整型表示,按二进制位设定每一位权限值,1为true,0为false
 * 权限位的顺序从低位(1)到高位(20)依次排列.
 ********************************************************************/

/* 设置权限位
 * ulPrivilege:		现有权限码
 * ucBit:			权限位(取值范围1-20)
 * bEnabled:		权限值
 * <RETURN>:		设置权限后的新权限码 */
AFX_EXT_CLASS unsigned long SetPrivilege(unsigned long ulPrivilege,unsigned char ucBit,bool bEnabled);

/* 获得权限位
 * ulPrivilege:		权限码
 * ucBit:			权限位(取值范围1-20)
 * <RETURN>:		权限值 */
AFX_EXT_CLASS bool GetPrivilege(unsigned long ulPrivilege,unsigned char ucBit);
