#ifndef DigitalPin_
#define DigitalPin_
#include <Arduino.h>

class DigitalPin
{
    public:

        DigitalPin(int pin); 
        void set_TCCRA(int val);
        void set_TCCRB(int val);
        void set_TCNT(int val);
        void set_OCR(int val);
        void factor_OCR(int factor);
        void set_TIMSK(int val);
        void set_off();
        void set_on();

        void set_pin();
        void set_output_mode();
        void set_input_mode();
        void on();
        void off();
        void invert_pin();

        void set_ICR();
        void set_duty_cycle(int val);

    private:
        int _pin;
        volatile uint8_t* _PORT;
        uint8_t _bits;
        volatile uint8_t* _DDR;
        volatile uint8_t* _PIN;
};

#endif