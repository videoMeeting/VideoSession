#ifndef __MYChannel_H__
#define __MYChannel_H__
/************************************************************************/
/* by zzw | 2013-7-10   11:44 My Local Headers                          */
/************************************************************************/

#include "VoeHeader.h"
using namespace webrtc;
#include "MyOutputMixer.h"
#include "AudioCodecModule.h"
//#include "FileWriter.h"

/************************************************************************/
/* by zzw | 2013-7-10   11:39 WebRTC Headers                            */
/************************************************************************/
#include "../webrtc/modules/interface/module_common_types.h"
#include "../webrtc/system_wrappers/interface/critical_section_wrapper.h"

//#include "webrtc/system_wrappers/interface/map_wrapper.h"
#include "../webrtc/modules/utility/interface/process_thread.h"
#include "../webrtc/modules/audio_device/include/audio_device.h"
#include "../webrtc/modules/audio_processing/include/audio_processing.h"

#include "../webrtc/modules/audio_conference_mixer/interface/audio_conference_mixer_defines.h"
#include "../webrtc/modules/audio_conference_mixer/interface/audio_conference_mixer.h"

/************************************************************************/
/* by zzw | 2013-7-10   11:39 NETEC Headers                             */
/************************************************************************/
#include "NETEC_MediaReceiver.h"
/************************************************************************/
/* by zzw | 2013-7-10   11:39  System Std Headers                       */
/************************************************************************/
#include <string>
#include <map>

class ChannelReceiverCallback
{
public:
    ~ChannelReceiverCallback() {}

    virtual void onVideoData(unsigned char*pData,int nLen);
};


class MyChannel : public NETEC_MediaReceiverCallback,
public MixerParticipant
{
public:
    static int32_t CreateChannel(MyChannel*& channel,
            unsigned long videoID);
    //void init();
    int32_t StartPlayout();
    int32_t StopPlayout();
    // Ready For Video
    int32_t StartReceiving();
    int32_t StopReceiving();
    // For Audio
    int32_t StartAudioReceiving();

    int32_t StopAudioReceiving();
    //////////////////////////////////////////////////////////////////////////
public:
    bool Receiving() const
    {
        return _receiving;
    }

    bool AudioReceiving() const
    {
        return _audio_receiving;
    }

    bool ExternalMixing() const
    {
        return _externalMixing;
    }

    bool Playing() const
    {
        return _playing;
    }

    // VoEExternalMediaProcessing
    int RegisterExternalMediaProcessing(ProcessingTypes type,
        VoEMediaProcess& processObject);
    int DeRegisterExternalMediaProcessing(ProcessingTypes type);
    int SetExternalMixing(bool enabled);

    uint32_t LastRemoteTimeStamp() { return _lastRemoteTimeStamp; }

    int SetRxAgcStatus(bool enable, AgcModes mode);

    int SetRxNsStatus(bool enable, NsModes mode);

    //////////////////////////////////////////////////////////////////////////
    int RegisterMediaCallback(ChannelReceiverCallback &callback);
    
    int DeRegisterMediaCallback();

public:
    MyChannel(unsigned long videoID);
    virtual ~MyChannel();
public:
    
    int32_t Init();

    int32_t SetEngineInformation(
        MyOutputMixer& outputMixer,
        //TransmitMixer& transmitMixer,
        ProcessThread& moduleProcessThread,
        AudioDeviceModule& audioDeviceModule,
        //VoiceEngineObserver* voiceEngineObserver,
        CriticalSectionWrapper* callbackCritSect,
        const std::string &server_ip, unsigned int uiPort);

    

public:
    /************************************************************************/
    /* by zzw | 2013-7-10   10:58 NETEC_MediaReceiverCallback               */
    /************************************************************************/
    /******************************************************************************
	* OnNETEC_MediaReceiverCallbackAudioPacket
	*描述：接收到音频数据包的回调
	*输入：	pData			-数据包指针
			nLen			-数据包长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char*pData,int nLen);

	/******************************************************************************
	* OnNETEC_MediaReceiverCallbackVideoPacket
	*描述：接收到视频数据包的回调
	*输入：	pData			-数据包指针
			nLen			-数据包长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char*pData,int nLen);


    /************************************************************************/
    /* by zzw | 2013-7-10   11:01  inherited from MixerParticipant          */
    /************************************************************************/
    // The implementation of this function should update audioFrame with new
    // audio every time it's called.
    //
    // If it returns -1, the frame will not be added to the mix.
    virtual int32_t GetAudioFrame(const int32_t id, AudioFrame& audioFrame);

    // mixed will be set to true if the participant was mixed this mix iteration
    //int32_t IsMixed(bool& mixed) const;

    // This function specifies the sampling frequency needed for the AudioFrame
    // for future GetAudioFrame(..) calls.
    virtual int32_t NeededFrequency(const int32_t id);
private:
    int32_t SetServerIP(const char* serverip, unsigned int uiPort);

    int ApmProcessRx(AudioFrame& frame);

private:
    /************************************************************************/
    /* by zzw | 2013-7-10   10:53 For Media   Receiver                      */
    /************************************************************************/
    //NETEC_MediaReceiver*	m_pMediaReceiver;
    unsigned long           m_ulPeerVideoID ;			//VideoID
    unsigned long           m_ulPeerAudioID ;			//AudioID
    char				    m_strServerIP[255];

    char                    m_peer_nodeid[255];
    char                    m_peer_nataddr[255];/*对方NAT地址*/	
    char                    m_peer_locaddr[255];/*对方本地地址*/
    int                     m_peer_locport;/*对方本地端口*/
    char       	            m_peer_mcuid[255];/*对方MCUID*/
    char       	            m_peer_mcuaddr[255];/*对方MCU地址*/
    int		                m_peer_mcuport;/*对方MCU端口*/
    /************************************************************************/
    /* by zzw | 2013-7-10   11:04                          */
    /************************************************************************/
    MyOutputMixer*          _outputMixerPtr;
    
    AudioFrame              _audioFrame;
    // For Test
    //MapWrapper              _mMapWrapper;
    CriticalSectionWrapper& _callbackCritSect;
    CriticalSectionWrapper* _callbackCritSectPtr;
    ProcessThread       * _moduleProcessThreadPtr;
    AudioDeviceModule   * _audioDeviceModulePtr;
    /************************************************************************/
    /* by zzw | 2013-7-14   12:33                          */
    /************************************************************************/
    bool _receiving;
    bool _audio_receiving;
    bool _playing;
    bool _audio_playing;
    //////////////////////////////////////////////////////////////////////////
    bool _inputExternalMedia;
    bool _outputExternalMedia;
    VoEMediaProcess* _inputExternalMediaCallbackPtr;
    VoEMediaProcess* _outputExternalMediaCallbackPtr;
    //////////////////////////////////////////////////////////////////////////
    
    bool _externalMixing;
    /************************************************************************/
    /* by zzw | 2013-7-14   21:10                          */
    /************************************************************************/
    uint32_t _lastLocalTimeStamp;
    uint32_t _lastRemoteTimeStamp;
    /************************************************************************/
    /* by zzw | 2013-7-16   13:50                          */
    /************************************************************************/
    AudioCodecModule    &_audioCodecModule;

    scoped_ptr<AudioProcessing> _audioProc;
    AudioProcessing* _rxAudioProcessingModulePtr;

    bool _rxApmIsEnabled;
    bool _rxAgcIsEnabled;
    bool _rxNsIsEnabled;
    //////////////////////////////////////////////////////////////////////////
    
   // FileWriter  *_fileWriter;

    bool _outputMedia;
    ChannelReceiverCallback         *_ptrChannelReceiverCallback;

   // FileWriter  *_file_audio_queue_index;
};

#endif