#pragma once

#include <SPI.h>
#include <SD.h>

extern File week_file;
extern File myFile;
extern String file_read_week;
extern String file_read;
extern char SD_count;
extern long str_number;
extern boolean first_out;

void sd_init();
void sd_write(const String& finall_kw_h, const FB_Time& t);
void sd_remove_first();
String sd_read_week();
