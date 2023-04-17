/*
  Example of BH1750 library usage. This example initialises the BH1750 object using the default high resolution continuous mode and then makes a light level reading every second.
*/

#include <LiquidCrystal.h>
// initialize the LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// output control pins
#define LCD_CONTRAST_PIN 6
#define LCD_BACKLIGHT_PIN 9
//LCD dec ends here

const int LIGHT_BUTTON = 22;


#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
#define relay1 11
#define relay2 12
#define relay3 13
#define relay4 14
#define relay5 15
#define relay6 16

void setup(){
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);

  analogWrite(LCD_BACKLIGHT_PIN, 255); //set backlight on
  analogWrite(LCD_CONTRAST_PIN, 1); //set some contrast 
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  //lcd setup ends here

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);

  pinMode(LIGHT_BUTTON, INPUT);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();
  int LightButton = digitalRead(LIGHT_BUTTON);
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.setCursor(0, 1);
  lcd.print(lux);
  Serial.println(lux);
  lcd.print(" lx");
  delay(500);
if (LightButton == LOW){
  if(lux >= 500 && lux <= 2500){
    Serial.println("stage 1 on");
    Serial.println(lux);
    digitalWrite(relay1, HIGH);
    delay(1000);
    digitalWrite(relay2, HIGH);
        delay(1000);
    digitalWrite(relay3, HIGH);
        delay(1000);
    digitalWrite(relay4, HIGH);
        delay(1000);
     
  }else if(lux >= 2500 && lux <= 5000){
    Serial.println("stage 2 on");
    digitalWrite(relay1, HIGH);
        delay(1000);
    digitalWrite(relay2, HIGH);
        delay(1000);
    digitalWrite(relay3,HIGH);
        delay(1000);
    digitalWrite(relay4,LOW);
        delay(1000);
  }
  else if(lux >= 5000 && lux <= 7500){
    Serial.println("stage 3 on");
    digitalWrite(relay1, HIGH);
        delay(1000);
    digitalWrite(relay2,HIGH);
        delay(1000);
    digitalWrite(relay3,LOW);
        delay(1000);
    digitalWrite(relay4,LOW);
        delay(1000);
  }else if(lux >=7500 && lux <= 10000){
    Serial.println("Stage 4 on");
    digitalWrite(relay1, HIGH);
     delay(1000);
    digitalWrite(relay2,LOW);
        delay(1000);
    digitalWrite(relay3,LOW);
        delay(1000);
    
  }
}
else if (LightButton == HIGH) {
    digitalWrite(relay1, HIGH);
     delay(100);
    digitalWrite(relay2,HIGH);
      delay(100);
    digitalWrite(relay3,HIGH);
      delay(100);
    digitalWrite(relay4,HIGH);
      delay(100);
    digitalWrite(relay5, HIGH);
      delay(100);
    digitalWrite(relay6, HIGH);
      delay(100);
}
}
