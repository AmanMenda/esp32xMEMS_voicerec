#ifndef VR_UTILS_H
#define VR_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include "vr_config.h"

/**
* @brief Apply a simple first-order low-pass filter to an audio sample
* 
* Implements the difference equation: y(n) = α·x(n) + (1-α)·y(n-1)
* where α (alpha) controls the filter cutoff frequency.
* 
* @param x Current input sample (raw audio data)
* @param y Previous filtered output value y(n-1)
* @param alpha Filter coefficient (0.0 to 1.0)
*                  - 0.0: Maximum filtering (very smooth, slow response)
*                  - 1.0: No filtering (passes input unchanged)
*                  - Typical values: 0.1-0.3 for audio applications
* 
* @return Filtered output sample as 32-bit signed integer
*/
int32_t low_pass_filter(int32_t x, float y, float alpha);

/**
* @brief Send audio sample data to serial plotter for real-time visualization
* 
* Processes and transmits audio samples in a format compatible with 
* Arduino Serial Plotter and similar visualization tools. Applies
* low-pass filtering and decimation to reduce data rate.
* 
* @param samples   Pointer to array of raw audio samples from I2S
* @param count     Number of samples in the array
* 
*/
void send_plotter_data(int32_t* samples, size_t count);

#endif