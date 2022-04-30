#include "machineinputs.h"
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

    inputStates nextPos = inputStates::neutral;

    if (Locked == LOW) {
        nextPos = inputStates::locked;
    } else if (XPos == LOW) {
        nextPos = inputStates::Xplus;
    } else if (XNeg == LOW) {
        nextPos = inputStates::Xminus;
    } else if (YPos == LOW) {
        if (ZActive == LOW) {
            nextPos = inputStates::Zplus;
        } else {
            nextPos = inputStates::Yplus;
        }
    } else if (YNeg == LOW) {
        if (ZActive == LOW) {
            nextPos = inputStates::Zminus;
        } else {
            nextPos = inputStates::Yminus;
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
            case inputStates::locked:
                strcpy(stateTxt, "locked");
                break;
            case inputStates::neutral:
                strcpy(stateTxt, "neutral");
                break;
            case inputStates::Xminus:
                strcpy(stateTxt, "x-");
                break;
            case inputStates::Xplus:
                strcpy(stateTxt, "x+");
                break;
            case inputStates::Yminus:
                strcpy(stateTxt, "y-");
                break;
            case inputStates::Yplus:
                strcpy(stateTxt, "y+");
                break;
            case inputStates::Zminus:
                strcpy(stateTxt, "z-");
                break;
            case inputStates::Zplus:
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

inputStates machineInputs::getPosition() {
    return thePosition;
};

bool machineInputs::grabState() {
    return theGrabState;
};