#ifndef __AUDEC_SPEAKERCTRL_H__
#define __AUDEC_SPEAKERCTRL_H__

#include "AUDEC_Export.h"

class AUDEC_ENGINE_API AUDEC_SpeakerCtrl
{
public:
	AUDEC_SpeakerCtrl(void);
	virtual ~AUDEC_SpeakerCtrl(void);
public:
	virtual void Attach(void);
	virtual void Detach(void);

	virtual int SetSpeakerMute(int nMute);
	virtual int GetSpeakerMute(void);

	virtual int SetSpeakerVolume(int nVolume);
	virtual int GetSpeakerVolume(void);

	virtual void OnSpeakerMuteChanged(int nMute);//nMute: 0|1
	virtual void OnSpeakerVolumeChanged(int nVolume);//nVolume:0-100
};


#endif