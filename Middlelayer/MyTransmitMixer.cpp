#include "MyTransmitMixer.h"
#include <AUDEC/AUDEC_Header.h>
#include <AUDEC/AUDEC_CodecID.h>
//#include "LocalConfig.h"
//#define DEFAULT_PORT 4222
#define LOG_TAG "WebRTC Voe | MyTransmitMixer"
#define LOGI printf
#define LOGE printf
#define LOGW printf
/************************************************************************/
/* by zzw | 2013-7-15   11:31  NETEC Headers                            */
/************************************************************************/
//#include "Audio/Audio_Header.h"
//#include "Audio/Audio_CodecID.h"
//#include "VIDEC/VIDEC_Header.h"

/************************************************************************/
/* by zzw | 2013-7-15   1:19 WebRTC Headers                             */
/************************************************************************/
#include "../webrtc/modules/utility/interface/audio_frame_operations.h"

int32_t MyTransmitMixer::Create(MyTransmitMixer*&mixer, uint32_t instanceId)
{
    mixer = new MyTransmitMixer(instanceId);
    if (mixer == NULL)
    {
        return -1;
    }
    return 0;
}

void MyTransmitMixer::Destory(MyTransmitMixer*&mixer)
{
    if (mixer != NULL)
    {
        delete mixer;
        mixer = NULL;
    }
}

MyTransmitMixer::MyTransmitMixer(uint32_t instanceId):
_instanceId(instanceId),
_critSect(*CriticalSectionWrapper::CreateCriticalSection()),
_callbackCritSect(*CriticalSectionWrapper::CreateCriticalSection()),
audioproc_(NULL),
_processThreadPtr(NULL),
_saturationWarning(false),
_captureLevel(0),
external_postproc_ptr_(NULL),
external_preproc_ptr_(NULL),
_mute(false)
//////////////////////////////////////////////////////////////////////////
// For NETEC Sender
//, m_pMediaSender(NULL)
, m_pOpenLocalUser(NULL)
, m_strServerIP("")
, m_ulLocalVideoID(0)
, m_ulLocalAudioID(0)
, m_pVideoPacket(NULL)
, m_nFrameBufferLength(0)
, m_bGotKeyFrameMain(false)
, m_usVideoSequence(0)
, m_pAudioPacket(NULL)
, m_nAudioFrameBufferLength(0)
, m_ulLastFrameTimestamp(0)
, m_ulLastPacketTimestamp(0)
, m_usAudioSequence(0)
//////////////////////////////////////////////////////////////////////////
, _audioCodingModule(*AudioCodecModule::Create((int32_t)(instanceId >> 16)))
, _timeStamp(0)
, stereo_codec_(false)
, m_IsSendAudio(true)
#if 0
, _file_writer(NULL)
, _aec_in_file_writer(NULL)
, _aec_out_file_writer(NULL)
, _audio_send_file_writer(NULL)
#endif
{
    LOGI("[MyTransmitMixer] MyTransmitMixer::MyTransmitMixer() - ctor");
    _audioCodingModule.Init();
    _audioCodingModule.RegisterTransportCallback(this);
#if 0
    /*
    _file_writer = new FileWriter();
    char file_name[120];
    memset(file_name,0,120);
    sprintf(file_name,"/storage/sdcard0/VSMetting/aec_in_%u.pcm",this);
    if(!_file_writer->SetFileName(file_name))
    {
        LOGI("[MyTransmitMixer] _file_writer->SetFileName Failed - %s",file_name);
    }
    */
#endif

#if 0
    if (_aec_in_file_writer == NULL)
    {
        _aec_in_file_writer = new FileWriter();
        char file_name[120];
        memset(file_name,0,120);
        sprintf(file_name,"%s/aec_in_%u.pcm",LocalConfig::getLocalAppDir().c_str(),this);
        if(!_aec_in_file_writer->SetFileName(file_name))
        {

        }
    }

    if (_aec_out_file_writer == NULL)
    {
        _aec_out_file_writer = new FileWriter();
        char file_name[120];
        memset(file_name,0,120);
        sprintf(file_name,"%s/aec_out_%u.pcm",LocalConfig::getLocalAppDir().c_str(),this);
        if(!_aec_out_file_writer->SetFileName(file_name))
        {

        }
    }
#endif
}

void MyTransmitMixer::SetVideoID(OpenLocalUser* pOpenLocalUser)
{
    m_pOpenLocalUser = pOpenLocalUser;
    //m_ulLocalVideoID = video_id;
    //m_ulLocalAudioID = video_id; //+ 100;
#if 0
    if (_audio_send_file_writer == NULL)
    {
        _audio_send_file_writer = new FileWriter();
        char file_name[120];
        memset(file_name,0,120);
        sprintf(file_name,"/storage/sdcard0/VSMeeting/audio_queue_send_%u.txt",m_ulLocalVideoID);
        if(!_audio_send_file_writer->SetFileNameTxt(file_name))
        {

        }
    }
#endif
}

void MyTransmitMixer::StopSendAudio()
{
    m_IsSendAudio = false;
}

void MyTransmitMixer::StartSendAudio()
{
    m_IsSendAudio = true;
}

void MyTransmitMixer::SetServerIP(const char* strServerIP, unsigned int uiPort)
{
    strcpy(m_strServerIP, strServerIP);
    m_uiPort = uiPort;
}

MyTransmitMixer::~MyTransmitMixer()
{
    LOGI("[MyTransmitMixer] MyTransmitMixer::~MyTransmitMixer() - dtor");
    
    UnInit();
#if 0
    if (_file_writer)
    {
        delete _file_writer;
        _file_writer = NULL;
    }
    
    if (_aec_in_file_writer != NULL)
    {
        delete _aec_in_file_writer;
        _aec_in_file_writer = NULL;
    }

    if (_aec_out_file_writer != NULL)
    {
        delete _aec_out_file_writer;
        _aec_out_file_writer = NULL;
    }

    if(_audio_send_file_writer != NULL)
    {
        delete _audio_send_file_writer;
        _audio_send_file_writer = NULL;
    }
#endif
    delete &_callbackCritSect;
}

int32_t MyTransmitMixer::StartVideoSender()
{
#if 0
    if (m_pMediaSender == NULL || m_ulLocalVideoID == 0)
    {
        LOGI("[MyTransmitMixer] StartVideoSender() must call  MyTransmitMixer::Init() "
            " && MyTransmitMixer::SetVideoID() first");
        return -1;
    }

    if ( 0 != m_pMediaSender->StartVideo(m_ulLocalVideoID))
    {
        LOGI("[MyTransmitMixer] NETEC_MediaSender::StartVideo() Failed");
        return -1;
    }
#endif
    return 0;
}

void MyTransmitMixer::StopVideoSender()
{
#if 0
    if (m_pMediaSender == NULL || m_ulLocalVideoID == 0)
    {
        LOGI("[MyTransmitMixer] StopVideoSender() must call Init() first");
        return;
    }
    m_pMediaSender->StopVideo();
#endif
}
/************************************************************************/
/* by zzw | 2013-7-16   13:13                          */
/************************************************************************/
int32_t MyTransmitMixer::StartAudioSender()
{
#if 0
    if (m_pMediaSender == NULL || m_ulLocalAudioID == 0)
    {
        LOGE("[MyTransmitMixer] StartAudioSender() must call  MyTransmitMixer::Init() "
            " && MyTransmitMixer::SetAudioID() first %u m_pMediaSender:%d",m_ulLocalAudioID,m_pMediaSender);
        return -1;
    }

    if ( 0 != m_pMediaSender->StartAudio(m_ulLocalAudioID))
    {
        LOGE("[MyTransmitMixer] NETEC_MediaSender::StartAudio() Failed");
        return -1;
    }
#endif
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-16   13:13                          */
/************************************************************************/
void MyTransmitMixer::StopAudioSender()
{
    m_pOpenLocalUser = NULL;
#if 0
    if (m_pMediaSender == NULL || m_ulLocalAudioID == 0)
    {
        LOGE("[MyTransmitMixer] MyTransmitMixer::Init() "
            " && MyTransmitMixer::SetVideoID() must call Init() first");
        return;
    }
    m_pMediaSender->StopAudio();
#endif
}
/************************************************************************/
/* by zzw | 2013-7-16   13:13                          */
/************************************************************************/
int32_t MyTransmitMixer::SetEngineInformation(ProcessThread& processThread)
{
    _processThreadPtr = &processThread;
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-16   13:13                          */
/************************************************************************/
int32_t MyTransmitMixer::Init()
{
#if 0
    if (m_pMediaSender == NULL)
    {
        m_pMediaSender = NETEC_MediaSender::Create(*this);
        if (m_pMediaSender != NULL)
        {
            m_pMediaSender->SetLocalMCUID("MCU001");
            m_pMediaSender->SetLocalMCIIP(m_strServerIP);
            m_pMediaSender->SetLocalMCUPort(m_uiPort);
            m_pMediaSender->SetConnectStatus(2); // Set by zzw

            if (0!=m_pMediaSender->Open())
            {
                m_pMediaSender->Close();
                delete m_pMediaSender;
                m_pMediaSender = NULL;
                return -1;
            }
            return 0;
        }
    }
#endif
    return 0;
}

int32_t MyTransmitMixer::UnInit()
{
#if 0
    if (m_pMediaSender != NULL)
    {
        m_pMediaSender->Close();
        delete m_pMediaSender;
        m_pMediaSender = NULL;
    }
#endif
    return 0;
}


int32_t MyTransmitMixer::SetAudioProcessingModule(AudioProcessing* audioProcessingModule)
{
    audioproc_ = audioProcessingModule;
    return 0;
}

int MyTransmitMixer::GenerateAudioFrame(const int16_t audio[],
                       int samples_per_channel,
                       int num_channels,
                       int sample_rate_hz)
{
    //LOGD("[MyTransmitMixer] GenerateAudioFrame:samples_per_channel:%d ",samples_per_channel);
    //LOGD("[MyTransmitMixer] GenerateAudioFrame:num_channels:%d ",num_channels);
    //LOGD("[MyTransmitMixer] GenerateAudioFrame:sample_rate_hz:%d ",sample_rate_hz);
    // destination_rate  && num_codec_channels should be get from Channel Decode
    // GetSendCodecInfo(&destination_rate, &num_codec_channels);
    // 
    // Set by zzw
    int destination_rate = 16000;
    int num_codec_channels = 1;

    destination_rate = std::min(destination_rate,sample_rate_hz);
    stereo_codec_ = num_codec_channels == 2;

    const int16_t* audio_ptr = audio;
    static const int kMaxMonoDeviceDataSizeSamples = 960;
    int16_t mono_audio[kMaxMonoDeviceDataSizeSamples];

    //stereo_codec_ = nChannels == 2;
    if (num_channels == 2 &&  !stereo_codec_)
    {
        AudioFrameOperations::StereoToMono(audio, samples_per_channel,
            mono_audio);
        audio_ptr = mono_audio;
        num_channels = 1;
    }

    

    if (resampler_.InitializeIfNeeded(sample_rate_hz,
        destination_rate,
        num_channels) != 0) {
            LOGI("[MyTransmitMixer] MyTransmitMixer::GenerateAudioFrame() unable to resample");
            return -1;
    }

    int out_length = resampler_.Resample(audio_ptr,
        samples_per_channel * num_channels,
        _audioFrame.data_,
        AudioFrame::kMaxDataSizeSamples);
    //LOGI("[MyTransmitMixer] out_length:%d BufferLength:%d",out_length,out_length * sizeof(int16_t));
    
    if (out_length == -1) {
        LOGI("[MyTransmitMixer] TransmitMixer::GenerateAudioFrame() resampling failed");
        return -1;
    }

    _audioFrame.samples_per_channel_ = samples_per_channel;
    _audioFrame.id_             = _instanceId;
    _audioFrame.sample_rate_hz_ = sample_rate_hz;
    _audioFrame.speech_type_    = AudioFrame::kNormalSpeech;
    _audioFrame.vad_activity_   = AudioFrame::kVadUnknown;
    _audioFrame.num_channels_   = num_channels;
    _audioFrame.timestamp_      = -1;

    return 0;
}

int32_t MyTransmitMixer::PrepareDemux(const void* audioSamples,
                     uint32_t nSamples,
                     uint8_t  nChannels,
                     uint32_t samplesPerSec,
                     uint16_t totalDelayMS,
                     int32_t  clockDrift,
                     uint16_t currentMicLevel,
                     bool keyPressed)
{
    //LOGI("[MyTransmitMixer] MyTransmitMixer::PrepareDemux() nSamples:%d nChannels:%d samplesPerSec:%d",
    //    nSamples,nChannels,samplesPerSec);
    // buffer大小： 320
    // 数据存储到本地 (GenerateAudioFrame 内部的重采样只进行了数据拷贝)
    //LOGD("[MyTransmitMixer] Before GenerateAudioFrame: %u",TimeGetTimestamp());
    if(GenerateAudioFrame(static_cast<const int16_t*>(audioSamples),
                        nSamples,
                        nChannels,
                        samplesPerSec) == -1)
    {
        LOGI("[MyTransmitMixer] GenerateAudioFrame Failed");
        return -1;
    }
    //LOGW("[MyTransmitMixer] After  GenerateAudioFrame: %u",TimeGetTimestamp());

    {
        CriticalSectionScoped cs(&_callbackCritSect);
        if (external_preproc_ptr_) {
            external_preproc_ptr_->Process(-1, kRecordingPreprocessing,
                _audioFrame.data_,
                _audioFrame.samples_per_channel_,
                _audioFrame.sample_rate_hz_,
                _audioFrame.num_channels_ == 2);
        }
    }

    // 数据处理
    ProcessAudio(totalDelayMS, clockDrift, currentMicLevel);

    //if (swap_stereo_channels_ && stereo_codec_)
        // Only bother swapping if we're using a stereo codec.
    //     AudioFrameOperations::SwapStereoChannels(&_audioFrame);

    // --- Mute signal
    if (_mute)
    {
        AudioFrameOperations::Mute(_audioFrame);
    }

    {
        CriticalSectionScoped cs(&_callbackCritSect);
        if (external_postproc_ptr_) {
            external_postproc_ptr_->Process(-1, kRecordingAllChannelsMixed,
                _audioFrame.data_,
                _audioFrame.samples_per_channel_,
                _audioFrame.sample_rate_hz_,
                _audioFrame.num_channels_ == 2);
        }
    }

    // --- Measure audio level of speech after all processing.
    //_audioLevel.ComputeLevel(_audioFrame);

    return 0;
}

int32_t MyTransmitMixer::DemuxAndMix()
{
    //LOGD("[MyTransmitMixer] MyTransmitMixer::DemuxAndMix()");
    return 0;
}

int32_t MyTransmitMixer::EncodeAndSend()
{
    //LOGD("[MyTransmitMixer] MyTransmitMixer::EncodeAndSend()");
    if (_audioFrame.samples_per_channel_ == 0)
    {
        return -1;
    }

    _audioFrame.id_ = _instanceId;
    // Delete by zzw
    //_audioFrame.timestamp_ = _timeStamp;
    

    if (_audioCodingModule.Add10MsData((AudioFrame&)_audioFrame) != 0)
    {
        LOGE("[MyTransmitMixer] MyTransmitMixer::EncodeAndSend() ACM encoding failed");
        return -1;
    }

    
    _timeStamp += _audioFrame.samples_per_channel_;

    //
    // Send

    return _audioCodingModule.Process();//ProcessAudioFrame((char *)(_audioFrame.data_),_audioFrame.sample_rate_hz_,_audioFrame.timestamp_);
}


// VoEExternalMedia
int MyTransmitMixer::RegisterExternalMediaProcessing(VoEMediaProcess* object,
                                    ProcessingTypes type)
{
    //LOGD("[MyTransmitMixer] RegisterExternalMediaProcessing()");
    CriticalSectionScoped cs(&_callbackCritSect);
    if (!object) {
        return -1;
    }

    if (type == kRecordingPreprocessing) 
    {
        external_preproc_ptr_ = object;
    }
    if (type == kRecordingAllChannelsMixed) {
        external_postproc_ptr_ = object;
    }
    else
    {
        return -1;
    }
    return 0;
}

int MyTransmitMixer::DeRegisterExternalMediaProcessing(ProcessingTypes type)
{
    CriticalSectionScoped cs(&_callbackCritSect);
    if (type == kRecordingPreprocessing) 
    {
        external_preproc_ptr_ = NULL;
    }
    if (type == kRecordingAllChannelsMixed) {
        external_postproc_ptr_ = NULL;
    }
    else
    {
        return -1;
    }
    return 0;
}

int MyTransmitMixer::SetMute(bool enable)
{
    _mute = enable;
    return 0;
}

bool
MyTransmitMixer::Mute() const
{
    return _mute;
}

uint32_t MyTransmitMixer::CaptureLevel() const
{
    CriticalSectionScoped cs(&_critSect);
    return _captureLevel;
}
/************************************************************************/
/* by zzw | 2013-7-15   11:23                          */
/************************************************************************/
int32_t MyTransmitMixer::SendData(uint32_t timestamp,
                         const char* payload_data,
                         uint16_t payload_len_bytes)
{
    // LOGI("[MyTransmitMixer] MyTransmitMixer::SendData payload_len_bytes:%d",payload_len_bytes);
    return ProcessAudioFrame((char*)payload_data,payload_len_bytes,timestamp);
}

/************************************************************************/
/* by zzw | 2013-7-14   23:29 private                         */
/************************************************************************/

/************************************************************************/
/* by zzw | 2013-7-15   10:54 APM ProcessStream  called                 */
/************************************************************************/
void MyTransmitMixer::ProcessAudio(int delay_ms, int clock_drift,
        int current_mic_level) 
{
    //LOGD("[MyTransmitMixer] MyTransmitMixer::ProcessAudio()");
     if (audioproc_->set_num_channels(_audioFrame.num_channels_,
         _audioFrame.num_channels_) != 0) {
             LOGE("[MyTransmitMixer] MyTransmitMixer::ProcessAudio _audioFrame.num_channels_=%d _audioFrame.num_channels_:%d",
                 _audioFrame.num_channels_,
                 _audioFrame.num_channels_);
     }

     if (audioproc_->set_sample_rate_hz(_audioFrame.sample_rate_hz_) != 0) {
         LOGW("[MyTransmitMixer] MyTransmitMixer::ProcessAudio _audioFrame.sample_rate_hz_:%d",_audioFrame.sample_rate_hz_);
     }

     if (audioproc_->set_stream_delay_ms(delay_ms) != 0) {
         // Report as a warning; we can occasionally run into very large delays.
         LOGW("[MyTransmitMixer] MyTransmitMixer::ProcessAudio delay_ms:%d",delay_ms);
     }

     GainControl* agc = audioproc_->gain_control();
     if (agc->set_stream_analog_level(current_mic_level) != 0) {
         LOGW("[MyTransmitMixer] MyTransmitMixer::ProcessAudio  current_mic_level:%d",current_mic_level);
     }

     EchoCancellation* aec = audioproc_->echo_cancellation();
     if (aec->is_drift_compensation_enabled()) {
         aec->set_stream_drift_samples(clock_drift);
     }
      int err =0;
    // Capture Process Stream
#if 0
    LOGD("[MyTransmitMixer] Before: %u", TimeGetTimestamp());
    if (_aec_in_file_writer)
    {
        _aec_in_file_writer->WriteToFile(_audioFrame);
    }
#endif
    err = audioproc_->ProcessStream(&_audioFrame);
    
#if 0
    LOGD("[MyTransmitMixer] After : %u", TimeGetTimestamp());
    if (_aec_out_file_writer)
    {
        _aec_out_file_writer->WriteToFile(_audioFrame);
    }
#endif
     if (err != 0) {
         LOGE("[MyTransmitMixer] MyTransmitMixer::ProcessAudio  error:%d",err);
     }

     CriticalSectionScoped cs(&_critSect);

     // Store new capture level. Only updated when analog AGC is enabled.
     _captureLevel = agc->stream_analog_level();

     //LOGD("[MyTransmitMixer] current_mic_level:%d _captureLevel:%d",current_mic_level,_captureLevel);

     // Triggers a callback in OnPeriodicProcess().
     _saturationWarning |= agc->stream_is_saturated();
}

unsigned long TimeGetTimestamp();

int32_t MyTransmitMixer::ProcessAudioFrame(char*pData, int nLen, unsigned long ulTimestamp)
{

#if 0
    if (m_pMediaSender == NULL)
    {
        LOGE("[MyTransmitMixer] MyTransmitMixer::ProcessAudioFrame must call Init() first");
        return -1;
    }
#endif
    
    if(!m_IsSendAudio)
        return -1;
    
    if (m_nAudioFrameBufferLength<nLen+1024)
    {
        m_nAudioFrameBufferLength=nLen+2048;
        if (m_pAudioPacket)
        {
            free(m_pAudioPacket);
            m_pAudioPacket=NULL;
        }
        m_pAudioPacket=(char*)malloc(m_nAudioFrameBufferLength);
        if (m_pAudioPacket==NULL)
        {
            m_nAudioFrameBufferLength=0;
            return -1;
        }
    }

    if (m_pAudioPacket)
    {
        unsigned long ulCurTimestamp = TimeGetTimestamp();
        if (ulCurTimestamp-m_ulLastFrameTimestamp<120)
        {
            unsigned long ulDelta1=ulCurTimestamp-m_ulLastPacketTimestamp;
            unsigned long ulDelta2=m_ulLastPacketTimestamp-ulCurTimestamp;
            unsigned long ulDelta=(ulDelta1>ulDelta2?ulDelta2:ulDelta1);
            if (ulDelta==ulDelta2)
            {
                m_ulLastPacketTimestamp+=1;
            }
            else
            {
                m_ulLastPacketTimestamp=ulCurTimestamp;
            }
        }
        else
        {
            m_ulLastPacketTimestamp=ulCurTimestamp;
        }
        m_ulLastFrameTimestamp=ulCurTimestamp;

        AUDEC_HEADER_RESET(m_pAudioPacket);
        AUDEC_HEADER_SET_SEQUENCE(m_pAudioPacket, m_usAudioSequence++);
        AUDEC_HEADER_SET_TIMESTAMP(m_pAudioPacket, m_ulLastPacketTimestamp);
        AUDEC_HEADER_SET_CODEC_ID(m_pAudioPacket, X_AUDIO_CODEC_AMR_NB_475);//X_AUDIO_CODEC_AMR_NB_475);
        int nHeaderSize=AUDEC_HEADER_GET_LEN(m_pAudioPacket);
        memcpy(m_pAudioPacket+nHeaderSize,pData,nLen);
       
        //LOGD("[MyTransmitMixer] m_usAudioSequence:%u",m_usAudioSequence);
        //LOGD("[MyTransmitMixer] index:%d Timestamp:%u",i++,TimeGetTimestamp());
        //int nRet = m_pMediaSender->SendAudio((unsigned char*)m_pAudioPacket, nHeaderSize+nLen);
        if(m_pOpenLocalUser!=NULL)
            m_pOpenLocalUser->ProcessAudioFrame(m_pAudioPacket, nHeaderSize + nLen,0);
       
        return nLen;
    }
    return -1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void MyTransmitMixer::ProcessVideoFrame(char*pData, int nLen, bool bKeyFrame, unsigned long ulTimestamp, int nWidth, int nHeight)
{
    
#if 0
    if (m_nFrameBufferLength<nLen+1024)
    {
        m_nFrameBufferLength=nLen+2048;
        if (m_pVideoPacket)
        {
            free(m_pVideoPacket);
            m_pVideoPacket=NULL;
        }
        m_pVideoPacket=(char*)malloc(m_nFrameBufferLength);
        if (m_pVideoPacket==NULL)
        {
            m_nFrameBufferLength=0;
            return;
        }
    }

    if (m_bGotKeyFrameMain==false && bKeyFrame && m_pVideoPacket)
    {
        m_bGotKeyFrameMain=true;
    }

    if (m_bGotKeyFrameMain && m_pVideoPacket)
    {
        VIDEC_HEADER_EXT_RESET(m_pVideoPacket);
        VIDEC_HEADER_EXT_SET_CODEC_ID(m_pVideoPacket,4/*VIDEC_CODEC_H264*/);
        VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(m_pVideoPacket,0);
        VIDEC_HEADER_EXT_SET_KEYFRAME(m_pVideoPacket,(bKeyFrame?1:0));
        VIDEC_HEADER_EXT_SET_SEQUENCE(m_pVideoPacket,m_usVideoSequence++);
        VIDEC_HEADER_EXT_SET_TIMESTAMP(m_pVideoPacket,ulTimestamp);

        if (bKeyFrame)
        {
            VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(m_pVideoPacket,nWidth);
            VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(m_pVideoPacket,nHeight);
            VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(m_pVideoPacket,nWidth);
            VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(m_pVideoPacket,nHeight);
        }

        int nHeaderLen=VIDEC_HEADER_EXT_GET_LEN(m_pVideoPacket);

        memcpy(m_pVideoPacket+nHeaderLen,pData,nLen);

        VIDEC_HEADER_EXT_SET_MAIN_FRAME(m_pVideoPacket,1);
        if (m_pMediaSender != NULL)
        {
            //LOGI("m_pMediaSender->SendVideo length:%d",nLen+nHeaderLen);
            int nRet = m_pMediaSender->SendVideo((unsigned char *)m_pVideoPacket, nLen+nHeaderLen);
            if (nRet != 0)
            {
                LOGE("[MyTransmitMixer] VideoData Send Failed");
            }
            //LOGI("m_pMediaSender->SendVideo Return:%d",nRet);
        }
    }
#endif
}