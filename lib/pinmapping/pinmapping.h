
// outputs
#pragma once

class pinmapping {
    // ESP32 Saola version

  public:
    // inputs
    int JoyStickXPosPin = 1;
    int JoyStickXNegPin = 2;
    int JoyStickYPosPin = 4;
    int JoyStickYNegPin = 3;
    int ZButtonPin      = 5;
    int GrabButtonPin   = 6;
    // and GND

    //int GrabPWMpin       = 7;        // PWM Not in use as it's only illuminated when pressed. Thus connected to 3.3V
    int GrabRelaispin = 7;


    // other
    int led1_datapin = 10;        // bridge change in ledmadness.h file
    int led2_datapin = 11;        // change in ledmadness.h file
    int led3_datapin = 18;        // onboard led
    int TSrunningpin = 12;
    int TSlockpin    = 13;

    //Saola reserved pins: 
    // Serial1 = 19 and 21

    //Total 15 pins
    //GND 
};