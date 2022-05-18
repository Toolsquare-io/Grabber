
// outputs
#pragma once

class pinmapping {
    // ESP32 has 21 pins

  public:
    // inputs
    int JoyStickXPosPin = 35;
    int JoyStickXNegPin = 33;
    int JoyStickYPosPin = 31;
    int JoyStickYNegPin = 29;
    int ZButtonPin      = 41;
    // int LockPin         = 19;
    int GrabButtonPin = 39;

    int GrabPWMpin       = 11;        // PWM
    int ZButtonLEDpin    = 12;        // PWM
    int GrabButtonLEDpin = 13;        // PWM
    int GrabRelaispin    = 28;

    // CNCShield defined pin's:
    int M1_STP_PIN    = 2;
    int M2_STP_PIN    = 3;
    int Z_STP_PIN     = 4;
    int M1_DIR_PIN    = 5;
    int M2_DIR_PIN    = 6;
    int Z_DIR_PIN     = 7;
    int SHIELD_EN_PIN = 8;

    int x_plus_limitpin = 43;
    int x_min_limitpin  = 45;
    int y_plus_limitpin = 49;
    int y_min_limitpin  = 47;
    int z_plus_limitpin = 51;
    int z_min_limitpin  = 53;

    // other
    int led1_datapin = 26;        // bridge change in ledmadness.h file
    int led2_datapin = 25;        // change in ledmadness.h file
    int TSrunningpin = 24;
    int TSlockpin    = 22;
};