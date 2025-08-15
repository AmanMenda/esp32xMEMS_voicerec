#include "vr_private_core.h"
#include "vr_audio.h"

vr_state_t state = VR_STATE_IDLE;
int32_t raw_samples[VR_DEFAULT_FRAME_SIZE];

vr_err_t vr_init(const vr_config_t* config)
{
    if (!config)
        return VR_ERR_INVALID_STATE;
    
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = config->audio.sample_rate,
        .bits_per_sample = config->audio.bits_per_sample,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
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
    i2s_set_pin(config->audio.i2s_port, &i2s_mic_pins);
    return VR_OK;
}

vr_state_t vr_get_current_state(void)
{
    return state;
}

void vr_set_state(vr_state_t new_state)
{
    state = new_state;
}

vr_err_t vr_start(void)
{
    if (vr_get_current_state() != VR_STATE_IDLE) {
        ESP_LOGE(VR_CORE_TAG, "vr_start(): Le système n'est pas en état IDLE.");
        return VR_ERR_INVALID_STATE;
    }

    vr_err_t err = vr_audio_capture_start();
    if (err != VR_OK) {
        ESP_LOGE(VR_CORE_TAG, "vr_start(): Erreur démarrage capture audio (%d)", err);
        return err;
    }
    vr_set_state(VR_STATE_LISTENING);
    ESP_LOGI(VR_CORE_TAG, "vr_start(): Reconnaissance vocale démarrée.");
    return VR_OK;
}

vr_err_t vr_cleanup(void)
{
    vr_state_t state = vr_get_current_state();

    if (state == VR_STATE_LISTENING || 
        state == VR_STATE_RECORDING ||
        state == VR_STATE_PROCESSING) {
            // vr_audio_capture_stop();
            vr_set_state(VR_STATE_IDLE);
            ESP_LOGI(VR_CORE_TAG, "vr_cleanup(): Capture audio arrêtée.");
        }
    return VR_OK;
}