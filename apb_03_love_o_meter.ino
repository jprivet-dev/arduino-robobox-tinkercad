const int SENSOR_PIN = A0;
const int SENSOR_VAL_MIN = 20;
const int SENSOR_VAL_MAX = 358;
const int SENSOR_TEMP_MIN = -40;
const int SENSOR_TEMP_MAX = 125;

const int SERIAL_PORT = 9600;

const int LED_PIN_MIN = 2;
const int LED_PIN_MAX = 6;
const int LED_COUNT = LED_PIN_MAX - LED_PIN_MIN + 1;

const int TEMP_BASELINE_MIN = SENSOR_TEMP_MIN + 10;
const int TEMP_BASELINE_MAX = SENSOR_TEMP_MAX - 10;
const int TEMP_BASELINE_DELTA = TEMP_BASELINE_MAX - TEMP_BASELINE_MIN;
const int TEMP_INTERVAL = TEMP_BASELINE_DELTA / (LED_COUNT - 1);

const int lOOP_DELAY = 300;

void setup()
{
  Serial.begin(SERIAL_PORT);
  
  for(int ledPin = LED_PIN_MIN; ledPin <= LED_PIN_MAX; ledPin++) {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  }
  
  Serial.print("Ready!");
}

void loop()
{
  int sensorVal = analogRead(SENSOR_PIN);
  float sensorTemp = map(sensorVal, SENSOR_VAL_MIN, SENSOR_VAL_MAX, SENSOR_TEMP_MIN, SENSOR_TEMP_MAX);
  
  Serial.print("\nSensor Value: ");
  Serial.print(sensorVal); 
  Serial.print("\tdegrees C: ");
  Serial.print(sensorTemp);
  
  for(int i = 0; i < LED_COUNT; i++) {
	  int ledPin = LED_PIN_MIN + i;
	  int tempLevel = TEMP_BASELINE_MIN + (i * TEMP_INTERVAL);
	  if(sensorTemp > tempLevel) {
		digitalWrite(ledPin, HIGH);
	  }	else {
		digitalWrite(ledPin, LOW);
	  }
  }  
  
  delay(lOOP_DELAY);
}