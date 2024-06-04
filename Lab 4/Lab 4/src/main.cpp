#include <Arduino.h>
#include <DigitalPin.h>

int photoPin = A0;
int LEDPin = A2;
DigitalPin LED(6);

void setup() {
  LED.set_ICR();
  Serial.begin(9600);
}

void loop() {
  for (int dutyCycle = 0; dutyCycle <= 100; dutyCycle += 5) {

    LED.set_duty_cycle(dutyCycle);
    delay(1);
    float photoVoltage = (analogRead(photoPin) / 1023.0) * 5.0; // this is the formula for calculating volt in 5V scale
    delay(100);
    float LEDVoltage = (analogRead(LEDPin) / 1023.0) *5;

    Serial.print("Duty Cycle: ",dutyCycle,"%, Photocell Voltage: ",photoVoltage,"V LED Voltage", LEDVoltage, "V");
    
    delay(500);
  }
}