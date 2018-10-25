const byte O = OUTPUT;
const byte I = INPUT;
const byte H = HIGH;
const byte L = LOW;

const int serialPort = 9600;

const int redLedPin = 11;
const int greenLedPin = 9;
const int blueLedPin = 10;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

const int mapSensorValueMin = 54;
const int mapSensorValueMax = 974;
const int mapColorValueMin = 0;
const int mapColorValueMax = 255;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup()
{
  Serial.begin(serialPort);
  
  pinMode(redLedPin, O);
  pinMode(greenLedPin, O);
  pinMode(blueLedPin, O);
}

void loop()
{
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  
  blueSensorValue = analogRead(blueSensorPin);
  delay(5);
  
  Serial.print("\nRaw Sensor Values \t Red :");
  Serial.print(redSensorValue);
  Serial.print("\t Green:");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue:");
  Serial.print(blueSensorValue);
  
  redValue = map(redSensorValue, mapSensorValueMin, mapSensorValueMax, mapColorValueMin, mapColorValueMax);
  greenValue = map(greenSensorValue, mapSensorValueMin, mapSensorValueMax, mapColorValueMin, mapColorValueMax);
  blueValue = map(blueSensorValue, mapSensorValueMin, mapSensorValueMax, mapColorValueMin, mapColorValueMax);
  
  analogWrite(redLedPin, redValue);
  analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
  
  delay(300);
}