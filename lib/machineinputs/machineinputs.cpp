#include "machineinputs.h"
#include "pinmapping.h"
#include "logging.h"
#include "stdio.h"

extern uLog theLog;
extern pinmapping thePins;

void machineInputs::initialize() {
    pinMode(thePins.JoyStickXNegPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickXPosPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickYNegPin, INPUT_PULLUP);
    pinMode(thePins.JoyStickYPosPin, INPUT_PULLUP);
    pinMode(thePins.TSlockpin, INPUT_PULLUP);
    pinMode(thePins.TSrunningpin, OUTPUT);

    pinMode(thePins.ZButtonPin, INPUT_PULLUP);
    pinMode(thePins.GrabButtonPin, INPUT_PULLUP);

    digitalWrite(thePins.GrabButtonLEDpin, HIGH);
    digitalWrite(thePins.ZButtonLEDpin, HIGH);

    pinMode(thePins.GrabButtonLEDpin, OUTPUT);
    pinMode(thePins.GrabRelaispin, OUTPUT);
    pinMode(thePins.ZButtonLEDpin, OUTPUT);
    pinMode(thePins.GrabPWMpin, OUTPUT);
    digitalWrite(thePins.GrabPWMpin, grablevel);
};

void machineInputs::run() {
    int XPos    = digitalRead(thePins.JoyStickXPosPin);
    int XNeg    = digitalRead(thePins.JoyStickXNegPin);
    int YPos    = digitalRead(thePins.JoyStickYPosPin);
    int YNeg    = digitalRead(thePins.JoyStickYNegPin);
    int ZActive = digitalRead(thePins.ZButtonPin);
    int Locked  = digitalRead(thePins.TSlockpin);
    int Grab    = digitalRead(thePins.GrabButtonPin);

    inputStates nextPos = inputStates::neutral;

    if (Locked == HIGH) {
        nextPos = inputStates::locked;
    } else if (XPos == LOW) {
        nextPos = inputStates::Xplus;
    } else if (XNeg == LOW) {
        nextPos = inputStates::Xminus;
    } else if (YPos == LOW) {
        if (ZActive == HIGH) {
            nextPos = inputStates::Zplus;
        } else {
            nextPos = inputStates::Yplus;
        }
    } else if (YNeg == LOW) {
        if (ZActive == HIGH) {
            nextPos = inputStates::Zminus;
        } else {
            nextPos = inputStates::Yminus;
        }
    }

    // the grab button
    bool nextGrabState = false;

    if (Grab == LOW) {
        nextGrabState = true;
        // Serial.print("grab is true");
    } else {
        // Serial.println("grab is false");
    }

    if (nextGrabState != theGrabState) {
        theGrabState = nextGrabState;

        switch (thePosition) {
            case inputStates::locked:
                digitalWrite(thePins.GrabRelaispin, LOW);
                theLog.output(subSystem::input, loggingLevel::Info, "no grab, machine is locked");
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
    bool nextRunning = true;

    if (nextPos != thePosition) {
        char stateTxt[8];
        switch (nextPos) {
            case inputStates::locked:
                strcpy(stateTxt, "locked");
                nextRunning = false;
                break;
            case inputStates::neutral:
                strcpy(stateTxt, "neutral");
                nextRunning = false;

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

        if (nextRunning != isRunning) {
            //    if (millis() - runningtimer >= runningdebounce) {
            //      runningtimer = millis();

            isRunning = nextRunning;

            if (isRunning) {
                theLog.output(subSystem::input, loggingLevel::Debug, "running");
                digitalWrite(thePins.TSrunningpin, HIGH);
            } else {
                theLog.output(subSystem::input, loggingLevel::Debug, "idle");
                digitalWrite(thePins.TSrunningpin, LOW);
            }
            //}
        }
    }
};

inputStates machineInputs::getPosition() {
    return thePosition;
};

bool machineInputs::grabState() {
    return theGrabState;
};

void machineInputs::setButtonLeds() {
    // doesn't work because of the 3pin buttons....
    /*
    bool grabled = false;
    switch (thePosition) {
        case inputStates::locked:
        case inputStates::neutral:
            buttonBreathe();
            break;

        case inputStates::Xminus:
        case inputStates::Xplus:
            digitalWrite(thePins.ZButtonLEDpin, LOW);
            grabled = true;
            break;

        case inputStates::Yminus:
        case inputStates::Yplus:
        case inputStates::Zminus:
        case inputStates::Zplus:
            digitalWrite(thePins.ZButtonLEDpin, HIGH);
            grabled = true;
            break;

        default:
            theLog.output(subSystem::input, loggingLevel::Error, "unknown buttonledstate");
            break;
    }
    if (grabled) {
        if (theGrabState) {
            digitalWrite(thePins.GrabButtonLEDpin, LOW);
        } else {
            digitalWrite(thePins.GrabButtonLEDpin, HIGH);
        }
    }
    */
}

void machineInputs::buttonBreathe() {
    if (millis() - ledtimer >= ledpace) {
        analogWrite(thePins.ZButtonLEDpin, ledlevel);
        analogWrite(thePins.GrabButtonLEDpin, 255 - ledlevel);

        if (ledlevel >= 255 || ledlevel <= 0) {
            ledlevelincrement = -ledlevelincrement;
        }
        ledlevel += ledlevelincrement;
    }
}