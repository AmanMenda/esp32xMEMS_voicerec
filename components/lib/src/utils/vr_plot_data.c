#include "vr_utils.h"

void send_plotter_data(int32_t* samples, size_t count) {
    static float filter_state = .0f;

    for (int i = 0; i < count; i += 4) { // Une valeur sur 4 pour réduire le débit
        filter_state = low_pass_filter(samples[i], filter_state, VR_DEFAULT_ALPHA);
        printf("Raw:%ld,Filtered:%f\n", samples[i], filter_state);
    }
}