const byte O = OUTPUT;
const byte I = INPUT;
const byte H = HIGH;
const byte L = LOW;

const int SENSOR_PIN = A0;
const int SERIAL_PORT = 9600;

const int TEMP_INTERVAL = 15;
const int TEMP_BASELINE = 0;

const int SENSOR_VAL_MIN = 20;
const int SENSOR_VAL_MAX = 358;
const int SENSOR_TEMP_MIN = -40;
const int SENSOR_TEMP_MAX = 125;

const int LED_PIN_MIN = 2;
const int LED_PIN_MAX = 6;
const int LED_COUNT = LED_PIN_MAX - LED_PIN_MIN + 1;

const int lOOP_DELAY = 300;

void setup()
{
  Serial.begin(SERIAL_PORT);
  
  for(int pinNumber = LED_PIN_MIN; pinNumber <= LED_PIN_MAX; pinNumber++) {
    pinMode(pinNumber, O);
    digitalWrite(pinNumber, L);
  }
  
  Serial.print("Ready!");
}

void loop()
{
  int sensorVal = analogRead(SENSOR_PIN);
  float t = map(sensorVal, SENSOR_VAL_MIN, SENSOR_VAL_MAX, SENSOR_TEMP_MIN, SENSOR_TEMP_MAX);
  
  Serial.print("\nSensor Value: ");
  Serial.print(sensorVal); 
  Serial.print("\tdegrees C: ");
  Serial.print(t);
  
  for(int i = 0; i < LED_COUNT; i++) {
	  int pinNumber = LED_PIN_MIN + i;
	  int tempLevel = TEMP_BASELINE + (i * TEMP_INTERVAL);
	  if(t > tempLevel) {
		digitalWrite(pinNumber, H);
	  }	else {
		digitalWrite(pinNumber, L);
	  }
  }  
  
  delay(lOOP_DELAY);
}