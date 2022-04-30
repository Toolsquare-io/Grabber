#include <Arduino.h>
#include "machineinputs.h"
#include "pinmapping.h"
#include "logging.h"
#include "steppercontroller.h"

#define LEDPIN 13

uLog theLog;

machineInputs theInput;
pinmapping thePins;
steppercontroller theController;

void blink();

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

void setup() {
    theLog.setColoredOutput(0U, true);        // enable colored output - remember to set 'monitor_flags = --raw' in platformio.ini    theLog.output(subSystem::general, loggingLevel::Error, "This is an error");           //
    Serial.begin(112500);
    theLog.setOutput(0U, outputToSerial);
    theLog.outputIsActive(true);
    theLog.setLoggingLevel(0U, subSystem::general, loggingLevel::Debug);
    theLog.setLoggingLevel(0U, subSystem::stepper, loggingLevel::Debug);
    theLog.output(subSystem::general, loggingLevel::Info, "starting");        //

    pinMode(LEDPIN, OUTPUT);
    theInput.initialize();
    theController.setup();
}

void loop() {
    theInput.run();
    theController.run(theInput.getPosition());
    blink();
}

unsigned long blinktimer   = 0;
unsigned long blinktimeout = 500;
bool ledstate              = false;

void blink() {
    if ((millis() - blinktimer) >= blinktimeout) {
        blinktimer = millis();
        ledstate   = !ledstate;
        if (ledstate) {
            digitalWrite(LEDPIN, HIGH);
            // theLog.output(subSystem::general, loggingLevel::Warning, "high");
            // Serial.println("High");
        } else {
            digitalWrite(LEDPIN, LOW);
            // Serial.println("Low");
        }
    }
};
