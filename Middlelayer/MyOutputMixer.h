#ifndef __MYOUTPUT_MIXER_H__
#define __MYOUTPUT_MIXER_H__

/************************************************************************/
/* by zzw | 2013-7-13   20:59                          */
/************************************************************************/
#include "VoeHeader.h"
#include "AudioCodecModule.h"

//#include "FileWriter.h"
/************************************************************************/
/* by zzw | 2013-7-10   11:24 WebRTC Headers                            */
/************************************************************************/
#include "../webrtc/system_wrappers/interface/critical_section_wrapper.h"
#include "../webrtc/modules/interface/module_common_types.h"
#include "../webrtc/modules/audio_processing/include/audio_processing.h"

#include "../webrtc/modules/audio_conference_mixer/interface/audio_conference_mixer_defines.h"
#include "../webrtc/modules/audio_conference_mixer/interface/audio_conference_mixer.h"

#include "../webrtc/common_audio/resampler/include/push_resampler.h"

using namespace webrtc;


class MyOutputMixer: public AudioMixerOutputReceiver,
    public AudioMixerStatusReceiver
{

public:
    static int32_t Create(MyOutputMixer*& mixer, uint32_t instanceId);

    static void Destroy(MyOutputMixer*& mixer);

    virtual ~MyOutputMixer();

    int32_t SetAudioProcessingModule(
        AudioProcessing* audioProcessingModule);

    // VoEExternalMedia
    int RegisterExternalMediaProcessing(
        VoEMediaProcess& proccess_object);

    int DeRegisterExternalMediaProcessing();

    int32_t MixActiveChannels();

    int32_t DoOperationsOnCombinedSignal();

    int32_t SetMixabilityStatus(MixerParticipant& participant,
        bool mixable);

    int32_t SetAnonymousMixabilityStatus(MixerParticipant& participant,
        bool mixable);

    int GetMixedAudio(int sample_rate_hz, int num_channels,
        AudioFrame* audioFrame);

protected:
    /************************************************************************/
    /* by zzw | 2013-7-10   11:27   AudioMixerOutputReceiver                */
    /************************************************************************/
    virtual void NewMixedAudio(const int32_t id,
        const AudioFrame& generalAudioFrame,
        const AudioFrame** uniqueAudioFrames,
        const uint32_t size);

    /************************************************************************/
    /* by zzw | 2013-7-10   11:28    AudioMixerStatusReceiver               */
    /************************************************************************/
    // Callback function that provides an array of ParticipantStatistics for the
    // participants that were mixed last mix iteration.
    virtual void MixedParticipants(
        const int32_t id,
        const ParticipantStatistics* participantStatistics,
        const uint32_t size);
    // Callback function that provides an array of the ParticipantStatistics for
    // the participants that had a positiv VAD last mix iteration.
    virtual void VADPositiveParticipants(
        const int32_t id,
        const ParticipantStatistics* participantStatistics,
        const uint32_t size);
    // Callback function that provides the audio level of the mixed audio frame
    // from the last mix iteration.
    virtual void MixedAudioLevel(
        const int32_t  id,
        const uint32_t level);

protected:
    MyOutputMixer(int instanceId);

    AudioProcessing* _audioProcessingModulePtr;
    // owns
    CriticalSectionWrapper& _callbackCritSect;

    AudioConferenceMixer& _mixerModule;
    AudioFrame  _audioFrame;
    PushResampler resampler_;  // converts mixed audio to fit ADM format
    PushResampler audioproc_resampler_;  // converts mixed audio to fit APM rate

    VoEMediaProcess* _externalMediaCallbackPtr;
    bool _externalMedia;

    int _mixingFrequencyHz;
    int _instanceId;

    AudioCodecModule&       _audioCodingModule;
private:
    void APMAnalyzeReverseStream();
#if 0
    FileWriter *_file_mixer_in;
    FileWriter *_file_mixer_out;
    FileWriter *_file_mixer_from_conf;
#endif
};

#endif