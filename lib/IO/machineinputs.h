#pragma once
#include <Arduino.h>
#include "joystickpos.h"
#include "grabberpinmapping.h"

class machineInputs {
  public:
  void initialize();
  void run();
  joystickPositions getPosition();

  private:
  joystickPositions thePosition=joystickPositions::neutral;
};
