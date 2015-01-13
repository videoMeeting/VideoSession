#include "VoeManager.h"

#define LOG_TAG "WebRTC Voe | VoeManager"

#define LOGE printf
#define LOGI printf
/************************************************************************/
/* by zzw | 2013-7-11   22:17 My Local headers                         */
/************************************************************************/
#include "MyOutputMixer.h"
#include "MyTransmitMixer.h"
#include "MyChannel.h"

/************************************************************************/
/* by zzw | 2013-7-11   14:58 WebRTC Headers                            */
/************************************************************************/
#include "../webrtc/common_audio/signal_processing/include/spl_inl.h"
#include "../webrtc/common_audio/signal_processing/include/signal_processing_library.h"

#include "../webrtc/voice_engine_defines.h"

using namespace webrtc;

VoeManager* VoeManager::Create()
{
    VoeManager *ptr = new VoeManager();
    if (ptr == NULL)
    {
        LOGE("[VoeManager] alloc VoeManager Failed");
    }
    return ptr;
}

bool VoeManager::Delete(VoeManager* & voeManager)
{
    if (voeManager != NULL)
    {
        delete voeManager;
        voeManager = NULL;
    }
    return YES;
}
/************************************************************************/
/* by zzw | 2013-7-16   13:31                          */
/************************************************************************/
VoeManager::VoeManager():_shared(this)
    , _callbackCritSect(*CriticalSectionWrapper::CreateCriticalSection())
    , _start_recording(false)
    //, _mixer_file(NULL)
{
#if 0
    LOGI("[VoeManager] VoeManager::VoeManager ctor");
    
    if (_mixer_file == NULL)
    {
        _mixer_file = new FileWriter();
        char name[100];
        memset(name,0,100);
        sprintf(name,"/storage/sdcard0/VSMeeting/mixer_%u.pcm",this);

        if (_mixer_file->SetFileName(name))
        {
        }
    }
#endif
}

VoeManager::~VoeManager()
{
    LOGI("[VoeManager] VoeManager::~VoeManager dtor");
    //TerminateInternal();
#if 0
    if (_mixer_file != NULL)
    {
        delete _mixer_file;
        _mixer_file = NULL;
    }
#endif

    delete &_callbackCritSect;
}

int VoeManager::Init(AudioDeviceModule* external_adm/* = NULL*/,
                 AudioProcessing* audioproc/* = NULL*/)
{
    //LOGD("[VoeManager] VoeManager::Init");
    CriticalSectionScoped cs(_shared->crit_sec());

    WebRtcSpl_Init();

    if (_shared->process_thread())
    {
        if (_shared->process_thread()->Start() != 0)
        {
            LOGE("[VoeManager] Init() failed to start module process thread");
            return -1;
        }
    }
    /************************************************************************/
    /* by zzw | 2013-7-11   15:28 ADM Init                                  */
    /************************************************************************/
    if (external_adm == NULL)
    {
        _shared->set_audio_device(CreateAudioDeviceModule(_shared->instance_id(),_shared->audio_device_layer()));
        if (_shared->audio_device() == NULL)
        {
            LOGE("[VoeManager] Create Audio Device Module Failed");
            return -1;
        }
    }
    else
    {
        _shared->set_audio_device(external_adm);
        LOGE("[VoeManager] An external ADM implementation will be used in VoiceEngine");
    }

    if (_shared->process_thread() && _shared->process_thread()->RegisterModule(_shared->audio_device()) != 0)
    {
        LOGE("[VoeManager] Init() failed to register the ADM");
        return -1;
    }

    bool available(false);

    if (_shared->audio_device()->RegisterEventObserver(this) != 0)
    {
        LOGE("[VoeManager] Init() failed to register event observer for the ADM");
    }

    if (_shared->audio_device()->RegisterAudioCallback(this) != 0)
    {
        LOGE("[VoeManager] Init() failed to register audio callback for the ADM");
    }

    if (_shared->audio_device()->Init() != 0)
    {
        LOGE("[VoeManager] Init() failed to initialize the ADM");
        return -1;
    }

    if (_shared->audio_device()->SetPlayoutDevice(0) != 0 )  // /*AudioDeviceModule::kDefaultCommunicationDevice*/
    {
        //AudioDeviceModule::kDefaultCommunicationDevice

        LOGE("[VoeManager] Init() failed to set the default output device");
    }

    if (_shared->audio_device()->SpeakerIsAvailable(&available) != 0)
    {
        LOGE("[VoeManager] Init() failed to check speaker availability, trying to "
            "initialize speaker anyway");
    }
    else if (!available)
    {
        LOGE("[VoeManager] Init() speaker not available, trying to initialize speaker "
            "anyway");
    }

    if (_shared->audio_device()->InitSpeaker() != 0)
    {
        LOGE("[VoeManager]  Init() failed to initialize the speaker");
    }

    // Initialize the default microphone
    if (_shared->audio_device()->SetRecordingDevice(0
        /*AudioDeviceModule::kDefaultCommunicationDevice*/) != 0)
    {
        LOGE("[VoeManager]  Init() failed to set the default input device");
    }
    if (_shared->audio_device()->MicrophoneIsAvailable(&available) != 0)
    {
        LOGE("[VoeManager]  "
            "Init() failed to check microphone availability, trying to "
            "initialize microphone anyway");
    }
    else if (!available)
    {
        LOGE("[VoeManager]  "
            "Init() microphone not available, trying to initialize "
            "microphone anyway");
    }
    if (_shared->audio_device()->InitMicrophone() != 0)
    {
        LOGE("[VoeManager]  "
            "Init() failed to initialize the microphone");
    }

    // Set number of channels
    if (_shared->audio_device()->StereoPlayoutIsAvailable(&available) != 0) {
        LOGE("[VoeManager]  "
            "Init() failed to query stereo playout mode");
    }
    if (_shared->audio_device()->SetStereoPlayout(available) != 0)
    {
        LOGE("[VoeManager]  "
            "Init() failed to set mono/stereo playout mode");
    }

    _shared->audio_device()->StereoRecordingIsAvailable(&available);
    if (_shared->audio_device()->SetStereoRecording(available) != 0)
    {
        LOGE("[VoeManager] Init() failed to set mono/stereo recording mode");
    }

    // Add by zzw | set enable external edit 
    //_shared->set_ext_playout(true);
    //_shared->set_ext_recording(true);

    /************************************************************************/
    /* by zzw | 2013-7-11   15:29   APM Init                                */
    /************************************************************************/
    if (!audioproc)
    {
        audioproc = AudioProcessing::Create(_shared->instance_id());
        if (!audioproc)
        {
            LOGE("[VoeManager] Failed to Create AudioProcessing");
            return -1;
        }
    }
    _shared->set_audio_processing(audioproc);
    
    if(audioproc->echo_cancellation()->set_device_sample_rate_hz(16000))
    {
        LOGE("[VoeManager] Error set_device_sample_rate_hz %d",16000);
        return -1;
    }

    if (audioproc->set_sample_rate_hz(16000))
    {
        LOGE("[VoeManager] Error set_sample_rate_hz %d",16000);
        return -1;
    }

    if (audioproc->set_num_channels(1,1) != 0)
    {
        LOGE("[VoeManager] Error set_num_channels %d %d",1,1);
        return -1;
    }

    if (audioproc->set_num_reverse_channels(1) != 0)
    {
        LOGE("[VoeManager] Error set_num_reverse_channels %d",1);
        return -1;
    }

    // Configure AudioProcessing components. All are disabled by default.
    if (audioproc->echo_control_mobile()->Enable(true) != 0)
    {
        LOGE("[VoeManager] audioproc->echo_control_mobile()->Enable Failed");
        return -1;
    }

    if (audioproc->echo_control_mobile()->enable_comfort_noise(true) != 0)
    {
        LOGE("[VoeManager] audioproc->echo_control_mobile()->enable_comfort_noise() Failed");
        return -1;
    }

    if (audioproc->echo_control_mobile()->set_routing_mode(EchoControlMobile::kLoudSpeakerphone) != 0)
    {
        LOGE("[VoeManager] audioproc->echo_control_mobile()->set_routing_mode() Failed");
        return -1;
    }
    
#if 0
    if (audioproc->high_pass_filter()->Enable(true) != 0) {
        LOGI("[VoeManager] high_pass_filter()->Enable  true");
        return -1;
    }
    if (audioproc->echo_cancellation()->enable_drift_compensation(false) != 0) {
        LOGI("[VoeManager] enable_drift_compensation  false");
        return -1;
    }
#endif
    if (audioproc->noise_suppression()->set_level(NoiseSuppression::kHigh) != 0) {
        LOGI("[VoeManager] noise_suppression()->set_level %d", NoiseSuppression::kHigh);
        return -1;
    }

    if (audioproc->noise_suppression()->Enable(true) != 0)
    {
        LOGI("[VoeManager] noise_suppression()->Enable(true)");
        return -1;
    }
    
    // AGC is Unable on Android
    GainControl* agc = audioproc->gain_control();
    if (agc->set_analog_level_limits(kMinVolumeLevel, kMaxVolumeLevel) != 0) {
        LOGI("[VoeManager] agc->set_analog_level_limits, kMinVolumeLevel=%d,kMaxVolumeLevel=%d",kMinVolumeLevel,kMaxVolumeLevel);
        return -1;
    }
    if (agc->set_mode(kDefaultAgcMode) != 0) { // kAdaptiveDigital
        LOGI("[VoeManager] agc->set_mode, kDefaultAgcMode=%d",kDefaultAgcMode);
        return -1;
    }
    if (agc->Enable(kDefaultAgcState) != 0) {
        LOGI("[VoeManager] agc->Enable, kDefaultAgcState=%d",kDefaultAgcState);
        return -1;
    }

#ifdef WEBRTC_VOICE_ENGINE_AGC
    bool agc_enabled = agc->mode() == GainControl::kAdaptiveAnalog &&
        agc->is_enabled();
    if (_shared->audio_device()->SetAGC(agc_enabled) != 0) {
        LOGI("[VoeManager]  audio_device()->SetAGC, agc_enabled=%d",agc_enabled);
        //_shared->SetLastError(VE_AUDIO_DEVICE_MODULE_ERROR);
        // TODO(ajm): No error return here due to
        // https://code.google.com/p/webrtc/issues/detail?id=1464
    }
#endif

    return 0;
}

int VoeManager::Terminate()
{
    CriticalSectionScoped cs(_shared->crit_sec());
    return TerminateInternal();
}

int VoeManager::MaxNumOfChannels()
{
    return 100; 
}


int VoeManager::CreateChannel(unsigned long videoID)
{
    CriticalSectionScoped cs(_shared->crit_sec());

    ChannelManagers::iterator iter = channelManager.find(videoID);

    if (iter != channelManager.end())
    {
        return 0;
    }

    MyChannel *channel = NULL;
    if(MyChannel::CreateChannel(channel,videoID) != 0)
    {
        LOGI("[VoeManager] CreateChannel() failed to allocate memory for channel");
        return -1;
    }

    bool destoryChannel(false);
    {
        if (channel == NULL)
        {
            LOGI("[VoeManager] CreateChannel() failed to allocate memory for channel");
            return -1;
        }
        else if (channel->SetEngineInformation(*_shared->output_mixer(),
            *_shared->process_thread(),
            *_shared->audio_device(),
            &_callbackCritSect,
            _shared->server_ip(),_shared->server_port()) != 0)
        {
            destoryChannel = true;
            LOGI("[VoeManager] CreateChannel() failed to associate engine and channel. Destroying channel.");
        }
        else if (channel->Init() != 0)
        {
            destoryChannel = true;
            LOGI("[VoeManager] CreateChannel() failed to initialize channel. Destroying channel.");
        }
    }
    if (destoryChannel)
    {
        delete channel;
        return -1;
    }
    else
    {
        //channel->SetRxNsStatus(true, kNsConference);
        //channel->SetRxAgcStatus(true,kAgcAdaptiveDigital);
    }

    channelManager.insert(std::pair<unsigned long,MyChannel *>(videoID,channel));
    return 0;
}

int VoeManager::DeleteChannel(unsigned long video_id)
{
    LOGI("[VoeManager] VoeManager::DeleteChannel video_id:%lul",video_id);
    CriticalSectionScoped cs(_shared->crit_sec());

    ChannelManagers::iterator iter = channelManager.find(video_id);
    if (iter == channelManager.end())
    {
        return -1;
    }

    MyChannel *channel = iter->second;
    if (channel == NULL)
    {
        LOGI("[VoeManager] DeleteChannel() failed to destroy channel");
        return -1;
    }
    
    delete channel;
    channel = NULL;

    channelManager.erase(iter);
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-15   2:32                          */
/************************************************************************/
int VoeManager::StartReceive(unsigned long  channel)
{
    CriticalSectionScoped cs(_shared->crit_sec());
    ChannelManagers::iterator iter = channelManager.find(channel);
    if (iter == channelManager.end())
    {
        LOGI("[VoeManager] No Such channel");
        return -1;
    }
    MyChannel *channelptr = iter->second;
    if (channelptr == NULL)
    {
        LOGI("[VoeManager] Channel is Empty");
        return -1;
    }
    return channelptr->StartAudioReceiving();
}

/************************************************************************/
/* by zzw | 2013-7-15   2:32                          */
/************************************************************************/
int VoeManager::StopReceive(unsigned long  channel)
{
    CriticalSectionScoped cs(_shared->crit_sec());
    ChannelManagers::iterator iter = channelManager.find(channel);
    if (iter == channelManager.end())
    {
        return -1;
    }
    MyChannel *channelptr = iter->second;
    if (channelptr == NULL)
    {
        return -1;
    }
    return channelptr->StopAudioReceiving();
}

int VoeManager::StartPlayout(unsigned long  channel)
{
    CriticalSectionScoped cs(_shared->crit_sec());
    ChannelManagers::iterator iter = channelManager.find(channel);
    if (iter == channelManager.end())
    {
        return -1;
    }
    MyChannel *channelptr = iter->second;
    if (channelptr == NULL)
    {
        return -1;
    }

    if (channelptr->Playing())
    {
        LOGI("[VoeManager] channel:%lul is Playing",channel);
        return 0;
    }
    
    if (StartPlayout() != 0)
    {
        return -1;
    }
    return channelptr->StartPlayout();
}

int VoeManager::StopPlayout(unsigned long  channel)
{
    CriticalSectionScoped cs(_shared->crit_sec());
    ChannelManagers::iterator iter = channelManager.find(channel);
    if (iter == channelManager.end())
    {
        return -1;
    }
    MyChannel *channelptr = iter->second;
    if (channelptr == NULL)
    {
        LOGE("[VoeManager] channel:%lu ", channel);
        return -1;
    }

    if (channelptr->StopPlayout() != 0)
    {
        LOGI("[VoeManager] StopPlayout() failed to stop playout for channel %lu", channel);
    }

    return StopPlayout();
}

void VoeManager::CallbackAudioPacket(unsigned long m_ulPeerAudioID,unsigned char* pData,int nLen)
{
    CriticalSectionScoped cs(_shared->crit_sec());
    ChannelManagers::iterator iter = channelManager.find(m_ulPeerAudioID);
    if (iter == channelManager.end())
    {
        return ;
    }
    MyChannel *channelptr = iter->second;
    if (channelptr == NULL)
    {
        return ;
    }
    channelptr->OnNETEC_MediaReceiverCallbackAudioPacket(pData, nLen);
}

/************************************************************************/
/* by zzw | 2013-7-15   3:28                          */
/************************************************************************/
int VoeManager::StartLocalAudio(OpenLocalUser* pOpenLocalUser)
{
    LOGI("[VoeManager] VoeManager::StartLocalAudio()");
    if (_start_recording)
    {
        return 0;
    }
    
    if (StartSend() != 0)
    {
        LOGI("[VoeManager] VoeManager StartSend failed");
        return -1;
    }
    
    _shared->transmit_mixer()->SetServerIP(server_ip(), server_port());
    _shared->transmit_mixer()->Init();
    _shared->transmit_mixer()->SetVideoID(pOpenLocalUser);
    _shared->transmit_mixer()->StartAudioSender();

    _start_recording = true;
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-15   3:28                          */
/************************************************************************/
int VoeManager::StopLocalAudio()
{
    if (!_start_recording)
    {
        LOGI("[VoeManager] AudioRecord Not Start");
        return 0;
    }
    StopSend();
    _shared->transmit_mixer()->StopAudioSender();
    // _shared->transmit_mixer()->UnInit();
    _start_recording = false;
    return 0;
}

void VoeManager::StopSendAudio()
{
   if(_shared)
       _shared->transmit_mixer()->StopSendAudio();
}

void VoeManager::StartSendAudio()
{
    if(_shared)
        _shared->transmit_mixer()->StartSendAudio();
}
/*
void VoeManager::SetVideoID(unsigned long video_id)
{
    _shared->transmit_mixer()->SetVideoID(video_id);
}
*/
/************************************************************************/
/* by zzw | 2013-7-11   13:56  Inherit AudioTransport                   */
/************************************************************************/
int32_t VoeManager::RecordedDataIsAvailable(const void* audioSamples,
                                        const uint32_t nSamples,
                                        const uint8_t nBytesPerSample,
                                        const uint8_t nChannels,
                                        const uint32_t samplesPerSec,
                                        const uint32_t totalDelayMS,
                                        const int32_t clockDrift,
                                        const uint32_t currentMicLevel,
                                        const bool keyPressed,
                                        uint32_t& newMicLevel)
{
    //LOGI("[VoeManager] RecordedDataIsAvailable");
   // LOGD("[VoeManager] totalDelayMS:%d",totalDelayMS);
    //LOGI("[VoeManager] --> nSamples:%d nBytesPerSample:%d samplesPerSec:%d ",nSamples,nBytesPerSample,samplesPerSec);
    //LOGI("[VoeManager] --> nChannels:%d",nChannels);
    // By zzw
    // User Transmit_mixer to control Data ??????
    bool isAnalogAGC(false);
    uint32_t maxVolume(0);
    uint32_t currentVoEMicLevel(0);
    uint32_t newVoEMicLevel(0);

    if (_shared->audio_processing() && 
        (_shared->audio_processing()->gain_control()->mode() == GainControl::kAdaptiveAnalog))
    {
        isAnalogAGC = true;
    }
    
    if (isAnalogAGC)
    {
        if (_shared->audio_device()->MaxMicrophoneVolume(&maxVolume) == 0)
        {
            if (0 != maxVolume)
            {
                currentVoEMicLevel = (uint16_t)(( currentMicLevel * kMaxVolumeLevel + (int)(maxVolume / 2 ))/(maxVolume));
            }
        }

        if (currentVoEMicLevel > kMaxVolumeLevel)
        {
            currentVoEMicLevel = kMaxVolumeLevel;
            maxVolume = currentMicLevel;
        }
    }

    if (_oldMicLevel == currentMicLevel)
    {
        currentVoEMicLevel = (uint16_t) _oldVoEMicLevel;
    }
    
    _shared->transmit_mixer()->PrepareDemux(audioSamples,nSamples,nChannels,samplesPerSec,
        static_cast<uint16_t>(totalDelayMS),clockDrift,
        currentVoEMicLevel, keyPressed);

    // Empty function NOW
    _shared->transmit_mixer()->DemuxAndMix();

    //
    _shared->transmit_mixer()->EncodeAndSend();

    // Will only deal with the volume in adaptive analog mode
    if (isAnalogAGC)
    {
        // Scale from VoE to ADM level range
        newVoEMicLevel = _shared->transmit_mixer()->CaptureLevel();
        if (newVoEMicLevel != currentVoEMicLevel)
        {
            // Add (kMaxVolumeLevel/2) to round the value
            newMicLevel = (uint32_t) ((newVoEMicLevel * maxVolume
                + (int) (kMaxVolumeLevel / 2)) / (kMaxVolumeLevel));
        }
        else
        {
            // Pass zero if the level is unchanged
            newMicLevel = 0;
        }

        // Keep track of the value AGC returns
        _oldVoEMicLevel = newVoEMicLevel;
        _oldMicLevel = currentMicLevel;
    }

    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-12   15:22 ADM Õ®π˝¥Àªÿµ˜Ω”ø⁄ªÒ»°–Ë“™≤•∑≈µƒ ˝æ›  */
/*  Manager Õ®π˝ output_mixer »°µ√ªÏ“Ù∫Ûµƒ ˝æ›                     */
/************************************************************************/
int32_t VoeManager::NeedMorePlayData(const uint32_t nSamples,
                                 const uint8_t nBytesPerSample,
                                 const uint8_t nChannels,
                                 const uint32_t samplesPerSec,
                                 void* audioSamples,
                                 uint32_t& nSamplesOut)
{
#if 0
    ChannelManagers::iterator iter = channelManager.begin();
    if (iter != channelManager.end())
    {
       MyChannel*channel =  iter->second;
       channel->GetAudioFrame(0,_audioFrame);
    }
#else
    //LOGI("[VoeManager] Get Mixer Data ------------------------------------------");
    //LOGI("[VoeManager] NeedMorePlayData");
    _shared->output_mixer()->MixActiveChannels();

    _shared->output_mixer()->DoOperationsOnCombinedSignal();

    // ªÒ»°ªÏ“Ù∫Ûµƒ ˝æ›
    LOGI("[VoeManager] nChannels:%d", nChannels);
    LOGI("[VoeManager] samplesPerSec:%d", samplesPerSec);
    _shared->output_mixer()->GetMixedAudio(samplesPerSec, nChannels,
        &_audioFrame);
#endif
    //LOGI("[VoeManager] nChannels:%d", nChannels);
    //LOGI("[VoeManager] samplesPerSec:%d", samplesPerSec);
    //LOGI("[VoeManager] _audioFrame.samples_per_channel_:%d", _audioFrame.samples_per_channel_);
    //LOGI("[VoeManager] _audioFrame.num_channels_:%d",_audioFrame.num_channels_); 
    
    memcpy(
        (int16_t*) audioSamples,
        (const int16_t*) _audioFrame.data_,
        sizeof(int16_t) * (_audioFrame.samples_per_channel_
        * _audioFrame.num_channels_));

    nSamplesOut = _audioFrame.samples_per_channel_;

    return 0;
}

/************************************************************************/
/* by zzw | 2013-7-11   13:56  Inherit AudioDeviceObserver              */
/************************************************************************/
void VoeManager::OnErrorIsReported(const ErrorCode error)
{
    LOGI("[VoeManager] AudioDeviceObserver->OnErrorIsReported: %d ",error);
}

void VoeManager::OnWarningIsReported(const WarningCode warning)
{
    LOGI("[VoeManager] AudioDeviceObserver->OnWarningIsReported: %d ",warning);
}

/************************************************************************/
/* by zzw | 2013-7-11   16:06 Private Hello                             */
/************************************************************************/
int32_t VoeManager::TerminateInternal()
{
    LOGI("[VoeManager] VoeManager::TerminateInternal()");
    if(_shared->process_thread())
    {
        if (_shared->audio_device())
        {
            if (_shared->process_thread()->DeRegisterModule(_shared->audio_device()) != 0)
            {
                LOGI("[VoeManager] TerminateInternal() failed to deregister ADM");
            }
        }

        if (_shared->process_thread()->Stop() != 0)
        {
            LOGI("[VoeManager] TerminateInternal() failed to stop module process thread");
        }
    }

    if (_shared->audio_device())
    {
        if (_shared->audio_device()->StopPlayout() != 0)
        {
            LOGI("[VoeManager] TerminateInternal() failed to stop playout");
        }

        if (_shared->audio_device()->StopRecording() != 0)
        {
            LOGI("[VoeManager] TerminateInternal() failed to stop recording");
        }

        if (_shared->audio_device()->RegisterEventObserver(NULL) != 0)
        {
            LOGI("[VoeManager] TerminateInternal() failed to de-register event observer "
                "for the ADM");
        }

        if (_shared->audio_device()->RegisterAudioCallback(NULL) != 0)
        {
            LOGI("[VoeManager] TerminateInternal() failed to de-register audio callback "
                "for the ADM");
        }

        if (_shared->audio_device()->Terminate() != 0)
        {
            LOGI("[VoeManager] TerminateInternal() failed to terminate the ADM");
        }
        _shared->set_audio_device(NULL);
    }

    if (_shared->audio_processing())
    {
        _shared->set_audio_processing(NULL);
    }

    return 0;
}



/************************************************************************/
/* by zzw | 2013-7-15   2:05 Private                                    */
/************************************************************************/
int32_t VoeManager::StartPlayout()
{
    LOGI("[VoeManager] VoeManager::StartPlayout()");
    if (_shared->audio_device()->Playing())
    {
        return 0;
    }
    if (!_shared->ext_playout())
    {
        LOGI("[VoeManager] _shared->audio_device()->InitPlayout()");
        if (_shared->audio_device()->InitPlayout() != 0)
        {
            LOGI("[VoeManager] StartPlayout() failed to initialize playout");
            return -1;
        }
        LOGI("[VoeManager] _shared->audio_device()->StartPlayout()");
        if (_shared->audio_device()->StartPlayout() != 0)
        {
            LOGI("[VoeManager] StartPlayout() failed to start playout");
            return -1;
        }
    }
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-15   2:09                          */
/************************************************************************/
int32_t VoeManager::StopPlayout()
{
    LOGI("[VoeManager] VoeManager::StopPlayout()");

    if (_shared->audio_device()->StopPlayout() != 0)
    {
        LOGI("[VoeManager] StopPlayout() failed to stop playout");
        return -1;
    }
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-15   23:57                          */
/************************************************************************/
int32_t VoeManager::StartSend()
{
    if (_shared->audio_device()->Recording())
    {
        LOGI("[VoeManager] _shared->audio_device() is Recording()");
        return 0;
    }
    
    if (!_shared->ext_recording())
    {
        LOGI("[VoeManager] _shared->audio_device()->InitRecording()");
        if (_shared->audio_device()->InitRecording() != 0)
        {
            LOGI("[VoeManager] StartSend() failed to initialize recording");
            return -1;
        }
        LOGI("[VoeManager] _shared->audio_device()->StartRecording()");
        if (_shared->audio_device()->StartRecording() != 0)
        {
            LOGI("[VoeManager] StartSend() failed to start recording");
            return -1;
        }
    }
    
    return 0;
}

/************************************************************************/
/* by zzw | 2013-7-15   23:57                          */
/************************************************************************/
int32_t VoeManager::StopSend()
{
    if (_shared->audio_device()->StopRecording() != 0)
    {
        LOGI("[VoeManager] StopSend() failed to stop recording");
        return -1;
    }
    
    return 0;
}