#include <Arduino.h>
#include "DigitalPin.h"

DigitalPin::DigitalPin(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void DigitalPin::On()
{
  digitalWrite(_pin, HIGH);
}
void DigitalPin::Off()
{
  digitalWrite(_pin, LOW);
}

void DigitalPin::set_TCCRA(int num)
{
  if (_pin == 11)
  { // timer 1
    TCCR1A = num;
  }
  else if (_pin == 44)
  { // timer 5
    TCCR5A = num;
  }
  else if (_pin == 6)
  { // timer 4
    TCCR4A = num;
  }
  else if (_pin == 5)
  { // timer 3
    TCCR3A = num;
  }
}

void DigitalPin::set_TCCRB(int num)
{
  if (_pin == 11)
  { // timer 1
    TCCR1B = num;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12);
  }
  else if (_pin == 44)
  { // timer 5
    TCCR5B = num;
    TCCR5B |= (1 << WGM52);
    TCCR5B |= (1 << CS52);
  }
  else if (_pin == 6)
  { // timer 4
    TCCR4B = num;
    TCCR4B |= (1 << WGM42);
    TCCR4B |= (1 << CS42);
  }
  else if (_pin == 5)
  { // timer 3
    TCCR3B = num;
    TCCR3B |= (1 << WGM32);
    TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);
  }
}
void DigitalPin::set_TCNT(int num)
{
  if (_pin == 11)
  { // timer 1
    TCNT1 = num;
  }
  else if (_pin == 44)
  { // timer 5
    TCNT5 = num;
  }
  else if (_pin == 6)
  { // timer 4
    TCNT4 = num;
  }
  else if (_pin == 5)
  { // timer 3
    TCNT3 = num;
  }
}
void DigitalPin::set_OCR(int num)
{
  if (_pin == 11)
  { // timer 1
    OCR1A = num;
  }
  else if (_pin == 44)
  { // timer 5
    OCR5A = num;
  }
  else if (_pin == 6)
  { // timer 4
    OCR4A = num;
  }
  else if (_pin == 5)
  { // timer 3
    OCR3A = num;
  }
}
void DigitalPin::factor_OCR(int factor)
{
  if (_pin == 11)
  { // timer 1
    OCR1A = OCR1A / factor;
  }
  else if (_pin == 44)
  { // timer 5
    OCR5A = OCR5A / factor;
  }
  else if (_pin == 6)
  { // timer 4
    OCR4A = OCR4A / factor;
  }
  else if (_pin == 5)
  { // timer 3
    OCR3A = OCR3A / factor;
  }
}
void DigitalPin::set_TIMSK(int num)
{
  if (_pin == 11)
  { // timer 1
    if (num == 0)
    {
      TIMSK1 = 0;
    }
    else
    {
      TIMSK1 = 0;
      TIMSK1 |= (1 << OCIE1A);
    }
  }
  else if (_pin == 44)
  { // timer 5
    if (num == 0)
    {
      TIMSK5 = 0;
    }
    else
    {
      TIMSK5 = 0;
      TIMSK5 |= (1 << OCIE5A);
    }
  }
  else if (_pin == 6)
  { // timer 4
    if (num == 0)
    {
      TIMSK4 = 0;
    }
    else
    {
      TIMSK4 = 0;
      TIMSK4 |= (1 << OCIE4A);
    }
  }
  else if (_pin == 5)
  { // timer 3
    if (num == 0)
    {
      TIMSK3 = 0;
    }
    else
    {
      TIMSK3 = 0;
      TIMSK3 |= (1 << OCIE3A);
    }
  }
}