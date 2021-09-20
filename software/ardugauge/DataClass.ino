#include "Arduino.h"
#include "DataClass.h"

Data::Data(uint16_t address, uint16_t length, int16_t min, int16_t max) {
  _address = address;
  _length = length;
  _min = min;
  _max = max;
  _value = 0;
}

void Data::request(uint16_t timeout) {
  Serial.write('r');
  Serial.write((byte)0);
  Serial.write((byte)48);
  Serial.write((byte)_address);
  Serial.write((byte)0);
  Serial.write((byte)_length);
  Serial.write((byte)0);

  // wait for data or timeout
  uint32_t start = millis();
  uint32_t end = start;
  while (Serial.available() < (2 + _length) && (end - start) < timeout) {
    end = millis();
  }

  // if within timeout, read data
  if (end - start < timeout) {
    // skip first two bytes
    Serial.read();  // 'r'
    Serial.read();  // 0x30

    // store data
    for (uint8_t i = 0; i < _length; i++) {
      _data[i] = Serial.read();
    }
  }
  // else sweep
  else
  {
    _timer = millis() & 0x3FF;
  
    int value = 0;

    if(_timer < 512){
      value = _min+(((_max-_min)*_timer)>>9);
    }
    else{
      value = _min+(((_max-_min)*(1023-_timer))>>9);
    }
    _data[1] = value >> 8;
    _data[0] = value & 0xFF;
  }
}

int Data::get() {
  if (_length == 2) {
    _value = _data[0] + (_data[1] << 8);
  } else {
    _value = _data[0];
  }
  return _value;
}

int16_t Data::getMin(){
  return _min;
}

int16_t Data::getMax(){
  return _max;
}