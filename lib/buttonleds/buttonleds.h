#pragma once
#include <Arduino.h>
#include "inputstates.h"

class buttonleds {
  public:
    buttonleds(/* args */);
    void setup();
    void setButtonLeds(inputStates theState, bool theGrabState);

  private:
    void buttonBreathe();
    unsigned long ledpace  = 50;
    unsigned long ledtimer = 0;
    uint8_t ledlevel       = 100;
    int ledlevelincrement  = 1;
};
