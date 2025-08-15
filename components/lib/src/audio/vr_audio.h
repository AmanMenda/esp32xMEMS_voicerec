#ifndef VR_AUDIO_H
#define VR_AUDIO_H

#include "voice_recognition.h"
#include <driver/i2s.h>

/**
 * @brief Make the call to the I2S lib functions to start the audio capture
 * @return VR_OK on success, VR_ERR_INVALID_ARG if i2s_read() fails.
 */
vr_err_t vr_audio_capture_start(void);

#endif