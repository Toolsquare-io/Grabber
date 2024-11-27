#include <Arduino.h>
#include "logging.h"
#include "machineinputs.h"
#include "pinmapping.h"
#include "ledmadness.h"
#include "inputstates.h"

// creating the objects
uLog theLog;
machineInputs theInput;
pinmapping thePins;
ledmadness theLeds;

// forward declarations
// void echoSerial();
bool outputToSerial(const char* contents);
bool loggingTime(char* contents, uint32_t length);
void printHeartBeat();

void setup() {
    // configure output
    theLog.setColoredOutput(0U, true);        // enable colored output - remember to set 'monitor_flags = --raw' in platformio.ini    theLog.output(subSystem::general, loggingLevel::Error, "This is an error");           //
    Serial.begin(112500);
    Serial1.begin(115200);
    Serial1.setTimeout(50);
    theLog.setOutput(0U, outputToSerial);
    theLog.outputIsActive(true);

    // setting logginlevels
    theLog.setLoggingLevel(0U, loggingLevel::Debug);

    // setup start
    theLog.output(subSystem::general, loggingLevel::Info, "starting");        //

    theInput.initialize();
    theLeds.setup();

    delay(8000);
    Serial1.println("$H");
    delay(20000);
    Serial1.println("G01 X160 Y10 Z0 F2000");

  
}

void loop() {
    theInput.run();
    theLeds.run(theInput.getPosition());
    // echoSerial();
}

unsigned long timervalue;
unsigned long heartbeattimeout = 1000;

void printHeartBeat() {
    if (millis() - timervalue >= heartbeattimeout) {
        timervalue = millis();
        inputStates theState;
        theState = theInput.getPosition();
        switch (theState) {
            case inputStates::locked:
                Serial.println("locked");
                break;
            case inputStates::neutral:
                Serial.println("neutral");
                break;
            case inputStates::Xminus:
                Serial.println("x-");
                break;
            case inputStates::Xplus:
                Serial.println("x+");
                break;
            case inputStates::Yminus:
                Serial.println("y-");
                break;
            case inputStates::Zminus:
                Serial.println("z-");
                break;
            case inputStates::Zplus:
                Serial.println("z+");
                break;
            default:
                Serial.print(".");
                break;
        }
    }
}
// void echoSerial() {
//     while (Serial1.available()) {
//         theLog.output(subSystem::stepper, loggingLevel::Info, Serial1.read());
//     }
// }

// Logging helper functions
bool outputToSerial(const char* contents) {        // Step 3. Add a function which sends the output of the logging to the right hw channel, eg Serial port
    size_t nmbrBytesSent;
    nmbrBytesSent = Serial.print(contents);
    if (nmbrBytesSent > 0) {
        return true;
    } else {
        return false;
    }
}

bool loggingTime(char* contents, uint32_t length) {        // Step 4. Add a function which generates a timestamp string, so your logging events can get timestamped. Simple example is using millis()
    itoa(millis(), contents, 10);                          // convert millis to a string
    return true;
}
