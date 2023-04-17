#include <Wire.h> 
#include <LiquidCrystal.h> 
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,16,2);  //in simulation use 0x20 and in real use 0x27 i2c address, while 16 = columns, and 2 = rows. 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// output control pins
#define LCD_CONTRAST_PIN 6
#define LCD_BACKLIGHT_PIN 10

 int timedata_sqeeze = A0; // analog pin0 , a Potentiometer is connected with A0 pin of Arduino. 
 int timerawdata = 0; // stores the value comming from the Potentiometer. 
 int settime_sqeeze = 0;// time duration in millisconds 

 int timedata_weld = A1;
 int timerawdata_weld = 0;
 int settime_weld = 0;

 int timedata_hold = A2;
 int timerawdata_hold = 0;
 int settime_hold = 0;


 
const int button = 3; // button to start the welding 
int relay1 = 4;// the output relay
int relay2 = 5;
int relay3 = 6;

//int ReadyLed = 8; // when this led is turned ON, it means you can start the welding
//int Sflag = 0; // stops the unnecessary repition of code.


void setup()
{
Serial.begin(9600);
analogWrite(LCD_BACKLIGHT_PIN, 135); //set backlight on 145
analogWrite(LCD_CONTRAST_PIN, 40); //set some contrast  68 ============= 21 dec
lcd.begin(16, 2);

pinMode(button, INPUT_PULLUP);
//digitalWrite(startb, HIGH);
pinMode(timedata_sqeeze, INPUT); // POTENTIOMETER CONNECTED
pinMode(timedata_weld, INPUT);
pinMode(timedata_hold, INPUT);


pinMode(relay1, OUTPUT); 
digitalWrite(relay1, LOW);

pinMode(relay2, OUTPUT); 
digitalWrite(relay2, LOW);

pinMode(relay3, OUTPUT); 
digitalWrite(relay3, LOW);

//pinMode(ReadyLed, OUTPUT);
//delay(2000);
//digitalWrite(ReadyLed,HIGH);
 // lcd.init();                 //Init the LCD
  //lcd.backlight();            //Activate backlight     
 //lcd.home();  

}


void loop()
{

 int buttonState = digitalRead(button);
 
 timerawdata = analogRead(timedata_sqeeze);
 settime_sqeeze = map(timerawdata, 0, 1024, 0, 4000); // 0 to 4000 milliseconds

 timerawdata = analogRead(timedata_weld);
 settime_weld = map(timerawdata, 0, 1024, 0, 4000); // 0 to 4000 milliseconds

 timerawdata = analogRead(timedata_hold);
 settime_hold = map(timerawdata, 0, 1024, 0, 4000); // 0 to 4000 milliseconds

if(buttonState == LOW) // If you press the start button
 { 
//digitalWrite(ReadyLed, LOW);
//digitalWrite(relay, HIGH);
//delay(settime_sqeeze);
//digitalWrite(relay,LOW);
//delay(settime);
//digitalWrite(ReadyLed, HIGH);
//Sflag = 0;   


   digitalWrite(relay1, HIGH);
   digitalWrite(relay3, HIGH);// sets the LED on
   delay(settime_sqeeze); // waits for a second
   //digitalWrite(R3, HIGH); // sets the LED off
  // delay(1000); // waits for a second
   digitalWrite(relay1, LOW); // sets the LED off
   delay(settime_sqeeze);


   digitalWrite(relay2, HIGH); // sets the LED on
   delay(settime_weld); // waits for a second
   digitalWrite(relay2, LOW); // sets the LED off
   delay(settime_weld); // waits for a second
   digitalWrite(relay3, LOW); // sets the LED on
   delay(settime_sqeeze); // waits for a second
   //digitalWrite(R3, LOW); // sets the LED off
   //delay(1000); // waits for a second

}

 else
  if (buttonState == HIGH) {
    Serial.println("The button is unpressed");
    digitalWrite(relay1, LOW);// turn off
    digitalWrite(relay2,  LOW);
    digitalWrite(relay3, LOW);

  }
// lcd.clear();
lcd.setCursor(0, 0);
lcd.print("ON Time: ");
lcd.setCursor(5, 0);
lcd.print(settime_sqeeze); 
delay(200); 

lcd.print("ON Time: ");
lcd.print(settime_weld); 
delay(200);

lcd.print("ON Time: ");
lcd.print(settime_hold); 
delay(200);
}  
