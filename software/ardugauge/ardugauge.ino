#include "Arduino.h"
#include "Pages.h"
#include "Comms.h"
#define N_PAGES 10

/* Data sources*/
// Data dataDwl = {3, 1, 0, 100, 10, false, "Dwell (ms)"};

void setup()
{
  Serial.begin(115200);
  initDisplay();
}

void loop()
{
  static uint16_t pageNum = 0;
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
  int16_t value = 0;

  switch (pageNum)
  {
  case 0:
    showBar("Engine Speed (RPM)", getWord(14), 0, 6000);
    break;
  case 1:
    showBar("MAP (kPa)", getWord(4), 0, 101);
    break;
  case 2:
    showBar("AFR", getByte(10), 60, 200, 1);
    break;
  case 3:
    value = (((int32_t)getByte(7) - 32) * 500) / 900;
    showBar("Coolant Temp (\367C)", value, 0, 120);
    break;
  case 4:
    showBar("Oil Pressure (psi)", getByte(104), 0, 100);
    break;
  case 5:
    showBar("Battery (V)", getByte(9), 60, 160, 1);
    break;
  case 6:
    showNumeric("Speed (kph)", getWord(100), 0, 300);
    break;
  case 7:
    showSplash("Oil Pressure vs RPM");
    // show2Bar("Oil Pressure (psi)", getByte(104), 0, 100, 0,
    //          "Engine Speed (RPM)", getWord(14), 0, 6000, 0);
    break;
  case 8:
    showBar("Dwell(ms)", getByte(3), 0, 200, 1);
    // show2Bar("Dwell(ms)", getByte(3), 0, 200, 1,
    //  "Battery (V)", getByte(9), 60, 160, 1);
    break;
  case 9:
    showBar("Advance (deg)", (int8_t)getByte(23), -10, 40);
    break;
  default:
    showSplash("Coming Soon!");
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