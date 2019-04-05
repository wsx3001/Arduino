#include <SoftwareSerial.h>
#include <U8g2lib.h>
#include <OneWire.h> //ds18b20

#define CS_DI 10 //CS_DI = 10
#define DC_DI 9 //DC_DI = 9
#define RST_DI 8 //RST_DI = 8

U8G2_SH1106_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, CS_DI, 9, 8); // Пины панели
OneWire ds(2); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком

char* n[] = {"First 1"};
int strDisp = 5; //Старт с 5 - загрузка, 0 - select menu,
int timer1 = 5;
int plus = 2;
int led = 7; //Пин светодиод

void setup(void) {
  u8g2.begin(); //Начало
  Serial.begin(9600);
  pinMode(led, OUTPUT); //Диод
}
void load(int a){
// Загрузка c анимкой
    int offset = a;

    if (offset >= 1){
        u8g2.clearBuffer();
      u8g2.drawStr(8,40,"/home/file/screan.h");
    }
        if (offset >= 50){
            u8g2.clearBuffer();
      u8g2.drawStr(8,40,"/home/file/bomb.h");
    }
            if (offset >= 60){
                u8g2.clearBuffer();
       u8g2.drawStr(8,40,"/home/file/load.h");
    }
        
            if (offset >= 80){
                u8g2.clearBuffer();
       u8g2.drawStr(8,40,"/home/doc/qwert.h");
    }
        u8g2.setFont(u8g2_font_courB18_tr);
    u8g2.drawStr(18,20,"Load...");
    u8g2.setFont(u8g2_font_6x13_tr ); 
    
    u8g2.drawBox(18,54,1+offset,5); //Горизонтальная, вертикальная, длина, высота
    u8g2.drawFrame(15,50,96,12);
    
}

void selectMenu(void){
  //Меню выбора (да/нет)

    u8g2.setFont(u8g2_font_7x14B_tf);
    u8g2.drawStr(12,20,"LETS CHECK YOUR");
    
    u8g2.setFont(u8g2_font_7x14B_tf);
    u8g2.drawStr(20,35,"TEMPERATURE?");

    u8g2.setFont(u8g2_font_7x14B_tf);
    u8g2.drawStr(8,52,"(1 - yes/2 - no)");
    
    }
void checkUART (void){
  //Проверяет uart
      if (Serial.available() > 0) {
        strDisp = 0;
        strDisp = Serial.read() - '0'; // '0' - Не понял, но работает...
    }
      //Serial.println(strDisp); //Для дебага.
      delay(500);
  
}
void TouchWifu(void){
  
  //Как этот кусок работает!?!?
  
  char timer1_str[3];
   strcpy(timer1_str, u8x8_u8toa(timer1, 2));    /* convert m to a string with two digits */
   u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_9x15B_mr );
      u8g2.drawStr(13,20,"DON'T TOUCH");
      u8g2.drawStr(36,35,"SENSOR");
      u8g2.drawStr(2,60,"turn after: ");
      u8g2.drawStr(101,60,timer1_str);
        } while ( u8g2.nextPage() );
        
    delay(1000);
    timer1--;
    if ( timer1 == 0 ){
      timer1 = 5;
      strDisp = 4; //Выходит из TouchWifu
    }

}

void ds18(int b){

  digitalWrite(led, HIGH);
  
  byte data[2]; // Место для значения температуры
  
    ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
    ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
    ds.write(0x44); // Даем датчику DS18b20 команду и ературы мы еще не получаем - датчик его положит во внутреннюю память
  
    delay(500); // Микросхема измеряет температуру, а мы ждем.  
  
    ds.reset(); // Теперь готовимся получить значение измеренной температуры
    ds.write(0xCC); 
    ds.write(0xBE); // Просим передать нам значение регистров со значением температуры

    // Получаем и считываем ответ
    data[0] = ds.read(); // Читаем младший байт значения температуры
    data[1] = ds.read(); // А теперь старший

    // Формируем итоговое значение: 
    //    - сперва "склеиваем" значение, 
    //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
    float temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  
    // Выводим полученное значение температуры в монитор порта
    //Serial.println(temperature);
    
        //Панель справа
      if (temperature < 24){
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.drawStr(53,17, "Very cold");
        u8g2.drawStr(53,30, "it's bad");

        u8g2.setFont(u8g2_font_unifont_t_symbols);
        u8g2.drawGlyph(102, 50, 0x2603);

      }
      if (temperature >=24){
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.drawStr(53,17, "It's good");
        u8g2.drawStr(53,30, "for home");
        
        u8g2.setFont(u8g2_font_unifont_t_symbols);
        u8g2.drawGlyph(102, 50, 0x2714);
      }
      if (temperature >=28){
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.drawStr(53,17, "It's okey");
        u8g2.drawStr(49,30, "for sunday");

        u8g2.setFont(u8g2_font_unifont_t_symbols);
        u8g2.drawGlyph(102, 50, 0x2615);
      }
 
      int offset = b;
      //Правая панель
      u8g2.setFont(u8g2_font_7x14B_tf);
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_profont17_mn);
      
      u8g2.setCursor(50, 50);
      u8g2.setFontMode(1);
      u8g2.setDrawColor(2);
      u8g2.print(temperature); //Может выводить float. Если требуется вывести данные принимаемые через переменую, использовать print.
      u8g2.drawBox(48,35,50,20);

      //Шкала
      u8g2.drawBox(3,4,40,(temperature-20) * 3); //Температура с датчика - 20 (начало диапазона, который надо отобразить),*3 - 45 /15, где 15 - 
      u8g2.drawFrame(1,2,44,54);
      u8g2.drawFrame(47,2,77,54);

      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_7x14B_tf);
      u8g2.setDrawColor(2);
      u8g2.drawStr(9,15, "COLD");// Не может выводить float.
      u8g2.drawStr(9,32, "NORM");
      u8g2.drawStr(13,50, "HOT");   
      
      digitalWrite(led, LOW);
}

void loop(void) {
   //Вывод
  u8g2.clearBuffer();

if (strDisp == 5){ //Загрузка. 5 - это меню загрузки
    load(plus); 
  plus++;
  plus = plus +10;
  delay(10);
    if (plus >= 90){
    strDisp = 0;
    u8g2.clearBuffer();
     }
}

  checkUART();
  if (strDisp == 0){ // 0 - это меню выбора
      selectMenu();
  }


  if (strDisp == 1){ // 1 - это не трогай сеноср через 5 сек.
    TouchWifu();
  }

  if (strDisp == 4){ //Загрузка. 5 - это меню загрузки
  ds18(plus);
  plus++;
  //delay(100);
    if (plus >= 42){
    plus = 0;
     }
}
  
  u8g2.sendBuffer();
  
}
