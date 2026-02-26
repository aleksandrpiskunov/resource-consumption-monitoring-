#include "main.hpp"

void setup() {
    delay(300);
    Serial.begin(9600);
    bot.attach(newMsg);
    pinMode(PIN_D8, INPUT);
    energyTotal = ENERGY_TOTAL_START;
    energyFraction = ENERGY_FRACTION_START;
    lastPulseState = 1;
    pulseCount = 0;
    energyIncrement = ENERGY_INCREMENT_DEFAULT;
    wifi_init();
    sd_init();
}

void loop() {
    if (millis() - lastMeterPoll > METER_POLL_PERIOD_MS) {
        updateConsumption();
        lastMeterPoll = millis();
    }
    FB_Time t = bot.getTime(3);
    handleMeterData(t);
    bot.tick();
}

void handleMeterData(const FB_Time& t) {
    String fractionStr = String(energyFraction, DEC);
    String fractionStrShort = fractionStr.substring(1);
    String totalStr = String(energyTotal, DEC);
    String el = "ЭЛ=";
    String kw_hs = "кВт*ч";
    String prefin_kw_h = totalStr + fractionStrShort;
    prefin_kw_h.remove(8);
    String finalKwH = el + prefin_kw_h + kw_hs;
    if (micros() - lastDataSend >= DATA_SEND_INTERVAL_US) {
        Serial.print(t.timeString());
        Serial.print(' ');
        Serial.println(t.dateString());
        Serial.print(" ");
        Serial.println(finalKwH);
        Serial.print("lenght=");
        Serial.println(finalKwH.length());
        sd_write(finalKwH, t);
        sd_remove_first();
        handleTelegramSend(finalKwH);
        lastDataSend = micros();
    }
}

void handleTelegramSend(const String& finalKwH) {
    bot_send(finalKwH);
}

void newMsg(FB_msg& msg) {
    handleTelegramMsg(msg);
}

void handleTelegramMsg(FB_msg& msg) {
    FB_Time t(msg.unix, 3);
    if (msg.text == "/command1") {
        File file = SD.open(SD_FILENAME, "r");
        bot_send_file(file);
        file.close();
    }
    if (msg.text == "/command2") {
        String week_data = sd_read_week();
        bot.sendMessage(week_data, msg.chatID);
    }
}
