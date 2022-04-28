#include "machineinputs.h"
#include "joystickpos.h"

void machineInputs::initialize() {
    pinMode(JoyStickXNegPin, INPUT_PULLUP);
    pinMode(JoyStickXPosPin, INPUT_PULLUP);
    pinMode(JoyStickYNegPin, INPUT_PULLUP);
    pinMode(JoyStickYPosPin, INPUT_PULLUP);
    pinMode(ZButtonPin, INPUT_PULLUP);
};

void machineInputs::run() {
    int XPos    = digitalRead(JoyStickXPosPin);
    int XNeg    = digitalRead(JoyStickXNegPin);
    int YPos    = digitalRead(JoyStickYPosPin);
    int YNeg    = digitalRead(JoyStickYNegPin);
    int ZActive = digitalRead(ZButtonPin);

    if (XPos) {
        thePosition = joystickPositions::Xplus;
    } else if (XNeg) {
        thePosition = joystickPositions::Xminus;
    } else if (YPos) {
        if (ZActive) {
            thePosition = joystickPositions::Zplus;
        } else {
            thePosition = joystickPositions::Yplus;
        }

    } else if (YNeg) {
        if (ZActive) {
            thePosition = joystickPositions::Zminus;
        } else {
            thePosition = joystickPositions::Yminus;
        }
    }
};

joystickPositions machineInputs::getPosition() {
    return thePosition;
};