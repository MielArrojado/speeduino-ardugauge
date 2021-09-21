#ifndef PAGES_H
#define PAGES_H

#include "DataClass.h"

void initDisplay();
void showSplash(char* message="");
void showNumeric(Data &source, char* label, char* units = "");
void showBar(Data &source, char* label, char* units = "");
// void show2Bar(Data &source1, char* label1, char* units1,
//               Data &source2, char* label2, char* units2);

uint8_t centering(Data &source, char* buf, uint8_t c_width, uint8_t field_width = 128);
void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_h, uint8_t bar_w);

#endif //PAGES_H