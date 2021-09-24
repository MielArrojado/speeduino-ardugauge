#ifndef PAGES_H
#define PAGES_H

#define STRING_LENGTH 22

#include "Comms.h"

void initDisplay();
void showSplash(const __FlashStringHelper *message);

void showNumeric(const __FlashStringHelper *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal = 0);
void showBar(const __FlashStringHelper *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal = 0);
void show2Bar(const __FlashStringHelper *label1, int16_t value1, int16_t min_val1, int16_t max_val1, uint8_t decimal1,
              const __FlashStringHelper *label2, int16_t value2, int16_t min_val2, int16_t max_val2, uint8_t decimal2);
void show4Numeric(const __FlashStringHelper *label1, int16_t value1, int16_t min_val1, int16_t max_val1, uint8_t decimal1,
                  const __FlashStringHelper *label2, int16_t value2, int16_t min_val2, int16_t max_val2, uint8_t decimal2,
                  const __FlashStringHelper *label3, int16_t value3, int16_t min_val3, int16_t max_val3, uint8_t decimal3,
                  const __FlashStringHelper *label4, int16_t value4, int16_t min_val4, int16_t max_val4, uint8_t decimal4);
void showFlags(const __FlashStringHelper *label1, bool value1,
               const __FlashStringHelper *label2, bool value2,
               const __FlashStringHelper *label3, bool value3,
               const __FlashStringHelper *label4, bool value4,
               const __FlashStringHelper *label5, bool value5,
               const __FlashStringHelper *label6, bool value6,
               const __FlashStringHelper *label7, bool value7,
               const __FlashStringHelper *label8, bool value8);

void drawFlag(const __FlashStringHelper *label, bool value, uint8_t x, uint8_t y, uint8_t w = 62, uint8_t h = 14);

uint8_t maxChar(int32_t min_val, int32_t max_val, uint8_t decimal);
uint8_t formatValue(char *buf, int32_t value, uint8_t decimal);
uint8_t centering(char *buf, uint8_t c_width, uint8_t field_width = 128, uint8_t max_char = 0);
void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_h, uint8_t bar_w);
void clearBuffer(char *buf, uint8_t bufLen = STRING_LENGTH);

#endif //PAGES_H