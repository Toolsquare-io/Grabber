#pragma once
#include "inputstates.h"
#include "machineinputs.h"
#include "stepper.h"

extern machineInputs theInput;

class steppercontroller {
  public:
    steppercontroller();
    void setup();
    void run(inputStates newPosition);

  private:
    stepper M1;
    stepper M2;
    stepper MZ;

    void changeState();
    void checklimits();
    inputStates thePosition = inputStates::locked;
   
    unsigned long stepperInterval = 1;
    unsigned long stepperTimer;

    long deltaM1;
    long deltaM2;
    long deltaX;
    long deltaY;
    long deltaZ;

    byte xpluslimitState;
    byte xminlimitState;
    byte ypluslimitState;
    byte yminlimitState;
    byte zpluslimitState;
    byte zminlimitState;
};
