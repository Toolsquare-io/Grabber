
// outputs
#pragma once

class pinmapping {
  public:
    // inputs
    int JoyStickXPosPin = 14;
    int JoyStickXNegPin = 15;
    int JoyStickYPosPin = 16;
    int JoyStickYNegPin = 17;
    int ZButtonPin      = 18;
    int LockPin         = 19;
    int GrabButtonPin   = 20;

    // CNCShield defined pin's:
    int M1_STP_PIN = 2;
    int M2_STP_PIN = 3;
    int Z_STP_PIN = 4;
    int M1_DIR_PIN = 5;
    int M2_DIR_PIN = 6;
    int Z_DIR_PIN = 7;
    int SHIELD_EN_PIN = 8;

    int x_plus_limitpin = 9;
    int x_min_limitpin = 10;
    int y_plus_limitpin = 11;
    int y_min_limitpin = 12;
    // TODO add zpins

    //other
    int led_datapin = 21;

};
