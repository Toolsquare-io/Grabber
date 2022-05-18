#pragma once
#include "FastLED.h"
#include "machineinputs.h"

#define LED_PIN1 26
#define LED_PIN2 25
#define NUM_LEDS1 26 //bridge
#define NUM_LEDS2 100
#define UPDATES_PER_SECOND 100


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
    inputStates theState;
    CRGBPalette16 currentPalette;
    TBlendType currentBlending;
    unsigned long updatesPerSecond = 100;

    void redBreathe();
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void changeState(inputStates newState);
};
