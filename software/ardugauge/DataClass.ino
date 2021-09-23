#include "Arduino.h"
#include "DataClass.h"

// Data::Data(uint16_t address, uint16_t length, int16_t min, int16_t max, uint16_t factor, bool isSigned)
// {
//   _address = address;
//   _length = length;
//   _value = 0;
//   _factor = factor;
//   _min = min;
//   _max = max;
//   _signed = isSigned;

//   _scale = 1;
//   _offset = 0;
// }

// int Data::get()
// {
//   if (_length == 2)
//   {
//     _value = buffer[_address] + (buffer[_address + 1] << 8);
//   }
//   else if (_signed)
//   {
//     _value = (signed char)buffer[_address];
//   }
//   else
//   {
//     _value = buffer[_address];
//   }

//   _value = _value * _scale + _offset;

//   return _value;
// }

// int16_t Data::getMin()
// {
//   return _min;
// }

// int16_t Data::getMax()
// {
//   return _max;
// }

// uint16_t Data::getFactor()
// {
//   return _factor;
// }

// void Data::setScale(float scale)
// {
//   _scale = scale;
// }

// void Data::setOffset(int16_t offset)
// {
//   _offset = offset;
// }

int16_t getValue(Data &source)
{
  int16_t value;
  if (source.length == 2)
  {
    value = buffer[source.address] + (buffer[source.address + 1] << 8);
  }
  else if (source.isSigned)
  {
    value = (signed char)buffer[source.address];
  }
  else
  {
    value = buffer[source.address];
  }

  return value;
}

void requestData(uint16_t timeout)
{
  Serial.setTimeout(timeout);

  // flush input buffer

  Serial.write('n');

  // wait for data or timeout
  uint32_t start = millis();
  uint32_t end = start;
  while (Serial.available() < 3 && (end - start) < timeout)
  {
    end = millis();
  }

  // if within timeout, read data
  if (end - start < timeout)
  {
    // skip first two bytes
    Serial.read(); // 'n'
    Serial.read(); // 0x32
    uint8_t dataLen = Serial.read();
    bytesRead = Serial.readBytes(buffer, dataLen);
  }
}
