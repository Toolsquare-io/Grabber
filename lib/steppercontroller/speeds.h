#pragma once
#include <Arduino.h>

enum class speeds : uint8_t {
    veryslow,
    slow,
    normal,
    fast,
    veryfast,
    ludicrous
};