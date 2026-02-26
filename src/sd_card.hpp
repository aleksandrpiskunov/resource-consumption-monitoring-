#pragma once

#include <SPI.h>
#include <SD.h>

// Переменные для работы с SD-картой
extern File meterFile; // Файл с показаниями
extern File tempFile; // Временный файл
extern String weekDataStr; // Строка данных за неделю
extern String tempDataStr; // Временная строка
extern long weekDataOffset; // Смещение для чтения
extern boolean isFirstWrite; // Флаг первого вывода

// Константы для работы с SD-картой
constexpr char SD_FILENAME[] = "test.txt"; // Имя файла показаний
constexpr int WEEK_DATA_OFFSET_STEP = 40; // Шаг смещения для недели

// Функции работы с SD-картой
void sd_init();
void sd_write(const String& finalKwH, const FB_Time& t);
void sd_remove_first();
String sd_read_week();
