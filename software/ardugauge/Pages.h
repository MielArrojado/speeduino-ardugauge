#ifndef PAGES_H
#define PAGES_H

#include "DataClass.h"

void initDisplay();
// void showSplash(char *message = "");
// void showNumeric(Data &source);
void showBar(Data &source);
// void show2Bar(Data &source1, Data &source2);

uint8_t formatVal(Data &source, char *buf);
uint8_t centering(char *buf, uint8_t c_width, uint8_t field_width = 128, uint8_t min_len = 0);
void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_h, uint8_t bar_w);

#endif //PAGES_H