#include "machineinputs.h"
#include "joystickpos.h"
#include "pinmapping.h"
#include "logging.h"

extern uLog theLog;
extern pinmapping thePins;

void machineInputs::initialize() {
    pinMode(thePins.JoyStickXNegPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickXPosPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickYNegPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickYPosPin, INPUT_PULLUP);
    pinMode(thePins.ZButtonPin, INPUT_PULLUP);
    pinMode(thePins.LockPin, INPUT_PULLUP);
    pinMode(thePins.GrabButtonPin, INPUT_PULLUP);
};

void machineInputs::run() {
    int XPos    = digitalRead(thePins.JoyStickXPosPin);
    int XNeg    = digitalRead(thePins.JoyStickXNegPin);
    int YPos    = digitalRead(thePins.JoyStickYPosPin);
    int YNeg    = digitalRead(thePins.JoyStickYNegPin);
    int ZActive = digitalRead(thePins.ZButtonPin);
    int Locked  = digitalRead(thePins.LockPin);
    int Grab    = digitalRead(thePins.GrabButtonPin);

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
    int Grabbuttonstate = digitalRead(thePins.GrabButtonPin);
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