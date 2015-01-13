#ifndef __AUDIO_CODEC_MODULE_H__
#define __AUDIO_CODEC_MODULE_H__

/************************************************************************/
/* by zzw | 2013-7-15   10:14 AudioLibrary Headers                      */
/************************************************************************/
//#include "AVLibrary/AudioLibrary.h"

/************************************************************************/
/* by zzw | 2013-7-15   10:31 WebRTC Headers                            */
/************************************************************************/
#include "../webrtc/modules/interface/module_common_types.h"
#include "../webrtc/system_wrappers/interface/critical_section_wrapper.h"

#include "AudioCodes.h"
#include "AudioDecodes.h"

using namespace webrtc;
/************************************************************************/
/* by zzw | 2013-7-15   15:34                          */
/************************************************************************/
#include <queue>

#define N_REC_QUEUE_BUFFERS 20

class AudioCodingCallback
{
public:
    virtual ~AudioCodingCallback() {}

    virtual int32_t SendData(uint32_t timestamp,
        const char* payload_data,
        uint16_t payload_len_bytes) = 0;
};

class AudioCodecModule
{
public:
    static AudioCodecModule* Create(const int32_t id);

    static void Destroy(AudioCodecModule*& module);

    int16_t Init();

    int32_t Add10MsData(const AudioFrame& audio_frame);

    int32_t Process();

    int16_t Encode(const uint8_t* bitstream,
        int16_t bitstream_len_byte,
        uint32_t timestamp/*,
        WebRtcACMEncodingType* encoding_type*/);



    ///////////////////////////////////////////////////////////////////////////
    // int16_t Decode()
    // This function is used to decode a given bit-stream, without engaging
    // NetEQ.
    //
    // This function acquires the appropriate locks and calls DecodeSafe() for
    // the actual processing. Please note that this is not functional yet.
    //
    // Inputs:
    //   -bitstream         : a buffer where bit-stream will be read.
    //   -bitstream_len_byte : the length of the bit-stream in bytes.
    //
    // Outputs:
    //   -audio              : pointer to a buffer where the audio will written.
    //   -audio_samples      : number of audio samples out of decoding the given
    //                         bit-stream.
    //   -speech_type        : speech type (for future use).
    //
    // Return value:
    //   -1 if failed to decode,
    //    0 if succeeded.
    //
    int16_t Decode(uint8_t* bitstream,
        int16_t bitstream_len_byte,
        int16_t* audio,
        int16_t* audio_samples,
        int8_t* speech_type);

    virtual int32_t RegisterTransportCallback(
        AudioCodingCallback* transport);
    /************************************************************************/
    /* by zzw | 2013-7-15   14:53                          */
    /************************************************************************/
    virtual int32_t IncomingPacket(const uint8_t* incoming_payload,
        const int32_t payload_len_bytes);

    virtual int32_t PlayoutData10Ms(int32_t desired_freq_hz,
        AudioFrame* audio_frame);

protected:
    AudioCodecModule(const int32_t id);
    virtual ~AudioCodecModule();

private:
    CriticalSectionWrapper* callback_crit_sect_;
    CriticalSectionWrapper* playqueue_crit_sect_;

    AudioCodingCallback* transport_callback_;
    
    AudioDecodes  _audioDecodes;
    AudioCodes    _audioCodes;
    
#if 0
    IAudioDecodes   *_audioDecodes;
    IAudioCodes     *_audioCodes;
    CodeType        _codeType;
#endif
    int32_t         id_;
    AudioFrame      _audioFrame;

    //std::queue<int8_t*> _receive_queue;
    std::queue<int8_t*> _decoded_queue;
    std::queue<int8_t*> rec_ready_queue_;

    std::queue<int8_t*> net_rec_queue_;

    int8_t rec_buf_[N_REC_QUEUE_BUFFERS][320];
#if 0
    FileWriter  *_fileWriter;

    FileWriter  *_file_receive_;
    FileWriter  *_file_receive_2_;
#endif
};

#endif
