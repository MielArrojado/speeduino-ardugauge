#ifndef PAGES_H
#define PAGES_H

#include "DataClass.h"

void initDisplay();
void showSplash(char* message="");
void showNumeric(Data* source, char* label, char* units = "");
void showBar(Data* source, char* label, char* units = "");

class Page{
  public:
    Page(Data* source, char* label = "", char* units = "");
    void setLabel(char* label);
    void setUnits(char* units);
    void display();
    static void initDisplay();
    static void defaultPage(uint8_t pageNum=0);
  private:
    Data* _source;
    char _label[22];
    char _units[4];
    uint8_t _labelLen;
    uint8_t _unitsLen;
    uint8_t _valLen;
};

#endif //PAGES_H