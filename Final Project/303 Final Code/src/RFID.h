#ifndef RFID_
#define RFID_

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

extern MFRC522 mfrc522;
extern const int buzzer;
bool rfid();

#endif 