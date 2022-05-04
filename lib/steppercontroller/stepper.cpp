#include "stepper.h"
#include "Arduino.h"

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

void stepper::step() {
    if (pulsestate) {
        pulsestate = LOW;
    } else {
        pulsestate = HIGH;
    }

    digitalWrite(pulsePin, pulsestate);
}

long stepper::getDelta() {
}