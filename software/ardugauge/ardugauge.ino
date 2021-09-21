#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"

/* Data sources*/
Data dataRPM(14,2,0,6000);
Data dataMAP(4,2,0,120);
Data data_O2(10,1,0,20);
Data dataCLT(7,1,0,120);
Data dataEOP(104, 1, 0, 100);
Data dataVbt(9,1,6, 16);
Data dataVSS(100,2,0,1000);
Data dataDwl(3,1,0,100);
Data dataAdv(23,1,-120,120);

/* Pages*/
// Page Page0(&dataRPM, "Engine Speed", "RPM");
// Page Page1(&dataMAP, "MAP", "kPa");
// Page Page2(&data_O2, "AFR",":1");
// Page Page3(&dataCLT, "Coolant Temp", "\'C");
// Page Page4(&dataEOP, "Oil Pressure", "psi");
// Page Page5(&dataVbt, "Battery", "V");
// Page Page6(&dataVSS, "Speed", "kph"); // speed
// Page Page7(&dataVbat,"AFR",":1"); // oil vs rpm
// Page Page8(&dataDwl, "Dwell","ms"); // dwell vs V
// Page Page9(&dataAdv,"Advance",""); // adv vs rpm and map
// Page Page10(&dataVbat,"AFR",":1"); // 4 window fast
// Page Page11(&dataVbat,"AFR",":1"); // 4 window slow
// Page Page12(&dataVbat,"AFR",":1"); // status bits
// Page Page13(&dataVbat,"AFR",":1"); // 4 window system


void setup() {
  Serial.begin(115200);
  initDisplay();
}

void loop() {
  static uint8_t pageNum = 6;
  static bool buttonLast = false;
  bool buttonNow = !digitalRead(2);
  if (buttonLast & !buttonNow){
    pageNum++;
  }
  buttonLast = buttonNow;

  switch(pageNum){
    case 0: showBar(&dataRPM, "Engine Speed", "RPM"); break;
    case 1: showBar(&dataMAP, "MAP", "kPa"); break;
    case 2: showBar(&data_O2, "AFR",":1"); break;
    case 3: showBar(&dataCLT, "Coolant Temp", "\'C"); break;
    case 4: showBar(&dataEOP, "Oil Pressure", "psi"); break;
    case 5: showBar(&dataVbt, "Battery", "V"); break;
    case 6: showNumeric(&dataVSS, "Speed", "kph"); break;
    case 7: showSplash("Oil vs RPM"); break;
    case 8: showSplash("Dwell vs Voltage"); break;
    case 9: showSplash("2D Advance, rpm, map"); break;
    case 10: showSplash("4W RPM map o2 adv"); break;
    case 11: showSplash("4W RPM oil volt clt"); break;
    case 12: showSplash("system"); break;
    case 13: showSplash("status"); break;
    
    default:
      showBar(&dataRPM, "Engine Speed", "RPM");
      pageNum = 0;
      break; 
  }
  // dataVSS.request(10);
  // dataDwl.request(10);
  // dataAdv.request(10);
  delay(10);
}