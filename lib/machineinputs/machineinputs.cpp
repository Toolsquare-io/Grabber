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

    pinMode(thePins.ZButtonPin, INPUT_PULLDOWN);
    pinMode(thePins.GrabButtonPin, INPUT_PULLDOWN);

    pinMode(thePins.GrabRelaispin, OUTPUT);
    //pinMode(thePins.GrabPWMpin, OUTPUT);
    //digitalWrite(thePins.GrabPWMpin, grablevel);
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

    if (theZButtonState != ZActive) {
        theZButtonState = ZActive;
        if (ZActive == HIGH) {
            Serial.println("Z High");
        } else {
            Serial.println("Z LOW");
        }
    }

    /*
    if (Locked == LOW) {
        nextPos = inputStates::locked;
    } else
    */

    if (XPos == LOW) {
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
                    //Grab release move to "home"
                    Serial1.println("G01 X160 Y10 Z0 F2000");
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
                Serial1.write(0x85);
                nextRunning = false;

                break;
            case inputStates::Xminus:
                strcpy(stateTxt, "x-");
                Serial1.println("$J=G91 G21 F1000 X-1000");
                break;
            case inputStates::Xplus:
                strcpy(stateTxt, "x+");
                Serial1.println("$J=G91 G21 F1000 X1000");
                break;
            case inputStates::Yminus:
                strcpy(stateTxt, "y-");
                Serial1.println("$J=G91 G21 F1000 Y-1000");
                break;
            case inputStates::Yplus:
                strcpy(stateTxt, "y+");
                Serial1.println("$J=G91 G21 F1000 Y1000");
                break;
            case inputStates::Zminus:
                strcpy(stateTxt, "z-");
                Serial1.println("$J=G91 G21 F1000 Z1000");
                break;
            case inputStates::Zplus:
                strcpy(stateTxt, "z+");
                Serial1.println("$J=G91 G21 F1000 Z-1000");
                break;

            default:
                theLog.output(subSystem::general, loggingLevel::Error, "unknown joystick state");
                break;
        }
        Serial.println(stateTxt);
        // theLog.output(subSystem::general, loggingLevel::Info, stateTxt);
        thePosition = nextPos;        // the switch!

        if (nextRunning != isRunning) {
            //    if (millis() - runningtimer >= runningdebounce) {
            //      runningtimer = millis();

            isRunning = nextRunning;

            if (isRunning) {
                //theLog.output(subSystem::input, loggingLevel::Debug, "running");
                digitalWrite(thePins.TSrunningpin, HIGH);
            } else {
                //theLog.output(subSystem::input, loggingLevel::Debug, "idle");
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
