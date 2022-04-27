#pragma once
#include <Arduino.h>
#include "joystickpos.h"


class machineInputs {
  public:
  void initialize();
  void run();
  joystickPositions getPosition();

  private:
  joystickPositions thePosition;
};
