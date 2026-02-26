#pragma once

#include <FastBot.h>
#include <ESP8266WIFI.h>

constexpr char TELEGRAM_CHAT_ID[] = "*****";
constexpr char WIFI_SSID_VALUE[] = "******";
constexpr char WIFI_PASS_VALUE[] = "*****";
constexpr char TELEGRAM_BOT_TOKEN[] = "*****";

extern FastBot bot;

void wifi_init();
void bot_send(const String& msg);
void bot_send_file(File& file);
