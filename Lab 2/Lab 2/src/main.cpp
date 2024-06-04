#include <Arduino.h>
#include <Safe.h>
#include <DigitalPin.h>

#define RED1 11
#define RED2 44
#define RED3 6
#define RED4 5
DigitalPin LED[4] = {DigitalPin(RED1), DigitalPin(RED2), DigitalPin(RED3), DigitalPin(RED4)};
int password = 1234;
Safe Pass(password);
// int password = random(10000);
int attempts = 99;
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  noInterrupts();
  for (int x = 0; x < 4; x++)
  {
    LED[x].set_TCCRA(0);
    LED[x].set_TCCRB(0);
    LED[x].set_TCNT(0);
    LED[x].set_OCR(31248);
    LED[x].set_TIMSK(1);
  }
  interrupts();

  // put your setup code here, to run once:
}

void loop()
{
  if(attempts==99){
    Serial.print("This is the code");
    Pass.displayCode();
    Serial.println("Input Guess");
    attempts = 0;

    }

  while (Serial.available() == 4)
  {
    

    
    int Val = Serial.parseInt();
    int copy = Pass.getCode();

    Serial.println(Val, DEC);
    int Val4 = Val % 10;
    Val/=10;
    int Val3 = Val % 10;
    Val/=10;
    int Val2 = Val % 10;
    Val/=10;
    int Val1 = Val % 10;
    int password4 = copy % 10;
    copy /= 10;
    int password3 = copy % 10;
    copy /= 10;
    int password2 = copy % 10;
    copy /= 10;
    int password1 = copy % 10;
//Serial.println(Val4);
//Serial.println(password4);

    if (Val4 == password4)
    {
      LED[3].set_TIMSK(0);
      LED[3].Off();
    }
    if (Val3 == password3)
    {
      LED[2].set_TIMSK(0);
      LED[2].Off();
    }
    if (Val2 == password2)
    {
      LED[1].set_TIMSK(0);
      LED[1].Off();
    }
  
    if (Val1 == password1)
    {
      LED[0].set_TIMSK(0);
      LED[0].Off();
    }

    attempts++;
    Serial.println(attempts);
    for (int i = 0; i < 4; i++)
    {
      LED[i].factor_OCR(2);
    }
    Serial.println("Input Guess");
    if (attempts == 5)
    {
      Serial.println("TOO MANY ATTEMPS");
      for (int k = 0; k < 4; k++)
      {
        LED[k].set_TIMSK(0);
        LED[k].On();
      }
    }
  }
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(RED1, !digitalRead(RED1));
}

ISR(TIMER5_COMPA_vect)
{
  digitalWrite(RED2, !digitalRead(RED2));
}

ISR(TIMER4_COMPA_vect)
{
  digitalWrite(RED3, !digitalRead(RED3));
}

ISR(TIMER3_COMPA_vect)
{
  digitalWrite(RED4, !digitalRead(RED4));
}
