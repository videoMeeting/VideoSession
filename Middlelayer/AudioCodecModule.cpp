#include "AudioCodecModule.h"

#define LOG_TAG "WebRTC Voe | AudioCodecModule"

#define LOGI printf
#define LOGE printf
//wangguijun
AudioCodecModule* AudioCodecModule::Create(const int32_t id)
{
    return new AudioCodecModule(id);
}

void AudioCodecModule::Destroy(AudioCodecModule*& module)
{
    if (module)
    {
        delete module;
        module = NULL;
    }
}

AudioCodecModule::AudioCodecModule(const int32_t id):id_(id)
    , callback_crit_sect_(CriticalSectionWrapper::CreateCriticalSection())
    , playqueue_crit_sect_(CriticalSectionWrapper::CreateCriticalSection())
    , transport_callback_(NULL)
    //, _fileWriter(NULL)
   // , _file_receive_(NULL)
{
    memset(rec_buf_, 0, sizeof(rec_buf_));

    for (int i = 0; i < N_REC_QUEUE_BUFFERS; i++)
    {
        rec_ready_queue_.push(rec_buf_[i]);
    }

#if 0
    {
        _file_receive_ = new FileWriter();
        char file_name[120];
        memset(file_name,0,120);
        sprintf(file_name,"/storage/sdcard0/VSMeeting/received_data_in_1_%u.pcm",this);
        if(!_file_receive_->SetFileName(file_name))
        {

        }
    }
    
    {
        _file_receive_2_ = new FileWriter();
        char file_name[120];
        memset(file_name,0,120);
        sprintf(file_name,"/storage/sdcard0/VSMeeting/received_data_in_2_%u.pcm",this);
        if(!_file_receive_2_->SetFileName(file_name))
        {

        }
    }
    
#endif
}

AudioCodecModule::~AudioCodecModule()
{
#if 0
    if (_file_receive_ != NULL)
    {
        delete _file_receive_;
        _file_receive_ = NULL;
    }

    if (_file_receive_2_ != NULL)
    {
        delete _file_receive_2_;
        _file_receive_2_ = NULL;
    }
#endif
    
    _audioDecodes.unInitAudioDecode();
    _audioCodes.unInitAudioCode();
    
#if 0
    if(_audioCodes)
    {
        _audioCodes->Destory();
        _audioCodes = NULL;
    }

    if (_audioDecodes)
    {
        _audioDecodes->Destory();
        _audioDecodes = NULL;
    }
#endif
    {
        CriticalSectionScoped        cs(playqueue_crit_sect_);
        while(!_decoded_queue.empty())
        {
//            int8_t* data_ptr_ = _decoded_queue.front();
            _decoded_queue.pop();
            //free(data_ptr_);
        }
    }

    if (callback_crit_sect_)
    {
        delete callback_crit_sect_;
        callback_crit_sect_ = NULL;
    }
}

#if 0
void AudioCodecModule::setFileWriter(FileWriter *fileWriter)
{
    _fileWriter = fileWriter;
}
#endif

/************************************************************************/
/* by zzw | 2013-7-15   10:32                          */
/************************************************************************/
int16_t AudioCodecModule::Init()
{
    //LOGI("[AudioCodecModule] AudioCodecModule::Init()");
    
    _audioDecodes.initAudioDecode(AMR_NBCODE);
    _audioCodes.initAudioCode(AMR_NBCODE);
#if 0
    if (_audioDecodes == NULL)
    {
        _audioDecodes = CreateAudioDecodes();
        _audioDecodes->initAudioDecode(_codeType);
    }

    if (_audioCodes == NULL)
    {
        _audioCodes = CreateAudioCodes();
        _audioCodes->initAudioCode(_codeType);
    }
#endif
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-15   10:32                          */
/************************************************************************/
int32_t AudioCodecModule::Add10MsData(const AudioFrame& audio_frame)
{
    if (audio_frame.samples_per_channel_ <= 0)
    {
        LOGI("[AudioCodecModule] Cannot Add 10 ms audio, payload length is negative or zero");
        return -1;
    }

    if ((audio_frame.sample_rate_hz_ != 8000)
        && (audio_frame.sample_rate_hz_ != 16000)
        && (audio_frame.sample_rate_hz_ != 32000)
        && (audio_frame.sample_rate_hz_ != 48000))
    {
        LOGI("[AudioCodecModule] Cannot Add 10 ms audio, input frequency not valid");
        return -1;
    }

    if ((audio_frame.sample_rate_hz_ / 100) != audio_frame.samples_per_channel_) {
        LOGI("[AudioCodecModule] Cannot Add 10 ms audio, input frequency and length doesn't match");
        return -1;
    }

    if (audio_frame.num_channels_ != 1 && audio_frame.num_channels_ != 2) {
        LOGI("[AudioCodecModule] Cannot Add 10 ms audio, invalid number of channels.");
        return -1;
    }


    _audioFrame.CopyFrom(audio_frame);
    return 0;
}

int32_t AudioCodecModule::Process()
{
    return Encode((uint8_t*)_audioFrame.data_
        ,(_audioFrame.samples_per_channel_*_audioFrame.num_channels_*sizeof(int16_t))
        ,_audioFrame.timestamp_);
}


/************************************************************************/
/* by zzw | 2013-7-15   10:23 ±àÂë                                 */
/************************************************************************/
int16_t AudioCodecModule::Encode(const uint8_t* bitstream,
        int16_t bitstream_len_byte,
        uint32_t timestamp/*,
        WebRtcACMEncodingType* encoding_type*/)
{
#if 1
    //LOGI("[AudioCodecModule]  AudioCodecModule::Encode");
    
#if 1
    int Num = bitstream_len_byte << 1;
    bool IsNull = false;
    for(int i = 0; i < Num; i++)
    {
        if(bitstream[i] != '\0')
        {
            IsNull = true;
            break;
        }
    }
    
    if(!IsNull)
        return 0;
#endif
    
    char data[120];
    memset(data,0,120);
    int outsize = 0;
    //LOGI("[AudioCodecModule::Encode] 1. %u",TimeGetTimestamp());
    if ( _audioCodes.CodeAudio((char *)bitstream,bitstream_len_byte << 1,data,&outsize) != 0)
    {
        
        LOGE("[AudioCodecModule] Encode Failed");
        return -1;
    }
#endif
    //LOGI("[AudioCodecModule::Encode] 2. %u",TimeGetTimestamp());

    {
        CriticalSectionScoped lock(callback_crit_sect_);
        if (transport_callback_ != NULL)
        {
            //LOGD("[AudioCodecModule] transport_callback_  SendData");
            transport_callback_->SendData(timestamp,data,outsize);
        }
    }
    //LOGI("[AudioCodecModule::Encode] 3. %u",TimeGetTimestamp());

        
    return 0;
}
/************************************************************************/
/* by zzw | 2013-7-15   10:22 ½âÂë                                 */
/************************************************************************/
int16_t AudioCodecModule::Decode(uint8_t* bitstream,
               int16_t bitstream_len_byte,
               int16_t* audio,
               int16_t* audio_samples,
               int8_t* speech_type)
{
#if 0
    if (_audioDecodes == NULL)
    {
        if( _audioCodes == NULL)
        {
            LOGI("[AudioCodecModule] AudioCodecModule::Decode() must call Init() first");
            return -1;
        }
    }
#endif
    
    return 0;
}

int32_t AudioCodecModule::RegisterTransportCallback(
    AudioCodingCallback* transport)
{
    CriticalSectionScoped lock(callback_crit_sect_);
    transport_callback_ = transport;
    return 0;
}

/************************************************************************/
/* by zzw | 2013-7-15   14:56 For Decode                                */
/************************************************************************/
int32_t AudioCodecModule::IncomingPacket(const uint8_t* incoming_payload,
                               const int32_t payload_len_bytes)
{
    if (payload_len_bytes < 0)
    {
        LOGI("[AudioCodecModule] IncomingPacket() Error, payload-length cannot be negative");
        return -1;
    }
    //LOGI("[AudioCodecModule] payload_len_bytes:%d",payload_len_bytes);
    CriticalSectionScoped lock(playqueue_crit_sect_);

    int8_t *data = (int8_t *)malloc(payload_len_bytes);
    memset(data,0,payload_len_bytes);
    memcpy(data,incoming_payload,payload_len_bytes);
    net_rec_queue_.push(data);
    
    return 0;
}

int32_t AudioCodecModule::PlayoutData10Ms(int32_t desired_freq_hz,
                                AudioFrame* audio_frame)
{
    //LOGI("[AudioCodecModule] AudioCodecModule::PlayoutData10Ms() desired_freq_hz:%u",desired_freq_hz);

    if(net_rec_queue_.size() <= 0)
    {
        LOGE("[AudioCodecModule] net_rec_queue_ is Empty %lu",net_rec_queue_.size());
        return -1;
    }

    {
        //LOGI("[AudioCodecModule] 1");
        CriticalSectionScoped cs(playqueue_crit_sect_);
        int8_t* data_ptr = net_rec_queue_.front();
        net_rec_queue_.pop();
        //LOGI("[AudioCodecModule] 2");

        unsigned int out_size = 0;
        char outBuffer[320];
        memset(outBuffer,0,320);

#if 1
        if (_audioDecodes.DecodeAudio((char *)data_ptr,13,(char *)outBuffer,&out_size) != 0)
        {
            LOGE("[AudioCodecModule] Decode Failed");
            free(data_ptr);
            return -1;
        }
#endif

//         if (_file_receive_ != NULL)
//         {
//             _file_receive_->WriteToFile((const uint8_t*)outBuffer,320);
//         }

        audio_frame->UpdateFrame(id_
            , 0
            , (int16_t*)outBuffer
            , 160
            , 16000//audio_frame->samples_per_channel_ * 100
            , AudioFrame::kNormalSpeech
            , AudioFrame::kVadUnknown
            , 1);

#if 0
        if (_file_receive_2_)
        {
            _file_receive_2_->WriteToFile(*audio_frame);
        }
#endif
        //LOGI("[AudioCodecModule] 3");
        free(data_ptr);
        //LOGI("[AudioCodecModule] 4");
    }
#if 0
    //LOGI("[AudioCodecModule] Enter AudioCodecModule::PlayoutData10Ms() desired_freq_hz:%d",desired_freq_hz);
    if (_decoded_queue.size() <= 0)
    {
        LOGE("[AudioCodecModule] _decoded_queue is Empty %d",rec_ready_queue_.size());
        return -1;
    }
    {
        CriticalSectionScoped cs(playqueue_crit_sect_);
        int8_t* data_ptr = _decoded_queue.front();
        _decoded_queue.pop();
        //memcpy(audio_frame->data_,data_ptr,320);
        //free(data_ptr);

//         int id,
//         uint32_t timestamp,
//         const int16_t* data,
//         int samples_per_channel,
//         int sample_rate_hz,
//         SpeechType speech_type,
//         VADActivity vad_activity,
//         int num_channels,
//         uint32_t energy

        audio_frame->UpdateFrame(id_
            , 0
            , (int16_t*)data_ptr
            , 160
            , audio_frame->samples_per_channel_ * 100
            , AudioFrame::kNormalSpeech
            , AudioFrame::kVadUnknown
            , 1);

//         audio_frame->samples_per_channel_ = 160;
//         audio_frame->speech_type_ = AudioFrame::kNormalSpeech;
//         audio_frame->num_channels_ = 1;
//         audio_frame->sample_rate_hz_ = audio_frame->samples_per_channel_ * 100;
//         audio_frame->timestamp_ = 0;
//         audio_frame->id_ = -1;
        
        //free(data_ptr);
        memset(data_ptr,0,320);
        rec_ready_queue_.push(data_ptr);
    }
#endif
    return 0;
}