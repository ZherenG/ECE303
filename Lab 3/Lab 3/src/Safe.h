#ifndef Safe_h
#define Safe_h

#include <Arduino.h>

class Safe
{
  public:
    Safe(int code); 
    int getCode();
    void displayCode();
   
  private:
    int _code;
};

#endif