#ifndef __VOE_HEADER_H__
#define __VOE_HEADER_H__

#include "../webrtc/common_types.h"

using namespace webrtc;

class VoEMediaProcess
{
public:
    // The VoiceEngine user should override the Process() method in a
    // derived class. Process() will be called when audio is ready to
    // be processed. The audio can be accessed in several different modes
    // given by the |type| parameter. The function should modify the
    // original data and ensure that it is copied back to the |audio10ms|
    // array. The number of samples in the frame cannot be changed.
    // The sampling frequency will depend upon the codec used.
    // If |isStereo| is true, audio10ms will contain 16-bit PCM data
    // samples in interleaved stereo format (L0,R0,L1,R1,...).
    virtual void Process(int channel, ProcessingTypes type,
        int16_t audio10ms[], int length,
        int samplingFreq, bool isStereo) = 0;

protected:
    virtual ~VoEMediaProcess() {}
};

#endif