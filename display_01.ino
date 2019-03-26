#include <SoftwareSerial.h>
#include "HCuOLED.h"
#include "SPI.h"
#define CS_DI 10
#define DC_DI 9
#define RST_DI 8

HCuOLED HCuOLED(SH1106, CS_DI, DC_DI, RST_DI); // For SH1106 displays (HCMODU0058 & HCMODU0059)

unsigned int i = 0;
int mySt = 3;
char n[] = "1";
int numberAgain = 0;

void setup() {
  Serial.begin(9600);
  HCuOLED.Reset();
  
}

void loop() {


//Осталось

/*
  for(int a = 0; numberAgain <= 10 ; a++){
    
      numberAgain = numberAgain++;
      HCuOLED.Cursor(45, 4);
      HCuOLED.SetFont(MedProp_11pt);
      HCuOLED.Print("Last");
      HCuOLED.Print(numberAgain);
      
      if (numberAgain > 10){
        HCuOLED.ClearBuffer();
        numberAgain = 0;
      }
  }
*/
  
  HCuOLED.Cursor(mySt, 24);
  HCuOLED.SetFont(LCDLarge_24pt);

  //int meSerial = Serial.available();

  if (Serial.available() > 0) {

 if (mySt >= 29875){
    mySt = 3;
    HCuOLED.Cursor(mySt, 24);
    HCuOLED.ClearBuffer();
}

    //HCuOLED.Print(n); // Не выводит последний символ

    delay(100);
    Serial.print("I received: ");
    n[0] = Serial.read();
    //delay(300);
    Serial.println(n);
    Serial.println(numberAgain);
    //Serial.println(mySt); // для дебага
    //delay(300);
    
    HCuOLED.Print(n); // Выводит все.
    
        for (int i=0; n>=i; i++)
    {
      mySt = mySt+12;
    }

  }

//Если n = `, то чистим буфер

 if (n == 0){
    HCuOLED.ClearBuffer();
}

  //HCuOLED.Print(n);
  
//  for (i = 0; i > 5; i++) {
//  Serial.print("I for: ");
 // Serial.print(n);
//
//}
  
  HCuOLED.Rect(0, 0, 125, 63, OUTLINE);

  HCuOLED.Cursor(7, 4);
  HCuOLED.SetFont(MedProp_11pt);
  HCuOLED.Print("10 char. total");
      
  HCuOLED.Refresh();
  //HCuOLED.ClearBuffer();
  delay(50);

}
