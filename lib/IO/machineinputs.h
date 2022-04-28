#pragma once
#include <Arduino.h>
#include "joystickpos.h"
#include "grabberpinmapping.h"

class machineInputs {
  public:
    void initialize();
    void run();
    joystickPositions getPosition();
    bool grabState();

  private:
    joystickPositions thePosition = joystickPositions::neutral;
    bool theGrabState             = false;
};
