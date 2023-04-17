/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-relay
 */

const int BUTTON_PIN = 3; // Arduino pin connected to button's pin
const int RELAY_PIN1  = 4;// Arduino pin connected to relay's pin
const int RELAY_PIN2  = 5;
const int RELAY_PIN3  = 6;

int flag = 0;

int timedata_sqeeze = A0; // analog pin0 , a Potentiometer is connected with A0 pin of Arduino. 
int timerawdata = 0; // stores the value comming from the Potentiometer. 
int settime_sqeeze = 0;// time duration in millisconds 

int timedata_weld = A1;
int timerawdata_weld = 0;
int settime_weld = 0;

int timedata_hold = A2;
int timerawdata_hold = 0;
int settime_hold = 0;

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN1, OUTPUT);        // set arduino pin to output mode

  //pinMode(BUTTON_PIN2, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN2, OUTPUT); 

  //pinMode(BUTTON_PIN3, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN3, OUTPUT); 

  pinMode(timedata_sqeeze, INPUT); // POTENTIOMETER CONNECTED
  pinMode(timedata_weld, INPUT);
  pinMode(timedata_hold, INPUT);
}


void loop() {

   int buttonState = digitalRead(BUTTON_PIN); // read new state

   timerawdata = analogRead(timedata_sqeeze);
   settime_sqeeze = map(timerawdata, 0, 1024, 0, 4000); // 0 to 4000 milliseconds

   timerawdata_weld = analogRead(timedata_weld);
   settime_weld = map(timerawdata_weld, 0, 1024, 0, 4000); // 0 to 4000 milliseconds

   timerawdata_hold = analogRead(timedata_hold);
   settime_hold = map(timerawdata_hold, 0, 1024, 0, 4000); // 0 to 4000 milliseconds
  
  if ((buttonState == LOW)&& (flag == 0)) {
    flag = 1;
  if(flag == 1){
    Serial.println("The button is being pressed");
    digitalWrite(RELAY_PIN1, HIGH); // turn on
    digitalWrite(RELAY_PIN3, HIGH);
    delay(settime_sqeeze);
    digitalWrite(RELAY_PIN1, LOW);
    delay(settime_sqeeze);
    digitalWrite(RELAY_PIN2, HIGH);
    delay(settime_weld);
    digitalWrite(RELAY_PIN2, LOW);
    //delay(settime_weld);
    delay(settime_hold);
    digitalWrite(RELAY_PIN3, LOW);
    delay(settime_hold);
    
  }
  }
 
  else if (buttonState == HIGH) {
    flag = 0;
    Serial.println("The button is unpressed");
    digitalWrite(RELAY_PIN1, LOW);// turn off
    digitalWrite(RELAY_PIN2,  LOW);
    digitalWrite(RELAY_PIN3, LOW);
    
  
  }
}
