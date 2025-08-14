#ifndef VR_CONFIG_H
#define VR_CONFIG_H

#include "sdkconfig.h"
#include "vr_types.h"

// Default configuration values
#define VR_DEFAULT_SAMPLE_RATE          16000
#define VR_DEFAULT_FRAME_SIZE           512
#define VR_DEFAULT_HOP_SIZE             256
#define VR_DEFAULT_BUFFER_SIZE          2048
#define VR_DEFAULT_DMA_BUF_COUNT        4
#define VR_DEFAULT_DMA_BUF_LEN          1024

#define VR_DEFAULT_ENERGY_THRESHOLD     1000.0f
#define VR_DEFAULT_SILENCE_FRAMES       10
#define VR_DEFAULT_MAX_WORD_FRAMES      40
#define VR_DEFAULT_NUM_MFCC_COEFFS      6

#define VR_DEFAULT_DTW_THRESHOLD        15.0f
#define VR_DEFAULT_MAX_KEYWORDS         8

#define VR_DEFAULT_NVS_NAMESPACE        "voice_rec"

// Configuration macros based on menuconfig
#ifndef CONFIG_VR_SAMPLE_RATE
#define CONFIG_VR_SAMPLE_RATE           VR_DEFAULT_SAMPLE_RATE
#endif

#ifndef CONFIG_VR_MAX_KEYWORDS
#define CONFIG_VR_MAX_KEYWORDS          VR_DEFAULT_MAX_KEYWORDS
#endif

// Default configuration initializer
#define VR_DEFAULT_CONFIG() { \
    .audio = { \
        .i2s_sck_pin = GPIO_NUM_14, \
        .i2s_ws_pin = GPIO_NUM_15, \
        .i2s_sd_pin = GPIO_NUM_32, \
        .i2s_port = I2S_NUM_0, \
        .sample_rate = CONFIG_VR_SAMPLE_RATE, \
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, \
        .buffer_size = VR_DEFAULT_BUFFER_SIZE, \
        .dma_buf_count = VR_DEFAULT_DMA_BUF_COUNT, \
        .dma_buf_len = VR_DEFAULT_DMA_BUF_LEN \
    }, \
    .processing = { \
        .frame_size = VR_DEFAULT_FRAME_SIZE, \
        .hop_size = VR_DEFAULT_HOP_SIZE, \
        .energy_threshold = VR_DEFAULT_ENERGY_THRESHOLD, \
        .silence_frames = VR_DEFAULT_SILENCE_FRAMES, \
        .max_word_frames = VR_DEFAULT_MAX_WORD_FRAMES, \
        .num_mfcc_coeffs = VR_DEFAULT_NUM_MFCC_COEFFS \
    }, \
    .recognition = { \
        .dtw_threshold = VR_DEFAULT_DTW_THRESHOLD, \
        .max_keywords = CONFIG_VR_MAX_KEYWORDS, \
        .enable_noise_reduction = true, \
        .enable_auto_gain_control = true \
    }, \
    .enable_debug_logs = false, \
    .nvs_namespace = VR_DEFAULT_NVS_NAMESPACE \
}

#endif // VR_CONFIG_H