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
    bool isRunning();

  private:
    int pulsestate;
    int pulsePin;
    int dirPin;
    long delta;
    direction theDirection;
    void step();
    unsigned long stepperInterval = 1;
    unsigned long stepperTimer    = 0;

    unsigned long accelTimer     = 0;
    unsigned long accelInterval  = 5;
    unsigned long theSpeed       = 0;         // RPM
    unsigned long speedTarget    = 0;         // RPM
    unsigned long speedIncrement = 1;         // RPMM
    unsigned long topspeed       = 50;        // RPM
};
