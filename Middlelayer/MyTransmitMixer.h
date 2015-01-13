#ifndef __MY_TRANSMIT_MIXER_H__
#define __MY_TRANSMIT_MIXER_H__

/************************************************************************/
/* by zzw | 2013-7-15   0:22                          */
/************************************************************************/
#include "VoeHeader.h"
#include "AudioCodecModule.h"
#include "OpenLocalUser.h"
//#include "FileWriter.h"

/************************************************************************/
/* by zzw | 2013-7-15   0:20                          */
/************************************************************************/
#include "../webrtc/system_wrappers/interface/critical_section_wrapper.h"
#include "../webrtc/modules/interface/module_common_types.h"
#include "../webrtc/modules/audio_processing/include/audio_processing.h"
#include "../webrtc/modules/utility/interface/process_thread.h"
#include "../webrtc/common_audio/resampler/include/push_resampler.h"

using namespace webrtc;
/************************************************************************/
/* by zzw | 2013-7-15   0:21  NETEC Headers                             */
/************************************************************************/
#include "../../include/NETEC/NETEC_MediaSender.h"
/************************************************************************/
/* by zzw | 2013-7-15   2:56   System STL Headers                       */
/************************************************************************/
#include <string>


/************************************************************************/
/* by zzw | 2013-7-15   2:57                          */
/************************************************************************/
class MyTransmitMixer : public NETEC_MediaSenderCallback
    , public AudioCodingCallback
{
public:
    static int32_t Create(MyTransmitMixer*&mixer, uint32_t instanceId);

    static void Destory(MyTransmitMixer*&mixer);

    int32_t SetEngineInformation(ProcessThread& processThread);

    int32_t Init();

    int32_t UnInit();

    int32_t SetAudioProcessingModule(AudioProcessing* audioProcessingModule);

    int GenerateAudioFrame(const int16_t audioSamples[],
        int nSamples,
        int nChannels,
        int samplesPerSec);

    int32_t PrepareDemux(const void* audioSamples,
        uint32_t nSamples,
        uint8_t  nChannels,
        uint32_t samplesPerSec,
        uint16_t totalDelayMS,
        int32_t  clockDrift,
        uint16_t currentMicLevel,
        bool keyPressed);

    int32_t DemuxAndMix();

    int32_t EncodeAndSend();
    // VoEExternalMedia
    int RegisterExternalMediaProcessing(VoEMediaProcess* object,
        ProcessingTypes type);
    int DeRegisterExternalMediaProcessing(ProcessingTypes type);

    int SetMute(bool enable);

    bool Mute() const;

    void SetVideoID(OpenLocalUser* pOpenLocalUser);

    uint32_t CaptureLevel() const;

    ~MyTransmitMixer();

    /************************************************************************/
    /* by zzw | 2013-7-15   2:59 For NETEC Sender                           */
    /************************************************************************/
    void SetServerIP(const char* strServerIP, unsigned int uiPort);
    
    int32_t StartVideoSender();

    void StopVideoSender();
    /************************************************************************/
    /* by zzw | 2013-7-18   13:31                          */
    /************************************************************************/
    int32_t StartAudioSender();
    /************************************************************************/
    /* by zzw | 2013-7-18   13:31                          */
    /************************************************************************/
    void StopAudioSender();

    void ProcessVideoFrame(char*pData, int nLen, bool bKeyFrame, unsigned long ulTimestamp, int nWidth, int nHeight);
    
    void StopSendAudio();
    void StartSendAudio();
protected:
    // ACM AudioCodingCallback
    virtual int32_t SendData(uint32_t timestamp,
        const char* payload_data,
        uint16_t payload_len_bytes);

private:
    MyTransmitMixer(uint32_t instanceId);
    // APM 
    void ProcessAudio(int delay_ms, int clock_drift, int current_mic_level);
    // NETEC
    virtual int32_t ProcessAudioFrame(char*pData, int nLen, unsigned long ulTimestamp);

private:
    bool _saturationWarning;
    int _instanceId;

    AudioProcessing* audioproc_;
    ProcessThread* _processThreadPtr;

    AudioFrame _audioFrame;
    PushResampler resampler_;  // ADM sample rate -> mixing rate
    CriticalSectionWrapper& _critSect;
    CriticalSectionWrapper& _callbackCritSect;
    VoEMediaProcess* external_postproc_ptr_;
    VoEMediaProcess* external_preproc_ptr_;
    bool _mute;
    uint32_t _captureLevel;
    //////////////////////////////////////////////////////////////////////////
    
    //NETEC_MediaSender*		m_pMediaSender;
    char             m_strServerIP[255];
    unsigned int     m_uiPort;
    OpenLocalUser*          m_pOpenLocalUser;
    unsigned long           m_ulLocalVideoID;
    unsigned long           m_ulLocalAudioID;
    //////////////////////////////////////////////////////////////////////////
    // VIDEO
    char*					m_pVideoPacket;
    int						m_nFrameBufferLength;
    bool					m_bGotKeyFrameMain;
    unsigned short			m_usVideoSequence;
    // AUDIO
    char*					m_pAudioPacket;
    int                     m_nAudioFrameBufferLength;
    unsigned long           m_ulLastFrameTimestamp;
    unsigned long           m_ulLastPacketTimestamp;
    unsigned short	        m_usAudioSequence;
    //////////////////////////////////////////////////////////////////////////
    
    AudioCodecModule&       _audioCodingModule;

    uint32_t                _timeStamp;
    bool                    m_IsSendAudio;
    bool                    stereo_codec_;
    //////////////////////////////////////////////////////////////////////////
#if 0
    FileWriter              *_file_writer;
    FileWriter              *_aec_in_file_writer;
    FileWriter              *_aec_out_file_writer;
    FileWriter              *_audio_send_file_writer;
#endif
};

#endif