#include "vr_utils.h"

// follows the formula: y(n) = alpha*x(n) + (1 - a)*y(n-1)
int32_t low_pass_filter(int32_t x, float y, float alpha)
{ 
    return (alpha * x) + (1 - alpha) * (y);
}