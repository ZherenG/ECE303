#include <Arduino.h>
#include <Servo.h>
#include <RFID.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <LiquidCrystal.h>
#define REMOTEPIN 2
#define UP 4127850240
#define DOWN 4161273600
#define ONE 4077715200 
#define TWO 3877175040
#define THREE 2707357440
#define SS_PIN 53
#define RST_PIN 45

LiquidCrystal lcd(46,35,37,33,47,49);
MFRC522 mfrc522(SS_PIN , RST_PIN);

const int forward = 5;
const int backward = 7;
int time_delay=3000;
int val = 0;
int speed = 0;

int degree = 0;
int servo_pin = 9;
Servo servo;

int trigPin = 10;    
int echoPin = 11;    
long duration, cm, inches;

const int max = 255;   
const int min = 100;  
const int thresholdDistance = 20;  
const int stopDistance = 10;   
int current = max;

int power_pin = 4;
int signal_pin = A0;
int waterval = 0;

int ThermistorPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
bool access = false;
const int buzzer = 8;


void go_forward(int speed){
  analogWrite(forward, speed);
}
void go_backward(){
  analogWrite(backward, 0);
}

void brake(){
  digitalWrite(forward, 0);
  digitalWrite(backward, 0);
}

IRrecv irrecv(REMOTEPIN);
void RemoteChange(){
    if (irrecv.decode()){
        if (irrecv.decodedIRData.decodedRawData == UP){
            // increase motor speed by 10%
            Serial.println("UP!");
            current += current * 0.10;
            if (current > max) { current = max;}
            go_forward(current);
            }
        
        if (irrecv.decodedIRData.decodedRawData == DOWN ){
            // decrease DC motor by 10
            Serial.println("Down");
            current -= current * 0.10;
            if (current < min) { current = min;}
            go_forward(current);
                       
        }
      irrecv.resume();
    }
    
}

void setup() { 

  lcd.begin(16,2);

  irrecv.enableIRIn();
  mfrc522.PCD_Init();
  servo.attach(servo_pin);
  servo.write(0);
  pinMode(buzzer, OUTPUT);

  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  digitalWrite(backward, 0);
  digitalWrite(forward, 1);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(power_pin, OUTPUT);
  digitalWrite(power_pin, 0);

  SPI.begin();
  Serial.begin (9600);
  while (!access){
    access = rfid();
    delay(500);
   }
}

void loop() {

  RemoteChange();
  digitalWrite(power_pin, 1);  
  delay(10);                      
  waterval = analogRead(signal_pin); 
  digitalWrite(power_pin, 0);   
  lcd.setCursor(0,0);
  lcd.print("Water:");
  lcd.print(waterval);

  Serial.println(waterval);


  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  lcd.setCursor(0,1);
  lcd.print("Temp(F):");
  lcd.print(T);

  Serial.println(T);

  if (waterval>=100 && T < 90){
    digitalWrite(trigPin, 0);
    delayMicroseconds(5);
    digitalWrite(trigPin, 1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0);
  

    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, 1);
  
    cm = (duration/2) / 29.1; 
    Serial.println(cm);
    if (cm > 25) {
      go_forward(255); 
      go_backward();
      servo.write(180);
    } else if (cm > 20) {
      go_forward(150); 
      go_backward();
      servo.write(135);
    } else if (cm > 15) {
      go_forward(100);
      go_backward();
      servo.write(90);
    } else {
      brake(); 
      servo.write(45);
    }
    delay(1000);
    }
  else{
    brake();
    servo.write(0);
    cm = 0;
    Serial.println(cm);
    delay(1000);
  }
}