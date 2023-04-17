#define LED_PIN 2
#define LED_PIN1 3
#define LED_PIN2 4
#define LED_PIN3 5
const int LIGHT_BUTTON = 8;
#define LightPin 7

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LightPin, OUTPUT);  
  pinMode(LIGHT_BUTTON, INPUT);
  
}

void loop() {

  int LightButton = digitalRead(LIGHT_BUTTON);
  if(LightButton == HIGH){
     digitalWrite(LightPin, LOW);  
  }else{
    digitalWrite(LightPin, HIGH);
  }
  if((LightButton == HIGH)&& (LightPin == LOW)){
  
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  delay(500);

  digitalWrite(LED_PIN1, LOW);
  delay(500);
  digitalWrite(LED_PIN1, HIGH);
  delay(500);

  digitalWrite(LED_PIN2, LOW);
  delay(500);
  digitalWrite(LED_PIN2, HIGH);
  delay(500);

  digitalWrite(LED_PIN3, LOW);
  delay(500);
  digitalWrite(LED_PIN3, HIGH);
  delay(500);
  }
  else if (LightPin == LOW) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, LOW);

}
}
