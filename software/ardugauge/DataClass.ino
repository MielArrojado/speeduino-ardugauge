#include "Arduino.h"
#include "DataClass.h"

Data::Data(uint16_t address, uint16_t length, int16_t min, int16_t max, uint16_t factor) {
  _address = address;
  _length = length;
  _value = 0;
  _factor = factor;
  _min = min;
  _max = max;
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
  else if(_min != _max)
  {
    _timer = (millis()>>2) & 0x3FF;
  
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
  else 
  {
    _data[1] = 0;
    _data[0] = 0;
  }
}

int Data::get() {
  if (_length == 2) {
    _value = _data[0] + (_data[1] << 8);
  } else {
    _value = (signed char)_data[0];
  }
  return _value;
}

int16_t Data::getMin(){
  return _min;
}

int16_t Data::getMax(){
  return _max;
}

uint16_t Data::getFactor(){
  return _factor;
}