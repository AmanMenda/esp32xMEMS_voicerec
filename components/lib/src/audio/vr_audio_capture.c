#include "vr_audio.h"
#include "vr_utils.h"

vr_err_t vr_audio_capture_start(void)
{
    size_t bytes_read = 0;
    int samples_read;

    memset(raw_samples, 0, sizeof(raw_samples));
    while (1) {
        if (i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t)*VR_DEFAULT_FRAME_SIZE,
                     &bytes_read, portMAX_DELAY) != ESP_OK) {
            return VR_ERR_INVALID_ARG;
        }
        samples_read = bytes_read / sizeof(int32_t);
        send_plotter_data(raw_samples, samples_read);
    }
    return VR_OK;
}

