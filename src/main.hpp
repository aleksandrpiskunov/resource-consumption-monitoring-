#pragma once

#include "pins.hpp"
#include "wifi_bot.hpp"
#include "sd_card.hpp"
#include "consumption.hpp"

void setup();
void loop();
void newMsg(FB_msg& msg);
