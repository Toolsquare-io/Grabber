#include "steppercontroller.h"
#include "pinmapping.h"
#include "logging.h"
#include <Arduino.h>

extern pinmapping thePins;
extern uLog theLog;

steppercontroller::steppercontroller() {
}

void steppercontroller::setup() {
    M1.setPins(thePins.M1_STP_PIN, thePins.M1_DIR_PIN);
    M2.setPins(thePins.M2_STP_PIN, thePins.M2_DIR_PIN);
    MZ.setPins(thePins.Z_STP_PIN, thePins.Z_DIR_PIN);

    digitalWrite(thePins.SHIELD_EN_PIN, LOW);

    pinMode(thePins.x_min_limitpin, INPUT_PULLUP);
    pinMode(thePins.x_plus_limitpin, INPUT_PULLUP);
    pinMode(thePins.y_min_limitpin, INPUT_PULLUP);
    pinMode(thePins.x_plus_limitpin, INPUT_PULLUP);

    theLog.output(subSystem::stepper, loggingLevel::Info, "Stepper setup done");
}

void steppercontroller::run(inputStates newPosition) {
    checklimits();

    if (newPosition != thePosition) {
        thePosition = newPosition;
        changeState();
    }

    if (millis() - stepperTimer >= stepperInterval) {
        stepperTimer = millis();

        switch (thePosition) {
            case inputStates::locked:
                break;
            case inputStates::Xminus:
                if (xminlimitState) {
                    M1.step();
                    M2.step();
                }
                break;

            case inputStates::Xplus:
                if (xpluslimitState) {
                    M1.step();
                    M2.step();
                }
                break;

            case inputStates::Yminus:
                if (yminlimitState) {
                    M1.step();
                    M2.step();
                }
                break;

            case inputStates::Yplus:
                if (ypluslimitState) {
                    M1.step();
                    M2.step();
                }
                break;

            case inputStates::Zminus:        // TODO add z limits
            case inputStates::Zplus:
                MZ.step();
                break;
            default:
                break;
        }
    }
}

void steppercontroller::checklimits() {
    byte new_xminlimit  = digitalRead(thePins.x_min_limitpin);
    byte new_xpluslimit = digitalRead(thePins.x_plus_limitpin);
    byte new_yminlimit  = digitalRead(thePins.y_min_limitpin);
    byte new_ypluslimit = digitalRead(thePins.y_plus_limitpin);

    if (new_xminlimit != xminlimitState) {
        xminlimitState = new_xminlimit;
        if (xminlimitState) {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "xmin limitstate is HIGH");
        } else {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "xmin limitstate is LOW");
        }
    }
    if (new_xpluslimit != xpluslimitState) {
        xpluslimitState = new_xpluslimit;
        theLog.snprintf(subSystem::stepper, loggingLevel::Warning, "xplus limitstate %c ", xpluslimitState);
    }

    if (new_yminlimit != yminlimitState) {
        yminlimitState = new_yminlimit;
        theLog.output(subSystem::stepper, loggingLevel::Warning, "ymin limitstate");
    }
    if (new_ypluslimit != ypluslimitState) {
        ypluslimitState = new_ypluslimit;
        theLog.output(subSystem::stepper, loggingLevel::Warning, "yplus limitstate");
    }

    // TODO add z limits
}

void steppercontroller::changeState() {
    switch (thePosition) {
        case inputStates::Xminus:
            M1.setDir(direction::clockwise);
            M2.setDir(direction::counterclockwise);
            break;

        case inputStates::Xplus:
            M1.setDir(direction::counterclockwise);
            M2.setDir(direction::clockwise);

        case inputStates::Yminus:
            M1.setDir(direction::clockwise);
            M2.setDir(direction::clockwise);
            break;

        case inputStates::Yplus:
            M1.setDir(direction::counterclockwise);
            M2.setDir(direction::counterclockwise);

        case inputStates::Zminus:
            MZ.setDir(direction::clockwise);
            break;

        case inputStates::Zplus:
            MZ.setDir(direction::counterclockwise);
            break;

        default:
            theLog.output(subSystem::stepper, loggingLevel::Debug, "no direction change");
            break;
    }
}
