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
    bool isRunning;
    inputStates thePosition = inputStates::neutral;
    bool theGrabState       = false;
    int theZButtonState     = LOW;
    void setButtonLeds();
    void buttonBreathe();
    unsigned long ledpace  = 50;
    unsigned long ledtimer = 0;
    uint8_t ledlevel       = 100;
    int ledlevelincrement  = 1;
    void grabcontroll();
    uint8_t grablevel             = 120;
    unsigned long runningdebounce = 500;
    unsigned long runningtimer    = 0;
    unsigned long goHomeTimer = 0;
    unsigned long goHomeTimeout = 5000;
    bool isHome = false;
};
