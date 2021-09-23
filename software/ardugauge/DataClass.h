#ifndef DATACLASS_H
#define DATACLASS_H

#include "Arduino.h"

// class Data
// {
// public:
//   Data(uint16_t address, uint16_t length, int16_t min = 0, int16_t max = 100, uint16_t factor = 1, bool isSigned = false);
//   int get();
//   int16_t getMin();
//   int16_t getMax();
//   uint16_t getFactor();
//   void setScale(float scale);
//   void setOffset(int16_t offset);

// private:
//   uint16_t _address;
//   uint16_t _length;
//   int16_t _value;
//   uint16_t _factor;
//   bool _signed;
//   int16_t _min;
//   int16_t _max;
//   uint32_t _timer;
//   int16_t _offset;
//   float _scale;
// };

typedef struct
{
  uint16_t address;
  uint16_t length;
  int16_t min;
  int16_t max;
  uint16_t factor;
  bool isSigned;
  char label[21];
} Data;

int16_t getValue(Data &source);
void requestData(uint16_t timeout = 20);
static uint8_t buffer[119];
uint16_t bytesRead = 0;

#endif //DATACLASS_H