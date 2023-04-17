#include "Arduino.h"
#include "uRTCLib.h"
#include<Wire.h>
#include<BH1750.h>
BH1750 lightMeter;
int Relay = 4;
const int OFF_hour = 19;
const int OFF_min = 00; 
int second = 0;

// uRTCLib rtc;
uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  delay(3000); // wait for console opening
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  URTCLIB_WIRE.begin();
  Wire.begin();
  lightMeter.begin();

  // Comment out below line once you set the date & time.
  // Following line sets the RTC with an explicit date & time
  // for example to set January 13 2022 at 12:56 you would call:
   rtc.set(0, 58, 18, 5, 8, 3, 23);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  // set day of week (1=Sunday, 7=Saturday)
}

void loop() {
  rtc.refresh();
  Serial.print("Current Date & Time: ");
  Serial.print(rtc.year());
  Serial.print('/');
  Serial.print(rtc.month());
  Serial.print('/');
  Serial.print(rtc.day());

  Serial.print(" (");
  Serial.print(daysOfTheWeek[rtc.dayOfWeek()-1]);
  Serial.print(") ");

  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.print(rtc.minute());
  Serial.print(':');
  Serial.println(rtc.second());
  
  Serial.println();
  delay(1000);

  if(rtc.hour() == 18 && rtc.minute() == 59){
        stopwatch();
     }
  else if (rtc.hour() == OFF_hour && rtc.minute() == OFF_min){
    digitalWrite(Relay, LOW);
    Serial.println("Light off");
    delay(second);
  }
  return 0;
 
}

void setclock(){
  
  second++;
  delay(1000);
}

void stopwatch(){
 float lux = lightMeter.readLightLevel();
 Serial.print(lux);

 if(digitalRead(8)==1)
{
 if(lux>10000)
{  
  setclock();
}
}

}
