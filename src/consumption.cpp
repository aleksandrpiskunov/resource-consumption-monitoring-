#include "consumption.hpp"
#include "pins.hpp"

void update_consumption() {
    x = digitalRead(PIN_D8);
    if (x == 0 && past_x == 1) {
        imp_count = imp_count+1;
        past_x = x;
    } else {
        past_x = x;
    }
    if (imp_count == 32) {
        imp_count = 0;
        drob = drob + slog;
        if (drob == 1) {
            kw_h += 1;
            drob = 0.00;
        }
        Serial.println("HOP");
    }
}
