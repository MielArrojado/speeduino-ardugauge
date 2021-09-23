#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"

/* Data sources*/
Data dataRPM = {14, 2, 0, 6000, 1, false, "Engine Speed (RPM)"};
Data dataMAP = {4, 2, 0, 120, 1, false, "MAP (kPa)"};
Data data_O2 = {10, 1, 70, 200, 10, false, "AFR"};
Data dataCLT = {7, 1, 0, 120, 1, false, "Coolant Temp (\367C)"};
Data dataEOP = {104, 1, 0, 100, 1, false, "Oil Pressure (psi)"};
Data dataVbt = {9, 1, 60, 160, 10, false, "Battery (V)"};
Data dataVSS = {100, 2, 0, 1000, 1, false, "Speed (kph)"};
Data dataDwl = {3, 1, 0, 100, 10, false, "Dwell (ms)"};
Data dataAdv = {23, 1, -20, 20, 1, true, "Advance (deg)"};

void setup()
{
  Serial.begin(115200);
  initDisplay();
}

void loop()
{
  static uint8_t pageNum = 0;
  static bool buttonLast = false;
  bool buttonNow = !digitalRead(2);
  digitalWrite(LED_BUILTIN, buttonNow);
  if (buttonLast & !buttonNow)
  {
    pageNum++;
  }
  buttonLast = buttonNow;

  switch (pageNum)
  {
  case 0:
    showBar(dataRPM);
    break;
  case 1:
    showBar(dataMAP);
    break;
  case 2:
    showBar(data_O2);
    break;
  case 3:
    showBar(dataEOP);
    break;
  case 4:
    showBar(dataVbt);
    break;
  case 5:
    showBar(dataAdv);
    break;
  default:
    pageNum = 0;
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