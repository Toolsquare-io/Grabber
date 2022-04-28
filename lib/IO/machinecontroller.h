#pragma once
#include "CNCShield.h"

#define NO_OF_STEPS 200
#define SLEEP_BETWEEN_STEPS_MS 1
#define SPEED_STEPS_PER_SECOND 1000

class machinecontroller {
  public:
    void initialize();
    void run();

  private:
    /*
     * Create a CNCShield object and get a pointer to motor 0 (X axis).
     */
    CNCShield cnc_shield;
    StepperMotor *motor1;
};
