#ifndef PAGES_H
#define PAGES_H

#include "DataClass.h"

void initDisplay();
void showSplash(char* message="");
void showNumeric(Data* source, char* label, char* units = "");
void showBar(Data* source, char* label, char* units = "");

uint8_t centering24p(Data* source, char* buf);
void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_w);

#endif //PAGES_H