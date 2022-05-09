#include "ledmadness.h"
#include "pinmapping.h"

extern pinmapping thePins;

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define LED_PIN 21
#define UPDATES_PER_SECOND 100

ledmadness::ledmadness(/* args */) {
}

void ledmadness::setup() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(brightness);
}

void ledmadness::run(inputStates inputState) {
    if (NUM_LEDS - ledindex >= ledbatch) {
        for (ledindex; ledindex < ledindex + ledbatch; ledindex++) {
            leds[ledindex] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
            colorIndex += 3;
        }
    } else {
        if (NUM_LEDS - ledindex >= 0) {
            /* code */
        }
        if (inputState != theState) {
            changeState(inputState);
        }
        FastLED.show();
        FastLED.delay(1000 / updatesPerSecond);
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
