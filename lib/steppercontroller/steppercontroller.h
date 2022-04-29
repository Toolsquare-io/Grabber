#pragma once
#include "joystickpos.h"
#include "machineinputs.h"

extern machineInputs theInput;

class steppercontroller {
  public:
    steppercontroller();
    void setup();
    void run(joystickPositions newPosition);

  private:
    void changeState();
    joystickPositions thePosition = joystickPositions::locked;
    void coreStep();
    void zStep();
    unsigned long stepperInterval = 100;
    unsigned long stepperTimer    = 0;
};
