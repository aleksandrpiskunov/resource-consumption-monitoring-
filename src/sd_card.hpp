#pragma once

#include <SPI.h>
#include <SD.h>

extern File meterFile;
extern File tempFile;
extern String weekDataStr;
extern String tempDataStr;
extern long weekDataOffset;
extern boolean isFirstWrite;

constexpr char SD_FILENAME[] = "test.txt";
constexpr int WEEK_DATA_OFFSET_STEP = 40;

void sd_init();
void sd_write(const String& finall_kw_h, const FB_Time& t);
void sd_remove_first();
String sd_read_week();
