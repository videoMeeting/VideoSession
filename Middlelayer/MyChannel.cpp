#include "MyChannel.h"

#define LOG_TAG "WebRTC Voe | MyChannel"

#define ENABLE_APM 1

#define LOGI printf
#define LOGE printf
//#define DEFAULT_PORT 4222

#include <AUDEC/AUDEC_Header.h>
#include <AUDEC/AUDEC_CodecID.h>

/************************************************************************/
/* by zzw | 2013-7-15   1:35 Audio Headers                              */
/************************************************************************/
//#include <Audio/Audio_Header.h>
/************************************************************************/
/* by zzw | 2013-7-17   17:18  WebRTC                                   */
/************************************************************************/
#include "../webrtc/voice_engine_defines.h"

namespace webrtc {
    // Cheshire cat implementation of MixerParticipant's non virtual functions.
    class MixHistory
    {
    public:
        MixHistory();
        ~MixHistory();
        
        // MixerParticipant function
        int32_t IsMixed(bool& mixed) const;
        
        // Sets wasMixed to true if the participant was mixed previous mix
        // iteration.
        int32_t WasMixed(bool& wasMixed) const;
        
        // Updates the mixed status.
        int32_t SetIsMixed(const bool mixed);
        
        void ResetMixedStatus();
    private:
        bool _isMixed;
    };
}

MixerParticipant::MixerParticipant()
: _mixHistory(new MixHistory())
{
}

MixerParticipant::~MixerParticipant()
{
    if (_mixHistory) {
          delete _mixHistory;
        _mixHistory=NULL;
    }
  
}

int32_t MixerParticipant::IsMixed(bool& mixed) const
{
    return _mixHistory->IsMixed(mixed);
}


int32_t MyChannel::CreateChannel(MyChannel*& channel,unsigned long videoID)
{
    channel = new MyChannel(videoID);
    if (channel == NULL)
    {
        return -1;
    }
    return 0;
}

MyChannel::MyChannel(unsigned long videoID):m_ulPeerVideoID(videoID)
    , m_ulPeerAudioID(videoID)
    , _callbackCritSect(*CriticalSectionWrapper::CreateCriticalSection())
    , _outputMixerPtr(NULL)
    , _moduleProcessThreadPtr(NULL)
    , _audioDeviceModulePtr(NULL)
    //, m_pMediaReceiver(NULL)
    //////////////////////////////////////////////////////////////////////////
    , _receiving(false)
    , _audio_receiving(false)
    , _playing(false)
    , _audio_playing(false)
    //////////////////////////////////////////////////////////////////////////
    , _inputExternalMedia(false)
    , _outputExternalMedia(false)
    , _inputExternalMediaCallbackPtr(NULL)
    , _outputExternalMediaCallbackPtr(NULL)
    , _externalMixing(false)
    , _callbackCritSectPtr(NULL)
    //////////////////////////////////////////////////////////////////////////
    , _lastLocalTimeStamp(0)
    , _lastRemoteTimeStamp(0)
    , _audioCodecModule(*AudioCodecModule::Create(videoID))
    //////////////////////////////////////////////////////////////////////////
    // For NETEC Receiver
    , m_strServerIP("")
    , m_peer_nodeid("")
    , m_peer_nataddr("")/*对方NAT地址*/	
    , m_peer_locaddr("")/*对方本地地址*/
    , m_peer_locport(0)/*对方本地端口*/
    , m_peer_mcuid("MCU001")/*对方MCUID*/
    , m_peer_mcuaddr("")/*对方MCU地址*/
    , m_peer_mcuport(0)/* */
    //////////////////////////////////////////////////////////////////////////
    , _rxApmIsEnabled(false)
    , _rxAgcIsEnabled(false)
    , _rxNsIsEnabled(false)
    //////////////////////////////////////////////////////////////////////////
    //, _fileWriter(NULL)
    , _ptrChannelReceiverCallback(NULL)
    , _outputMedia(false)
    //, _file_audio_queue_index(NULL)
{
    LOGI("[MyChannel] MyChannel::MyChannel ctor");
    LOGI("[MyChannel] m_ulPeerVideoID:%lu",m_ulPeerVideoID);
    LOGI("[MyChannel] m_ulPeerAudioID:%lu",m_ulPeerAudioID);

    _rxAudioProcessingModulePtr = AudioProcessing::Create(videoID >> 16);

#if 0
    char file_name[120];
    memset(file_name,0,120);

    sprintf(file_name,"/storage/sdcard0/rec_%u.pcm",videoID);

    _fileWriter = new FileWriter();
    if(!_fileWriter->SetFileName(file_name))
    {
        LOGE("[MyChannel] File Open Failed %s",file_name);
    }
    else
    {
        _audioCodecModule.setFileWriter(_fileWriter);
    }

    if (_file_audio_queue_index == NULL)
    {
        _file_audio_queue_index = new FileWriter();
        char file_name[120];
        memset(file_name,0,120);
        sprintf(file_name,"/storage/sdcard0/VSMeeting/audio_queue_receive_%u.txt",videoID);
        if(!_file_audio_queue_index->SetFileNameTxt(file_name))
        {

        }
    }
#endif

}

int32_t MyChannel::Init()
{
    if (_moduleProcessThreadPtr == NULL || strlen(m_strServerIP) == 0)
    {
        LOGE("[MyChannel] Channel::Init() must call SetEngineInformation() first");
        return -1;
    }
#if 0
    if (m_pMediaReceiver == NULL)
    {
        m_pMediaReceiver = NETEC_MediaReceiver::Create(*this);
        if (m_pMediaReceiver != NULL)
        {
            m_pMediaReceiver->SetLocalMCUID("MCU001");
            m_pMediaReceiver->SetLocalMCIIP(m_strServerIP);
            m_pMediaReceiver->SetLocalMCUPort(m_peer_mcuport);

            int nRet = m_pMediaReceiver->Open(m_peer_nodeid, m_peer_nataddr, m_peer_locaddr, 
                m_peer_locport, m_peer_mcuid, m_peer_mcuaddr, m_peer_mcuport);
            if (0 != nRet)
            {
                m_pMediaReceiver->Close();
                delete m_pMediaReceiver;
                m_pMediaReceiver=NULL;
                return -1;
            }
        }
        else
        {
            LOGE("[MyChannel] Allocate NETEC_MediaReceiver Failed");
            return -1;
        }
    }
#endif

    if(_audioCodecModule.Init() != 0 )
    {
        return -1;
    }

#if ENABLE_APM
    if (_rxAudioProcessingModulePtr == NULL)
    {
        LOGE("[MyChannel] MyChannel::Init() failed to create the far-end AudioProcessing"
            " module");
        return -1;
    }

    if (_rxAudioProcessingModulePtr->set_sample_rate_hz(16000))
    {
        LOGE("[MyChannel] MyChannel::Init() failed to set the sample rate to 8K for"
            " far-end AP module");
    }

    if (_rxAudioProcessingModulePtr->set_num_channels(1,1) != 0)
    {
        LOGE("[MyChannel] Init() failed to set channels for the primary audio stream");
    }

    if (_rxAudioProcessingModulePtr->high_pass_filter()->Enable(WEBRTC_VOICE_ENGINE_RX_HP_DEFAULT_STATE) != 0)
    {
        LOGE("[MyChannel] MyChannel::Init() failed to set the high-pass filter for"
            " far-end AP module");
    }

    if (_rxAudioProcessingModulePtr->noise_suppression()->set_level((NoiseSuppression::Level)WEBRTC_VOICE_ENGINE_RX_NS_DEFAULT_MODE) != 0)
    {
        LOGE("[MyChannel] MyChannel::Init() failed to set noise reduction level for far-end"
            " AP module");
    }

    if (_rxAudioProcessingModulePtr->noise_suppression()->Enable(WEBRTC_VOICE_ENGINE_RX_NS_DEFAULT_STATE) != 0)
    {
        LOGE("[MyChannel] Init() failed to set noise reduction state for far-end"
            " AP module");
    }

    if (_rxAudioProcessingModulePtr->gain_control()->set_mode((GainControl::Mode)WEBRTC_VOICE_ENGINE_RX_AGC_DEFAULT_MODE) != 0)
    {
        LOGE("[MyChannel] Init() failed to set AGC mode for far-end AP module");
    }

    if (_rxAudioProcessingModulePtr->gain_control()->Enable(WEBRTC_VOICE_ENGINE_RX_AGC_DEFAULT_STATE) != 0)
    {
        LOGE("[MyChannel] Init() failed to set AGC state for far-end AP module");
    }
#endif
    

    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-16   13:53                          */
/************************************************************************/
int32_t MyChannel::SetEngineInformation(
                             MyOutputMixer& outputMixer,
                             //TransmitMixer& transmitMixer,
                             ProcessThread& moduleProcessThread,
                             AudioDeviceModule& audioDeviceModule,
                             //VoiceEngineObserver* voiceEngineObserver,
                             CriticalSectionWrapper* callbackCritSect,
                             const std::string &server_ip, unsigned int uiPort)
{
    _outputMixerPtr = &outputMixer;
    _moduleProcessThreadPtr = &moduleProcessThread;
    _audioDeviceModulePtr = &audioDeviceModule;
    _callbackCritSectPtr = callbackCritSect;
    // add by zzw
    SetServerIP(server_ip.c_str(),uiPort);
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-16   13:53                          */
/************************************************************************/
MyChannel::~MyChannel()
{
    if (_outputExternalMedia)
    {
        DeRegisterExternalMediaProcessing(kPlaybackPerChannel);
    }

    if (_inputExternalMedia)
    {
        DeRegisterExternalMediaProcessing(kRecordingPreprocessing);
    }

    StopAudioReceiving();

    StopPlayout();
#if 0
    if (m_pMediaReceiver != NULL)
    {
        m_pMediaReceiver->Close();
        delete m_pMediaReceiver;
        m_pMediaReceiver = NULL;
    }
#endif
    AudioCodecModule *_audioCodecModulePtr = &_audioCodecModule;
    AudioCodecModule::Destroy(_audioCodecModulePtr);

    if (_rxAudioProcessingModulePtr != NULL)
    {
        AudioProcessing::Destroy(_rxAudioProcessingModulePtr);
        _rxAudioProcessingModulePtr = NULL;
    }
#if 0
    if (_fileWriter != NULL)
    {
        delete _fileWriter;
        _fileWriter = NULL;
    }

    if (_file_audio_queue_index != NULL)
    {
        delete _file_audio_queue_index;
        _file_audio_queue_index = NULL;
    }
#endif
    delete &_callbackCritSect;
    if (_mixHistory) {
        delete _mixHistory;
        _mixHistory=NULL;
    }
    
}
/************************************************************************/
/* by zzw | 2013-7-14   12:31                          */
/************************************************************************/
int32_t MyChannel::StartPlayout()
{
    LOGI("[MyChannel] MyChannel::StartPlayout()");
    if (_playing)
    {
        //LOGW("[MyChannel] MyChannel::StartPlayout() is already Palying");
        return 0;
    }

    if (!_externalMixing)
    {
        if (_outputMixerPtr->SetMixabilityStatus(*this,true) != 0)
        {
            LOGE("[MyChannel] StartPlayout() failed to add participant to mixer");
            return -1;
        }
    }
    
    _playing = true;

    //LOGD("[MyChannel]  MyChannel::StartPlayout() OK");
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-16   13:38                          */
/************************************************************************/
int32_t MyChannel::StopPlayout()
{
    if (!_playing)
    {
        //LOGW("[MyChannel] MyChannel::StopPlayout() Not palyed");
        return 0;
    }

    if (!_externalMixing)
    {
        if(_outputMixerPtr->SetMixabilityStatus(*this,false) != 0)
        {
            return -1;
        }
    }

    _playing = false;

   // LOGD("[MyChannel]  MyChannel::StopPlayout() OK");
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-21   17:48                          */
/************************************************************************/
int32_t MyChannel::StartReceiving()
{
    if (_receiving)
    {
        return 0;
    }
#if 0
    if (m_pMediaReceiver == NULL || m_ulPeerVideoID ==0)
    {
        LOGE("[MyChannel] MyTransmitMixer::StartPlayout() must call Init() first");
        return -1;
    }
    if( 0 != m_pMediaReceiver->SetVideoID(m_ulPeerVideoID))
    {
        LOGE("[MyChannel] NETEC_MediaReceiver::SetVideoID() Failed");
        return -1;
    }
    if( 0 != m_pMediaReceiver->StartVideo())
    {
        LOGE("[MyChannel] NETEC_MediaReceiver::StartVideo() Failed");
        return -1;
    }
#endif
    _receiving = true;
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-21   17:47                          */
/************************************************************************/
int32_t MyChannel::StopReceiving()
{
    if (!_receiving)
    {
        return 0;
    }
#if 0
    if (m_pMediaReceiver == NULL || m_ulPeerVideoID ==0)
    {
        return -1;
    }
    m_pMediaReceiver->StopVideo();
#endif
    _receiving = false;
    return 0;
}

int32_t MyChannel::StartAudioReceiving()
{
    if (_audio_receiving)
    {
        LOGE("[MyChannel] MyTransmitMixer::StartAudioReceiving() is Receiving");
        return 0;
    }
#if 0
    if (m_pMediaReceiver == NULL || m_ulPeerAudioID ==0)
    {
        LOGE("[MyChannel] MyTransmitMixer::StartPlayout() must call Init() first");
        return -1;
    }
    if( 0 != m_pMediaReceiver->SetAudioID(m_ulPeerAudioID))
    {
        LOGE("[MyChannel] NETEC_MediaReceiver::SetAudioID() Failed");
        return -1;
    }
    if( 0 != m_pMediaReceiver->StartAudio())
    {
        LOGE("[MyChannel] NETEC_MediaReceiver::StartAudio() Failed");
        return -1;
    }
#endif
    _audio_receiving = true;
    return 0;
}

int32_t MyChannel::StopAudioReceiving()
{
    if (!_audio_receiving)
    {
        LOGE("[MyChannel] MyTransmitMixer::StopAudioReceiving() is Not Receiving");
        return 0;
    }
#if 0
    if (m_pMediaReceiver == NULL || m_ulPeerAudioID == 0 )
    {
        return -1;
    }

    m_pMediaReceiver->StopAudio();
#endif

    _audio_receiving = false;
    return 0;
}

int MyChannel::RegisterExternalMediaProcessing(ProcessingTypes type,
                                    VoEMediaProcess& processObject)
{
    CriticalSectionScoped cs(&_callbackCritSect);

    if (kPlaybackPerChannel == type)
    {
        if (_outputExternalMediaCallbackPtr)
        {
            LOGI("[MyChannel] "
                "Channel::RegisterExternalMediaProcessing() "
                "output external media already enabled");
            return -1;
        }
        _outputExternalMediaCallbackPtr = &processObject;
        _outputExternalMedia = true;
    }
    else if (kRecordingPerChannel == type)
    {
        if (_inputExternalMediaCallbackPtr)
        {
            LOGI("[MyChannel] "
                "Channel::RegisterExternalMediaProcessing() "
                "output external media already enabled");
            return -1;
        }
        _inputExternalMediaCallbackPtr = &processObject;
        _inputExternalMedia = true;
    }
    return 0;
}

int MyChannel::DeRegisterExternalMediaProcessing(ProcessingTypes type)
{
    CriticalSectionScoped cs(&_callbackCritSect);

    if (kPlaybackPerChannel == type)
    {
        if (!_outputExternalMediaCallbackPtr)
        {
            LOGI("[MyChannel] "
                "Channel::DeRegisterExternalMediaProcessing() "
                "output external media already disabled");
            return 0;
        }
        _outputExternalMedia = false;
        _outputExternalMediaCallbackPtr = NULL;
    }
    else if (kRecordingPerChannel == type)
    {
        if (!_inputExternalMediaCallbackPtr)
        {
            LOGI("[MyChannel] "
                "Channel::DeRegisterExternalMediaProcessing() "
                "input external media already disabled");
            return 0;
        }
        _inputExternalMedia = false;
        _inputExternalMediaCallbackPtr = NULL;
    }

    return 0;
}

int MyChannel::RegisterMediaCallback(ChannelReceiverCallback &callback)
{
    CriticalSectionScoped cs(&_callbackCritSect);
    if (!_ptrChannelReceiverCallback)
    {
        return 0;
    }
    _ptrChannelReceiverCallback = &callback;
    _outputMedia = true;
      return 0;
}
int MyChannel::DeRegisterMediaCallback()
{
    CriticalSectionScoped cs(&_callbackCritSect);
    _outputMedia = false;
    _ptrChannelReceiverCallback = NULL;
      return 0;
}

int MyChannel::SetExternalMixing(bool enabled)
{
    if (_playing)
    {
        return -1;
    }
    _externalMixing = enabled;
      return 0;
}

int MyChannel::SetRxAgcStatus(bool enable, AgcModes mode)
{
    GainControl::Mode agcMode(GainControl::kFixedDigital);
    switch (mode)
    {
    case kAgcDefault:
        agcMode = GainControl::kAdaptiveDigital;
        break;
    case kAgcUnchanged:
        agcMode = _rxAudioProcessingModulePtr->gain_control()->mode();
        break;
    case kAgcFixedDigital:
        agcMode = GainControl::kFixedDigital;
        break;
    case kAgcAdaptiveDigital:
        agcMode =GainControl::kAdaptiveDigital;
        break;
    default:
        LOGE("[MyChannel] SetRxAgcStatus() invalid Agc mode");
        return -1;
    }

    if (_rxAudioProcessingModulePtr->gain_control()->set_mode(agcMode) != 0)
    {
        LOGE("[MyChannel] SetRxAgcStatus() failed to set Agc mode");
        return -1;
    }
    if (_rxAudioProcessingModulePtr->gain_control()->Enable(enable) != 0)
    {
        LOGE("[MyChannel] SetRxAgcStatus() failed to set Agc state");
        return -1;
    }

    _rxAgcIsEnabled = enable;
    _rxApmIsEnabled = ((_rxAgcIsEnabled == true) || (_rxNsIsEnabled == true));
    return 0;
}

int MyChannel::SetRxNsStatus(bool enable, NsModes mode)
{
    NoiseSuppression::Level nsLevel(
        (NoiseSuppression::Level)WEBRTC_VOICE_ENGINE_RX_NS_DEFAULT_MODE);
    switch (mode)
    {

    case kNsDefault:
        nsLevel = (NoiseSuppression::Level)
            WEBRTC_VOICE_ENGINE_RX_NS_DEFAULT_MODE;
        break;
    case kNsUnchanged:
        nsLevel = _rxAudioProcessingModulePtr->noise_suppression()->level();
        break;
    case kNsConference:
        nsLevel = NoiseSuppression::kHigh;
        break;
    case kNsLowSuppression:
        nsLevel = NoiseSuppression::kLow;
        break;
    case kNsModerateSuppression:
        nsLevel = NoiseSuppression::kModerate;
        break;
    case kNsHighSuppression:
        nsLevel = NoiseSuppression::kHigh;
        break;
    case kNsVeryHighSuppression:
        nsLevel = NoiseSuppression::kVeryHigh;
        break;
    }

    if (_rxAudioProcessingModulePtr->noise_suppression()->set_level(nsLevel)
        != 0)
    {
        LOGE("[MyChannel] SetRxAgcStatus() failed to set Ns level");
        return -1;
    }
    if (_rxAudioProcessingModulePtr->noise_suppression()->Enable(enable) != 0)
    {
        LOGE("[MyChannel] SetRxAgcStatus() failed to set Agc state");
        return -1;
    }

    _rxNsIsEnabled = enable;
    _rxApmIsEnabled = ((_rxAgcIsEnabled == true) || (_rxNsIsEnabled == true));

    return 0;
}

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
void MyChannel::OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char*pData,int nLen)
{
    //LOGF("[MyChannel] MyChannel::OnNETEC_MediaReceiverCallbackAudioPacket %u",TimeGetTimestamp());
    if (!_playing)
    {
        LOGI("[MyChannel] OnNETEC_MediaReceiverCallbackAudioPacket");
        return;
    }

    // Push the incoming data to ACM (Audio Codec Module)
    // 
    // Decode AudioData

    _lastRemoteTimeStamp    = AUDEC_HEADER_GET_TIMESTAMP(pData);//rtpHeader->header.timestamp;

    int nHeaderSize         = AUDEC_HEADER_GET_LEN(pData);
//      unsigned short nQueue   =
   AUDEC_HEADER_GET_SEQUENCE(pData);

    int nDataLength = nLen-nHeaderSize;

    if(_audioCodecModule.IncomingPacket((const uint8_t *)(pData+nHeaderSize),nDataLength) != 0)
    {
        LOGI("[MyChannel] MyChannel::OnReceivedPayloadData() unable to push data to the ACM");
    }
    //LOGI("[MyChannel] _lastRemoteTimeStamp:%d",_lastRemoteTimeStamp);
}
/******************************************************************************
* OnNETEC_MediaReceiverCallbackVideoPacket
*描述：接收到视频数据包的回调
*输入：	pData			-数据包指针
		nLen			-数据包长度
*输出： 无
*返回值：无
*****************************************************************************/
void MyChannel::OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char*pData,int nLen)
{
    //LOGD("[MyChannel] OnNETEC_MediaReceiverCallbackVideoPacket");

    CriticalSectionScoped cs(&_callbackCritSect);
    if (_ptrChannelReceiverCallback)
    {
        _ptrChannelReceiverCallback->onVideoData(pData,nLen);
    }
}

/************************************************************************/
/* by zzw | 2013-7-10   11:01  inherited from MixerParticipant          */
/************************************************************************/
// The implementation of this function should update audioFrame with new
// audio every time it's called.
//
// If it returns -1, the frame will not be added to the mix.
int32_t MyChannel::GetAudioFrame(const int32_t id, AudioFrame& audioFrame)
{
    //LOGF("[MyChannnel] MyChannel::GetAudioFrame() %u",TimeGetTimestamp());
    // Get PCM Data from ACM (Audio Codec Module)
    if(_audioCodecModule.PlayoutData10Ms(audioFrame.sample_rate_hz_,
        &audioFrame) != 0)
    {
        LOGI("[MyChannel] MyChannel::GetAudioFrame() PlayoutData10Ms() failed!");
        return -1;
    }

    if (_rxApmIsEnabled)
    {
        //ApmProcessRx(audioFrame);
    }

    return 0;
}

// mixed will be set to true if the participant was mixed this mix iteration
//int32_t MyChannel::IsMixed(bool& mixed) const
//{
//    return 0;
//}

// This function specifies the sampling frequency needed for the AudioFrame
// for future GetAudioFrame(..) calls.
int32_t MyChannel::NeededFrequency(const int32_t id)
{
    return 16000;
}


/************************************************************************/
/* by zzw | 2013-7-15   2:46 Private                                    */
/************************************************************************/
int32_t MyChannel::SetServerIP(const char* serverIP, unsigned int uiPort)
{
    m_peer_locport = uiPort;/*对方本地端口*/
    m_peer_mcuport = uiPort;
    
    strcpy(m_strServerIP, serverIP);
    strcpy(m_peer_mcuaddr, m_strServerIP);
    strcpy(m_peer_nataddr, m_strServerIP);
    strcpy(m_peer_locaddr, m_strServerIP);
    return 0;
}


int MyChannel::ApmProcessRx(AudioFrame& frame) {
    AudioProcessing* audioproc = _rxAudioProcessingModulePtr;
    // Register the (possibly new) frame parameters.
    if (audioproc->set_sample_rate_hz(frame.sample_rate_hz_) != 0) {
        LOGI("[MyChannel] MyChannel::ApmProcessRx set_sample_rate_hz:%d", frame.sample_rate_hz_);
    }
    if (audioproc->set_num_channels(frame.num_channels_,
        frame.num_channels_) != 0) {
            LOGI("[MyChannel] MyChannel::ApmProcessRx set_num_channels:%d", frame.num_channels_);
    }
    if (audioproc->ProcessStream(&frame) != 0) {
        LOGI("[MyChannel] MyChannel::ApmProcessRx ProcessStream Failed");
    }
    return 0;
}