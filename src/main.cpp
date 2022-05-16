#include <Arduino.h>
#include "machineinputs.h"
#include "pinmapping.h"
#include "logging.h"
#include "steppercontroller.h"
#include "ledmadness.h"

//creating the objects
uLog theLog;
machineInputs theInput;
pinmapping thePins;
steppercontroller theController;
ledmadness theLeds;

//forward declarations
bool outputToSerial(const char* contents);
bool loggingTime(char* contents, uint32_t length);
void blinksetup();
void blink();

void setup() {
    
    //blinker
    //blinksetup();

    //configure output
    theLog.setColoredOutput(0U, true);        // enable colored output - remember to set 'monitor_flags = --raw' in platformio.ini    theLog.output(subSystem::general, loggingLevel::Error, "This is an error");           //
    Serial.begin(112500);
    theLog.setOutput(0U, outputToSerial);
    theLog.outputIsActive(true);

    //setting logginlevels
    theLog.setLoggingLevel(0U, subSystem::general, loggingLevel::Debug);
    theLog.setLoggingLevel(0U, subSystem::stepper, loggingLevel::Debug);
    theLog.setLoggingLevel(0U, subSystem::input, loggingLevel::Debug);
    theLog.setLoggingLevel(0U, subSystem::neopixels, loggingLevel::Debug);

    //setup start
    theLog.output(subSystem::general, loggingLevel::Info, "starting");        //

    theInput.initialize();
    theController.setup();
    theLeds.setup();
}

void loop() {
    //blink();
    theInput.run();
    theController.run(theInput.getPosition());
}


//Logging helper functions

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

//Blink

unsigned long blinktimeout = 500;
unsigned long blinktimer;
byte blinkstate = 0;

void blinksetup() {
    pinMode(13, OUTPUT);
}

void blink() {
    if (millis() - blinktimer >= blinktimeout) {
        blinktimer = millis();
        if (blinkstate==HIGH)
        {
            //theLog.output(subSystem::general,loggingLevel::Debug, "LOW");
            blinkstate=LOW;
        }else
        {
             //theLog.output(subSystem::general,loggingLevel::Debug, "HIGH");
            blinkstate=HIGH;
        }
        digitalWrite(13, blinkstate);
    }
}
