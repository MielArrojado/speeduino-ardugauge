#include "Arduino.h"
#include "Pages.h"
#include "Comms.h"
#include <Adafruit_SSD1306.h>
#include "Numbers24pt7b.h"
#include "splash.h"

Adafruit_SSD1306 OLED(128, 64, &Wire, -1);

void initDisplay()
{
  OLED.begin(SSD1306_SWITCHCAPVCC, 60);
  OLED.setFont();
  OLED.setTextColor(WHITE);
  showSplash("ARDUGAUGE");
  delay(1000);
}

void showSplash(char *message)
{
  OLED.clearDisplay();
  OLED.drawBitmap((128 - splash1_width) / 2, (64 - splash1_height) / 2,
                  splash1_data, splash1_width, splash1_height, 1);
  uint8_t offset = centering(message, 6);
  OLED.setCursor(offset, 56);
  OLED.print(message);
  OLED.display();
}

void showNumeric(char *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal)
{

  // allocate character space
  static char valString[22];
  formatValue(valString, value, decimal);
  uint8_t offset = centering(valString, 24, 128, maxChar(min_val, max_val, decimal));
  uint8_t width = constrain(map(value, min_val, max_val, 0, 128), 0, 128);

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(offset, 51);
  OLED.print(valString);
  OLED.setFont();
  OLED.display();
}

void showBar(char *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal)
{
  // allocate character space
  static char valString[22];
  formatValue(valString, value, decimal);
  uint8_t offset = centering(valString, 24, 128, maxChar(min_val, max_val, decimal));
  uint8_t width = constrain(map(value, min_val, max_val, 0, 128), 0, 128);

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(offset, 44);
  OLED.print(valString);
  OLED.setFont();
  drawHBar(0, 50, 128, 14, 8, width);
  OLED.display();
}

void show2Bar(char *label1, int16_t value1, int16_t min_val1, int16_t max_val1, uint8_t decimal1,
              char *label2, int16_t value2, int16_t min_val2, int16_t max_val2, uint8_t decimal2)

{

  // allocate character space
  static char valString1[22];
  formatValue(valString1, value1, decimal1);
  uint8_t offset1 = centering(valString1, 12, 128, maxChar(min_val1, max_val1, decimal1));
  uint8_t width1 = constrain(map(value1, min_val1, max_val1, 0, 128), 0, 128);

  static char valString2[22];
  formatValue(valString2, value2, decimal2);
  uint8_t offset2 = centering(valString2, 12, 128, maxChar(min_val2, max_val2, decimal2));
  uint8_t width2 = constrain(map(value2, min_val2, max_val2, 0, 128), 0, 128);

  OLED.clearDisplay();

  OLED.setCursor(0, 0);
  OLED.print(label1);
  // OLED.setFont(&Numbers24pt7b);
  OLED.setTextSize(2);
  OLED.setCursor(offset1, 9);
  OLED.print(valString1);
  // OLED.setFont();
  OLED.setTextSize(1);
  drawHBar(0, 23, 128, 8, 4, width1);

  OLED.setCursor(0, 33);
  OLED.print(label2);
  // OLED.setFont(&Numbers24pt7b);
  OLED.setTextSize(2);
  OLED.setCursor(offset2, 42);
  OLED.print(valString2);
  // OLED.setFont();
  OLED.setTextSize(1);
  drawHBar(0, 56, 128, 8, 4, width2);

  OLED.display();
}

uint8_t maxChar(int32_t min_val, int32_t max_val, uint8_t decimal)
{
  static char buf[22];
  uint8_t max_char = formatValue(buf, min_val, decimal);
  max_char = max(formatValue(buf, max_val, decimal), max_char);
  return max_char;
}

uint8_t formatValue(char *buf, int32_t value, uint8_t decimal)
{
  sprintf(buf, "%d", value);
  uint8_t len = strlen(buf);
  if (decimal != 0)
  {
    if (value != 0)
    {
      for (uint8_t i = 0; i < decimal + 1; i++)
      {
        buf[len - i] = buf[len - 1 - i];
        buf[len - 1 - i] = '.';
      }
    }
    else
    {
      for (uint8_t i = 0; i < decimal + 1; i++)
      {
        buf[len + 1 - i] = buf[len - 1 - i];
        buf[len - 1 - i] = '.';
      }
      buf[0] = '0';
    }
  }
}

uint8_t centering(char *buf, uint8_t c_width, uint8_t field_width, uint8_t max_char)
{
  if (max_char == 0)
  {
    max_char = strlen(buf);
  }
  return ((field_width - c_width * max_char) / 2 + (max_char - strlen(buf)) * c_width);
}

void drawHBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bar_h, uint8_t bar_w)
{
  uint8_t q0 = x;
  uint8_t q1 = x + (w - 1) >> 2;
  uint8_t q2 = x + (w - 1) >> 1;
  uint8_t q3 = x + 3 * ((w - 1) >> 2);
  uint8_t q4 = x + w - 1;
  uint8_t bar_y = (h - bar_h - 1) / 2 + y;

  OLED.drawFastVLine(q0, y, h, SSD1306_WHITE);
  OLED.drawFastVLine(q1, y + h - 5, 4, SSD1306_WHITE);
  OLED.drawFastVLine(q2, y + h - 5, 4, SSD1306_WHITE);
  OLED.drawFastVLine(q2 + 1, y + h - 5, 4, SSD1306_WHITE);
  OLED.drawFastVLine(q3, y + h - 5, 4, SSD1306_WHITE);
  OLED.drawFastVLine(q4, y, h, SSD1306_WHITE);
  OLED.drawFastHLine(x, y + h - 1, w, SSD1306_WHITE);
  OLED.fillRect(x, bar_y, bar_w, bar_h, SSD1306_WHITE);
  OLED.drawFastVLine(q0 + 1, bar_y, bar_h, SSD1306_BLACK);
  OLED.drawFastVLine(q4 - 1, bar_y, bar_h, SSD1306_BLACK);
}