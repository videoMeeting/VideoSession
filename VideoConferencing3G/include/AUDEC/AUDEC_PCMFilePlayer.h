//AUDEC_PCMFilePlayer.h
#ifndef __AUDEC_PCMFILEPLAYER_H__
#define __AUDEC_PCMFILEPLAYER_H__

#include <AUDEC/AUDEC_Export.h>

class AUDEC_ENGINE_API AUDEC_PCMFilePlayer
{
public:
	AUDEC_PCMFilePlayer(void){};
	virtual ~AUDEC_PCMFilePlayer(void){};
public:
	virtual int Open(const char*cszPCMFile,unsigned long ulSampleRate,bool bLoop=false)=0;
	virtual void Close(void)=0;
	virtual bool IsDone(void)=0;

	static AUDEC_PCMFilePlayer*Create(void);
};

#endif
