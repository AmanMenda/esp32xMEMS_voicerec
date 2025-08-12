#include "../../include/voice_recognition.h"
#include <driver/i2s.h>

vr_err_t vr_init(const vr_config_t* config)
{
    if (!config)
        return VR_ERR_INVALID_STATE;
    
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = config->audio.sample_rate,
        .bits_per_sample = config->audio.bits_per_sample,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = config->audio.dma_buf_count,
        .dma_buf_len = config->audio.dma_buf_len,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };
    if (i2s_driver_install(config->audio.i2s_port, &i2s_config, 0, NULL) != ESP_OK) {
        return VR_ERR_HARDWARE_FAIL;
    }
    i2s_pin_config_t i2s_mic_pins = {
        .bck_io_num = config->audio.i2s_sck_pin,
        .ws_io_num = config->audio.i2s_ws_pin,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = config->audio.i2s_sd_pin
    };
    return VR_OK;
}