//AUDEC_Conference.h
#ifndef __AUDEC_CONFERENCE_H__
#define __AUDEC_CONFERENCE_H__

#include <AUDEC/AUDEC_Export.h>
#include <AUDEC/AUDEC_Engine.h>

class AUDEC_ENGINE_API AUDEC_Mixer
{
public:
	AUDEC_Mixer(void){};
	virtual~AUDEC_Mixer(void){};
public:
	virtual int Open(AUDEC_CapChan*pCapChan)=0;
	virtual void Close(void)=0;
	virtual void ExcludePlayChan(AUDEC_PlayChan*pPlayChan)=0;

	static AUDEC_Mixer*Create(void);
};

#endif
