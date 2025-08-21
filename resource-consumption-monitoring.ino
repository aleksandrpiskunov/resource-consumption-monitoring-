static const uint8_t PIN_D0 = 16;// работает
      static const uint8_t PIN_D1 = 5;// работает   
      static const uint8_t PIN_D2 = 4; // работает       
      static const uint8_t PIN_D3 = 0;//работает
      static const uint8_t PIN_D4 = 2;//работает
      static const uint8_t PIN_D5 = 14;//работает 
      static const uint8_t PIN_D6 = 12;//работает
      static const uint8_t PIN_D7 = 13;//работает
     static const uint8_t PIN_D8 = 15; //работает
#include <SPI.h> //сд карта
#include <SD.h>

String file_read_week;

boolean first_out=0;

File week_file;


File myFile;
long str_number=-280;

#define CHAT_ID "*****"
#define WIFI_SSID  "******"
#define WIFI_PASS  "*****"
#define BOT_TOKEN "*****"
#include <FastBot.h>
#include <ESP8266WIFI.h>
FastBot bot(BOT_TOKEN);
String kw_h_string;
char SD_count;


float drob=0.00;
float slog = 0.01;
boolean past_x; //счетчики 
boolean x; 
char imp_count;
unsigned long kw_h ;
unsigned long last_surv;
unsigned long last_output;

String file_read;

void setup() {
  delay(300);
  Serial.begin(9600);
  
  bot.attach(newMsg);
  


  pinMode(PIN_D8, INPUT);
  kw_h = 22070;
  drob=0.15;

  past_x = 1;
  imp_count = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }

  
  while(!Serial){}
  Serial.println("Подключение SD...");

  if(!SD.begin(PIN_D0)) {
    Serial.println("ошибка подключеия!");
    while (1);
  }
  Serial.println("Подключено "); 
  SD.remove("test.txt");


  
  }
void loop() {
  if (millis()- last_surv > 40){
     x = digitalRead(PIN_D8);
     if ( x == 0 and past_x == 1) {
        imp_count = imp_count+1;
        past_x = x;
     }
     
     else {
        past_x = x;
     }
     
     if (imp_count == 32){
      
        imp_count = 0;
        drob=drob+slog;
        if (drob ==1){
          kw_h+=1;
          drob=0.00;
        }

        Serial.println("HOP");
     }


     last_surv = millis();
  }
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
    if (first_out==0){
      SD.remove("test.txt");
      first_out=1;
    }



      bot.setChatID("1128631348");
      bot.sendMessage(finall_kw_h);
      last_output=micros();

     }
sending:
  bot.tick(); 

 }
void newMsg(FB_msg& msg) {
    FB_Time t(msg.unix, 3);
    if (msg.text == "/command1") {
       File file;
       file = SD.open("/test.txt", "r");
       bot.sendFile(file, FB_DOC, "test.txt", CHAT_ID);
       file.close();

      }
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