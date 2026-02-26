#pragma once

#include <FastBot.h>
#include <ESP8266WIFI.h>

// Константы для Telegram и Wi-Fi
constexpr char TELEGRAM_CHAT_ID[] = "*****"; // ID чата Telegram
constexpr char WIFI_SSID_VALUE[] = "******"; // SSID Wi-Fi
constexpr char WIFI_PASS_VALUE[] = "*****"; // Пароль Wi-Fi
constexpr char TELEGRAM_BOT_TOKEN[] = "*****"; // Токен Telegram-бота

extern FastBot bot; // Объект Telegram-бота

// Функции для работы с Wi-Fi и Telegram
void wifi_init();
void bot_send(const String& msg);
void bot_send_file(File& file);
