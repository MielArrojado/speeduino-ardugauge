#include "Arduino.h"
#include "Pages.h"
#include "DataClass.h"

/* Data sources*/
Data dataRPM(14,2,0,6000);  // ok
Data dataMAP(4,2,0,120);    //ok
Data data_O2(10,1,70,200,10);   //ok
Data dataCLT(7,1,0,120);        // not ok
Data dataEOP(104, 1, 0, 100);   // ok
Data dataVbt(9,1,60, 160,10);   // not ok
Data dataVSS(100,2,0,1000);     // ok
Data dataDwl(3,1,0,100,10);     // not ok;
Data dataAdv(23,1,-20,20,1,true);

void setup() {
  Serial.begin(115200);
  initDisplay();

  // calibration for CLT
  dataCLT.setScale(5.0/9);
  dataCLT.setOffset(-(32*5)/9);
  dataRPM.setValue(2006);
}

void loop() {
  static uint8_t pageNum = 0;
  static bool buttonLast = false;
  bool buttonNow = !digitalRead(2);
  digitalWrite(LED_BUILTIN,buttonNow);
  if (buttonLast & !buttonNow){
    pageNum++;
  }
  buttonLast = buttonNow;

  switch(pageNum){
    case 0: showBar(dataRPM, "Engine Speed", "RPM"); break;
    case 1: showBar(dataMAP, "MAP", "kPa"); break;
    case 2: showBar(data_O2, "AFR",":1"); break;
    case 3: showBar(dataCLT, "Coolant Temp", "\'C"); break;
    case 4: showBar(dataEOP, "Oil Pressure", "PSI"); break;
    case 5: showBar(dataVbt, "Battery", "V"); break;
    case 6: showNumeric(dataVSS, "Speed", "kph"); break;
    // case 7: show2Bar(&dataRPM, "Engine Speed","RPM",
    //                  &dataEOP, "Oil Pressure", "PSI"); break;
    case 7: showSplash("EOP vs RPM"); break;
    // case 8: show2Bar(&dataDwl, "Dwell","ms",
    //                  &dataVbt, "Battery", "V"); break;
    case 8: showBar(dataDwl, "Dwell","ms"); break;
    case 9: showBar(dataAdv,"Advance","deg");break;
    // case 10: showSplash("4W RPM map o2 adv"); break;
    // case 11: showSplash("4W RPM oil volt clt"); break;
    // case 12: showSplash("system"); break;
    // case 13: showSplash("status"); break;
    
    default:
      // showSplash("default"); break;
      pageNum = 0;
      break; 
  }
  delay(100);
}