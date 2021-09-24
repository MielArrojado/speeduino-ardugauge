#include "Arduino.h"
#include "Pages.h"
#include "Comms.h"
#define N_PAGES 12

void setup()
{
  Serial.begin(115200);
  initDisplay();
}

void loop()
{
  static uint16_t pageNum = 10;
  static bool buttonLast = false;
  bool buttonNow = !digitalRead(2);
  digitalWrite(LED_BUILTIN, buttonNow);
  if (buttonLast & !buttonNow)
  {
    pageNum++;
    if (pageNum >= N_PAGES)
      pageNum = 0;
  }
  buttonLast = buttonNow;
  int16_t value = (((int32_t)getByte(7) - 32) * 500) / 900;

  switch (pageNum)
  {
  case 0:
    showBar(F("Engine Speed (RPM)"), getWord(14), 0, 6000);
    break;
  case 1:
    showBar(F("MAP (kPa)"), getWord(4), 0, 101);
    break;
  case 2:
    showBar(F("AFR"), getByte(10), 80, 210, 1);
    break;
  case 3:
    showBar(F("Coolant Temp (\367C)"), value, 0, 120);
    break;
  case 4:
    showBar(F("Oil Pressure (psi)"), getByte(104), 0, 100);
    break;
  case 5:
    showBar(F("Battery (V)"), getByte(9), 60, 160, 1);
    break;
  case 6:
    showNumeric(F("Speed (kph)"), getWord(100), 0, 300);
    break;
  case 7:
    show2Bar(F("Oil Pressure (psi)"), getByte(104), 0, 100, 0,
             F("Engine Speed (RPM)"), getWord(14), 0, 6000, 0);
    break;
  case 8:
    show2Bar(F("Dwell(ms)"), getByte(3), 0, 200, 1,
             F("Battery (V)"), getByte(9), 60, 160, 1);
    break;
  case 9:
    showBar(F("Advance (deg)"), (int8_t)getByte(23), -10, 40);
    break;
  case 10:
    show4Numeric(F("RPM"), getWord(14), 0, 6000, 0,
                 F("MAP (kpa)"), getWord(4), 0, 120, 0,
                 F("AFR"), getByte(10), 80, 210, 1,
                 F("Adv (deg)"), (int8_t)getByte(23), -10, 40, 0);
    //  F(""), 0, 0, 1, 0);
    break;
  case 11:
    show4Numeric(F("CLT (\367C)"), value, 0, 120, 0,
                 F("EOP (psi)"), getByte(104), 0, 100, 0,
                 F("Batt (V)"), getByte(9), 60, 160, 1,
                 //  F(""), 0, 0, 1, 0);
                 F("Dwell (ms)"), (int8_t)getByte(23), -10, 40, 0);

    break;
  default:
    showSplash(F("Coming Soon!"));
    break;
  }

  // timed update rate
  static uint32_t lastUpdate = millis();
  if (millis() - lastUpdate > 200)
  {
    requestData(50);
    lastUpdate = millis();
  }
}