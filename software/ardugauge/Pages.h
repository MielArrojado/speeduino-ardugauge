#ifndef PAGES_H
#define PAGES_H

#include "Comms.h"

void initDisplay();
void showSplash(char *message);
void showNumeric(char *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal = 0);
void showBar(char *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal = 0);
void show2Bar(char *label1, int16_t value1, int16_t min_val1, int16_t max_val1, uint8_t decimal1,
              char *label2, int16_t value2, int16_t min_val2, int16_t max_val2, uint8_t decimal2);

uint8_t maxChar(int32_t min_val, int32_t max_val, uint8_t decimal);
uint8_t formatValue(char *buf, int32_t value, uint8_t decimal);
uint8_t centering(char *buf, uint8_t c_width, uint8_t field_width = 128, uint8_t max_char = 0);
void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_h, uint8_t bar_w);

#endif //PAGES_H