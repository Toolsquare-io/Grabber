#pragma once
#include "FastLED.h"
#include "machineinputs.h"

#define NUM_LEDS 50
#define UPDATES_PER_SECOND 100


extern machineInputs theInputs;

class ledmadness {
  public:
    ledmadness();
    void setup();
    void run(inputStates inputState);

  private:
    uint8_t brightness = 64;
    CRGB leds[NUM_LEDS];
    inputStates theState;
    CRGBPalette16 currentPalette;
    TBlendType currentBlending;
    unsigned long updatesPerSecond = 100;

    void redBreathe();
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void changeState(inputStates newState);
};
