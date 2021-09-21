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
Data dataVSS(100,2,0,0);
Data dataDwl(3,1,0,100);
Data dataAdv(23,1,-120,120);

/* Pages*/
Page Page0(&dataRPM, "Engine Speed", "RPM");
Page Page1(&dataMAP, "MAP", "kPa");
Page Page2(&data_O2, "AFR",":1");
Page Page3(&dataCLT, "Coolant Temp", "\'C");
Page Page4(&dataEOP, "Oil Pressure", "psi");
Page Page5(&dataVbt, "Battery", "V");
// Page Page6(&dataVSS, "Speed", "kph"); // speed
// Page Page7(&dataVbat,"AFR",":1"); // oil vs rpm
// Page Page8(&dataDwl, "Dwell","ms"); // dwell vs V
Page Page9(&dataAdv,"Advance",""); // adv vs rpm and map
// Page Page10(&dataVbat,"AFR",":1"); // 4 window fast
// Page Page11(&dataVbat,"AFR",":1"); // 4 window slow
// Page Page12(&dataVbat,"AFR",":1"); // status bits
// Page Page13(&dataVbat,"AFR",":1"); // 4 window system


void setup() {
  Serial.begin(115200);
  Page::initDisplay();
}

void loop() {
  static uint8_t pageNum = 0;
  static bool buttonLast = false;
  bool buttonNow = !digitalRead(2);
  if (buttonLast & !buttonNow){
    pageNum++;
  }
  buttonLast = buttonNow;

  switch(pageNum){
    case 0: Page0.display(); break;
    case 1: Page1.display(); break;
    case 2: Page2.display(); break;
    case 3: Page3.display(); break;
    case 4: Page4.display(); break;
    case 5: Page5.display(); break;
    case 6: Page::defaultPage(pageNum+1); break;
    case 7: Page::defaultPage(pageNum+1); break;
    case 8: Page::defaultPage(pageNum+1); break;
    case 9: Page::defaultPage(pageNum+1); break;
    case 10: Page::defaultPage(pageNum+1); break;
    case 11: Page::defaultPage(pageNum+1); break;
    case 12: Page::defaultPage(pageNum+1); break;
    case 13: Page::defaultPage(pageNum+1); break;
    
    default:
      Page0.display();
      pageNum = 0;
      break; 
  }
  // dataVSS.request(10);
  // dataDwl.request(10);
  // dataAdv.request(10);
  delay(10);
}