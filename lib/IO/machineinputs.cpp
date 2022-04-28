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
    pinMode(LockPin, INPUT_PULLUP);
    pinMode(GrabButtonPin, INPUT_PULLUP);
};

void machineInputs::run() {
    int XPos    = digitalRead(JoyStickXPosPin);
    int XNeg    = digitalRead(JoyStickXNegPin);
    int YPos    = digitalRead(JoyStickYPosPin);
    int YNeg    = digitalRead(JoyStickYNegPin);
    int ZActive = digitalRead(ZButtonPin);
    int Locked  = digitalRead(LockPin);
    int Grab    = digitalRead(GrabButtonPin);

    joystickPositions nextPos = joystickPositions::neutral;

    if (Locked == LOW) {
        nextPos = joystickPositions::locked;
    } else if (XPos == LOW) {
        nextPos = joystickPositions::Xplus;
    } else if (XNeg == LOW) {
        nextPos = joystickPositions::Xminus;
    } else if (YPos == LOW) {
        if (ZActive == LOW) {
            nextPos = joystickPositions::Zplus;
        } else {
            nextPos = joystickPositions::Yplus;
        }
    } else if (YNeg == LOW) {
        if (ZActive == LOW) {
            nextPos = joystickPositions::Zminus;
        } else {
            nextPos = joystickPositions::Yminus;
        }
    }

    // the grab button
    int Grabbuttonstate = digitalRead(GrabButtonPin);
    bool nextGrabState  = false;
    if (Grabbuttonstate == LOW) {
        nextGrabState = true;
    } else {
        nextGrabState = false;
    }

    // output
    if (nextPos != thePosition) {
        char stateTxt[8];
        switch (nextPos) {
            case joystickPositions::locked:
                strcpy(stateTxt, "locked");
                break;
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
            case joystickPositions::Yplus:
                strcpy(stateTxt, "y+");
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
        thePosition = nextPos;        // the switch!
    }

    if (nextGrabState != theGrabState) {
        if (nextGrabState == true) {
            theLog.output(subSystem::general, loggingLevel::Info, "grab activated");
        } else {
            theLog.output(subSystem::general, loggingLevel::Info, "grab released");
        }
        theGrabState = nextGrabState;
    }
};

joystickPositions machineInputs::getPosition() {
    return thePosition;
};

bool machineInputs::grabState() {
    return theGrabState;
};