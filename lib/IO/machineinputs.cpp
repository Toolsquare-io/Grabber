#include "machineinputs.h"
#include "joystickpos.h"
#include "logging.h"

extern uLog theLog;

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

    joystickPositions nextPos;

    if (XPos) {
        nextPos = joystickPositions::Xplus;
    } else if (XNeg) {
        nextPos = joystickPositions::Xminus;
    } else if (YPos) {
        if (ZActive) {
            nextPos = joystickPositions::Zplus;
        } else {
            nextPos = joystickPositions::Yplus;
        }

    } else if (YNeg) {
        if (ZActive) {
            nextPos = joystickPositions::Zminus;
        } else {
            nextPos = joystickPositions::Yminus;
        }
    } else {
        nextPos = joystickPositions::neutral;
    }

    if (nextPos != thePosition) {
        char stateTxt[8];
        switch (nextPos) {
            case joystickPositions::neutral:
                strcpy(stateTxt, "neutral");
                break;
            case joystickPositions::Xminus:
                strcpy(stateTxt, "x-");
                break;
            case joystickPositions::Xplus:
                strcpy(stateTxt, "x+");
                break;
            case joystickPositions::Yminus:
                strcpy(stateTxt, "y-");
                break;
            case joystickPositions::Zminus:
                strcpy(stateTxt, "z-");
                break;
            case joystickPositions::Zplus:
                strcpy(stateTxt, "z+");
                break;

            default:
            theLog.output(subSystem::general, loggingLevel::Error, "unknown joystick state");
                break;
        }
        theLog.output(subSystem::general, loggingLevel::Info, stateTxt);
    }
};

joystickPositions machineInputs::getPosition() {
    return thePosition;
};