#ifndef PAGES_H
#define PAGES_H

#include "DataClass.h"

class Page{
  public:
    Page(Data* source);
    void setLabel(char* label);
    void setUnits(char* units);
    void display();
    static void initDisplay();
  private:
    Data* _source;
    char _label[22];
    char _units[4];
    uint8_t _labelLen;
    uint8_t _unitsLen;
    uint8_t _valLen;
};

#endif //PAGES_H