
#include "buttonleds.h"
#include "pinmapping.h"
#include "logging.h"

extern uLog theLog;
extern pinmapping thePins;


void buttonleds::setButtonLeds() {
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