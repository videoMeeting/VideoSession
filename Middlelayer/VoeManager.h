#ifndef __VOE_MANAGER_H__
#define __VOE_MANAGER_H__


#include "MyShareData.h"
#include "MyChannel.h"

class OpenLocalUser;

//#include "FileWriter.h"
/************************************************************************/
/* by zzw | 2013-7-11   13:51                          */
/************************************************************************/
#include "../webrtc/system_wrappers/interface/critical_section_wrapper.h"
#include "../webrtc/modules/audio_device/include/audio_device_defines.h"
#include "../webrtc/modules/interface/module_common_types.h"

using namespace webrtc;
/************************************************************************/
/* by zzw | 2013-7-14   22:07 Sys Headers                               */
/************************************************************************/
#include <string>
#include <list>
#include <map>

class VoeManager : public MyShareData
    , public AudioTransport
    , public AudioDeviceObserver
{
public:
    static VoeManager* Create();

    static bool Delete(VoeManager* & voeManager);

    virtual int Init(AudioDeviceModule* external_adm = NULL,
        AudioProcessing* audioproc = NULL);

    virtual AudioProcessing* audio_processing() {
        return _shared->audio_processing();
    }

    int Terminate();

    virtual int MaxNumOfChannels();

    int CreateChannel(unsigned long video_id);

    virtual int DeleteChannel(unsigned long video_id);

    virtual int StartReceive(unsigned long  channel);

    virtual int StopReceive(unsigned long  channel);

    virtual int StartPlayout(unsigned long  channel);

    virtual int StopPlayout(unsigned long  channel);

    void CallbackAudioPacket(unsigned long m_ulPeerAudioID,unsigned char* pData,int nLen);
    //////////////////////////////////////////////////////////////////////////
    
    // Add by zzw
    int StartLocalAudio(OpenLocalUser* pOpenLocalUser);

    int StopLocalAudio();
    
    void StopSendAudio();
    
    void StartSendAudio();

    //void SetVideoID(unsigned long video_id);

    virtual ~VoeManager();
protected:
    /************************************************************************/
    /* by zzw | 2013-7-11   13:56  Inherit AudioTransport                   */
    /************************************************************************/
    virtual int32_t RecordedDataIsAvailable(const void* audioSamples,
        const uint32_t nSamples,
        const uint8_t nBytesPerSample,
        const uint8_t nChannels,
        const uint32_t samplesPerSec,
        const uint32_t totalDelayMS,
        const int32_t clockDrift,
        const uint32_t currentMicLevel,
        const bool keyPressed,
        uint32_t& newMicLevel);  

    virtual int32_t NeedMorePlayData(const uint32_t nSamples,
        const uint8_t nBytesPerSample,
        const uint8_t nChannels,
        const uint32_t samplesPerSec,
        void* audioSamples,
        uint32_t& nSamplesOut);

    /************************************************************************/
    /* by zzw | 2013-7-11   13:56  Inherit AudioDeviceObserver              */
    /************************************************************************/
    virtual void OnErrorIsReported(const ErrorCode error);

    virtual void OnWarningIsReported(const WarningCode warning);

protected:
    VoeManager();

    uint32_t _oldVoEMicLevel;
    
    uint32_t _oldMicLevel;
    
    AudioFrame _audioFrame;

    MyShareData* _shared;
private:
    int32_t StartPlayout();
    int32_t StopPlayout();
    int32_t StartSend();
    int32_t StopSend();
private:
    int32_t TerminateInternal();
    CriticalSectionWrapper& _callbackCritSect;

    typedef std::map<unsigned long,MyChannel *> ChannelManagers;
    ChannelManagers channelManager;
    //////////////////////////////////////////////////////////////////////////

    bool _start_recording;

   // FileWriter  *_mixer_file;
};

#endif