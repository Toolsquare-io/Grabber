#pragma once
#include "inputstates.h"
#include "machineinputs.h"
#include "stepper.h"
#include "speeds.h"

extern machineInputs theInput;

enum class limitwarnings: uint8_t{
  clear,
  xmin,
  xplus,
  ymin,
  yplus,
  zmin,
  zplus
};


class steppercontroller {
  public:
    steppercontroller();
    void setup();
    void run(inputStates newPosition);

  private:
    stepper M1;
    stepper M2;
    stepper MZ;
    limitwarnings thewarning;
    inputStates thePosition = inputStates::locked;

    void changeState();
    void checklimits();
    void printWarning();
   
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
