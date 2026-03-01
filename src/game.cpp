// ═══════════════════════════════════════════════════════════════════
// ═══ STEP 4 — Alive!: buttonMash mini-game ═══════════════════════
// ═══════════════════════════════════════════════════════════════════

#include <Arduino.h>
#include "game.h"

int32_t buttonMash(int32_t pin, uint32_t durationMs) {
    int32_t  presses = 0;
    bool     lastBtn = digitalRead(pin);
    uint32_t start   = millis();

    while (millis() - start < durationMs) {
        bool btn = digitalRead(pin);
        if (btn && !lastBtn) presses++;
        lastBtn = btn;
        delay(10);
    }
    return presses;
}
