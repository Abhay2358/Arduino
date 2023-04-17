/* Flashing LED
   * ------------
   * Turns on and off a light emitting diode(LED) connected to a digital
   * pin, in intervals of 2 seconds. *
*/

int ledPin = 13; // LED connected to digital pin 13

void setup() {
   pinMode(ledPin, OUTPUT); // sets the digital pin as output
}

void loop() {
 //delay(5000);
  int minute = 0;
  int sec=500;
  minute=sec%60;
  Serial.println(minute);
   digitalWrite(ledPin, HIGH); // sets the LED on
   Serial.println("delay on ");
   delay(1000); // waits for a second
   
   digitalWrite(ledPin, LOW); // sets the LED off
   delay(1000); // waits for a second
}
