#ifndef __MY_SHAREDATA_H__
#define __MY_SHAREDATA_H__
/************************************************************************/
/* by zzw | 2013-7-31   9:31                          */
/************************************************************************/
#include "audio_defines.h"
/************************************************************************/
/* by zzw | 2013-7-14   22:07 WebRTC Headers                            */
/************************************************************************/
#include "webrtc/modules/audio_device/include/audio_device.h"
#include "webrtc/modules/audio_processing/include/audio_processing.h"
#include "webrtc/system_wrappers/interface/scoped_ptr.h"
#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"
#include "webrtc/modules/utility/interface/process_thread.h"

using namespace webrtc;
/************************************************************************/
/* by zzw | 2013-7-14   22:07 Sys Headers                               */
/************************************************************************/
#include <string>
#include <map>

/************************************************************************/
/* by zzw | 2013-7-14   22:08                          */
/************************************************************************/
class MyOutputMixer;
class MyTransmitMixer;

class MyShareData
{
public:

    uint32_t instance_id() const { return _instanceId; }

    MyOutputMixer* output_mixer() { return _outputMixerPtr; }
    MyTransmitMixer* transmit_mixer() { return _transmitMixerPtr; }
    /************************************************************************/
    /* by zzw | 2013-7-11   11:40  ADM Audio Device Module                  */
    /************************************************************************/
    AudioDeviceModule* audio_device() { return _audioDevicePtr; }
    void set_audio_device(AudioDeviceModule* audio_device);

    // Level
    AudioDeviceModule::AudioLayer audio_device_layer() const {
        return _audioDeviceLayer;
    }
    void set_audio_device_layer(AudioDeviceModule::AudioLayer layer) {
        _audioDeviceLayer = layer;
    }

    // APM Audio Process Module
    AudioProcessing* audio_processing() { return audioproc_.get(); }
    void set_audio_processing(AudioProcessing* audioproc);

    //////////////////////////////////////////////////////////////////////////
    CriticalSectionWrapper* crit_sec() { return _apiCritPtr; }
    //////////////////////////////////////////////////////////////////////////
    ProcessThread* process_thread() { return _moduleProcessThreadPtr; }

    //////////////////////////////////////////////////////////////////////////
    bool ext_playout() const { return _externalPlayout; }
    void set_ext_playout(bool value) { _externalPlayout = value; }

    bool ext_recording() const { return _externalRecording; }
    void set_ext_recording(bool value) { _externalRecording = value; }
    //////////////////////////////////////////////////////////////////////////
    const char* server_ip() const { return _server_ip;}
    void set_server_ip(const char* server_ip);
    
    unsigned int server_port() const { return _server_port;};
    void set_server_port(unsigned int uiPort){ _server_port = uiPort;};

protected:
    const uint32_t _instanceId;
    CriticalSectionWrapper* _apiCritPtr;

    MyOutputMixer*              _outputMixerPtr;    // Output
    MyTransmitMixer*            _transmitMixerPtr;  // Input

    scoped_ptr<AudioProcessing> audioproc_;
    ProcessThread*              _moduleProcessThreadPtr;

    AudioDeviceModule*          _audioDevicePtr;

    AudioDeviceModule::AudioLayer _audioDeviceLayer;

    bool _externalRecording;
    bool _externalPlayout;

    MyShareData();
    virtual ~MyShareData();

    /************************************************************************/
    /* by zzw | 2013-7-14   22:08                          */
    /************************************************************************/
    char* _server_ip;
    unsigned int _server_port;
};

#endif