#pragma once

#include <FastBot.h>
#include <ESP8266WIFI.h>

#define CHAT_ID "*****"
#define WIFI_SSID  "******"
#define WIFI_PASS  "*****"
#define BOT_TOKEN "*****"

extern FastBot bot;

void wifi_init();
void bot_send(const String& msg);
void bot_send_file(File& file);
