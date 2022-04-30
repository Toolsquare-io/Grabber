#pragma once
#include <stdint.h>

enum class subSystem : uint8_t {
    general,
    input,
    stepper,
    neopixels,
};