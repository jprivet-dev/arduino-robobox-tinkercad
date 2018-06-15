const byte O = OUTPUT;
const byte I = INPUT;
const byte H = HIGH;
const byte L = LOW;

const int SENSOR_PIN = A0;
const int SERIAL_PORT = 9600;

const int TEMP_INTERVAL = 15;
const int TEMP_LEVEL_0 = 0;
const int TEMP_LEVEL_1 = TEMP_LEVEL_0+(1*TEMP_INTERVAL);
const int TEMP_LEVEL_2 = TEMP_LEVEL_0+(2*TEMP_INTERVAL);
const int TEMP_LEVEL_3 = TEMP_LEVEL_0+(3*TEMP_INTERVAL);
const int TEMP_LEVEL_4 = TEMP_LEVEL_0+(4*TEMP_INTERVAL);

const int SENSOR_VAL_MIN = 20;
const int SENSOR_VAL_MAX = 358;
const int TEMP_MIN = -40;
const int TEMP_MAX = 125;

const int LED_1_PIN = 5;
const int LED_2_PIN = 4;
const int LED_3_PIN = 3;
const int LED_4_PIN = 2;

const int LED_PIN_MIN = 2;
const int LED_PIN_MAX = 5;
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
  int tempLevel;
  int pinNumber;
  int level;
  int sensorVal = analogRead(SENSOR_PIN);
  float t = map(sensorVal, SENSOR_VAL_MIN, SENSOR_VAL_MAX, TEMP_MIN, TEMP_MAX);
  
  Serial.print("\nSensor Value: ");
  Serial.print(sensorVal); 
  Serial.print("\tdegrees C: ");
  Serial.print(t);
  
  for(int i = 0; i < LED_COUNT; i++) {
	  pinNumber = i + LED_PIN_MIN;
	  tempLevel = TEMP_LEVEL_0 + (i * TEMP_INTERVAL);
	  if(t > tempLevel) {
		digitalWrite(pinNumber, H);
	  }	else {
		digitalWrite(pinNumber, L);
	  }
  }  
  
  delay(lOOP_DELAY);
}