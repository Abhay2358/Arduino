#include "Arduino.h"
#include "uRTCLib.h"
#include<Wire.h>
//#include<BH1750.h>
#include <LiquidCrystal.h> 

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);
#define LCD_CONTRAST_PIN 8

//BH1750 lightMeter;
int Relay = 9;
const int OFF_hour = 19;
const int OFF_min = 01; 
int secondss = 0;
int flag = 0;
// uRTCLib rtc;
uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  
  Wire.begin();
//  lightMeter.begin();

  lcd.begin(16, 2);
  analogWrite(LCD_CONTRAST_PIN, 40);

  // Comment out below line once you set the date & time.
  // Following line sets the RTC with an explicit date & time
  // for example to set January 13 2022 at 12:56 you would call:
   rtc.set(0, 19, 18, 5, 8, 3, 23);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  // set day of week (1=Sunday, 7=Saturday)
}

void display_Date_Time(){
  rtc.refresh();
  lcd.setCursor(0, 0);
  lcd.print("Date : ");
  lcd.print(rtc.day());
  lcd.print("/");  
  lcd.print(rtc.month());
  lcd.print("/");
  lcd.print(rtc.year());
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("Time : ");
  lcd.print(rtc.hour());
  lcd.print(":");
  lcd.print(rtc.minute());
  lcd.print(":");
  lcd.print(rtc.second());
  delay(500);
}

void loop() {

  display_Date_Time();
    
//  if((rtc.hour() == 18 && rtc.minute() == 58) && (rtc.hour()< 19)){
//        Serial.println("stopwatch on ");
//        stopwatch();
//     }
  if (rtc.minute()>= 20){
    for(int i=0; i<secondss; i++){
        Serial.println(rtc.minute());
        Serial.println(rtc.second());
      if(rtc.minute()<= 25 && flag == 0){
              digitalWrite(Relay, HIGH);
              Serial.println("Light ON");
              delay(1000); 
      }else{
        flag = 1;
        Serial.println(rtc.minute());
        digitalWrite(Relay, LOW);
        Serial.println("Light OFF");
        delay(1000);
        }
    }
  }
  return 0;
 
}

void setClock(){
  secondss++;
  delay(1000);
  Serial.println(secondss);
}

void stopwatch(){
 //float lux = lightMeter.readLightLevel();
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("Light: ");
//  lcd.setCursor(0, 1);
//  lcd.print(lux);
//  Serial.println(lux);
//  lcd.print(" lx");
//  delay(1000);

// if(lux>10000)
//{  
//  setClock();
//}

//void setClock(){
//  
//  second++;
//  delay(1000);
//}
}
