byte O = OUTPUT;
byte I = INPUT;
byte H = HIGH;
byte L = LOW;

int switchCase = L;
int time = 250;

int pinLed1Red = 5;
int pinLed2Red = 4;
int pinLed3Green = 3;

int pinButton = 2;

void setup()
{
  pinMode(pinLed1Red, 	O);
  pinMode(pinLed2Red, 	O);
  pinMode(pinLed3Green, O);
  pinMode(pinButton, 	I);
}

void loop()
{
  switchCase = digitalRead(pinButton);
  
  if (switchCase == L) {
    
    digitalWrite(pinLed1Red, 	L);
    digitalWrite(pinLed2Red, 	L);
    digitalWrite(pinLed3Green, 	H);
    
  } else {
    
    digitalWrite(pinLed1Red, 	H);
    digitalWrite(pinLed2Red, 	L);
    digitalWrite(pinLed3Green, 	L);
    
    delay(time);

    digitalWrite(pinLed1Red, 	L);
    digitalWrite(pinLed2Red, 	H);
    
    delay(time);

  }
}
