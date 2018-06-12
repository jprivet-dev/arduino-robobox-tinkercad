const byte O = OUTPUT;
const byte I = INPUT;
const byte H = HIGH;
const byte L = LOW;

const int sensorPin = A0;
const int serialPort = 9600;
const float baselineTemp = 20.0;
  
const int pinNumberMin = 2;
const int pinNumberMax = 4;

const int sensorValFromLow = 20;
const int sensorValToHigh = 358;
const int temperatureFromLow = -40;
const int temperatureToHigh = 125;

const int ledPin1 = 4;
const int ledPin2 = 3;
const int ledPin3 = 2;

void setup()
{
  Serial.begin(serialPort);
  
  for(int pinNumber = pinNumberMin; pinNumber <= pinNumberMax; pinNumber++) {
    pinMode(pinNumber, O);
    digitalWrite(pinNumber, L);
  }
}

void loop()
{
  int sensorVal = analogRead(sensorPin);
  
  Serial.print("\nSensor Value: ");
  Serial.print(sensorVal);
  
  float temperature = map(sensorVal, sensorValFromLow, sensorValToHigh, temperatureFromLow, temperatureToHigh);
  
  Serial.print(", degrees C: ");
  Serial.print(temperature);
  
  if(temperature < baselineTemp) {
    digitalWrite(ledPin1, L);
    digitalWrite(ledPin2, L);
    digitalWrite(ledPin3, L);
  } else if(temperature >= baselineTemp+10 && temperature < baselineTemp+20) {
    digitalWrite(ledPin1, H);
    digitalWrite(ledPin2, L);
    digitalWrite(ledPin3, L);
  } else if(temperature >= baselineTemp+20 && temperature < baselineTemp+30) {
    digitalWrite(ledPin1, H);
    digitalWrite(ledPin2, H);
    digitalWrite(ledPin3, L);
  } else if(temperature >= baselineTemp+30) {
    digitalWrite(ledPin1, H);
    digitalWrite(ledPin2, H);
    digitalWrite(ledPin3, H);
  }
  
  delay(300);
}
