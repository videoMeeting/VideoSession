#pragma once

#ifndef WIN32 /* Remove CR, on unix systems. */
#define INI_REMOVE_CR
#define DONT_HAVE_STRUPR
#endif

#define tpNULL       0
#define tpSECTION    1
#define tpKEYVALUE   2
#define tpCOMMENT    3

struct ENTRY
{
   char   Type;
   char  *pText;
   struct ENTRY *pPrev;
   struct ENTRY *pNext;
};

typedef struct
{
   struct ENTRY *pSec;
   struct ENTRY *pKey;
   char          KeyText [128];
   char          ValText [128];
   char          Comment [255];
}EFIND;

/* Macros */
#define ArePtrValid(Sec,Key,Val) ((Sec!=NULL)&&(Key!=NULL)&&(Val!=NULL))

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KIniFile
{
public:
	KIniFile();
	~KIniFile();

	bool Open(const char* pFileName);
	void Close(void);

	bool ReadBool(const char* pSection,const char* pKey,bool bDefault);
	int ReadInt(const char* pSection,const char* pKey,int nDefault);
	double ReadDouble(const char* pSection,const char* pKey,double dDefault);
	const char* ReadString(const char* pSection,const char* pKey,const char* pDefault);

	void WriteBool(const char* pSection,const char* pKey,bool bValue);
	void WriteInt(const char* pSection,const char* pKey,int nValue);
	void WriteDouble(const char* pSection,const char* pKey,double dValue);
	void WriteString(const char* pSection,const char* pKey,const char* pValue);

	bool WriteClose(const char* pFileName);
	bool DeleteKey(const char* pSection,const char* pKey);

protected:
	struct ENTRY* m_pEntry;
	struct ENTRY* m_pCurEntry;
	char m_result [255];
	FILE* m_pIniFile;
	void AddKey(struct ENTRY* pEntry, const char *pKey, const char* pValue);
	bool AddItem(char Type,const char* pText);
	bool AddItemAt(struct ENTRY* pEntryAt,char Mode,const char* pText);
	void FreeMem(void* pPtr);
	void FreeAllMem(void);
	bool FindKey(const char* pSection,const char* pKey,EFIND* pList);
	bool AddSectionAndKey(const char* pSection,const char* pKey,const char* pValue);
	struct ENTRY* MakeNewEntry(void);
	struct ENTRY* FindSection(const char* pSection);
};
