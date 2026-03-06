// ═══════════════════════════════════════════════════════════════════
// ═══ STEP 3 — LEDs: RGB pins, setLed & Simon Says game ═══════════
// ═══════════════════════════════════════════════════════════════════

#include <Arduino.h>
#include "leds.h"

const int PIN_LED_R = 16;
const int PIN_LED_G = 17;
const int PIN_LED_B = 18;

void setupLeds() {
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_LED_B, OUTPUT);
}

void setLed(int r, int g, int b) {
    digitalWrite(PIN_LED_R, r);
    digitalWrite(PIN_LED_G, g);
    digitalWrite(PIN_LED_B, b);
}

