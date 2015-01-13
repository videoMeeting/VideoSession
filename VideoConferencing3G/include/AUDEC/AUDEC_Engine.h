//AUDEC_Engine.h
#ifndef __AUDEC_ENGINE_H__
#define __AUDEC_ENGINE_H__

#include <stdio.h>

#include <AUDEC/AUDEC_Export.h>

typedef struct{
	int		id;
	int		pl_type;
	char	pl_name[32];
	int		pl_freq;
	int		framesize;
	int		bitrate;
	char	desc[128];//g711u 64kbps
}AUDEC_CodecInst;

class AUDEC_ENGINE_API AUDEC_SampleOut
{
public:
	AUDEC_SampleOut(void){};
	virtual~AUDEC_SampleOut(void){};
public:
	virtual int GetSampleRate(void)=0;
	// true for ok, false for fail
	virtual bool Write(const short*pSamples,int nSamples)=0;
};

class AUDEC_ENGINE_API AUDEC_StreamOut
{
public:
	AUDEC_StreamOut(void){};
	virtual~AUDEC_StreamOut(void){};
public:
	// true for ok, false for fail
	virtual bool Write(const void*data,int len)=0; 
};

class AUDEC_ENGINE_API AUDEC_RecordSamples
{
public:
	AUDEC_RecordSamples(void){};
	virtual~AUDEC_RecordSamples(void){};
public:
	virtual void OnRecordSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp)=0;
};

class AUDEC_ENGINE_API AUDEC_PlayChan;
class AUDEC_ENGINE_API AUDEC_CapChan
{
public:
	AUDEC_CapChan(void){};
	virtual~AUDEC_CapChan(void){};
public:
	virtual int Connect(AUDEC_CodecInst*pCodecInst)=0;
	virtual void ReleaseConnections(void)=0;

	virtual int SetCodec(AUDEC_CodecInst*pCodecInst)=0;
	virtual int GetCodec(AUDEC_CodecInst*pCodecInst)=0;

	virtual int StartCapture(void)=0;
	virtual int StopCapture(void)=0;
	//<0:error 0:false,else true
	virtual int GetCapturing(void)=0;

	//<0:error >=0:level[0-10]
	virtual int GetLevel(void)=0;

	//<0:error else bps
	virtual int GetBitrate(void)=0;

	//<0:error 0:ok nVAD[0:disable,1:enable]
	//virtual int SetVAD(int nVAD)=0;
	//<0:error 0:disable 1:enable
	//virtual int GetVAD(void)=0;

	virtual int AddStreamOut(AUDEC_StreamOut*pStreamOut)=0;
	virtual int RemoveStreamOut(AUDEC_StreamOut*pStreamOut)=0;

	virtual int SetVolume(int volume)=0;//0-10-20
	virtual int GetVolume(void)=0;//0-10-20

	virtual int StartMixingWithPlayChan(AUDEC_PlayChan*pPlayChan)=0;
	virtual int StopMixingWithPlayChan(AUDEC_PlayChan*pPlayChan)=0;

	virtual int SetRecordSamples(AUDEC_RecordSamples*pRecordSamples)=0;

	virtual int StartMixingWithWaveFile(const char*cszPathName)=0;
	virtual void StopMixingWithWaveFile(void)=0;
};

class AUDEC_ENGINE_API AUDEC_CapChanExternal
	: public AUDEC_CapChan
{
public:
	AUDEC_CapChanExternal(void){};
	virtual~AUDEC_CapChanExternal(void){};
public:
	virtual int GetBufferedTime(void)=0;//ms
	virtual int WriteSamples(short*pSamples,int nSamples,int nSampleRate,bool bDiscontinious)=0;
};

class AUDEC_ENGINE_API AUDEC_PlayChan
	: public AUDEC_StreamOut
{
public:
	AUDEC_PlayChan(void){};
	virtual~AUDEC_PlayChan(void){};
public:
	virtual int Connect(unsigned long*lpnVidFrameTimestamp=(unsigned long*)NULL,unsigned long*lpnAudFrameTimestamp=(unsigned long*)NULL)=0;
	virtual void ReleaseConnections(void)=0;

	virtual int GetCodec(AUDEC_CodecInst*codec_inst)=0;

	virtual int SetVolume(int volume)=0;//0-10-20
	virtual int GetVolume(void)=0;//0-10-20

	//<0:error 0:ok mute[0:disable 1:enable]
	virtual int SetMute(int mute)=0;
	//<0:error else mute[0:disable 1:enable]
	virtual int GetMute(void)=0;

	//<0:error level[0-10]
	virtual int GetLevel(void)=0;//0-10

	//<0:error else bps
	virtual int GetBitrate(void)=0;

	//<0:error else 0:100
	virtual int GetLostPackets(void)=0;

	//<0:error else 0:100
	virtual int GetLostPacketsPercent(void)=0;

	//<0:error 0:ok status[0:disable 1:enable]
	virtual int SetJitterBuffer(int value)=0;
	//<0:error else status[0:disable 1:enable]
	virtual int GetJitterBuffer(void)=0;
	//min[60-3000]
	virtual int SetJitterMin(int min)=0;
	virtual int GetJitterMin(void)=0;
	//max[5000-10000]
	virtual int SetJitterMax(int max)=0;
	virtual int GetJitterMax(void)=0;

	virtual int AddStreamOut(AUDEC_StreamOut*pStreamOut)=0;
	virtual int RemoveStreamOut(AUDEC_StreamOut*pStreamOut)=0;

	virtual int AddSampleOut(AUDEC_SampleOut*pSampleOut)=0;
	virtual int RemoveSampleOut(AUDEC_SampleOut*pSampleOut)=0;

	virtual int GetBufferedTime(void)=0;

	virtual int PlaySamples(short*pSamples,int nSamples,int nSampleRate,unsigned short usSeqNo)=0;

	virtual int SetSynFlag(int nFlag)=0;

	virtual int SetRecordSamples(AUDEC_RecordSamples*pRecordSamples)=0;

	virtual int SetSynFlag(int nFlag,unsigned long*pnVideoSynTime,unsigned long*pnAudioSynTime)=0;
};

class AUDEC_ENGINE_API AUDEC_RTPCall
{
public:
	AUDEC_RTPCall(void){}
	virtual~AUDEC_RTPCall(void){};
public:
	virtual int Connect(const char*cszLocalIP,unsigned short usLocalPort)=0;
	virtual void ReleaseConnections(void)=0;

	virtual int SetRemoteSDP(int nPayloadType,const char*cszPayloadName,const char*cszIP,unsigned short usPort)=0;

	virtual AUDEC_CapChan*GetCapChan(void)=0;
	virtual AUDEC_PlayChan*GetPlayChan(void)=0;

	virtual int SendDTMF(int nPayloadType,char dtmf)=0;
};


class AUDEC_ENGINE_API AUDEC_Engine
{
public:
	AUDEC_Engine(void){};
	virtual~AUDEC_Engine(void){};
public:
	static int AUDEC_Init(int nUsedByRS=0);
	//0:ok,<0:error
	static int AUDEC_Terminate(void);

	//0:no dev,>0:dev count <0:error
	static int AUDEC_GetMicNumDevs(void);
	//0:ok,<0:error
	static int AUDEC_GetMicDevDesc(int dev,char desc[]);

	//0:no dev,>0:dev count <0:error
	static int AUDEC_GetSpeakerNumDevs(void);
	//0:ok,<0:error
	static int AUDEC_GetSpeakerDevDesc(int dev,char desc[]);

	//0:no codec,>0:codec count,<0:error
	static int	AUDEC_GetNumCodecs(void);
	//0:ok,<0:error
	static int	AUDEC_GetCodecByIndex(int index,AUDEC_CodecInst*pCodecInst);
	//0:ok,<0:error
	static int	AUDEC_GetCodecByID(int id,AUDEC_CodecInst*pCodecInst);


	virtual int AUDEC_SetAEC(int nAEC)=0;//0:diable aec,1:enable aec
	virtual int AUDEC_GetAEC(void)=0;

	virtual int AUDEC_SetDefaultMicVolume(int nVolume)=0;
	virtual int AUDEC_GetDefaultMicVolume(void)=0;

	virtual int AUDEC_SetPreAGC(int nAGC)=0;
	virtual int AUDEC_GetPreAGC(void)=0;

	virtual int AUDEC_SetPostAGC(int nAGC)=0;
	virtual int AUDEC_GetPostAGC(void)=0;

	virtual int AUDEC_SetPreNS(int nNS)=0;
	virtual int AUDEC_GetPreNS(void)=0;

	virtual int AUDEC_SetVAD(int nVAD)=0;
	virtual int AUDEC_GetVAD(void)=0;

	virtual int AUDEC_SetFEC(int nFEC)=0;
	virtual int AUDEC_GetFEC(void)=0;

	virtual int AUDEC_SetSpeakerDev(int nDev)=0;
	virtual int AUDEC_SetMicDev(int nDev)=0;

	virtual int AUDEC_CreateCapChan(AUDEC_CapChan**ppCapChan)=0;
	virtual int AUDEC_CreateCapChanExternal(AUDEC_CapChanExternal**ppCapChanExternal)=0;
	virtual int AUDEC_CreatePlayChan(AUDEC_PlayChan**ppPlayChan)=0;


	//dtmf['0'-'9','#','*']
	virtual int AUDEC_PlayDTMF(char dtmf)=0;

	virtual int AUDEC_CreateRTPCall(AUDEC_RTPCall**ppRTPCall)=0;

	//for debug only
	//record pcm raw 16khz mono
	virtual int AUDEC_StartRecordPreAEC(FILE*hFile)=0;
	virtual int AUDEC_StopRecordPreAEC(void)=0;
	virtual int AUDEC_StartRecordPostAEC(FILE*hFile)=0;
	virtual int AUDEC_StopRecordPostAEC(void)=0;

#define	AUDEC_DTMF_RFC2833			0
#define AUDEC_DTMF_INBAND			1
	virtual int AUDEC_SetDTMFType(int nType)=0;
	virtual int AUDEC_GetDTMFType(void)=0;

	virtual int AUDEC_SetCNG(int nCNG)=0;
	virtual int AUDEC_GetCNG(void)=0;

	// nState以下值
	// 0 : 表示正常输入音量；
	// 1 : 表示输入音量过大，需要降低MIC音量
	// 2 : 表示输入音量过小，需要提升MIC音量
	// 3 : 表示背景噪音过大，需要适当降低音量，或关闭一个MIC.
	// 4 : 提示需要关闭MIC boost
	// 5 : 提示需要打开MIC boost
	virtual int AUDEC_GetMicrophoneVolumeState(int&nState)=0;
	virtual int AUDEC_SetMicBoost(int nMicBoost)=0;

	virtual int AUDEC_GetSpeakerLevel(void)=0;
};

AUDEC_ENGINE_API AUDEC_Engine&AUDEC_GetEngine(void);

#endif


