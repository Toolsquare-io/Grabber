#include "ledmadness.h"
#include "pinmapping.h"
#include "logging.h"

extern pinmapping thePins;
extern uLog theLog;

#define LED_TYPE WS2812B //WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
#define BRIGHTNESS  64

ledmadness::ledmadness(/* args */) {
}

void ledmadness::setup() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(brightness);
    currentPalette=RainbowColors_p;
    currentBlending=LINEARBLEND;
}

void ledmadness::run(inputStates inputState) {
    //theLog.output(subSystem::neopixels, loggingLevel::Info, "running the pixels");
    if (inputState != theState) {
        changeState(inputState);
    }

    static uint8_t startIndex = 0;
    startIndex                = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors(startIndex);

    FastLED.show();
    FastLED.delay(1000 / updatesPerSecond);
}

void ledmadness::FillLEDsFromPaletteColors(uint8_t colorIndex) {
    //uint8_t brightness = 255;

    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void ledmadness::changeState(inputStates newState) {
    theState = newState;

    switch (theState) {
        case inputStates::locked:
            currentPalette  = RainbowColors_p;
            currentBlending = LINEARBLEND;
            break;

        case inputStates::neutral:
            currentPalette  = LavaColors_p;
            currentBlending = LINEARBLEND;
            break;

        case inputStates::Xminus:
        case inputStates::Xplus:
        case inputStates::Yminus:
        case inputStates::Yplus:
        case inputStates::Zminus:
        case inputStates::Zplus:
            currentPalette  = RainbowColors_p;
            currentBlending = LINEARBLEND;
            break;

        default:
            break;
    }
}

// This function sets up a palette of purple and green stripes.
void ledmadness::redBreathe() {
    CRGB red   = CRGB::Red;
    CRGB black = CRGB::Black;

    currentPalette = CRGBPalette16(
        red, black);
}
