/**
*
* тачпад на модулях MPR121
* к сенсорам модулей припаяны лакированные провода
* которые создают матрицу.
* в местах пересечений они изолированы
* принцип - отследить нажатие 2 пересекающихся проводов
* эта программа просто пример
*
*
* 20.05.2025
* Mitroshin Aleksey (miam.devsoft@yandex.ru, lapadaviloff@yandex.ru)
*
*/



#include <Wire.h>
#include "Adafruit_MPR121.h"




Adafruit_MPR121 senseCol = Adafruit_MPR121();
Adafruit_MPR121 senseRow = Adafruit_MPR121();

#define MPR121_ADDRCOL 0x5a
#define MPR121_ADDRROW 0x5b
#define PRINT_DELAY 100

int16_t toucPadColibrate[12][12]; //-калибровачный массив фона
int16_t  touchPad[12][12];//- считываемый массив
byte sens = 30; //- чуствительность, чем меньше, тем чуствмтельнее

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  if(!senseCol.begin(MPR121_ADDRCOL))
  {
  Serial.println("Error setting up MPR121");
  while(1);
  }
   if(!senseRow.begin(MPR121_ADDRROW))
  {
  Serial.println("Error setting up MPR121");
  while(1);
}

 delay(200);
 touchPadRead(toucPadColibrate);

}

void loop()
{
  touchPadRead(touchPad);
  touchPadPrint();
  
}

void touchPadPrint()
{
 for(uint8_t i=0; i<12; i++)
  {
     for(uint8_t j=0; j<12; j++)
  {
     if ((toucPadColibrate[i][j] - touchPad[i][j]) > sens ) Serial.print("1");
   else Serial.print("0");
   Serial.print(" ");
  }
   Serial.print("\n"); 
  delay(PRINT_DELAY);
  }


}


void touchPadRead(int16_t touchPadMass [][12])
{
 
  for(uint8_t i=0; i<12; i++)
  {
   for(uint8_t j=0; j<12; j++)
   {
    touchPadMass[i][j] = senseCol.filteredData(i)+senseRow.filteredData(j);
   }
  }

}

