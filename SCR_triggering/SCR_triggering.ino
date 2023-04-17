// Half wave controlled rectifier with Arduino (SCR controller with Arduino)

#define scr_trig   8
#define pot       A0

bool ZC = 0;
uint16_t alpha;
void setup(void) {
  pinMode(scr_trig, OUTPUT);
  digitalWrite(scr_trig, LOW);
  attachInterrupt(0, ZC_detect, FALLING);       // Enable external interrupt (INT0)
}

void ZC_detect() {
  ZC = 1;
}
void loop() {
  if(ZC){
    delayMicroseconds(alpha);
    digitalWrite(scr_trig, HIGH);
    delay(1);
    digitalWrite(scr_trig, LOW);
    ZC = 0;
    alpha = analogRead(pot) * 10;
    if(alpha > 10000)
      alpha = 10000;
  }
}
/*{
char keypressed = kpd.getKey();
if (keypressed != NO_KEY)
{
Serial.println(keypressed);
}

// for PC input at Serial Monitor
if (Serial.available())
{
DoOneTest();
delay(500);

}
lcd.display();
delay(500);

// Button Input
digitalWrite(3, HIGH);
int buttonValue = digitalRead(buttonPin);

if (buttonValue == HIGH) {
lcd.clear();
DoOneTest();
delay(500);

}
digitalWrite(3, LOW);
delay(500);

// Print a message to the LCD.
for (int j = 0; j <= 1; j++)
{
lcd.setCursor(0,j);
lcd.print("Q");
lcd.setCursor(1,j);
lcd.print(j);

delay(500);
}
}
*/
