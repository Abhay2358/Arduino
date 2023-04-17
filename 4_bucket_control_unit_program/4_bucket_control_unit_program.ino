#include "DHT.h"
#define DHTPIN 10
#define DHTTYPE DHT22 //DHT22 
DHT dht(DHTPIN, DHTTYPE);
#define RELAY1 17 // cooler relay
#define RELAY2 18 // heater relay
#define RELAY3 19 // humidifier relay
#define RELAY4 29 // DRYER RELAY
//temp & hum dec ends here
const int LIGHT_BUTTON = 22;
const int LOAD_BUTTON = 24;
#include <LiquidCrystal.h>                                        
// initialize the LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// output control pins
#define LCD_CONTRAST_PIN 6
#define LCD_BACKLIGHT_PIN 9
//LCD dec ends here

//#define RELAY5 31   // Light relay
//const int ldrPin = A0;  //the number of the LDR pin
// LDR dec ends here

#include <Wire.h>
#include <BH1750.h>
//float calibration_value = 35.25;
//int phval = 0;
//unsigned long int avgval;
//int buffer_arr[10], temp;
//#define RELAY6 33
//#define RELAY7 35
//ph program ends here

//light Intensity relays
BH1750 lightMeter;
#define relay1 11
#define relay2 12
#define relay3 13
#define relay4 14
#define relay5 15
#define relay6 16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogWrite(LCD_BACKLIGHT_PIN, 135); //set backlight on 145
  analogWrite(LCD_CONTRAST_PIN, 40); //set some contrast  68 ============= 21 dec
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  //lcd setup ends here

  pinMode(LIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LOAD_BUTTON, INPUT_PULLUP);
  
  pinMode(RELAY1,OUTPUT);// set Cooler RELAY pin as output
  pinMode(RELAY2,OUTPUT);// set Heater RELAY pin as output
  pinMode(RELAY3,OUTPUT);// set Heater RELAY pin as output
  pinMode(RELAY4,OUTPUT);// set Heater RELAY pin as output
  dht.begin();
  //tem & hum setup ends here // put your setup code here, to run once:

 // pinMode(RELAY5, OUTPUT);  //initialize the relay pin as an output
  //pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
  //ldr setup ends here

//  pinMode(RELAY6, OUTPUT);
//  pinMode(RELAY7, OUTPUT);
  //PH setup ends here

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);

  Wire.begin();

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));

}

void loop() {
  
  displayonly();
  delay(1000);
  //phloop();
  //delay(1000);
 // ldrloop();
 // delay(1000);
  temploop();
  delay(1000);
  LightIntensity();
  delay(1000);

}


void displayonly()

{
  
//    for (int i = 0; i < 10; i++)
//  {
//    buffer_arr[i] = analogRead(A1);
//    delay(30);
//  }
//  for (int i = 0; i < 9; i++)
//  {
//    for (int j = i + 1; j < 10; j++)
//    {
//      if (buffer_arr[i] > buffer_arr[j])
//      {
//        temp = buffer_arr[i];
//        buffer_arr[i] = buffer_arr[j];
//        buffer_arr[j] = temp;
//      }
//    }
//  }
//  avgval = 0;
//  for (int i = 2; i < 8; i++)
//    avgval += buffer_arr[i];
//  float volt = (float)avgval * 5.0 / 1024 / 6;
//  float ph_act = -5.70 * volt + calibration_value;
//  lcd.setCursor(0, 0);
//  lcd.print("pH :");
//  lcd.setCursor(5, 0);
//  lcd.print(ph_act);
//  lcd.setCursor(0,0);
//  delay(1000);
//  lcd.setCursor(0, 0);
//  lcd.print("                ");
//  lcd.setCursor(0,1);
//  lcd.print("                          ");
//  phloop();
//  delay(1000);

  float temp = (getTemp("c"));
  int hum = (getTemp("h"));
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

  delay(1000);

//  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value
//  if (ldrStatus <=300) {
//     lcd.setCursor(0, 0);
//     lcd.print("Light Status =");
//     lcd.setCursor(0, 1);
//     lcd.print("Above 5000 Lum");
//     lcd.setCursor(0,0);
//     delay(2000);
//     lcd.print("                ");
//     lcd.setCursor(0,1);
//     lcd.print("                ");
//     delay(500);
//     }else if(ldrStatus >=500) {
//     lcd.setCursor(0, 0);
//     lcd.print("Light Status =");
//     lcd.setCursor(0, 1);
//     lcd.print("Below 5000 Lum");
//     lcd.setCursor(0,0);
//     delay(1000);
//     lcd.print("                ");
//     lcd.setCursor(0,1);

//     lcd.print("                ");
//     }
//     ldrloop();
//   delay (1000);

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


//void phloop()
//{
//  for (int i = 0; i < 10; i++)
//  {
//    buffer_arr[i] = analogRead(A1);
//    delay(30);
//  }
//  for (int i = 0; i < 9; i++)
//  {
//    for (int j = i + 1; j < 10; j++)
//    {
//      if (buffer_arr[i] > buffer_arr[j])
//      {
//        temp = buffer_arr[i];
//        buffer_arr[i] = buffer_arr[j];
//        buffer_arr[j] = temp;
//      }
//    }
//  }
//  avgval = 0;
//  for (int i = 2; i < 8; i++)
//    avgval += buffer_arr[i];
//  float volt = (float)avgval * 5.0 / 1024 / 6;
//  float ph_act = -5.70 * volt + calibration_value;
//  
//       if(ph_act > 6.5){
//       digitalWrite(RELAY6, LOW);
//       delay(100);
//       digitalWrite(RELAY7, HIGH);
//       }else if(ph_act < 5.5)
//    {
//
//      digitalWrite(RELAY7, LOW);
//      delay(100);
//      digitalWrite(RELAY6, HIGH);
//      }else if(5.5 < ph_act < 6.5)
//    {
//      digitalWrite(14, HIGH); // sets the digital pin 13 on
//      delay(1000);  
//      digitalWrite(RELAY6, LOW);
//      delay(100);
//      digitalWrite(RELAY7, LOW);
//      delay(100);
//    }
//}

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

//void ldrloop()
//{
//  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value
//  if (ldrStatus <=300) {
//     digitalWrite(RELAY5 , LOW ); // Light ON as luminance is Low 
//     delay(100);
//  }
//  else if(ldrStatus >=500)
//  {
//     digitalWrite(RELAY5 , HIGH ); // Light OFF as luminance is High 
//     delay(100);
//  }
//}

void temploop(){
  //Have to use this code logic for temperature 
  float inputTemperature = (getTemp("c"));
  bool HeaterON, CoolerON;
  int relayState1 = digitalRead(RELAY1);
  int relayState2 = digitalRead(RELAY2);
////  //Serial.begin(9600);
////  //Serial.println(inputTemperature);
////  //Serial.println(HeaterON);
////
////  // if (relayState2 == LOW)
////   //{
////     //Serial.println("LOW");
////   //} 
////   //else {
////     //Serial.println("HIGH");
////   //}
////
////  
////  //lcd.setCursor(0, 0);
////  //lcd.print("Temp  :");
////  //lcd.setCursor(11, 0);
////  //lcd.print(inputTemperature);
////
int LoadButton = digitalRead(LOAD_BUTTON);
if(LoadButton == HIGH){
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
    
    
 
//if(temp < 24)
//{
//  digitalWrite(RELAY2, LOW); // Heater is turned ON
//  delay(100);
//  digitalWrite(RELAY1, HIGH);  // Cooler is turned OFF
//  delay(100);
//  
//  
//}else if (temp > 27)
//{
//  digitalWrite(RELAY1, LOW); // cooler is turned On
//  delay(100);
//  digitalWrite(RELAY2, HIGH); // Heater is turned OFF
//  delay(100);
//  
//}else if(24< temp < 27)
//{
//  digitalWrite(RELAY1, LOW); // cooler is turned On
//  delay(100);
//  digitalWrite(RELAY2, LOW); // Heater is turned OFF
//  delay(100);
//}
humlogic();
}
else if (LoadButton == LOW){
  digitalWrite (RELAY1, LOW);
  digitalWrite (RELAY2,LOW);
  digitalWrite (RELAY3, LOW);
}
}

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
int LightButton = digitalRead(LIGHT_BUTTON);
//  lcd.setCursor(0, 0);
//  lcd.print("Light: ");
//  lcd.setCursor(0, 1);
//  lcd.print(lux);
//  lcd.print(" lx");
//  delay(1000);

if (LightButton == HIGH){
  if(lux >= 0 && lux <= 1500){
    Serial.println("stage 1 on");
    digitalWrite(relay1, HIGH);
        delay(100);
    digitalWrite(relay2, HIGH);
        delay(100);
    digitalWrite(relay3, HIGH);
        delay(100);
    digitalWrite(relay4, HIGH);
        delay(100);
    digitalWrite(relay5, HIGH);
        delay(100);
    digitalWrite(relay6, HIGH);
        delay(100);
     
  }
  else if(lux >= 1500 && lux <= 3000){
    Serial.println("stage 2 on");
    digitalWrite(relay1, HIGH);
        delay(100);
    digitalWrite(relay2, HIGH);
        delay(100);
    digitalWrite(relay3,HIGH);
        delay(100);
    digitalWrite(relay4,HIGH);
        delay(100);
    digitalWrite(relay5, HIGH);
        delay(100);
    digitalWrite(relay6, LOW);
        delay(100);
  }
  else if(lux >= 3000 && lux <= 4500){
    Serial.println("stage 3 on");
    digitalWrite(relay1, HIGH);
        delay(100);
    digitalWrite(relay2,HIGH);
        delay(100);
    digitalWrite(relay3,HIGH);
        delay(100);
    digitalWrite(relay4,HIGH);
        delay(100);
    digitalWrite(relay5, LOW);
        delay(100);
    digitalWrite(relay6, LOW);
        delay(100);
    
  }
  else if(lux >=4500 && lux <= 6000){
    Serial.println("Stage 4 on");
    digitalWrite(relay1, HIGH);
     delay(100);
    digitalWrite(relay2,HIGH);
        delay(100);
    digitalWrite(relay3,HIGH);
        delay(100);
    digitalWrite(relay4,LOW);
        delay(100);
    digitalWrite(relay5, LOW);
        delay(100);
    digitalWrite(relay6, LOW);
        delay(100);
  }
  else if(lux >= 6000 && lux <= 7500){
    Serial.println("Stage 5 on");
    digitalWrite(relay1, HIGH);
     delay(100);
    digitalWrite(relay2,HIGH);
        delay(100);
    digitalWrite(relay3,LOW);
        delay(100);
    digitalWrite(relay4,LOW);
        delay(100);
    digitalWrite(relay5, LOW);
        delay(100);
    digitalWrite(relay6, LOW);
        delay(100);
  }
  else if(lux >= 7500 && lux <= 9000){
    Serial.println("Stage 6 on");
    digitalWrite(relay1, HIGH);
     delay(100);
    digitalWrite(relay2,LOW);
        delay(100);
    digitalWrite(relay3,LOW);
        delay(100);
    digitalWrite(relay4,LOW);
        delay(100);
    digitalWrite(relay5, LOW);
        delay(100);
    digitalWrite(relay6, LOW);
        delay(100);
      }
 else if(lux > 9000){      // stage 7 added 21 dec
    Serial.println("Stage 7 on");
    digitalWrite(relay1, LOW);
     delay(100);
    digitalWrite(relay2,LOW);
        delay(100);
    digitalWrite(relay3,LOW);
        delay(100);
    digitalWrite(relay4,LOW);
        delay(100);
    digitalWrite(relay5, LOW);
        delay(100);
    digitalWrite(relay6, LOW);
        delay(100);
  } 
}
else if (LightButton == LOW) {
    digitalWrite(relay1, LOW);
     delay(100);
    digitalWrite(relay2,LOW);
      delay(100);
    digitalWrite(relay3,LOW);
      delay(100);
    digitalWrite(relay4,LOW);
      delay(100);
    digitalWrite(relay5, LOW);
      delay(100);
    digitalWrite(relay6, LOW);
      delay(100);
}
}
