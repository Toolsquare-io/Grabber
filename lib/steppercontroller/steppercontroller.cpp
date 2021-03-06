#include "steppercontroller.h"
#include "pinmapping.h"
#include "logging.h"
#include <Arduino.h>
#include "ledmadness.h"

extern pinmapping thePins;
extern uLog theLog;
extern ledmadness theLeds;

steppercontroller::steppercontroller() {
}

void steppercontroller::setup() {
    M1.setPins(thePins.M1_STP_PIN, thePins.M1_DIR_PIN);
    M2.setPins(thePins.M2_STP_PIN, thePins.M2_DIR_PIN);
    MZ.setPins(thePins.Z_STP_PIN, thePins.Z_DIR_PIN);
    M1.setspeed(speeds::ludicrous);
    M2.setspeed(speeds::ludicrous);
    MZ.setspeed(speeds::fast);

    pinMode(thePins.x_min_limitpin, INPUT_PULLUP);
    pinMode(thePins.x_plus_limitpin, INPUT_PULLUP);
    pinMode(thePins.y_min_limitpin, INPUT_PULLUP);
    pinMode(thePins.y_plus_limitpin, INPUT_PULLUP);
    pinMode(thePins.z_min_limitpin, INPUT_PULLUP);
    pinMode(thePins.z_plus_limitpin, INPUT_PULLUP);

    pinMode(thePins.SHIELD_EN_PIN, OUTPUT);
    digitalWrite(thePins.SHIELD_EN_PIN, LOW);

    theLog.output(subSystem::stepper, loggingLevel::Info, "stepper setup done");
}

void steppercontroller::run(inputStates newPosition) {
    checklimits();

    if (newPosition != thePosition) {
        thePosition = newPosition;
        changeState();
    }

    limitwarnings newWarning;

    switch (thePosition) {
        case inputStates::locked:
            // TODO add Toolsquare running output to low
            theLeds.run(thePosition);
            break;

        case inputStates::neutral:
            // TODO add Toolsquare running output to low
            theLeds.run(thePosition);
            break;

        case inputStates::Xminus:
            if (xminlimitState) {
                M1.run();
                M2.run();
            } else {
                newWarning = limitwarnings::xmin;
            }
            break;

        case inputStates::Xplus:
            if (xpluslimitState) {
                M1.run();
                M2.run();
            } else {
                newWarning = limitwarnings::xplus;
            }
            break;

        case inputStates::Yminus:
            if (yminlimitState) {
                M1.run();
                M2.run();
            } else {
                newWarning = limitwarnings::ymin;
            }
            break;

        case inputStates::Yplus:
            if (ypluslimitState) {
                M1.run();
                M2.run();
            } else {
                newWarning = limitwarnings::yplus;
            }
            break;

        case inputStates::Zminus:
            if (zminlimitState) {
                MZ.run();
            } else {
                newWarning = limitwarnings::zmin;
            }
            break;

        case inputStates::Zplus:
            if (zpluslimitState) {
                MZ.run();
            } else {
                newWarning = limitwarnings::zplus;
            }
            break;

        default:
            theLog.output(subSystem::stepper, loggingLevel::Error, "unknown input state");
            break;
    }
    if (thewarning != newWarning) {
        thewarning = newWarning;
        printWarning();
    }
}

void steppercontroller::checklimits() {
    byte new_xminlimit  = digitalRead(thePins.x_min_limitpin);
    byte new_xpluslimit = digitalRead(thePins.x_plus_limitpin);
    byte new_yminlimit  = digitalRead(thePins.y_min_limitpin);
    byte new_ypluslimit = digitalRead(thePins.y_plus_limitpin);
    byte new_zminlimit  = digitalRead(thePins.z_min_limitpin);
    byte new_zpluslimit = digitalRead(thePins.z_plus_limitpin);

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
        if (xpluslimitState) {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "xplus limitstate is HIGH");
        } else {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "xplus limitstate is LOW");
        }
    }
    if (new_yminlimit != yminlimitState) {
        yminlimitState = new_yminlimit;
        if (yminlimitState) {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "ymin limitstate is HIGH");
        } else {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "ymin limitstate is LOW");
        }
    }
    if (new_ypluslimit != ypluslimitState) {
        ypluslimitState = new_ypluslimit;
        if (ypluslimitState) {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "yplus limitstate is HIGH");
        } else {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "yplus limitstate is LOW");
        }
    }
    if (new_zminlimit != zminlimitState) {
        zminlimitState = new_zminlimit;
        if (zminlimitState) {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "zmin limitstate is HIGH");
        } else {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "zmin limitstate is LOW");
        }
    }
    if (new_zpluslimit != zpluslimitState) {
        zpluslimitState = new_zpluslimit;
        if (zpluslimitState) {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "zplus limitstate is HIGH");
        } else {
            theLog.output(subSystem::stepper, loggingLevel::Warning, "zplus limitstate is LOW");
        }
    }
}

void steppercontroller::printWarning() {
    switch (thewarning) {
        case limitwarnings::xmin:
            theLog.output(subSystem::stepper, loggingLevel::Warning, "can't move in xmin");
            break;
        case limitwarnings::xplus:
            theLog.output(subSystem::stepper, loggingLevel::Warning, "can't move in xplus");
            break;
        case limitwarnings::ymin:
            theLog.output(subSystem::stepper, loggingLevel::Warning, "can't move in ymin");
            break;
        case limitwarnings::yplus:
            theLog.output(subSystem::stepper, loggingLevel::Warning, "can't move in yplus");
            break;
        case limitwarnings::zmin:
            theLog.output(subSystem::stepper, loggingLevel::Warning, "can't move in zmin");
            break;
        case limitwarnings::zplus:
            theLog.output(subSystem::stepper, loggingLevel::Warning, "can't move in zplus");
            break;

        default:
            theLog.output(subSystem::stepper, loggingLevel::Error, "unknown stepperwarining");
            break;
    }
}

void steppercontroller::changeState() {
    switch (thePosition) {
        case inputStates::Xminus:
            M1.setDir(direction::clockwise);
            M2.setDir(direction::clockwise);
            break;

        case inputStates::Xplus:
            M1.setDir(direction::counterclockwise);
            M2.setDir(direction::counterclockwise);
            break;

        case inputStates::Yminus:
            M1.setDir(direction::counterclockwise);
            M2.setDir(direction::clockwise);
            break;

        case inputStates::Yplus:
            M1.setDir(direction::clockwise);
            M2.setDir(direction::counterclockwise);
            break;

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
