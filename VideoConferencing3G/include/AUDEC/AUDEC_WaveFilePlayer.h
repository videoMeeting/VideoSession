//AUDEC_WaveFilePlayer.h
#ifndef __AUDEC_WAVEFILEPLAYER_H__
#define __AUDEC_WAVEFILEPLAYER_H__

#include <AUDEC/AUDEC_Export.h>

class AUDEC_ENGINE_API AUDEC_WaveFilePlayer
{
public:
	AUDEC_WaveFilePlayer(void){};
	virtual~AUDEC_WaveFilePlayer(void){};
public:
	virtual int Open(const char*cszPathName)=0;
	virtual void Close(void)=0;
	virtual int GetLevel(void)=0;
	virtual void SetVolume(int nVolume)=0;//0-10-20

	static AUDEC_WaveFilePlayer*Create(void);
};


#endif