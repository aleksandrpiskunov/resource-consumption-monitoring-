#include "wifi_bot.hpp"

FastBot bot(BOT_TOKEN);

void wifi_init() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (millis() > 15000) ESP.restart();
    }
}

void bot_send(const String& msg) {
    bot.setChatID(CHAT_ID);
    bot.sendMessage(msg);
}

void bot_send_file(File& file) {
    bot.sendFile(file, FB_DOC, "test.txt", CHAT_ID);
}
