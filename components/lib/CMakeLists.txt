idf_component_register(
    SRCS 
        "src/core/vr_core.c"
        "src/audio/vr_audio_capture.c"
        "src/utils/vr_low_pass_filter.c"
        "src/utils/vr_plot_data.c"
        # "src/core/vr_state_machine.c"
        # "src/audio/vr_audio_buffer.c"
        # "src/signal_processing/vr_feature_extraction.c"
        # "src/signal_processing/vr_fft.c"
        # "src/signal_processing/vr_filters.c"
        # "src/recognition/vr_template_matching.c"
        # "src/recognition/vr_dtw.c"
        # "src/storage/vr_template_storage.c"
        # "src/storage/vr_nvs_manager.c"
        # "src/utils/vr_math_utils.c"
        # "src/utils/vr_log.c"
        # "src/utils/vr_memory_pool.c"
    
    INCLUDE_DIRS 
        "include"
    
    PRIV_INCLUDE_DIRS 
        "src/core"
        "src/audio"
        "src/utils"
        # "src/signal_processing"
        # "src/recognition"
        # "src/storage"
    
    REQUIRES 
        driver
        nvs_flash
        esp_common
        freertos
    
    PRIV_REQUIRES 
        unity
)