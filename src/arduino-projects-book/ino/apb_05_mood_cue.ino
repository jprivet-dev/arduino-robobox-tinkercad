#include <Servo.h>
Servo myServo;

const int serialPort = 9600;
const int potPin = A0;
const int servoPin = 9;
const int potValMin = 0;
const int potValMax = 1023;
const int angleMin = 0;
const int angleMax = 179;

int potVal;
int angle;

void setup()
{
  myServo.attach(servoPin);
  Serial.begin(serialPort);
}

void loop()
{
  potVal = analogRead(potPin);
  
  Serial.print("\n potVal: ");
  Serial.print(potVal);
  
  angle = map(potVal, potValMin, potValMax, angleMin, angleMax);

  Serial.print("\t angle: ");
  Serial.print(angle);
  
  myServo.write(angle);
  delay(15);
}