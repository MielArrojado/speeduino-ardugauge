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
  char temp[16];
  uint8_t centering = centering24p(source,temp);

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setCursor(127-6*unitsLen,0);
  OLED.print(units);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(centering,51);
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
  char temp[16];
  uint8_t centering = centering24p(source,temp);
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
  drawHBar( 0, 50, 128, 14, width);
  OLED.display();
}

uint8_t centering24p(Data* source, char* buf){
  uint8_t valLen = 15;
  uint16_t factor = source->getFactor();
  int value = source->get();
  char temp[16];

  // get max character count
  sprintf(temp,"%d", source->getMin());
  valLen = strlen(temp);
  sprintf(temp,"%d", source->getMax());
  valLen = max(valLen,strlen(temp));
  // add space for decimal point
  if(factor!=1)valLen++;

  // calc center offset
  if (factor > 1){
    sprintf(temp,"%d",factor);
    dtostrf((float)value/factor,1+strlen(temp),strlen(temp)-1,buf);
  }
  else{
    sprintf(buf,"%d",value);
  }

  return (64-(12*valLen)+(valLen - strlen(buf))*24);
}

void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_w){
  uint8_t q0 = x;
  uint8_t q1 = x+(w-1)>>2;
  uint8_t q2 = x+(w-1)>>1;
  uint8_t q3 = x+3*((w-1)>>2);
  uint8_t q4 = x+w-1;

  OLED.drawFastVLine(q0,  y,    h,  SSD1306_WHITE);
  OLED.drawFastVLine(q1,  y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q2,  y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q2+1,y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q3,  y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q4,  y,    h,  SSD1306_WHITE);
  OLED.drawFastHLine(x,   y+h-1,w,  SSD1306_WHITE);
  OLED.fillRect(x,   y+2, bar_w,h-6,SSD1306_WHITE);
  OLED.drawFastVLine(q0+1,y+2,  h-6,SSD1306_BLACK);
  OLED.drawFastVLine(q4-1,y+2,  h-6,SSD1306_BLACK);
}