#include "DHT.h"
#define DHTPIN 10
#define DHTTYPE DHT22 //DHT22 
DHT dht(DHTPIN, DHTTYPE);  // DHT 22 sensor program
#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);
#define LCD_CONTRAST_PIN 8

#define RELAY1 1 // cooler relay
#define RELAY2 12 // heater relay
#define RELAY3 13 // humidifier relay
#define RELAY4 29 // DRYER RELAY

////const int LOAD_BUTTON = 24;

#include "Arduino.h"
#include "uRTCLib.h"
#include<Wire.h>
#include<BH1750.h>
BH1750 lightMeter;
int Relay = 9;  // light relay 
const int OFF_hour = 19;
const int OFF_min = 00; 
int secondss = 0;
int minutes = 0;
int flag = 0;
int max_count = 240;

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
  
  dht.begin();

  pinMode(RELAY1,OUTPUT);// set Cooler RELAY pin as output
  pinMode(RELAY2,OUTPUT);// set Heater RELAY pin as output
  pinMode(RELAY3,OUTPUT);// set Heater RELAY pin as output
  pinMode(RELAY4,OUTPUT);//

  lcd.begin(16, 2);
  analogWrite(LCD_CONTRAST_PIN, 40);

  // Comment out below line once you set the date & time.
  // Following line sets the RTC with an explicit date & time
  // for example to set January 13 2022 at 12:56 you would call:
   rtc.set(0, 45, 9, 2, 20, 3, 23);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  // set day of week (1=Sunday, 7=Saturday)
}



void loop() {
  display_Date_Time();
  delay(500);
  displaytemp();
  delay(1000);
  temploop();
  delay(1000);
  

  if((rtc.hour() > 8) && (rtc.hour() < 18 )){
        Serial.println("stopwatch on ");
        stopwatch();
     }
  else if (rtc.hour() > 17 && rtc.hour() < 22  && flag == 0){
    if (minutes < max_count){
      for(int i=0; i<minutes; i++){
        digitalWrite(Relay, HIGH);
        temploop();
        delay(1000);
        displaytemp();
        delay(1000);
        Serial.println("Light ON");
        delay(58000);
        Serial.println(i);
        }
      }
      else if(minutes > max_count){
        for(int i=0; i<max_count; i++){
          digitalWrite(Relay, HIGH);
          temploop();
          delay(1000);
          displaytemp();
          delay(1000);
          Serial.println("Light ON for max time");
          delay(58000);
          
      }
    }
    flag = 1;
  }
  if(flag == 1 && rtc.hour() < 22){ // this is the off condition of the relay after 7pm lights are on 
    digitalWrite(Relay, LOW);
    Serial.println("Light OFF");
    minutes = 0;
    }
    else{
      flag = 0;
    }
  return 0;
 
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

void displaytemp(){

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
  delay(100);
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
  ////int LoadButton = digitalRead(LOAD_BUTTON);
  
  ////if(LoadButton == LOW)//{
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
    delay(100);
  }
  else
  {
    digitalWrite(RELAY2, LOW); // Heater is turned OFF
    delay(100);
  }

  if(CoolerON == true)
  {
    digitalWrite(RELAY1, HIGH);  // Cooler is turned ON
    delay(100);
  }
  else
  {
    digitalWrite(RELAY1, LOW);  // Cooler is turned OFF
    delay(100);
    }
    
humlogic();
}
//else if (LoadButton == HIGH){
//  //Loadflag = 1;
//  //if(Loadflag == 1){
//  digitalWrite (RELAY1, HIGH);
//  digitalWrite (RELAY2,HIGH);
//  digitalWrite (RELAY3, HIGH);
//
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

void setClock(){
  secondss++;
  delay(1000);
  secondss =  secondss + 5;
  //secondss = secondss*1000;
  Serial.println(secondss);
  if (secondss>59){
    secondss=0;
    minutes++;
    Serial.println(minutes);
  }
}

void stopwatch(){
 float lux = lightMeter.readLightLevel();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.setCursor(0, 1);
  lcd.print(lux);
  Serial.println(lux);
  lcd.print(" lx");
  delay(500);

 if(lux<10000)
{  
  setClock();
}

//void setClock(){
//  
//  second++;
//  delay(1000);
//}
}
