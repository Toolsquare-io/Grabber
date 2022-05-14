#include <Arduino.h>
#include "stepper.h"

stepper::stepper(/* args */) {
}

void stepper::setPins(int pulse, int dir) {
    pulsePin = pulse;
    dirPin   = dir;

    pinMode(pulsePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}

void stepper::setDir(direction dir) {
    switch (dir) {
        case direction::clockwise:
            digitalWrite(dirPin, HIGH);
            break;

        case direction::counterclockwise:
            digitalWrite(dirPin, LOW);
            break;

        default:
            break;
    }
}

void stepper::setspeed(speeds speed) {
    switch (speed) {
        case speeds::veryslow:
            stepperInterval = 30;
            break;
        case speeds::slow:
            stepperInterval = 10;
            break;
        case speeds::normal:
            stepperInterval = 5;
            break;

        case speeds::fast:
            stepperInterval = 3;
            break;

        case speeds::veryfast:
            stepperInterval = 2;
            break;

        case speeds::ludicrous:
            stepperInterval = 1;
            break;

        default:
            break;
    }
}

void stepper::run() {
    if (millis() - stepperTimer >= stepperInterval) {
        stepperTimer = millis();
        step();
    }
}

void stepper::step() {
    if (pulsestate) {
        pulsestate = LOW;
    } else {
        pulsestate = HIGH;
    }
    digitalWrite(pulsePin, pulsestate);
}
