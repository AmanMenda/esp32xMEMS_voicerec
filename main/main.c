#include <stdio.h>

#include "../lib/include/voice_recognition.h"

void recognition_callback(
    vr_event_t event,
    const vr_recognition_result_t* result,
    void* user_data
) {
    switch (event) {
        case VR_EVENT_KEYWORD_DETECTED:
            ESP_LOGI(TAG, "Keyword detected: %s (confidence: %.2f)", 
                     result->keyword_name, result->confidence);
            break;
        case VR_EVENT_TRAINING_COMPLETE:
            ESP_LOGI(TAG, "Training complete for: %s", result->keyword_name);
            break;
        case VR_EVENT_ERROR:
            ESP_LOGE(TAG, "Recognition error occurred");
            break;
        default:
            break;
    }
}

void app_main(void)
{
    vr_config_t config = VR_DEFAULT_CONFIG();
    vr_err_t err = vr_init(&config);
    
    if (err != VR_OK) {
        ESP_LOGE(TAG, "Failed to initialize voice recognition: %d", err);
        return;
    }
    vr_register_callback(recognition_callback, NULL);

    vr_add_keyword(0, "start");
    vr_add_keyword(1, "stop");
    vr_add_keyword(2, "left");
    vr_add_keyword(3, "right");

    vr_start();

    ESP_LOGI(TAG, "Voice recognition started. Say keywords: start, stop, left, right");    
    // Main loop
    while (1) {
        vr_status_t status;
        vr_get_status(&status);
        ESP_LOGI(TAG, "State: %d, Keywords: %d, Free heap: %zu", 
                status.current_state, status.active_keywords, status.free_heap);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}