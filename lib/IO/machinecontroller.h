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
    void moveX(int dir);
    void moveY(int dir);
    void moveZ(int dir);
    void stop();
    void grab();
    CNCShield cnc_shield;
    StepperMotor *motor1;
    StepperMotor *motor2;
    StepperMotor *motorZ;
};
