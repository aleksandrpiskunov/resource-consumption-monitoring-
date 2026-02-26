#include "wifi_bot.hpp"

FastBot bot(TELEGRAM_BOT_TOKEN);

constexpr unsigned long WIFI_CONNECT_TIMEOUT_MS = 15000;

void wifi_init() {
    WiFi.begin(WIFI_SSID_VALUE, WIFI_PASS_VALUE);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (millis() - startTime > WIFI_CONNECT_TIMEOUT_MS) ESP.restart();
    }
}

void bot_send(const String& msg) {
    bot.setChatID(TELEGRAM_CHAT_ID);
    bot.sendMessage(msg);
}

void bot_send_file(File& file) {
    bot.sendFile(file, FB_DOC, SD_FILENAME, TELEGRAM_CHAT_ID);
}
