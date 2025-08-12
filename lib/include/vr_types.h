#ifndef VR_TYPES_H
#define VR_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "driver/i2s.h"

// Error codes
typedef enum {
    VR_OK = 0,
    VR_ERR_INVALID_ARG,
    VR_ERR_NO_MEMORY,
    VR_ERR_INVALID_STATE,
    VR_ERR_TIMEOUT,
    VR_ERR_NOT_FOUND,
    VR_ERR_ALREADY_EXISTS,
    VR_ERR_HARDWARE_FAIL,
    VR_ERR_STORAGE_FAIL
} vr_err_t;

// System states
typedef enum {
    VR_STATE_IDLE,
    VR_STATE_LISTENING,
    VR_STATE_RECORDING,
    VR_STATE_PROCESSING,
    VR_STATE_TRAINING,
    VR_STATE_ERROR
} vr_state_t;

// Recognition events
typedef enum {
    VR_EVENT_KEYWORD_DETECTED,
    VR_EVENT_TRAINING_COMPLETE,
    VR_EVENT_SPEECH_START,
    VR_EVENT_SPEECH_END,
    VR_EVENT_ERROR
} vr_event_t;

// Audio configuration
typedef struct {
    gpio_num_t i2s_sck_pin;
    gpio_num_t i2s_ws_pin;
    gpio_num_t i2s_sd_pin;
    i2s_port_t i2s_port;
    uint32_t sample_rate;
    i2s_bits_per_sample_t bits_per_sample;
    size_t buffer_size;
    uint8_t dma_buf_count;
    size_t dma_buf_len;
} vr_audio_config_t;

// Processing configuration
typedef struct {
    uint16_t frame_size;
    uint16_t hop_size;
    float energy_threshold;
    uint8_t silence_frames;
    uint8_t max_word_frames;
    uint8_t num_mfcc_coeffs;
} vr_processing_config_t;

// Recognition configuration
typedef struct {
    float dtw_threshold;
    uint8_t max_keywords;
    bool enable_noise_reduction;
    bool enable_auto_gain_control;
} vr_recognition_config_t;

// Main configuration structure
typedef struct {
    vr_audio_config_t audio;
    vr_processing_config_t processing;
    vr_recognition_config_t recognition;
    bool enable_debug_logs;
    const char* nvs_namespace;
} vr_config_t;

// Recognition result
typedef struct {
    uint8_t keyword_id;
    char keyword_name[32];
    float confidence;
    uint32_t timestamp;
} vr_recognition_result_t;

// System status
typedef struct {
    vr_state_t current_state;
    uint8_t active_keywords;
    uint32_t total_recognitions;
    uint32_t false_positives;
    float average_confidence;
    size_t free_heap;
} vr_status_t;

// Callback function type
typedef void (*vr_recognition_callback_t)(vr_event_t event, 
                                        const vr_recognition_result_t* result, 
                                        void* user_data);

#endif // VR_TYPES_H