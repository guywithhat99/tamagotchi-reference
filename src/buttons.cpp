// ═══════════════════════════════════════════════════════════════════
// ═══ STEP 1 — Buttons: pin setup, edge detection, actions ════════
// ═══════════════════════════════════════════════════════════════════

#include <Arduino.h>
#include "buttons.h"
#include "sound.h"
#include "leds.h"
#include "simon.h"

const int PIN_BTN_RED    = 22;
const int PIN_BTN_YELLOW = 21;
const int PIN_BTN_GREEN  = 19;

static bool lastRed    = false;
static bool lastYellow = false;
static bool lastGreen  = false;

void setupButtons() {
    pinMode(PIN_BTN_RED,    INPUT_PULLDOWN);
    pinMode(PIN_BTN_YELLOW, INPUT_PULLDOWN);
    pinMode(PIN_BTN_GREEN,  INPUT_PULLDOWN);
}

void readButtons(Pet& pet) {
    bool red    = digitalRead(PIN_BTN_RED);
    bool yellow = digitalRead(PIN_BTN_YELLOW);
    bool green  = digitalRead(PIN_BTN_GREEN);

    if (red && !lastRed) {
        Serial.print("Red — food: "); Serial.println(pet.food);
        pet.feed();
        chirp(pet.mood());
    }

    // ═══ STEP 3 — yellow button triggers Simon Says ═══════════════
    if (yellow && !lastYellow) {
        Serial.println("Yellow — Simon Says!");
        int rounds = playSimon();
        Serial.print("  rounds: "); Serial.println(rounds);
        if (rounds > 0) {
            int feeds = rounds / 2;
            for (int i = 0; i < feeds; i++) pet.feed();
            String msg = String(rounds) + " rounds!";
            pet.say(msg);
            playMelody(VICTORY_TUNE, VICTORY_TUNE_LEN);
        } else {
            pet.say("Nope...");
            playTone(200, 300);
        }
    }

    if (green && !lastGreen) {
        Serial.print("Green — water: "); Serial.println(pet.water);
        pet.drink();
        chirp(pet.mood());
    }

    // Mood LED glow after any press
    if ((red && !lastRed) || (yellow && !lastYellow) || (green && !lastGreen)) {
        switch (pet.mood()) {
            case Mood::HAPPY: setLed(0, 1, 0); break;
            case Mood::SAD:   setLed(1, 0, 0); break;
            case Mood::DEAD:  setLed(0, 0, 0); break;
            default:          setLed(1, 1, 0); break;
        }
    }

    lastRed = red;
    lastYellow = yellow;
    lastGreen = green;
}
