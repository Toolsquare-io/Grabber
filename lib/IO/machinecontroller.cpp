#include "machinecontroller.h"
#include <Arduino.h>

void machinecontroller::initialize(/* args */) {
    motor1 = cnc_shield.get_motor(0);
    /*
     * Calling CNCShield.begin() is mandatory before using any motor1.
     */
    cnc_shield.begin();

    /*
     * Enable the shield (set enable pin to LOW).
     */
    cnc_shield.enable();
};

void machinecontroller::run() {
    motor1->set_dir(CLOCKWISE);
    for (int i = 0; i < NO_OF_STEPS; i++) {
        motor1->step();
        delay(SLEEP_BETWEEN_STEPS_MS);
    }

    motor1->set_dir(COUNTER);
    for (int i = 0; i < NO_OF_STEPS; i++) {
        motor1->step();
        delay(SLEEP_BETWEEN_STEPS_MS);
    }

    /*
     * Step in a direction.
     */
    /*
      for (int i = 0; i < NO_OF_STEPS; i++) {
        motor1->step(CLOCKWISE);
        delay(SLEEP_BETWEEN_STEPS_MS);
      }

      for (int i = 0; i < NO_OF_STEPS; i++) {
        motor1->step(COUNTER);
        delay(SLEEP_BETWEEN_STEPS_MS);
      }

     */
    /*
     *  Step a number of steps in a previously set direction
     *   with a previously set speed.
     */
    motor1->set_speed(SPEED_STEPS_PER_SECOND);
    motor1->set_dir(CLOCKWISE);
    motor1->step(200);

    motor1->set_dir(COUNTER);
    motor1->step(200);

    /*
     *  Step a number of steps in a direction
     *   with a previously set speed.
     */
    motor1->set_speed(SPEED_STEPS_PER_SECOND);
    motor1->step(200, CLOCKWISE);
    motor1->step(200, COUNTER);

    /*
     * Disable the shield (set enable pin to HIGH).
     */
    // cnc_shield.disable();
};
