#ifndef __AUDEC_MICCTRL_H__
#define __AUDEC_MICCTRL_H__

#include "AUDEC_Export.h"

class AUDEC_ENGINE_API AUDEC_MicCtrl
{
public:
	AUDEC_MicCtrl(void);
	virtual ~AUDEC_MicCtrl(void);
public:
	typedef enum {
		MIC=0,
		LINE_IN,
		WAVE_OUT_MIXER,
		UNKOWN
	}MIC_INPUT;

	virtual void Attach(void);
	virtual void Detach(void);

	virtual int SetMicBoost(int nBoost);
	virtual int GetMicBoost(void);

	virtual int SetMicInputType(AUDEC_MicCtrl::MIC_INPUT nType);
	virtual AUDEC_MicCtrl::MIC_INPUT GetMicInputType(void);

	virtual int SetMicVolume(int nVolume);
	virtual int GetMicVolume(void);

	virtual void OnMicBoostChanged(int nBoost);//nBoost: 0|1
	virtual void OnMicInputChanged(AUDEC_MicCtrl::MIC_INPUT nType);
	virtual void OnMicVolumeChanged(int nVolume);//nVolume:0-100
};


#endif