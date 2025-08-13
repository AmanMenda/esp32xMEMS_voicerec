#ifndef VOICE_RECOGNITION_H
#define VOICE_RECOGNITION_H

#include "vr_types.h"
#include "vr_config.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

static const vr_state_t state = VR_STATE_IDLE;

/**
 * @brief Initialize voice recognition system
 * @param config Configuration structure
 * @return VR_OK on success, error code otherwise
 */
vr_err_t vr_init(const vr_config_t* config);

/**
 * @brief Start voice recognition
 * @return VR_OK on success
 */
vr_err_t vr_start(void);

/**
 * @brief Stop voice recognition
 * @return VR_OK on success
 */
vr_err_t vr_stop(void);

/**
 * @brief Register callback for recognition events
 * @param callback Function to call when word is recognized
 * @param user_data User data passed to callback
 */
vr_err_t vr_register_callback(vr_recognition_callback_t callback, void* user_data);

/**
 * @brief Add keyword template (training mode)
 * @param keyword_id Unique identifier for keyword
 * @param keyword_name Human readable name
 * @return VR_OK on success
 */
vr_err_t vr_add_keyword(uint8_t keyword_id, const char* keyword_name);

/**
 * @brief Start training session for specific keyword
 * @param keyword_id ID of keyword to train
 * @return VR_OK on success
 */
vr_err_t vr_start_training(uint8_t keyword_id);

/**
 * @brief Save templates to persistent storage
 * @return VR_OK on success
 */
vr_err_t vr_save_templates(void);

/**
 * @brief Load templates from persistent storage
 * @return VR_OK on success
 */
vr_err_t vr_load_templates(void);

/**
 * @brief Get current system status
 * @param status Pointer to status structure
 * @return VR_OK on success
 */
vr_err_t vr_get_status(vr_status_t* status);

/**
 * @brief Set recognition sensitivity
 * @param sensitivity Value between 0.0 (very sensitive) and 1.0 (strict)
 * @return VR_OK on success
 */
vr_err_t vr_set_sensitivity(float sensitivity);

/**
 * @brief Cleanup and deinitialize
 * @return VR_OK on success
 */
vr_err_t vr_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif // VOICE_RECOGNITION_H