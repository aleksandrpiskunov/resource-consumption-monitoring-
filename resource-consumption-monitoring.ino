// Пины для платы Wemos D1 R2
static const uint8_t PIN_D0 = 16;  // работает
static const uint8_t PIN_D1 = 5;   // работает   
static const uint8_t PIN_D2 = 4;   // работает       
static const uint8_t PIN_D3 = 0;   // работает
static const uint8_t PIN_D4 = 2;   // работает
static const uint8_t PIN_D5 = 14;  // работает 
static const uint8_t PIN_D6 = 12;  // работает
static const uint8_t PIN_D7 = 13;  // работает
static const uint8_t PIN_D8 = 15;  // работает

#include <SPI.h>    // Для работы с SD-картой
#include <SD.h>

String file_read_week;   // Для чтения данных за неделю

boolean first_out=0;    // Флаг первого вывода

File week_file;         // Файл для данных недели
File myFile;            // Универсальный объект файла

long str_number=-280;   // Смещение для чтения последних строк

// Настройки Telegram-бота и Wi-Fi
#define CHAT_ID "*****"
#define WIFI_SSID  "******"
#define WIFI_PASS  "*****"
#define BOT_TOKEN "*****"
#include <FastBot.h>
#include <ESP8266WIFI.h>
FastBot bot(BOT_TOKEN);

String kw_h_string;     // Строка для хранения значения кВт*ч
char SD_count;          // Счетчик SD

// Переменные для подсчёта расхода
float drob=0.00;        // Дробная часть расхода
float slog = 0.01;      // Приращение расхода за каждый импульс
boolean past_x;         // Предыдущее значение импульса счетчика 
boolean x;              // Текущее значение импульса счетчика
char imp_count;         // Счётчик импульсов
unsigned long kw_h;     // Основной счетчик потребления (кВт*ч)
unsigned long last_surv;   // Время последнего опроса счетчика
unsigned long last_output; // Время последней отправки данных

String file_read;       // Переменная для чтения файла

void setup() {
  delay(300);                        // Небольшая задержка для стабильного запуска
  Serial.begin(9600);                // Запуск порта для отладки
  bot.attach(newMsg);                // Привязка обработчика новых сообщений Телеграм

  pinMode(PIN_D8, INPUT);            // Входной режим для импульсного выхода счетчика
  kw_h = 22070;                      // Начальное значение кВт*ч (пример)
  drob=0.15;                         // Начальное значение дробной части

  past_x = 1;                        // Стартовое значение последнего импульса
  imp_count = 0;                     // Счётчик импульсов

  // Подключение к Wi-Fi c проверкой на таймаут
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart(); // Перезапуск, если нет подключения дольше 15 секунд
  }

  while(!Serial){}                    // Ожидание Serial для корректного старта
  Serial.println("Подключение SD...");

  if(!SD.begin(PIN_D0)) {             // Запуск SD-карты через пин D0
    Serial.println("ошибка подключеия!");
    while (1);
  }
  Serial.println("Подключено "); 
  SD.remove("test.txt");              // Удаление старого файла при старте
}

void loop() {
  // Опрос счетчика с периодом более 40 мс
  if (millis()- last_surv > 40){
     x = digitalRead(PIN_D8); // Считывание импульса от счетчика
     if ( x == 0 and past_x == 1) { // Если обнаружен перепад (импульс)
        imp_count = imp_count+1;
        past_x = x;
     } else {
        past_x = x;
     }
     
     if (imp_count == 32){ // Каждые 32 импульса - обновление расхода
        imp_count = 0;
        drob=drob+slog;
        if (drob ==1){
          kw_h+=1;
          drob=0.00;
        }
        Serial.println("HOP"); // Сообщение отладки
     }
     last_surv = millis(); // Обновление времени последнего опроса
  }

  // Отправка данных каждые ~30 секунд (30_000_000 микросекунд)
  if (micros()-last_output<30000000){
    FB_Time t = bot.getTime(3);
    goto sending;
    }

  else{
      FB_Time t = bot.getTime(3);

      Serial.print(t.timeString());
      Serial.print(' ');
      Serial.println(t.dateString());
      Serial.print(" ");

      String drob_string = String(drob, DEC);
      String drob_string_kk = drob_string.substring(1);
      String kw_h_string = String(kw_h, DEC);
      String el = "ЭЛ=";
      String kw_hs = "кВт*ч";
      String prefin_kw_h = kw_h_string+drob_string_kk;
      prefin_kw_h.remove(8);
      String finall_kw_h = el+prefin_kw_h+kw_hs;
      Serial.println(finall_kw_h);
      Serial.print("lenght=");
      Serial.println(finall_kw_h.length());
      
      // Запись показаний в test.txt
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
    {
        Serial.println("Загрузка в test.txt...");

        myFile.print(t.hour);
        myFile.print(':');
        myFile.print(t.minute);
        myFile.print(' ');

        myFile.print(t.day);
        myFile.print(':');
        myFile.print(t.month);
        myFile.print(':');
        float year = t.year;
        String year_string = String(year, DEC);
        String year_1 = year_string.substring(2,4);
        myFile.print(year_1);
        myFile.print("  ");
   
        myFile.println(finall_kw_h);
        str_number+=40;
        Serial.println("Записано");
        myFile.close();
    }
    // При первом запуске удаляем test.txt для чистоты
    if (first_out==0){
      SD.remove("test.txt");
      first_out=1;
    }
      // Отправка данных в Telegram
      bot.setChatID("******");
      bot.sendMessage(finall_kw_h);
      last_output=micros();
     }
sending:
  bot.tick(); // Опрос событий Telegram-бота

}

// Обработка новых сообщений от Telegram
void newMsg(FB_msg& msg) {
    FB_Time t(msg.unix, 3);
    // Команда на отправку файла
    if (msg.text == "/command1") {
       File file;
       file = SD.open("/test.txt", "r");
       bot.sendFile(file, FB_DOC, "test.txt", CHAT_ID);
       file.close();

      }
    // Команда на отправку статистики/данных
    if (msg.text == "/command2") {
      myFile = SD.open("test.txt", FILE_READ);
         if(myFile)
      {   
         while (myFile.available())
          {
                  
           file_read = myFile.readString();
           file_read_week = file_read.substring(str_number);
           Serial.print("lenght=");
           Serial.println(file_read_week.length());
        
                  
           }
           myFile.close();      
       }
      bot.sendMessage(file_read_week, msg.chatID);
      }
    }
