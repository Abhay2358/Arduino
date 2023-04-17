const int LB = 8;
int flag ;
int flag1;

//const int VCC = 7;
void setup() {
pinMode(13, OUTPUT);
pinMode(10, OUTPUT);
pinMode(8, INPUT);
pinMode(7, OUTPUT);
}

void loop() {
 int LB = digitalRead(8);
 if ( LB == HIGH)//AUTO
 {
  flag = 0;
  if(flag == 0)
  //digitalWrite(VCC,LOW);
  //if(VCC == LOW)
  digitalWrite(13,LOW);
  digitalWrite(10,LOW);
  delay(1000);
  digitalWrite(13,LOW);
  digitalWrite(10,LOW);
  delay(1000);
 }
 if(LB == LOW) // MANUAL
 {
  flag = 1;
  //digitalWrite(VCC,HIGH);
  //if(VCC == HIGH)
  if(flag == 1)
  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);
  delay(1000);
  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);
  delay(1000);
 }
 }
