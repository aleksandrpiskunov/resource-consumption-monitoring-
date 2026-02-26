#include "sd_card.hpp"
#include "pins.hpp"

void sd_init() {
    Serial.println("Подключение SD...");
    if(!SD.begin(PIN_D0)) {
        Serial.println("ошибка подключеия!");
        while (1);
    }
    Serial.println("Подключено ");
    SD.remove(SD_FILENAME);
}

void sd_write(const String& finalKwH, const FB_Time& t) {
    meterFile = SD.open(SD_FILENAME, FILE_WRITE);
    if (meterFile) {
        Serial.println("Загрузка в test.txt...");
        meterFile.print(t.hour);
        meterFile.print(':');
        meterFile.print(t.minute);
        meterFile.print(' ');
        meterFile.print(t.day);
        meterFile.print(':');
        meterFile.print(t.month);
        meterFile.print(':');
        float year = t.year;
        String yearStr = String(year, DEC);
        String yearShort = yearStr.substring(2,4);
        meterFile.print(yearShort);
        meterFile.print("  ");
        meterFile.println(finalKwH);
        weekDataOffset += WEEK_DATA_OFFSET_STEP;
        Serial.println("Записано");
        meterFile.close();
    }
}

void sd_remove_first() {
    if (!isFirstWrite) {
        SD.remove(SD_FILENAME);
        isFirstWrite = true;
    }
}

String sd_read_week() {
    meterFile = SD.open(SD_FILENAME, FILE_READ);
    String result = "";
    if(meterFile) {
        while (meterFile.available()) {
            tempDataStr = meterFile.readString();
            weekDataStr = tempDataStr.substring(weekDataOffset);
            Serial.print("lenght=");
            Serial.println(weekDataStr.length());
        }
        meterFile.close();
        result = weekDataStr;
    }
    return result;
}
