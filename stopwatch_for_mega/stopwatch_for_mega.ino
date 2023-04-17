#include <LiquidCrystal.h>                 //includes the library code of LCD in aurdino
unsigned long time;
long int seconds=0;
int minutes=0;
int hours=0;
int set=0;
int reset=0;
LiquidCrystal LCD(8, 7, 5, 4, 3, 2);  //RS,EN,D4,D5,D6,D7 pin of LCD respectively
#include<Wire.h>
#include<BH1750.h>
BH1750 lightMeter;

void setup()
{
Serial.begin(9600);                   //initiates serial communication
LCD.begin(16, 2);     //sets the number of columns and rows
pinMode(8,INPUT);
pinMode(7,INPUT);
Wire.begin();
lightMeter.begin();
}

void loop()
{
//set=digitalRead(8);
//Serial.println(set);
float lux = lightMeter.readLightLevel();
Serial.print("light:");
Serial.println(lux); 
delay(750);
 
if(digitalRead(8)==1)
{
 if(lux>10000)
{  
setClock();         //function
LCD.setCursor(0,1);     //sets the cursor to 0th column and 1st row,numbering starts from 0
{
if(hours<10)        //suppose 4
{
LCD.print("0");     //LCD first prints 0 and stopwatch shows 0
LCD.print(hours);       //LCD then prints 4. So value printed is 04 stopwatch shows 04
}
else
{
LCD.print(hours);
}
}
LCD.print(":");
{
if(minutes<10)
{
LCD.print("0");
LCD.print(minutes);
LCD.print(":");
Serial.println("0");
Serial.println(minutes);
Serial.println(":");

}
else
{
LCD.print(minutes);
LCD.print(":");
Serial.println(minutes);
Serial.println(":");
}
}
{
if(seconds<10)
{
LCD.print("0");
LCD.print(seconds);
Serial.println("0");
Serial.println(seconds);

}
else
{
LCD.print(seconds);
Serial.println(seconds);


}
}
}
}
}

void setClock()
{
seconds++;       //counts seconds from 0
delay(1000);     //a delay of 1000 milliseconds is given for each second count
if (seconds>59)
{
seconds=0;      //whenever second is greater than 59 than second is made equal to
minutes++;     // zero and a minute is counted for it
}
if (minutes>59)
{hours++;
minutes=0;
}

if(hours>23)
{
hours=0;
}
}
