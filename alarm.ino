#include <Wire.h>
#include<EEPROM.h>
#include "RTClib.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <dht.h>
#define dataPin 8
dht DHT;

RTC_DS1307 RTC;
int temp, inc, hours1, minut, add = 11;

//int next = 10;
//#define next 7
int INC = 11;
int set_mad = 12;
//int flag1 = 0;
#define buzzer 13

int HOUR, MINUT, SECOND;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  lcd.begin();  
  lcd.backlight();
  pinMode(INC, INPUT);
  //pinMode(next, INPUT);
  pinMode(set_mad, INPUT);
  pinMode(buzzer, OUTPUT);
 // digitalWrite(next, HIGH);
  digitalWrite(set_mad, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(buzzer, LOW);


  if (!RTC.isrunning())
  {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop()
{
int readData = DHT.read11(dataPin); // Reads the data from the sensor
  int t = DHT.temperature; // Gets the values of the temperature
  int h = DHT.humidity;
  
  int temp = 0, val = 1, temp4;
  DateTime now = RTC.now();
  if (digitalRead(set_mad) == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("  Set Alarm  ");
    delay(2000);
    defualt();
    time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Alarm time ");
    lcd.setCursor(0, 1);
    lcd.print(" has been set  ");
    delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T");
  lcd.setCursor(2, 0);
  lcd.print(HOUR = now.hour(), DEC);
  lcd.print(":");
  lcd.print(MINUT = now.minute(), DEC);
  lcd.print(":");
  lcd.print(SECOND = now.second(), DEC);

  lcd.print(" ");
lcd.print("T:");
lcd.print(t);
lcd.print("C");

  
  lcd.setCursor(0, 1);
  lcd.print("D ");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);

  lcd.print(" ");
lcd.print("H:");
lcd.print(h);
lcd.print("%");
//  if (now.hour() == 13 && now.minute() == 45){
//      beep();
//      beep();}
  match();
  
  delay(200);
}

void defualt()
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

void time()
{
  int temp = 1, minuts = 0, hours = 0, seconds = 0;
  while (temp == 1)
  {
     
    if (digitalRead(INC) == 0)
    {
      HOUR++;
//      Serial.print("hr: ");
//      Serial.println(HOUR);
      if (HOUR == 24)
      {
         
        HOUR = 0;
      }
      while (digitalRead(INC) == 0);

    }
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Alarm Time ");
    //lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);

   // lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("  ");
//    lcd.print(":");
//    lcd.print(MINUT);
//    lcd.print(":");
//    lcd.print(SECOND);
//    delay(100);
    
//    if (digitalRead(next) == 0)
    if (digitalRead(set_mad) == 0)
    {
      hours1 = HOUR;
      EEPROM.write(add++, hours1);
      temp = 2;
//      Serial.print("temp in if: ");
//      Serial.println(temp);
//      while (digitalRead(next) == 0);
      while (digitalRead(set_mad) == 0);
    }
//     Serial.print("temp out if: ");
//      Serial.println(temp);
  }

  while (temp == 2)
  {
    if (digitalRead(INC) == 0)
    {
      MINUT++;
      if (MINUT == 60)
      {
        MINUT = 0;
      }
      while (digitalRead(INC) == 0);
      
    }
    // lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);

    lcd.setCursor(0,1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print("  ");
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);

    
//    if (digitalRead(next) == 0)
    if (digitalRead(set_mad) == 0)
    {
      minut = MINUT;
      EEPROM.write(add++, minut);
      temp = 0;
//      while (digitalRead(next) == 0);
      while (digitalRead(set_mad) == 0);
    }
  }
  delay(1000);
}


void match()
{
  int tem[17];
  for (int i = 11; i < 17; i++)
  {
    tem[i] = EEPROM.read(i);
  }
  if (HOUR == tem[11] && MINUT == tem[12])
  {
//    flag1=1;
//    Serial.print("Flag: ");
//     Serial.println(flag1);
    beep();
    beep();
    beep();
    beep();
    lcd.clear();
    lcd.print("Wake Up....");
    lcd.setCursor(0, 1);
    lcd.print("Wake Up....");
    beep();
    beep();
    beep();
    beep();
   // break;
  }

}
void beep()
{
  tone(buzzer, 10000,500);
//  digitalWrite(buzzer, HIGH);
  delay(500);
//  digitalWrite(buzzer, LOW);
//  delay(500);
}
