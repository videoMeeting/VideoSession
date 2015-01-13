#include "MyOutputMixer.h"

#define LOG_TAG "WebRTC Voe | MyOutputMixer"

#define LOGI printf

#include "output_mixer_internal.h"

using namespace webrtc;

int32_t MyOutputMixer::Create(MyOutputMixer*& mixer, uint32_t instanceId)
{
    mixer = new MyOutputMixer(instanceId);
    if (mixer == NULL)
    {
        return -1;
    }
    return 0;
}

void MyOutputMixer::Destroy(MyOutputMixer*& mixer)
{
    if(mixer)
    {
        delete mixer;
        mixer = NULL;
    }
}

MyOutputMixer::MyOutputMixer(int instanceId):_callbackCritSect(*CriticalSectionWrapper::CreateCriticalSection()),
    _mixerModule(*AudioConferenceMixer::Create(instanceId)),
    _externalMedia(false),
    _mixingFrequencyHz(16000),
    _instanceId(instanceId),
    _audioCodingModule(*AudioCodecModule::Create(instanceId+1))
#if 0
    , _file_mixer_in(NULL)
    , _file_mixer_out(NULL)
    , _file_mixer_from_conf(NULL)
#endif
{
    LOGI("[MyOutputMixer] MyOutputMixer::MyOutputMixer() - ctor");
        if ((_mixerModule.RegisterMixedStreamCallback(*this) == -1) || 
        (_mixerModule.RegisterMixerStatusCallback(*this,100) == -1))
    {
        LOGI("[MyOutputMixer] MyOutputMixer::MyOutputMixer() failed to register mixer callbacks");
    }

    _mixerModule.SetMinimumMixingFrequency(AudioConferenceMixer::kNbInHz);//kWbInHz);
}


MyOutputMixer::~MyOutputMixer()
{
    _mixerModule.UnRegisterMixerStatusCallback();
    _mixerModule.UnRegisterMixedStreamCallback();

#if 0
    if (_file_mixer_in == NULL)
    {
        delete _file_mixer_in;
        _file_mixer_in = NULL;
    }

    if (_file_mixer_out == NULL)
    {
        delete _file_mixer_out;
        _file_mixer_out = NULL;
    }
#endif
    delete &_mixerModule;
    delete &_callbackCritSect;
}

/************************************************************************/
/* by zzw | 2013-7-11   11:38                          */
/************************************************************************/
int32_t MyOutputMixer::SetAudioProcessingModule(
                                 AudioProcessing* audioProcessingModule)
{
    _audioProcessingModulePtr = audioProcessingModule;
    return 0;
}

int MyOutputMixer::RegisterExternalMediaProcessing(
                                    VoEMediaProcess& proccess_object)
{
    CriticalSectionScoped cs(&_callbackCritSect);
    _externalMediaCallbackPtr = &proccess_object;
    _externalMedia = true;

    return 0;
}

int MyOutputMixer::DeRegisterExternalMediaProcessing()
{
    CriticalSectionScoped cs(&_callbackCritSect);
    _externalMedia = false;
    _externalMediaCallbackPtr = NULL;
    return 0;
}

/************************************************************************/
/* by zzw | 2013-7-11   17:06                          */
/************************************************************************/

int32_t
MyOutputMixer::MixActiveChannels()
{
    int32_t nRet = _mixerModule.Process();
    LOGI("[MyOutputMixer] MyOutputMixer::MixActiveChannels() %d",nRet);
  _mixerModule.TimeUntilNextProcess();//  int32_t timeUntilNextProcess =
    LOGI("[MyOutputMixer] _mixerModule.TimeUntilNextProcess() %d",nRet);
    return nRet;
}

int32_t
MyOutputMixer::DoOperationsOnCombinedSignal()
{
    if (_audioFrame.sample_rate_hz_ != _mixingFrequencyHz)
    {
        _mixingFrequencyHz = _audioFrame.sample_rate_hz_;
    }

    // Delete By  zzw
    // Removed Dtmf Tone
    // removed Channel balance

    APMAnalyzeReverseStream();
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-12   0:14                          */
/************************************************************************/
int32_t MyOutputMixer::SetMixabilityStatus(MixerParticipant& participant,
                            bool mixable)
{
    return _mixerModule.SetMixabilityStatus(participant, mixable);
}
/************************************************************************/
/* by zzw | 2013-7-12   0:14                          */
/************************************************************************/
int32_t MyOutputMixer::SetAnonymousMixabilityStatus(MixerParticipant& participant,
                                     bool mixable)
{
    return _mixerModule.SetAnonymousMixabilityStatus(participant,mixable);
}

int MyOutputMixer::GetMixedAudio(int sample_rate_hz, int num_channels,
                  AudioFrame* frame)
{
    {
        // CriticalSectionScoped cs(&_fileCritSect);
        // Write to File
    }

    frame->num_channels_ = num_channels;
    frame->sample_rate_hz_ = sample_rate_hz;
    //LOGI("[MyOutputMixer] _audioFrame.sample_rate_hz_:%u",_audioFrame.sample_rate_hz_);
//     if (_file_mixer_in != NULL)
//     {
//         _file_mixer_in->WriteToFile((AudioFrame &)_audioFrame);
//     }
    int nRet = RemixAndResample(_audioFrame, &resampler_, frame);
//     if (_file_mixer_out != NULL)
//     {
//         _file_mixer_out->WriteToFile(*frame);
//     }
    return nRet;
}

/************************************************************************/
/* by zzw | 2013-7-10   11:27   AudioMixerOutputReceiver                */
/************************************************************************/
void MyOutputMixer::NewMixedAudio(const int32_t id,
                           const AudioFrame& generalAudioFrame,
                           const AudioFrame** uniqueAudioFrames,
                           const uint32_t size)
{
    //LOGI("[MyOutputMixer] generalAudioFrame.sample_rate_hz_ = %d",generalAudioFrame.sample_rate_hz_);
#if 0
    if(_file_mixer_from_conf != NULL)
    {
        _file_mixer_from_conf->WriteToFile(generalAudioFrame);
    }
#endif
    _audioFrame.CopyFrom(generalAudioFrame);
    _audioFrame.id_ = id;
}

/************************************************************************/
/* by zzw | 2013-7-10   11:28    AudioMixerStatusReceiver               */
/************************************************************************/
// Callback function that provides an array of ParticipantStatistics for the
// participants that were mixed last mix iteration.
void MyOutputMixer::MixedParticipants(
                               const int32_t id,
                               const ParticipantStatistics* participantStatistics,
                               const uint32_t size)
{
    LOGI("[MyOutputMixer] MyOutputMixer::MixedParticipants(id=%d, size=%u)", id, size);
}
// Callback function that provides an array of the ParticipantStatistics for
// the participants that had a positiv VAD last mix iteration.
void MyOutputMixer::VADPositiveParticipants(
                                     const int32_t id,
                                     const ParticipantStatistics* participantStatistics,
                                     const uint32_t size)
{
    LOGI("[MyOutputMixer] MyOutputMixer::VADPositiveParticipants(id=%d, size=%u)", id, size);
}
// Callback function that provides the audio level of the mixed audio frame
// from the last mix iteration.
void MyOutputMixer::MixedAudioLevel(
                             const int32_t  id,
                             const uint32_t level)
{
    LOGI("[MyOutputMixer] MyOutputMixer::MixedAudioLevel(id=%d, level=%u)", id, level);
}


// ----------------------------------------------------------------------------
//                             Private methods
// ----------------------------------------------------------------------------

void MyOutputMixer::APMAnalyzeReverseStream() {
    // Convert from mixing to AudioProcessing sample rate, determined by the send
    // side. Downmix to mono.
    AudioFrame frame;
    frame.num_channels_ = 1;
    frame.sample_rate_hz_ = _audioProcessingModulePtr->sample_rate_hz();
    if (RemixAndResample(_audioFrame, &audioproc_resampler_, &frame) == -1)
        return;

    if (_audioProcessingModulePtr->AnalyzeReverseStream(&frame) == -1) {
        LOGI("[MyOutputMixer] AudioProcessingModule::AnalyzeReverseStream() => error");
    }
}