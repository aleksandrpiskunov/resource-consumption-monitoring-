#pragma once

#include "pins.hpp"
#include "wifi_bot.hpp"
#include "sd_card.hpp"
#include "consumption.hpp"

void setup();
void loop();
void handleMeterData(const FB_Time& t);
void handleTelegramSend(const String& finalKwH);
void handleTelegramMsg(FB_msg& msg);
