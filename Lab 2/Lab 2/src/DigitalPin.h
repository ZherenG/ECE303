#ifndef DigitalPin_h
#define DigitalPin_h

#include <Arduino.h>

class DigitalPin
{
  public:
    DigitalPin(int pin);
    void On();
    void Off();
    void set_TCCRA(int num);
    void set_TCCRB(int num);
    void set_TCNT(int num);
    void set_OCR(int num);
    void factor_OCR(int factor);
    void set_TIMSK(int num);
  private:
    int _pin;
};

#endif