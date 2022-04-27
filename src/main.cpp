#include <Arduino.h>
#include "CNCShield.h"
#include "machineinputs.h"

#define NO_OF_STEPS               200
#define SLEEP_BETWEEN_STEPS_MS    1
#define SPEED_STEPS_PER_SECOND    1000

/*
 * Create a CNCShield object and get a pointer to motor 0 (X axis).
 */
CNCShield cnc_shield;
StepperMotor *motor = cnc_shield.get_motor(0);

#define LEDPIN 13

machineInputs theInput;

void blink();

void setup()
{
  Serial.begin(115200);
  Serial.println("starting");
  pinMode(LEDPIN, OUTPUT);
  theInput.initialize();


   /*
   * Calling CNCShield.begin() is mandatory before using any motor.
   */
  cnc_shield.begin();

  /*
   * Enable the shield (set enable pin to LOW).
   */
  cnc_shield.enable();

  
   
  motor->set_dir(CLOCKWISE);
  for (int i = 0; i < NO_OF_STEPS; i++) {
    motor->step();
    delay(SLEEP_BETWEEN_STEPS_MS);
  }

  motor->set_dir(COUNTER);
  for (int i = 0; i < NO_OF_STEPS; i++) {
    motor->step();
    delay(SLEEP_BETWEEN_STEPS_MS);
  }
   
  /*
   * Step in a direction.
   */
/*
  for (int i = 0; i < NO_OF_STEPS; i++) {
    motor->step(CLOCKWISE);
    delay(SLEEP_BETWEEN_STEPS_MS);
  }

  for (int i = 0; i < NO_OF_STEPS; i++) {
    motor->step(COUNTER);
    delay(SLEEP_BETWEEN_STEPS_MS);
  }
  
 */
  /*
   *  Step a number of steps in a previously set direction
   *   with a previously set speed.
   */
  motor->set_speed(SPEED_STEPS_PER_SECOND);
  motor->set_dir(CLOCKWISE);
  motor->step(200);

  motor->set_dir(COUNTER);
  motor->step(200);

  /*
   *  Step a number of steps in a direction
   *   with a previously set speed.
   */
  motor->set_speed(SPEED_STEPS_PER_SECOND);
  motor->step(200, CLOCKWISE);
  motor->step(200, COUNTER);

  /*
   * Disable the shield (set enable pin to HIGH).
   */
  //cnc_shield.disable();
}

void loop()
{
  theInput.run();
  blink();
}

unsigned long blinktimer = 0;
unsigned long blinktimeout = 500;
bool ledstate = false;

void blink()
{
  if ((millis() - blinktimer) >= blinktimeout)
  {
    blinktimer = millis();
    ledstate = !ledstate;
    if (ledstate)
    {
      digitalWrite(LEDPIN, HIGH);
      Serial.println("High");
    }
    else
    {
      digitalWrite(LEDPIN, LOW);
      Serial.println("Low");
    }
  }
};
