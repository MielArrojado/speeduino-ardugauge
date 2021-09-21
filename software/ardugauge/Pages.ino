#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"
#include <Adafruit_SSD1306.h>
#include "Numbers24pt7b.h"
#include <splash.h>

Adafruit_SSD1306 OLED(128, 64, &Wire, -1);

void initDisplay() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 60);
  OLED.display();
  delay(1000);
  OLED.setFont();
  OLED.setTextColor(WHITE);
}

void showSplash(char* message){
  OLED.clearDisplay();
  OLED.drawBitmap((128 - splash2_width) / 2, (64 - splash2_height) / 2,
               splash2_data, splash2_width, splash2_height, 1);
  OLED.setCursor(0,56);
  OLED.print(message);
  OLED.display();
}

void showNumeric(Data* source, char* label, char* units){
  // get source data
  int16_t min = source->getMin();
  int16_t max = source->getMax();
  uint16_t factor = source->getFactor();
  source->request(10);
  int value = source->get();
  
  // allocate character space
  uint8_t unitsLen = strlen(units);
  uint8_t valLen = 16;
  char temp[16];

  sprintf(temp,"%d", min);
  valLen = strlen(temp);
  sprintf(temp,"%d", max);
  valLen = max(valLen,strlen(temp));
  if(source->getFactor()!=1)valLen++;

  // Center Numeric Display
  if (factor > 1){
    sprintf(temp,"%d",factor);
    dtostrf((float)value/factor,1+strlen(temp),strlen(temp)-1,temp);
  }
  else{
    sprintf(temp,"%d",value);
  }
  uint8_t offset = (valLen - strlen(temp))*24;
  uint8_t centering = 64-(12*valLen)+offset;

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setCursor(127-6*unitsLen,0);
  OLED.print(units);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(centering,56);
  OLED.print(temp);
  OLED.setFont();
  OLED.display();
}

void showBar(Data* source, char* label, char* units){
  // get source data
  int16_t min = source->getMin();
  int16_t max = source->getMax();
  uint16_t factor = source->getFactor();
  source->request(10);
  int value = source->get();
  
  // allocate character space
  uint8_t unitsLen = strlen(units);
  uint8_t valLen = 16;
  char temp[16];

  sprintf(temp,"%d", min);
  valLen = strlen(temp);
  sprintf(temp,"%d", max);
  valLen = max(valLen,strlen(temp));
  if(source->getFactor()!=1)valLen++;
  
  // Center Numeric Display
  if (factor > 1){
    sprintf(temp,"%d",factor);
    dtostrf((float)value/factor,1+strlen(temp),strlen(temp)-1,temp);
  }
  else{
    sprintf(temp,"%d",value);
  }
  uint8_t offset = (valLen - strlen(temp))*24;
  uint8_t centering = 64-(12*valLen)+offset;
  uint8_t width = constrain(((long)value-min)*128/(max-min),0,128);

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setCursor(127-6*unitsLen,0);
  OLED.print(units);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(centering,44);
  OLED.print(temp);
  OLED.setFont();
  OLED.drawFastVLine(0, 50, 14, 1);
  OLED.drawFastVLine(31,60,4,1);
  OLED.drawFastVLine(63,60,4,1);
  OLED.drawFastVLine(64,60,4,1);
  OLED.drawFastVLine(96,60,4,1);
  OLED.drawFastVLine(127,50,14,1);
  OLED.drawFastHLine(0,63,128,1);
  OLED.fillRect(0, 52, width, 8, 1);
  OLED.drawFastVLine(1,52,8,0);
  OLED.drawFastVLine(126,52,8,0);
  OLED.display();
}


Page::Page(Data* source, char* label, char* units) {
  _source = source;
  // initialize properties
  setLabel(label);
  setUnits(units);
  // determine max width;
  char temp[16];
  sprintf(temp,"%d", _source->getMin());
  _valLen = strlen(temp);
  sprintf(temp,"%d", _source->getMax());
  _valLen = max(_valLen,strlen(temp));
  if(_source->getFactor()!=1)_valLen++;
}

void Page::display() {
  _source->request(10);
  int value = _source->get();
  char temp[16];

  // Center Numeric Display
  uint16_t factor = _source->getFactor();
  if (factor > 1){
    sprintf(temp,"%d",factor);
    dtostrf((float)value/factor,1+strlen(temp),strlen(temp)-1,temp);
  }
  else{
    sprintf(temp,"%d",value);
  }
  uint8_t offset = (_valLen - strlen(temp))*24;
  uint8_t centering = 64-(12*_valLen)+offset;
  
  // bar graph width
  int16_t min = _source->getMin();
  int16_t max = _source->getMax();

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(_label);
  OLED.setCursor(127-6*_unitsLen,0);
  OLED.print(_units);
  OLED.setFont(&Numbers24pt7b);
  
  if(max!=min){
    uint8_t width = constrain(((long)value-min)*128/(max-min),0,128);
    OLED.drawFastVLine(0, 50, 14, 1);
    OLED.drawFastVLine(31,60,4,1);
    OLED.drawFastVLine(63,60,4,1);
    OLED.drawFastVLine(64,60,4,1);
    OLED.drawFastVLine(96,60,4,1);
    OLED.drawFastVLine(127,50,14,1);
    OLED.drawFastHLine(0,63,128,1);
    OLED.fillRect(0, 52, width, 8, 1);
    OLED.drawFastVLine(1,52,8,0);
    OLED.drawFastVLine(126,52,8,0);
    OLED.setCursor(centering,44);
  }
  else{
    OLED.setCursor(centering,56);
  }
  OLED.print(temp);
  OLED.setFont();
  OLED.display();
}

void Page::setLabel(char* label){
  strcpy(_label, label);
  _labelLen = strlen(_label);
}

void Page::setUnits(char* units){
  strcpy(_units, units);
  _unitsLen = strlen(_units);
}

void Page::initDisplay() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 60);
  OLED.display();
  delay(1000);
  OLED.setFont();
  OLED.setTextColor(WHITE);
}

void Page::defaultPage(uint8_t pageNum){
  OLED.clearDisplay();
  OLED.drawBitmap((128 - splash2_width) / 2, (64 - splash2_height) / 2,
               splash2_data, splash2_width, splash2_height, 1);
  OLED.setCursor(0,56);
  OLED.print(pageNum);
  OLED.display();
}