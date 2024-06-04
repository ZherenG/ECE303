#include <Arduino.h>
const int forward = 5;
const int backward = 7;
int redLED = 38;
int greenLED = 40;
int yellowLED= 42;
int time_delay =3000;
int val = 0;
int outval = 0;
char temp;
int trigPin = 10;    // Trigger
int echoPin = 11;    // Echo
long duration, cm, inches;

void go_forward(){
  digitalWrite(forward,HIGH);
  digitalWrite(backward,LOW);
}

void go_backward(){
  digitalWrite(forward,LOW);
  digitalWrite(backward,HIGH);
}


void brake(){
  digitalWrite(forward,LOW);
  digitalWrite(backward,LOW);
}

void setup() {
   //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(forward,OUTPUT);
  pinMode(backward,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  digitalWrite(forward,HIGH);
  digitalWrite(backward,LOW);
}

void loop() {
  
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
  


  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();



   if(cm > 0 && cm < 2.5){
    Serial.println("close");
      analogWrite(forward,100);
      analogWrite(backward,0);
      digitalWrite(redLED,HIGH);
      digitalWrite(yellowLED,LOW);
      digitalWrite(greenLED,LOW);
    }
    if(cm >= 2.5 && cm <= 7){
      Serial.println("mid");
      analogWrite(forward,150);
      analogWrite(backward,0);
      digitalWrite(redLED,HIGH);
      digitalWrite(greenLED,HIGH);
      digitalWrite(yellowLED,LOW);
    }
    if(cm > 7){
      Serial.println("far");
      analogWrite(forward,255);
      analogWrite(backward,0);
      digitalWrite(redLED,HIGH);
      digitalWrite(yellowLED,HIGH);
      digitalWrite(greenLED,HIGH);
    }
  
  delay(2000);

}


