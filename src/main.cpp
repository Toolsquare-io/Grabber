#include <Arduino.h>
#include "machineinputs.h"
#include "pinmapping.h"
#include "logging.h"
#include "steppercontroller.h"
#include "ledmadness.h"

uLog theLog;

machineInputs theInput;
pinmapping thePins;
steppercontroller theController;
ledmadness theLeds;

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

    theInput.initialize();
    theController.setup();
    theLeds.setup();
}

void loop() {
    theInput.run();
    theController.run(theInput.getPosition());

}
