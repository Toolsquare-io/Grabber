#include "pinmapping.h"
#include "machineinputs.h"
#include "logging.h"
#include "buttonleds.h"

extern uLog theLog;
extern pinmapping thePins;
extern buttonleds theButtonLeds;

void machineInputs::initialize() {
    pinMode(thePins.JoyStickXNegPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickXPosPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickYNegPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickYPosPin, INPUT_PULLUP);
    pinMode(thePins.ZButtonPin, INPUT_PULLUP);
    pinMode(thePins.TSlockpin, INPUT_PULLUP);
    pinMode(thePins.GrabButtonPin, INPUT_PULLUP);

    pinMode(thePins.GrabPWMpin, OUTPUT);
    digitalWrite(thePins.GrabPWMpin, grablevel);
}

void machineInputs::run() {
    int XPos    = digitalRead(thePins.JoyStickXPosPin);
    int XNeg    = digitalRead(thePins.JoyStickXNegPin);
    int YPos    = digitalRead(thePins.JoyStickYPosPin);
    int YNeg    = digitalRead(thePins.JoyStickYNegPin);
    int ZActive = digitalRead(thePins.ZButtonPin);
    int Locked  = digitalRead(thePins.TSlockpin);
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
    bool nextGrabState = false;
    if (Grab == LOW) {
        nextGrabState = true;
    } else {
        nextGrabState = false;
    }

    if (nextGrabState != theGrabState) {
        theGrabState = nextGrabState;

        switch (thePosition) {
            case inputStates::locked:
                digitalWrite(thePins.GrabRelaispin, LOW);
                break;

            default:
                if (theGrabState) {
                    digitalWrite(thePins.GrabRelaispin, HIGH);
                    theLog.output(subSystem::input, loggingLevel::Info, "grab on");
                } else {
                    digitalWrite(thePins.GrabRelaispin, LOW);
                    theLog.output(subSystem::input, loggingLevel::Info, "grab off");
                }
                break;
        }
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

        theButtonLeds.setButtonLeds(thePosition, theGrabState);
    }
}

inputStates machineInputs::getPosition() {
    return thePosition;
}

bool machineInputs::grabState() {
    return theGrabState;
}
