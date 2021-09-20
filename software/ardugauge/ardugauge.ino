#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"

/* Data sources*/
Data dataRPM(14,2,0,6000);
/* Pages*/
Page Page1(&dataRPM);

void setup() {
  Serial.begin(115200);
  Page::initDisplay();
  Page1.setLabel("Engine Speed");
  Page1.setUnits("RPM");
}

void loop() {
  Page1.display();
  // delay(100);
}