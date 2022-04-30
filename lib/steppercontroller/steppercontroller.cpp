#include "steppercontroller.h"
#include "pinmapping.h"
#include "logging.h"
#include <Arduino.h>

extern pinmapping thePins;
extern uLog theLog;

steppercontroller::steppercontroller() {
}

void steppercontroller::setup() {
    pinMode(thePins.M1_DIR_PIN, OUTPUT);
    pinMode(thePins.M1_STP_PIN, OUTPUT);
    pinMode(thePins.M1_DIR_PIN, OUTPUT);
    pinMode(thePins.M2_STP_PIN, OUTPUT);
    pinMode(thePins.M2_DIR_PIN, OUTPUT);
    pinMode(thePins.Z_STP_PIN, OUTPUT);
    pinMode(thePins.Z_DIR_PIN, OUTPUT);
    pinMode(thePins.SHIELD_EN_PIN, OUTPUT);
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
                    coreStep();
                }
                break;

            case inputStates::Xplus:
                if (xpluslimitState) {
                    coreStep();
                }
                break;

            case inputStates::Yminus:
                if (yminlimitState) {
                    coreStep();
                }
                break;

            case inputStates::Yplus:
                if (ypluslimitState) {
                    coreStep();
                }
                break;

            case inputStates::Zminus:        // TODO add z limits
            case inputStates::Zplus:
                zStep();
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

void steppercontroller::coreStep() {
    // theLog.output(subSystem::general,loggingLevel::Debug,"core step");
    digitalWrite(thePins.M1_STP_PIN, HIGH);
    digitalWrite(thePins.M2_STP_PIN, HIGH);
    delay(1);
    digitalWrite(thePins.M1_STP_PIN, LOW);
    digitalWrite(thePins.M2_STP_PIN, LOW);
}

void steppercontroller::zStep() {
    digitalWrite(thePins.Z_STP_PIN, HIGH);
    digitalWrite(thePins.Z_STP_PIN, LOW);
}

void steppercontroller::changeState() {
    switch (thePosition) {
        case inputStates::Xminus:
            digitalWrite(thePins.M1_DIR_PIN, HIGH);
            digitalWrite(thePins.M2_DIR_PIN, LOW);
            break;

        case inputStates::Xplus:
            digitalWrite(thePins.M1_DIR_PIN, LOW);
            digitalWrite(thePins.M2_DIR_PIN, HIGH);

        case inputStates::Yminus:
            digitalWrite(thePins.M1_DIR_PIN, HIGH);
            digitalWrite(thePins.M2_DIR_PIN, HIGH);
            break;

        case inputStates::Yplus:
            digitalWrite(thePins.M1_DIR_PIN, LOW);
            digitalWrite(thePins.M2_DIR_PIN, LOW);

        case inputStates::Zminus:
            digitalWrite(thePins.Z_DIR_PIN, HIGH);
            break;

        case inputStates::Zplus:
            digitalWrite(thePins.Z_DIR_PIN, LOW);
            break;

        default:
            theLog.output(subSystem::stepper, loggingLevel::Debug, "no direction change");
            break;
    }
}
