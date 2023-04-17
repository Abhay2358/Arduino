#include <dht11.h>
dht11 DHT11;
#define dhtpin 2
void setup() {
  // put your setup code here, to run once:
 pinMode(2, INPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = analogRead(2);
  Serial.println("Temp=");
  Serial.println(temp);
  delay(5000);

}
