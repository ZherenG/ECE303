#ifndef DigitalPin_h
#define DigitalPin_h

#include <Arduino.h>

class DigitalPin
{
public:
  DigitalPin(int pin);
  void set_pin();
  void set_output_mode();
  void set_input_mode();
  void set_on();//lab 3 version
  void set_off();
  void invert_pin();

  void On();//lab 2 commands
  void Off();
  void set_TCCRA(int num);
  void set_TCCRB(int num);
  void set_TCNT(int num);
  void set_OCR(int num);
  void factor_OCR(int factor);
  void set_TIMSK(int num);

private:
  int _pin;
  volatile uint8_t *_PORT;
  uint8_t _bits;
  volatile uint8_t *_DDR;
  volatile uint8_t *_PIN;
};

#endif