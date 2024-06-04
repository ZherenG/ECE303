#include <Arduino.h>
#include "Safe.h"

Safe::Safe(int code)
{
 _code = code;
}

int Safe::getCode(){
  return _code;
}

void Safe::displayCode(){
  Serial.println(_code);
}




