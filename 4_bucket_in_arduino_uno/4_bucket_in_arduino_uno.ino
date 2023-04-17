#include "DHT.h"
#define DHTPIN 10
#define DHTTYPE DHT22 //DHT22 
DHT dht(DHTPIN, DHTTYPE);
#define RELAY1 1 // cooler relay
#define RELAY2 12 // heater relay
#define RELAY3 13 // humidifier relay
#define RELAY4 29 // DRYER RELAY
//temp & hum dec ends here
const int LIGHT_BUTTON = 22;
const int LOAD_BUTTON = 24;

#include <LiquidCrystal.h>                                        

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LCD_CONTRAST_PIN 8


#include <Wire.h>
#include <BH1750.h>

//light Intensity relays
BH1750 lightMeter;
//#define relay1 11
//#define relay2 12
//#define relay3 13
//#define relay4 14
//#define relay5 15
//#define relay6 16

void setup() {
  Serial.begin(9600);
 // analogWrite(LCD_BACKLIGHT_PIN, 135); //set backlight on 145
 
  lcd.begin(16, 2); 
  analogWrite(LCD_CONTRAST_PIN, 40); //set some contrast  68 ============= 21 dec
  //lcd setup ends here

  pinMode(LIGHT_BUTTON, INPUT);
  pinMode(LOAD_BUTTON, INPUT);
  
  pinMode(RELAY1,OUTPUT);// set Cooler RELAY pin as output
  pinMode(RELAY2,OUTPUT);// set Heater RELAY pin as output
  pinMode(RELAY3,OUTPUT);// set Heater RELAY pin as output
  pinMode(RELAY4,OUTPUT);// set Heater RELAY pin as output
  dht.begin();



  Wire.begin();

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));

}

void loop() {
  
  displayonly();
  delay(1000);
  temploop();
  delay(1000);
  LightIntensity();
  delay(1000);
}

void displayonly()

{
  
  float temp = (getTemp("c"));
  int hum = (getTemp("h"));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp     :");
  lcd.setCursor(11, 0);
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Humidity :");
  lcd.setCursor(11, 1);
  lcd.print(hum);
  lcd.setCursor(13, 1);
  lcd.print(" %");
  lcd.setCursor(0,0);
  delay(1000);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  Serial.println("display loop");
  delay(1000);

  int lux = lightMeter.readLightLevel(); // float to int 
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.setCursor(0, 1);
  lcd.print(lux);
  lcd.print(" lux");
  lcd.setCursor(0, 0);
  delay(1000);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  LightIntensity();
  delay(500);
}

float getTemp(String req)
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.print("Failed to read temp");
    return;
  }
  // Compute heat index in Kelvin 
  float k = t + 273.15;
  if(req =="c"){
    return t;//return Cilsus
  }else if(req =="f"){
    return f;// return Fahrenheit
  }else if(req =="h"){
    return h;// return humidity
  }else if(req =="hif"){
    return hif;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic;// return heat index in Cilsus
  }else if(req =="k"){
    return k;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
  }
 
}

void temploop(){
  //Have to use this code logic for temperature 
  float inputTemperature = (getTemp("c"));
  bool HeaterON, CoolerON;
  int relayState1 = digitalRead(RELAY1);
  int relayState2 = digitalRead(RELAY2);
  
 // int LoadButton = digitalRead(LOAD_BUTTON);
//  if(LoadButton == LOW){
  //Loadflag = 0;
  //if (Loadflag == 0){
  if (relayState2 == 0)
  {
    if(inputTemperature < 24)
      {
        HeaterON = true;
      }
      else
      {
        HeaterON = false;
      }
  }

  if (relayState2 == 1)
  {
      if(inputTemperature > 25)
      {
         HeaterON = false;
      }
      else
      {
        HeaterON = true;
      }
  }

  if (relayState1 == 0)
  {
    if(inputTemperature > 27)
      {
        CoolerON = true;
        digitalWrite(15, HIGH); // sets the digital pin 13 on
        delay(1000);  
      }
    else
      {
        CoolerON = false;
      }
  }

  if (relayState1 == 1)
  {
    if(inputTemperature < 26)
      {
        CoolerON = false;
      }
    else
      {
        CoolerON = true;
      }
  }

  if(HeaterON == true)
  {
    digitalWrite(RELAY2, HIGH); // Heater is turned ON
    delay(1000);
  }
  else
  {
    digitalWrite(RELAY2, LOW); // Heater is turned OFF
    delay(1000);
  }

  if(CoolerON == true)
  {
    digitalWrite(RELAY1, HIGH);  // Cooler is turned ON
    delay(1000);
  }
  else
  {
    digitalWrite(RELAY1, LOW);  // Cooler is turned OFF
    delay(1000);
    }
    
humlogic();
//}
}
//else if (LoadButton == HIGH){
//  //Loadflag = 1;
//  //if(Loadflag == 1){
//  digitalWrite (RELAY1, HIGH);
//  digitalWrite (RELAY2,HIGH);
//  digitalWrite (RELAY3, HIGH);
////}
//}
//}
void humlogic()
{
  int hum = (getTemp("h"));
  if( hum > 70)
{
  digitalWrite(RELAY3, HIGH);
  delay(100);
  digitalWrite(RELAY4, LOW);
  delay(100);
}else if( hum < 40 )
{
  
  digitalWrite(RELAY3, LOW);
  delay(100);
  digitalWrite(RELAY4, HIGH);
  delay(100);
  
}else if( 40 < hum < 70)
{
  digitalWrite(RELAY3, LOW);
  delay(100);
  digitalWrite(RELAY4, LOW);
  delay(100);
}
}

void LightIntensity(){
float lux = lightMeter.readLightLevel();
//int LightButton = digitalRead(LIGHT_BUTTON);
//
//if (LightButton == LOW){
//  if(lux >= 0 && lux <= 1500){
//    Serial.println("stage 1 on");
//    digitalWrite(relay1, LOW);
//        delay(100);
//    digitalWrite(relay2, LOW);
//        delay(100);
//    digitalWrite(relay3, LOW);
//        delay(100);
//    digitalWrite(relay4, LOW);
//        delay(100);
//    digitalWrite(relay5, LOW);
//        delay(100);
//    digitalWrite(relay6, LOW);
//        delay(100);
//     
//  }
//  else if(lux >= 1500 && lux <= 3000){
//    Serial.println("stage 2 on");
//    digitalWrite(relay1, HIGH);
//        delay(100);
//    digitalWrite(relay2, HIGH);
//        delay(100);
//    digitalWrite(relay3,HIGH);
//        delay(100);
//    digitalWrite(relay4,HIGH);
//        delay(100);
//    digitalWrite(relay5, HIGH);
//        delay(100);
//    digitalWrite(relay6, LOW);
//        delay(100);
//  }
//  else if(lux >= 3000 && lux <= 4500){
//    Serial.println("stage 3 on");
//    digitalWrite(relay1, HIGH);
//        delay(100);
//    digitalWrite(relay2,HIGH);
//        delay(100);
//    digitalWrite(relay3,HIGH);
//        delay(100);
//    digitalWrite(relay4,HIGH);
//        delay(100);
//    digitalWrite(relay5, LOW);
//        delay(100);
//    digitalWrite(relay6, LOW);
//        delay(100);
//    
//  }
//  else if(lux >=4500 && lux <= 6000){
//    Serial.println("Stage 4 on");
//    digitalWrite(relay1, HIGH);
//     delay(100);
//    digitalWrite(relay2,HIGH);
//        delay(100);
//    digitalWrite(relay3,HIGH);
//        delay(100);
//    digitalWrite(relay4,LOW);
//        delay(100);
//    digitalWrite(relay5, LOW);
//        delay(100);
//    digitalWrite(relay6, LOW);
//        delay(100);
//  }
//  else if(lux >= 6000 && lux <= 7500){
//    Serial.println("Stage 5 on");
//    digitalWrite(relay1, HIGH);
//     delay(100);
//    digitalWrite(relay2,HIGH);
//        delay(100);
//    digitalWrite(relay3,LOW);
//        delay(100);
//    digitalWrite(relay4,LOW);
//        delay(100);
//    digitalWrite(relay5, LOW);
//        delay(100);
//    digitalWrite(relay6, LOW);
//        delay(100);
//  }
//  else if(lux >= 7500 && lux <= 9000){
//    Serial.println("Stage 6 on");
//    digitalWrite(relay1, HIGH);
//     delay(100);
//    digitalWrite(relay2,LOW);
//        delay(100);
//    digitalWrite(relay3,LOW);
//        delay(100);
//    digitalWrite(relay4,LOW);
//        delay(100);
//    digitalWrite(relay5, LOW);
//        delay(100);
//    digitalWrite(relay6, LOW);
//        delay(100);
//      }
// else if(lux > 9000){      // stage 7 added 21 dec
//    Serial.println("Stage 7 on");
//    digitalWrite(relay1, HIGH);
//     delay(100);
//    digitalWrite(relay2,HIGH);
//        delay(100);
//    digitalWrite(relay3,HIGH);
//        delay(100);
//    digitalWrite(relay4,HIGH);
//        delay(100);
//    digitalWrite(relay5, HIGH);
//        delay(100);
//    digitalWrite(relay6, HIGH);
//        delay(100);
//    } 
//  }
////}
//else if (LightButton == HIGH) {
// // Lightflag = 0;
// // if(Lightflag == 0){
//    digitalWrite(relay1, HIGH);
//     delay(100);
//    digitalWrite(relay2,HIGH);
//      delay(100);
//    digitalWrite(relay3,HIGH);
//      delay(100);
//    digitalWrite(relay4,HIGH);
//      delay(100);
//    digitalWrite(relay5, HIGH);
//      delay(100);
//    digitalWrite(relay6, HIGH);
//      delay(100);
//}
}
//}
