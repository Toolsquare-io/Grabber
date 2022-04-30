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
    bool theGrabState             = false;
};
