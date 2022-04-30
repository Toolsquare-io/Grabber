#include "steppercontroller.h"
#include "pinmapping.h"
#include "logging.h"
#include <Arduino.h>

extern pinmapping thePins;
extern uLog theLog;

steppercontroller::steppercontroller() {
   
}

void steppercontroller::setup(){
 pinMode(thePins.M1_DIR_PIN, OUTPUT);
    pinMode(thePins.M1_STP_PIN, OUTPUT);
    pinMode(thePins.M1_DIR_PIN, OUTPUT);
    pinMode(thePins.M2_STP_PIN, OUTPUT);
    pinMode(thePins.M2_DIR_PIN, OUTPUT);
    pinMode(thePins.Z_STP_PIN, OUTPUT);
    pinMode(thePins.Z_DIR_PIN, OUTPUT);
    pinMode(thePins.SHIELD_EN_PIN, OUTPUT);
    digitalWrite(thePins.SHIELD_EN_PIN, LOW);
    theLog.output(subSystem::general,loggingLevel::Info,"Stepper setup done");
}

void steppercontroller::run(joystickPositions newPosition) {
    if (newPosition != thePosition) {
        thePosition = newPosition;
        changeState();
    }

    if (millis() - stepperTimer >= stepperInterval) {
        stepperTimer = millis();

        switch (thePosition) {
            case joystickPositions::locked:
            break;
            case joystickPositions::Xminus:
            case joystickPositions::Xplus:
            case joystickPositions::Yminus:
            case joystickPositions::Yplus:
                coreStep();
                break;
            case joystickPositions::Zminus:
            case joystickPositions::Zplus:
               zStep();
                break;
            default:
                break;
        }
    }
}

void steppercontroller::coreStep() {
    //theLog.output(subSystem::general,loggingLevel::Debug,"core step");
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
        case joystickPositions::Xminus:
            digitalWrite(thePins.M1_DIR_PIN, HIGH);
            digitalWrite(thePins.M2_DIR_PIN, LOW);
            break;

        case joystickPositions::Xplus:
            digitalWrite(thePins.M1_DIR_PIN, LOW);
            digitalWrite(thePins.M2_DIR_PIN, HIGH);

        case joystickPositions::Yminus:
            digitalWrite(thePins.M1_DIR_PIN, HIGH);
            digitalWrite(thePins.M2_DIR_PIN, HIGH);
            break;

        case joystickPositions::Yplus:
            digitalWrite(thePins.M1_DIR_PIN, LOW);
            digitalWrite(thePins.M2_DIR_PIN, LOW);

        case joystickPositions::Zminus:
            digitalWrite(thePins.Z_DIR_PIN, HIGH);
            break;

        case joystickPositions::Zplus:
            digitalWrite(thePins.Z_DIR_PIN, LOW);

        default:
            theLog.output(subSystem::general, loggingLevel::Debug, "no direction change");
            break;
    }
}
