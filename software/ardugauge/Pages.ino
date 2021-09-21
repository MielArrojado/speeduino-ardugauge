#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"
#include <Adafruit_SSD1306.h>
#include "Numbers24pt7b.h"
#include "splash.h"

Adafruit_SSD1306 OLED(128, 64, &Wire, -1);

void initDisplay() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 60);
  OLED.setFont();
  OLED.setTextColor(WHITE);
  showSplash("ARDUGAUGE");
  delay(1000);
}

void showSplash(char* message){
  OLED.clearDisplay();
  OLED.drawBitmap((128 - splash1_width) / 2, (64 - splash1_height) / 2,
               splash1_data, splash1_width, splash1_height, 1);
  uint8_t offset = centering(message,6);
  OLED.setCursor(offset, 56);
  OLED.print(message);
  OLED.display();
}

void showNumeric(Data &source, char* label, char* units){
  // get source data
  int16_t min = source.getMin();
  int16_t max = source.getMax();
  uint16_t factor = source.getFactor();
  source.request();
  int value = source.get();
  
  // allocate character space
  uint8_t unitsLen = strlen(units);
  char temp[16];
  uint8_t valLen = formatVal(source,temp);
  uint8_t offset = centering(temp, 24, 128, valLen);

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setCursor(127-6*unitsLen,0);
  OLED.print(units);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(offset,51);
  OLED.print(temp);
  OLED.setFont();
  OLED.display();
}

void showBar(Data &source, char* label, char* units){
  // get source data
  int16_t min = source.getMin();
  int16_t max = source.getMax();
  uint16_t factor = source.getFactor();
  source.request();
  int value = source.get();
  
  // allocate character space
  uint8_t unitsLen = strlen(units);
  char temp[16];
  uint8_t valLen = formatVal(source,temp);
  uint8_t offset = centering(temp, 24, 128, valLen);
  uint8_t width = constrain(((long)value-min)*128/(max-min),0,128);

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setCursor(127-6*unitsLen,0);
  OLED.print(units);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(offset,44);
  OLED.print(temp);
  OLED.setFont();
  drawHBar( 0, 50, 128, 14, 8, width);
  OLED.display();
}

// void show2Bar(Data* source1, char* label1, char* units1,
//               Data* source2, char* label2, char* units2){
//     // get source data
//   int16_t min1 = source1->getMin();
//   int16_t max1 = source1->getMax();
//   uint16_t factor1 = source1->getFactor();
//   int16_t min2 = source2->getMin();
//   int16_t max2 = source2->getMax();
//   uint16_t factor2 = source2->getFactor();
//   source1->request();
//   source2->request();
//   int value1 = source1->get();
//   int value2 = source2->get();
  
//   // allocate character space
//   uint8_t units1Len = strlen(units1);
//   char temp1[16];
//   uint8_t valLen1 = formatVal(source1,temp1);
  // uint8_t offset1 = centering(temp1, 24, 128, valLen1);
//   uint8_t width1 = constrain(((long)value1-min1)*128/(max1-min1),0,128);
  
//   uint8_t units2Len = strlen(units2);
//   char temp2[16];
//   uint8_t valLen2 = formatVal(source2,temp2);
  // uint8_t offset2 = centering(temp2, 24, 128, valLen2);
//   uint8_t width2 = constrain(((long)value2-min2)*128/(max2-min2),0,128);

//   OLED.clearDisplay();

//   OLED.setCursor(0, 0);
//   OLED.print(label1);
//   OLED.setCursor(127-6*units1Len,0);
//   OLED.print(units1);
//   // OLED.setFont(&Numbers24pt7b);
//   OLED.setTextSize(2);
//   OLED.setCursor(offset1,9);
//   OLED.print(temp1);
//   // OLED.setFont();
//   OLED.setTextSize(1);
//   drawHBar( 0, 23, 128, 8, 4, width1);

//   OLED.setCursor(0, 33);
//   OLED.print(label2);
//   OLED.setCursor(127-6*units2Len,33);
//   OLED.print(units2);
//   // OLED.setFont(&Numbers24pt7b);
//   OLED.setTextSize(2);
//   OLED.setCursor(offset2,42);
//   OLED.print(temp2);
//   // OLED.setFont();
//   OLED.setTextSize(1);
//   drawHBar( 0, 56, 128, 8, 4, width2);

//   OLED.display();
  
// }

uint8_t formatVal(Data &source, char* buf){
  uint8_t valLen = 15;
  uint16_t factor = source.getFactor();
  int value = source.get();
  char temp[16];

  // get max character count
  sprintf(temp,"%d", source.getMin());
  valLen = strlen(temp);
  sprintf(temp,"%d", source.getMax());
  valLen = max(valLen,strlen(temp));
  // add space for decimal point
  if(factor!=1)valLen++;

  // write string to buf 
  if (factor > 1){
    sprintf(temp,"%d",factor);
    dtostrf((float)value/factor,1+strlen(temp),strlen(temp)-1,buf);
  }
  else{
    sprintf(buf,"%d",value);
  }

  // return val length
  return valLen;
}

uint8_t centering(char* buf, uint8_t c_width, uint8_t field_width, uint8_t min_len){
  if (min_len == 0) {min_len = strlen(buf);}
  return ((field_width-c_width*min_len)/2+(min_len - strlen(buf))*c_width);
}

void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_h, uint8_t bar_w){
  uint8_t q0 = x;
  uint8_t q1 = x+(w-1)>>2;
  uint8_t q2 = x+(w-1)>>1;
  uint8_t q3 = x+3*((w-1)>>2);
  uint8_t q4 = x+w-1;
  uint8_t bar_y = (h-bar_h-1)/2+y;

  OLED.drawFastVLine(q0,  y,    h,  SSD1306_WHITE);
  OLED.drawFastVLine(q1,  y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q2,  y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q2+1,y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q3,  y+h-5,4,  SSD1306_WHITE);
  OLED.drawFastVLine(q4,  y,    h,  SSD1306_WHITE);
  OLED.drawFastHLine(x,   y+h-1,w,  SSD1306_WHITE);
  OLED.fillRect(x,   bar_y, bar_w,bar_h,SSD1306_WHITE);
  OLED.drawFastVLine(q0+1,bar_y,  bar_h,SSD1306_BLACK);
  OLED.drawFastVLine(q4-1,bar_y,  bar_h,SSD1306_BLACK);
}