#include <SoftwareSerial.h>
#include "HCuOLED.h"
#include "SPI.h"
#define CS_DI 10
#define DC_DI 9
#define RST_DI 8

HCuOLED HCuOLED(SH1106, CS_DI, DC_DI, RST_DI);

unsigned int i = 0;
int mySt = 3;
char n[] = "1";
int numberAgain = 0;

void setup() {
  Serial.begin(9600);
  HCuOLED.Reset();
  
}

void loop() {
  
  HCuOLED.Cursor(mySt, 24);
  HCuOLED.SetFont(LCDLarge_24pt);

  if (Serial.available() > 0) {

 if (mySt >= 29875){
    mySt = 3;
    HCuOLED.Cursor(mySt, 24);
    HCuOLED.ClearBuffer();
}

    delay(100);
    Serial.print("I received: ");
    n[0] = Serial.read();
    //delay(300);
    Serial.println(n);
    Serial.println(numberAgain);
    
    HCuOLED.Print(n);
    
        for (int i=0; n>=i; i++)
    {
      mySt = mySt+12;
    }

  }

 if (n == 0){
    HCuOLED.ClearBuffer();
}
  
  HCuOLED.Rect(0, 0, 125, 63, OUTLINE);

  HCuOLED.Cursor(7, 4);
  HCuOLED.SetFont(MedProp_11pt);
  HCuOLED.Print("10 char. total");
      
  HCuOLED.Refresh();
  delay(50);

}
