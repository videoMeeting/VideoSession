//VIDEC_MediaFile.h
#ifndef __VIDEC_MEDIAFILE_H__
#define __VIDEC_MEDIAFILE_H__

#include "VIDEC_Export.h"
#include "VIDEC.h"

class VIDEC_API VIDEC_MediaFile;
class VIDEC_MediaFileCallback
{
public:
	VIDEC_MediaFileCallback(void){};
	virtual~VIDEC_MediaFileCallback(void){};
public:
	virtual void OnVIDEC_MediaFileCallbackPositionChanged(VIDEC_MediaFile*pMediaFile,unsigned long ulSeconds)=0;
	virtual void OnVIDEC_MediaFileCallbackEnd(VIDEC_MediaFile*pMediaFile)=0;
	virtual void OnVIDEC_MediaFileCallbackPCMData(VIDEC_MediaFile*pMediaFile,unsigned char*pPCMData,int nLen,unsigned long ulTimestamp)=0;
};

class VIDEC_API VIDEC_MediaFile
	: public VIDEC_CapDev
{
public:
	VIDEC_MediaFile(void){};
	virtual~VIDEC_MediaFile(void){};
public:
	virtual int Open(const char*cszFileName,bool bLoop)=0;
	virtual void Close(void)=0;

	virtual unsigned long GetDuration(void)=0;
	virtual unsigned long GetPosition(void)=0;
	virtual int Seek(unsigned long ulSeconds)=0;
	virtual int Pause(void)=0;
	virtual int Play(void)=0;
	virtual bool IsPlaying(void)=0;

	virtual bool HasAudio(void)=0;
	virtual int SetVolume(int nVolume)=0;
	virtual int SetMute(int nMute)=0;
	virtual int SetBalance(int nBalance)=0;

	virtual bool HasVideo(void)=0;

	static VIDEC_MediaFile*Create(VIDEC_MediaFileCallback&rCallback);
};


#endif
