#pragma once
#include <stdint.h>

//use this file to overwrite the subsystems in the loggin library .pio -> lipdeps -> logging -> src -> subsystems.h

enum class subSystem : uint8_t {
    general,
    input,
    stepper,
    neopixels,
    nmbrOfSubsystems
};