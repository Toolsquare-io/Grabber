#pragma once
#include "FastLED.h"
#include "machineinputs.h"

#define LED_PIN1 10
#define LED_PIN2 11
#define NUM_LEDS1 26 //bridge
#define NUM_LEDS2 88
//#define UPDATES_PER_SECOND 10


extern machineInputs theInputs;

class ledmadness {
  public:
    ledmadness();
    void setup();
    void run(inputStates inputState);

  private:
    uint8_t brightness = 64;
    uint8_t ledindex = 0;
    uint8_t ledbatch = 10;
    uint8_t colorIndex = 1;

    CRGB leds1[NUM_LEDS1];
    CRGB leds2[NUM_LEDS2];
    CRGB leds3[1];
    inputStates theState;
    CRGBPalette16 currentPalette;
    TBlendType currentBlending;
    unsigned long updatesPerSecond = 10;

    void redBreathe();
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void changeState(inputStates newState);
};
