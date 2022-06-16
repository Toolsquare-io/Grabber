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
            speedTarget = 1;
            break;
        case speeds::slow:
            speedTarget = 2;
            break;
        case speeds::normal:
            speedTarget = 4;
            break;

        case speeds::fast:
            speedTarget = 8;
            break;

        case speeds::veryfast:
            speedTarget = 12;
            break;

        case speeds::ludicrous:
            speedTarget = 16;
            break;

        default:
            break;
    }
}

void stepper::run() {
    if (millis() - stepperTimer >= stepperInterval) {
        stepperTimer = millis();
        step();

        if (speedTarget != theSpeed) {
            if (speedTarget <= theSpeed)        // breaking
            {
                theSpeed = theSpeed - speedIncrement;
            } else {        // speedIncrement
                theSpeed = theSpeed + speedIncrement;
            }

            // Frequency calculation
            // NEMA 17 is a hybrid stepping motor with a 1.8° step angle (200 steps/revolution)
            // interval (mHz)=60000/(theSpeed*steps needed for 1 revolution) => 300/theSpeed
            stepperInterval = 300 / theSpeed;
        }
    }
}

bool stepper::isRunning() {
    if (speedTarget != 0 || theSpeed != 0) {
        return true;
    } else {
        return false;
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
