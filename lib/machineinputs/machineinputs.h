#pragma once
#include <Arduino.h>
#include "inputstates.h"

class machineInputs {
  public:
    void initialize();
    void run();
    inputStates getPosition();
    bool grabState();

  private:
    inputStates thePosition = inputStates::neutral;
    bool theGrabState       = false;
    void setButtonLeds();
    void buttonBreathe();
    unsigned long ledpace  = 50;
    unsigned long ledtimer = 0;
    uint8_t ledlevel       = 100;
    int ledlevelincrement = 1;
    void grabcontroll();
    uint8_t grablevel = 120;
};
