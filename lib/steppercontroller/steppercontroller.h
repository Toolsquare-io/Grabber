#pragma once
#include "inputstates.h"
#include "machineinputs.h"

extern machineInputs theInput;

class steppercontroller {
  public:
    steppercontroller();
    void setup();
    void run(inputStates newPosition);

  private:
    void changeState();
    void checklimits();
    inputStates thePosition = inputStates::locked;
    void coreStep();
    void zStep();
    unsigned long stepperInterval = 1;
    unsigned long stepperTimer;

    byte xpluslimitState;
    byte xminlimitState;
    byte ypluslimitState;
    byte yminlimitState;
    byte zpluslimitState;
    byte zminlimitState;
};
