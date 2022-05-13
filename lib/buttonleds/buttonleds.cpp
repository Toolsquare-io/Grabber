
#include "buttonleds.h"
#include "pinmapping.h"
#include "logging.h"

extern uLog theLog;
extern pinmapping thePins;

buttonleds::buttonleds(){

}

void buttonleds::setup() {
    pinMode(thePins.GrabButtonLEDpin, OUTPUT);
    pinMode(thePins.ZButtonLEDpin, OUTPUT);
}

void buttonleds::setButtonLeds(inputStates theState, bool theGrabState) {
    bool grabled = false;
    switch (theState) {
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
}

void buttonleds::buttonBreathe() {
    if (millis() - ledtimer >= ledpace) {
        analogWrite(thePins.ZButtonLEDpin, ledlevel);
        analogWrite(thePins.GrabButtonLEDpin, 255 - ledlevel);

        if (ledlevel >= 255 || ledlevel <= 0) {
            ledlevelincrement = -ledlevelincrement;
        }
        ledlevel += ledlevelincrement;
    }
}