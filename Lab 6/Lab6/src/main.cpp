#include <Arduino.h>
#include <DigitalPin.h>

int photoPin = A0;
int val1 = 0;
unsigned int val = 0;
unsigned int counter = 0;
DigitalPin Red(6);


void setup() {
  Red.set_ICR();
  Serial.begin(9600);
 
}


void loop() {
if (Serial.available() > 0){


  val=Serial.parseInt();
  Red.set_duty_cycle(counter);
  delay(500);
  val1 = analogRead(photoPin);
  Serial.println(val1);
  counter += 1;
  if (counter == 101){
    counter = 0;
  }
}
}