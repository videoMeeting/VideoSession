/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_VOICE_ENGINE_OUTPUT_MIXER_INTERNAL_H_
#define WEBRTC_VOICE_ENGINE_OUTPUT_MIXER_INTERNAL_H_

#include "../webrtc/common_audio/resampler/include/push_resampler.h"
#include "../webrtc/modules/interface/module_common_types.h"

using namespace webrtc;

#if 0
namespace webrtc {

class AudioFrame;
class PushResampler;

namespace voe {
#endif
// Upmix or downmix and resample the audio in |src_frame| to |dst_frame|.
// Expects |dst_frame| to have its |num_channels_| and |sample_rate_hz_| set to
// the desired values. Updates |samples_per_channel_| accordingly.
//
// On failure, returns -1 and copies |src_frame| to |dst_frame|.
int RemixAndResample(const AudioFrame& src_frame,
                     PushResampler* resampler,
                     AudioFrame* dst_frame);
#if 0
}  // namespace voe
}  // namespace webrtc
#endif
#endif  // VOICE_ENGINE_OUTPUT_MIXER_INTERNAL_H_
