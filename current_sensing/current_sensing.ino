void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc = analogRead(A0);
  float voltage = adc*5/1023.0;
  float current = ((voltage-0.9)/0.185)/100;
  Serial.print("Current : ");
  Serial.println(current);
  Serial.println("Voltage: ");
  Serial.println(voltage);
  delay(2000);
}
