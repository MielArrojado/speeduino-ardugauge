#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"

#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 OLED(128, 64, &Wire, -1);

Page::Page(Data* source) {
  _source = source;
  strcpy(_label, "");
  strcpy(_units, "");
  char temp[16];
  sprintf(temp,'%d', _source->getMin());
  _valLen = strlen(temp);
  sprintf(temp,'%d', _source->getMax());
  _valLen = max(_valLen,strlen(temp));
  Serial.println(_source->getMax());
}

void Page::display() {
  _source->request(10);
  int value = _source->get();

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(_label);
  OLED.setCursor(128-6*_unitsLen,0);
  OLED.print(_units);
  OLED.setCursor(0,8);
  OLED.setTextSize(2);
  OLED.print(value);
  OLED.setTextSize(1);
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