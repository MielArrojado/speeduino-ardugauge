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
  showSplash(F("ARDUGAUGE"));
  delay(1000);
}

void showSplash(const __FlashStringHelper *message)
{
  OLED.clearDisplay();
  OLED.drawBitmap((128 - splash1_width) / 2, (64 - splash1_height) / 2,
                  splash1_data, splash1_width, splash1_height, 1);
  uint8_t max_char = strlen_P(reinterpret_cast<const char *>(message));
  uint8_t offset = ((128 - 6 * max_char) / 2);
  OLED.setCursor(offset, 56);
  OLED.print(message);
  OLED.display();
}

void showNumeric(const __FlashStringHelper *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal)
{

  // allocate character space
  static char valString[22];
  formatValue(valString, value, decimal);
  uint8_t offset = centering(valString, 24, 128, maxChar(min_val, max_val, decimal));

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print(label);
  OLED.setFont(&Numbers24pt7b);
  OLED.setCursor(offset, 51);
  OLED.print(valString);
  OLED.setFont();
  OLED.display();
}

void showBar(const __FlashStringHelper *label, int16_t value, int16_t min_val, int16_t max_val, uint8_t decimal)
{
  // allocate character space
  static char valString[STRING_LENGTH];
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

void show2Bar(const __FlashStringHelper *label1, int16_t value1, int16_t min_val1, int16_t max_val1, uint8_t decimal1,
              const __FlashStringHelper *label2, int16_t value2, int16_t min_val2, int16_t max_val2, uint8_t decimal2)

{

  // allocate character space
  static char valString1[STRING_LENGTH];
  formatValue(valString1, value1, decimal1);
  uint8_t offset1 = centering(valString1, 12, 128, maxChar(min_val1, max_val1, decimal1));
  uint8_t width1 = constrain(map(value1, min_val1, max_val1, 0, 128), 0, 128);

  static char valString2[STRING_LENGTH];
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

void show4Numeric(const __FlashStringHelper *label1, int16_t value1, int16_t min_val1, int16_t max_val1, uint8_t decimal1,
                  const __FlashStringHelper *label2, int16_t value2, int16_t min_val2, int16_t max_val2, uint8_t decimal2,
                  const __FlashStringHelper *label3, int16_t value3, int16_t min_val3, int16_t max_val3, uint8_t decimal3,
                  const __FlashStringHelper *label4, int16_t value4, int16_t min_val4, int16_t max_val4, uint8_t decimal4)
{
  // allocate character space
  static char valString1[22];
  static char valString2[22];
  static char valString3[22];
  static char valString4[22];

  OLED.clearDisplay();
  OLED.drawFastHLine(0, 31, 128, SSD1306_WHITE);
  OLED.drawFastVLine(63, 0, 64, SSD1306_WHITE);

  if (strlen_P(reinterpret_cast<const char *>(label1)) != 0)
  {
    formatValue(valString1, value1, decimal1);
    uint8_t offset1 = centering(valString1, 12, 62, maxChar(min_val1, max_val1, decimal1));

    OLED.setCursor(0, 0);
    OLED.print(label1);
    // OLED.setFont(&Numbers24pt7b);
    OLED.setTextSize(2);
    OLED.setCursor(offset1, 12);
    OLED.print(valString1);
    // OLED.setFont();
    OLED.setTextSize(1);
  }

  if (strlen_P(reinterpret_cast<const char *>(label2)) != 0)
  {
    formatValue(valString2, value2, decimal2);
    uint8_t offset2 = centering(valString2, 12, 62, maxChar(min_val2, max_val2, decimal2));

    OLED.setCursor(0, 34);
    OLED.print(label2);
    // OLED.setFont(&Numbers24pt7b);
    OLED.setTextSize(2);
    OLED.setCursor(offset2, 46);
    OLED.print(valString2);
    // OLED.setFont();
    OLED.setTextSize(1);
  }

  if (strlen_P(reinterpret_cast<const char *>(label3)) != 0)
  {
    formatValue(valString3, value3, decimal3);
    uint8_t offset3 = centering(valString3, 12, 62, maxChar(min_val3, max_val3, decimal3));

    OLED.setCursor(66, 0);
    OLED.print(label3);
    // OLED.setFont(&Numbers24pt7b);
    OLED.setTextSize(2);
    OLED.setCursor(offset3 + 66, 12);
    OLED.print(valString3);
    // OLED.setFont();
    OLED.setTextSize(1);
  }

  if (strlen_P(reinterpret_cast<const char *>(label4)) != 0)
  {
    formatValue(valString4, value4, decimal4);
    uint8_t offset4 = centering(valString4, 12, 62, maxChar(min_val4, max_val4, decimal4));

    OLED.setCursor(66, 34);
    OLED.print(label4);
    // OLED.setFont(&Numbers24pt7b);
    OLED.setTextSize(2);
    OLED.setCursor(offset4 + 66, 46);
    OLED.print(valString4);
    // OLED.setFont();
    OLED.setTextSize(1);
  }

  OLED.display();
}

void showFlags(const __FlashStringHelper *label1, bool value1,
               const __FlashStringHelper *label2, bool value2,
               const __FlashStringHelper *label3, bool value3,
               const __FlashStringHelper *label4, bool value4,
               const __FlashStringHelper *label5, bool value5,
               const __FlashStringHelper *label6, bool value6,
               const __FlashStringHelper *label7, bool value7,
               const __FlashStringHelper *label8, bool value8)
{
  OLED.clearDisplay();

  drawFlag(label1, value1, 1, 1);
  drawFlag(label2, value2, 65, 1);
  drawFlag(label3, value3, 1, 17);
  drawFlag(label4, value4, 65, 17);
  drawFlag(label5, value5, 1, 33);
  drawFlag(label6, value6, 65, 33);
  drawFlag(label7, value7, 1, 49);
  drawFlag(label8, value8, 65, 49);

  OLED.display();
}

void drawFlag(const __FlashStringHelper *label, bool value, uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  if (strlen_P(reinterpret_cast<const char *>(label)) != 0)
  {
    uint8_t max_char = strlen_P(reinterpret_cast<const char *>(label));
    uint8_t x_offset = ((w - 6 * max_char) / 2);
    uint8_t y_offset = (h - 8) / 2;

    OLED.setCursor(x + x_offset, y + y_offset);
    OLED.print(label);

    OLED.setCursor(x, y);
    if (value)
    {
      OLED.fillRoundRect(x, y, w, h, 2, SSD1306_INVERSE);
    }
    else
    {
      OLED.drawRoundRect(x, y, w, h, 2, SSD1306_WHITE);
    }
  }
}

uint8_t maxChar(int32_t min_val, int32_t max_val, uint8_t decimal)
{
  static char buf[STRING_LENGTH];
  uint8_t max_char = formatValue(buf, min_val, decimal);
  max_char = max(formatValue(buf, max_val, decimal), max_char);
  return max_char;
}

uint8_t formatValue(char *buf, int32_t value, uint8_t decimal)
{
  // static char temp[STRING_LENGTH];
  // clearBuffer(temp);

  clearBuffer(buf);
  snprintf(buf, 22, "%d", value);
  uint8_t len = strlen(buf);

  if (decimal != 0)
  {
    uint8_t target = decimal + 1;
    uint8_t numLen = len - ((value < 0) ? 1 : 0);
    while (numLen < target)
    {
      for (uint8_t i = 0; i < numLen + 1; i++)
      // if negative, skip negative sign
      {
        buf[len - i + 1] = buf[len - i];
        buf[len - i] = '0';
      }
      buf[len + 1] = '\0';
      numLen++;
      len++;
    }
    // insert
    for (uint8_t i = 0; i < decimal + 1; i++)
    {
      buf[len - i + 1] = buf[len - i];
      buf[len - i] = '.';
    }
    // clearBuffer(buf);
    // snprintf(buf, STRING_LENGTH, "%d", target);
  }
  return strlen(buf);
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

void clearBuffer(char *buf, uint8_t bufLen)
{
  for (uint8_t i = 0; i < bufLen; i++)
  {
    buf[i] = '\0';
  }
}