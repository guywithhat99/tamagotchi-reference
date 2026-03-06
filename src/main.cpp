#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════
// ═══ STEP 0 — Hello World: includes, Pet, setup & loop ═══════════
// ═══════════════════════════════════════════════════════════════════

#include "Pet.h"
#include "buttons.h"
#include "sound.h"
#include "leds.h"
#include "game.h"

Pet pet;

// === PET SETTINGS — tweak these! ===
PetConfig config;

void setup() {
    // Customise your pet (try changing these values!)
    // config.decayRate      = 1;      // how much stats drop each tick
    // config.decayInterval  = 30000;  // ms between decay ticks (lower = harder)
    // config.feedAmount     = 20;     // how much food one press gives
    // config.drinkAmount    = 20;     // how much water one press gives
    // config.exerciseCap    = 30;     // max energy from one mash session
    // config.alertThreshold = 30;     // stat level that triggers alerts

    Serial.begin(115200);
    delay(1500);  // give USB serial time to connect before first print
    Serial.println("Pet alive!");

    pet.begin(config);
    setupButtons();   // ← STEP 1
    setupBuzzer();    // ← STEP 2
    setupLeds();      // ← STEP 3

    // ═══════════════════════════════════════════════════════════════
    // ═══ STEP 4 — Alive!: enableDecay + button mash ══════════════
    // ═══════════════════════════════════════════════════════════════
    pet.enableDecay();
}

void loop() {
    // ═══ STEP 4 (cont.) — green button mash logic ═════════════════
    static bool lastGreen = false;
    bool green = digitalRead(19);

    if (green && !lastGreen) {
        pet.say("MASH IT!");
        int32_t presses = buttonMash(19, 3000);
        pet.exercise(presses);
    }

    lastGreen = green;
    readButtons(pet);  // ← STEP 1
    pet.update();
    delay(50);
    Serial.println("tick");
}
