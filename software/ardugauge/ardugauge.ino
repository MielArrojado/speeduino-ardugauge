#include <EEPROM.h>
#include "Arduino.h"
#include "Pages.h"
#include "Comms.h"
#define N_PAGES 10

uint8_t pageNum = EEPROM.read(0);

void setup()
{
  Serial.begin(115200);
  initDisplay();
  if (pageNum >= N_PAGES)
  {
    pageNum = 0;
    EEPROM.update(0, pageNum);
  }
}

void loop()
{
  // button and page number operations
  static bool buttonLast = false;
  bool buttonNow = !digitalRead(2);
  digitalWrite(LED_BUILTIN, buttonNow);
  if (buttonLast & !buttonNow)
  {
    pageNum = EEPROM.read(0);
    pageNum++;
    if (pageNum >= N_PAGES)
      pageNum = 0;
    EEPROM.update(0, pageNum);
  }
  buttonLast = buttonNow;

  // serial operation, frequency based request
  static uint32_t lastUpdate = millis();
  if (millis() - lastUpdate > 10)
  {
    requestData(50);
    lastUpdate = millis();
  }

  // get refresh rate
  static uint32_t lastRefresh = millis();
  uint16_t refreshRate = 1000 / (millis() - lastRefresh);
  lastRefresh = millis();

  // display pages
  switch (pageNum)
  {
  case 0:
    showBar(F("Engine Speed (RPM)"), getWord(14), 0, 6000);
    break;
  case 1:
    showBar(F("MAP (kPa)"), getWord(4), 0, 101);
    break;
  case 2:
    showBar(F("Coolant Temp (\367C)"), (int16_t)getByte(7) - 40, 0, 120);
    break;
  case 3:
    showBar(F("Battery (V)"), getByte(9), 60, 160, 1);
    break;
  case 4:
    showNumeric(F("Speed (kph)"), getWord(100), 0, 300);
    break;
  case 5:
    show2Bar(F("Oil Pressure (psi)"), getByte(104), 0, 100, 0,
             F("Engine Speed (RPM)"), getWord(14), 0, 6000, 0);
    break;
  case 6:
    show4Numeric(F("RPM"), getWord(14), 0, 6000, 0,
                 F("MAP (kpa)"), getWord(4), 0, 120, 0,
                 F("AFR"), getByte(10), 80, 210, 1,
                 F("Adv (deg)"), (int8_t)getByte(23), -10, 40, 0);
    break;
  case 7:
    show4Numeric(F("CLT (\367C)"), (int16_t)getByte(7) - 40, 0, 120, 0, // temp offset by 40
                 F("EOP (psi)"), getByte(104), 0, 100, 0,
                 F("Batt (V)"), getByte(9), 60, 160, 1,
                 F("Dwell (ms)"), (int8_t)getByte(3), 0, 200, 1);
    break;
  case 8:
    showFlags(F("crank"), getBit(2, 1),
              F("RUN"), getBit(2, 0),
              F("sync"), getBit(31, 7),
              F("warm"), getBit(2, 3),
              F(""), false,
              F(""), false,
              F(""), false,
              F(""), false);
    break;
  case 9:
    show4Numeric(F("Cycles/sec"), getWord(25), 0, 1000, 0,
                 F("Mem (b)"), getWord(27), 0, 2048, 0,
                 F("FPS"), refreshRate, 0, 100, 0,
                 F(""), 0, 0, 100, 0);
    break;
  default:
    showSplash(F("Coming Soon!"));
    break;
  }
}