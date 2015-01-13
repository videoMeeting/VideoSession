#include "MyShareData.h"
#include "MyOutputMixer.h"
#include "MyTransmitMixer.h"

static int32_t _gInstanceCounter = 0;

MyShareData::MyShareData():_instanceId(_gInstanceCounter)
    , _apiCritPtr(CriticalSectionWrapper::CreateCriticalSection())
    , audioproc_(NULL)
    , _moduleProcessThreadPtr(ProcessThread::CreateProcessThread())
    , _audioDevicePtr(NULL)
    , _externalRecording(false)
    , _externalPlayout(false)
    , _server_ip(NULL)
{
    if (MyOutputMixer::Create(_outputMixerPtr,_gInstanceCounter) == 0)
    {
        // Init
    }

    if (MyTransmitMixer::Create(_transmitMixerPtr,_gInstanceCounter) == 0)
    {
        // Init
        _transmitMixerPtr->SetEngineInformation((*_moduleProcessThreadPtr));
    }
    _audioDeviceLayer = AudioDeviceModule::kPlatformDefaultAudio;
    
    _server_ip = new char[255];
}

MyShareData::~MyShareData()
{
    MyOutputMixer::Destroy(_outputMixerPtr);
    if (_audioDevicePtr)
    {
        _audioDevicePtr->Release();
    }
    delete _apiCritPtr;
    delete [] _server_ip;
}

void MyShareData::set_server_ip(const char* server_ip)
{
    strncpy(_server_ip,server_ip,strlen(server_ip));
}

void MyShareData::set_audio_device(AudioDeviceModule* audio_device)
{
    if (audio_device)
        audio_device->AddRef();
    if (_audioDevicePtr)
        _audioDevicePtr->Release();
    _audioDevicePtr = audio_device;
}

void MyShareData::set_audio_processing(AudioProcessing* audioproc) {
    audioproc_.reset(audioproc);
    _transmitMixerPtr->SetAudioProcessingModule(audioproc);
    _outputMixerPtr->SetAudioProcessingModule(audioproc);
}