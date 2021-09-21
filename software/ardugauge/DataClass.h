#ifndef DATACLASS_H
#define DATACLASS_H

#include "Arduino.h"

class Data {
public:
  Data(uint16_t address, uint16_t length, int16_t min = 0, int16_t max = 100, uint16_t factor = 1);
  void request(uint16_t timeout = 300);
  int get();
  int16_t getMin();
  int16_t getMax();
  uint16_t getFactor();

private:
  uint16_t _address;
  uint16_t _length;
  int16_t _value;
  uint16_t _factor;
  int16_t _min;
  int16_t _max;
  uint32_t _timer;
  uint8_t _data[];
};

#endif  //DATACLASS_H