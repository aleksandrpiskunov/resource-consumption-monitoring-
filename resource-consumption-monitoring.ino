// Пины для платы Wemos D1 R2
static const uint8_t PIN_D0 = 16;  // работает
static const uint8_t PIN_D1 = 5;   // работает   


#include "pins.hpp"
#include "wifi_bot.hpp"
#include "sd_card.hpp"
#include "consumption.hpp"
#include "main_functions.hpp"

FastBot bot(BOT_TOKEN);

void setup() {
  delay(300);
  Serial.begin(9600);
  bot.attach(newMsg);
  pinMode(PIN_D8, INPUT);
  kw_h = 22070;
  drob = 0.15;
  past_x = 1;
  imp_count = 0;
  wifi_init();
  while(!Serial){}
  sd_init();
}

void loop() {
  if (millis() - last_surv > 40) {
    update_consumption();
    last_surv = millis();
  }
  FB_Time t = bot.getTime(3);
  String drob_string = String(drob, DEC);
  String drob_string_kk = drob_string.substring(1);
  String kw_h_string = String(kw_h, DEC);
  String el = "ЭЛ=";
  String kw_hs = "кВт*ч";
  String prefin_kw_h = kw_h_string + drob_string_kk;
  prefin_kw_h.remove(8);
  String finall_kw_h = el + prefin_kw_h + kw_hs;
  if (micros() - last_output >= 30000000) {
    Serial.print(t.timeString());
    Serial.print(' ');
    Serial.println(t.dateString());
    Serial.print(" ");
    Serial.println(finall_kw_h);
    Serial.print("lenght=");
    Serial.println(finall_kw_h.length());
    sd_write(finall_kw_h, t);
    sd_remove_first();
    bot_send(finall_kw_h);
    last_output = micros();
  }
  bot.tick();
}

// Обработка новых сообщений от Telegram
void newMsg(FB_msg& msg) {
  FB_Time t(msg.unix, 3);
  if (msg.text == "/command1") {
    File file = SD.open("/test.txt", "r");
    bot_send_file(file);
    file.close();
  }
  if (msg.text == "/command2") {
    String week_data = sd_read_week();
    bot.sendMessage(week_data, msg.chatID);
  }
}
