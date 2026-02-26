#include "consumption.hpp"
#include "pins.hpp"

void updateConsumption() {
    currentPulseState = digitalRead(PIN_D8);
    if (currentPulseState == 0 && lastPulseState == 1) {
        pulseCount++;
        lastPulseState = currentPulseState;
    } else {
        lastPulseState = currentPulseState;
    }
    if (pulseCount == PULSE_COUNT_TO_UPDATE) {
        pulseCount = 0;
        energyFraction += energyIncrement;
        if (energyFraction >= ENERGY_FRACTION_MAX) {
            energyTotal += 1;
            energyFraction = 0.0;
        }
        Serial.println("HOP");
    }
}
