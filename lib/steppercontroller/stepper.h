#pragma once
#include "speeds.h"

enum class direction {
    clockwise,
    counterclockwise
};

class stepper {
  public:
    stepper();
    void setPins(int pPin, int dPin);
    void setDir(direction dir);
    void setspeed(speeds speed);
    void run();

  private:
    int pulsestate;
    int pulsePin;
    int dirPin;
    long delta;
    direction theDirection;
    void step();
    unsigned long stepperInterval = 1;
    unsigned long stepperTimer    = 0;
};
