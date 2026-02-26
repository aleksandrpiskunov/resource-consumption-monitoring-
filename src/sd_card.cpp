#include "sd_card.hpp"
#include "pins.hpp"

void sd_init() {
    Serial.println("Подключение SD...");
    if(!SD.begin(PIN_D0)) {
        Serial.println("ошибка подключеия!");
        while (1);
    }
    Serial.println("Подключено ");
    SD.remove("test.txt");
}

void sd_write(const String& finall_kw_h, const FB_Time& t) {
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
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
}

void sd_remove_first() {
    if (first_out==0) {
        SD.remove("test.txt");
        first_out=1;
    }
}

String sd_read_week() {
    myFile = SD.open("test.txt", FILE_READ);
    String result = "";
    if(myFile) {
        while (myFile.available()) {
            file_read = myFile.readString();
            file_read_week = file_read.substring(str_number);
            Serial.print("lenght=");
            Serial.println(file_read_week.length());
        }
        myFile.close();
        result = file_read_week;
    }
    return result;
}
