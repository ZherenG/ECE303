#include <Arduino.h>
#include "DigitalPin.h"

DigitalPin::DigitalPin(int pin){
    _pin = pin;
    this->set_pin();
    this->set_output_mode();
    
}
void DigitalPin::set_off(){
    digitalWrite(_pin, LOW);
}
void DigitalPin::set_on(){
    digitalWrite(_pin, HIGH);
}


void DigitalPin::set_TCCRA(int val){
    switch (_pin){
        case 44:
            TCCR5A = val;
            break;
        case 11:
            TCCR1A = val;
            break;      
        case 6:
            TCCR4A = val;
            break;
        case 5:
            TCCR3A = val;
            break;

    }
}

void DigitalPin::set_TCCRB(int val){ // WGM and CS values would change based on timer
    switch (_pin){
        case 44:
            TCCR5B = val;
            TCCR5B |= (1 << WGM52);
            TCCR5B |= (1 << CS52);
            break;
        case 11:
            TCCR1B = val;
            TCCR1B |= (1 << WGM12);
            TCCR1B |= (1 << CS12);
            break;      
        case 6:
            TCCR4B = val;
            TCCR4B |= (1<<WGM42);
            TCCR4B |= (1<<CS42);
            break;
        case 5:
            TCCR3B = val;
            TCCR3B |= (1 << WGM32); //ctc mode
            TCCR3B |= (1<< CS32) | (0<< CS31) | (0<< CS30); // 256 prescalar
            break;

    }
}

void DigitalPin::set_TCNT(int val){
    switch (_pin){
        case 44:
            TCNT5 = val;
            break;
        case 11:
            TCNT1 = val;
            break;      
        case 6:
            TCNT4 = val;
            break;
        case 5:
            TCNT3 = val;
            break;

    }
}
void DigitalPin::set_OCR(int val){
    switch (_pin){
        case 44:
            OCR5A = val;
            break;
        case 11:
            OCR1A = val;
            break;      
        case 6:
            OCR4A = val;
            break;
        case 5:
            OCR3A = val;
            break;
    }
}

void DigitalPin::factor_OCR(int factor){
    switch (_pin){
        case 44:
            OCR5A /= factor;
            break;
        case 11:
            OCR1A /= factor;
            break;      
        case 6:
            OCR4A /= factor;
            break;
        case 5:
            OCR3A /= factor;
            break;
    }
}

void DigitalPin::set_TIMSK(int val){
    if (val == 1){
        switch (_pin){
            case 44:
                TIMSK5 = 0;
                TIMSK5 |= (1<<OCIE0A);
                break;
            case 11:
                TIMSK1 = 0;
                TIMSK1 |= (1<<OCIE1A);
                break;      
            case 6:
                TIMSK4 = 0;
                TIMSK4 |= (1<<OCIE4A);
                break;
            case 5:
                TIMSK3 = 0;
                TIMSK3 |= (1<<OCIE3A);
                break;

        }
    }
    if (val == 0){
        switch (_pin){
            case 44:
                TIMSK5 = 0;
                break;
            case 11:
                TIMSK1 = 0;
                break;      
            case 6:
                TIMSK4 = 0;
                break;
            case 5:
                TIMSK3 = 0;
                break;

        }
    }
}


void DigitalPin::set_pin(){
    if (_pin == 5){
        _DDR = &DDRE;
        _PORT = &PORTE;
        _PIN = &PINE;
        _bits = (1 << (3));
    }
    else if (_pin == 6){
        _DDR = &DDRH;
        _PORT = &PORTH;
        _PIN = &PINH;
        _bits = (1 << (3));
    }
    else if (_pin == 11){
        _DDR = &DDRB;
        _PORT = &PORTB;
        _PIN = &PINB;
        _bits = (1 << (5));
    }
    else if (_pin == 44){
        _DDR = &DDRL;
        _PORT = &PORTL;
        _PIN = &PINL;
        _bits = (1 << (5));
    }
}

void DigitalPin::set_output_mode(){
    *(_DDR) |= _bits;
}
void DigitalPin::on(){
    *(_PORT) |= _bits;
}
void DigitalPin::off(){
    *(_PORT) &=  B00000000;
}
void DigitalPin::invert_pin(){
    *(_PIN) |= (_bits);
}
void DigitalPin::set_input_mode(){
    *(_DDR) &= ~(_bits);
}

void DigitalPin::set_ICR(){
    switch (_pin){
        case 6:
            TCCR4A = (1<<WGM41) | (1<<COM4A1);
            TCCR4B = (1<<WGM43) | (1<<CS40);
            ICR4 = 255;
            OCR4A = 0;
            TCNT4 = 0;
            break;
    }
}
void DigitalPin::set_duty_cycle(int val){
    switch (_pin){
        case 6:
            OCR4A = (val * 255) / 100;
            break;
    }
}