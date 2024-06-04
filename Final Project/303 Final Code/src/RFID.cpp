#include <RFID.h>


bool rfid(){

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return false;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return false;
  }
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {

     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content.substring(1) == "5C 38 18 E0") 
  {
    tone(buzzer, 2500, 1000);
    return true;
    
  }
 
 else{
    Serial.println("0");
    Serial.println("0");
    Serial.println("0");
    tone(buzzer, 500, 1000);
    return false;

  }
} 
