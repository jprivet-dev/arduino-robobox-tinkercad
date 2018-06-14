const byte O = OUTPUT;
const byte I = INPUT;
const byte H = HIGH;
const byte L = LOW;

const int SENSOR_PIN = A0;
const int SERIAL_PORT = 9600;

const int BASELINE_TEMP = 20.0;
const int BASELINE_TEMP_LEVEL_1 = BASELINE_TEMP;
const int BASELINE_TEMP_LEVEL_2 = BASELINE_TEMP+10;
const int BASELINE_TEMP_LEVEL_3 = BASELINE_TEMP+20;
const int BASELINE_TEMP_LEVEL_4 = BASELINE_TEMP+30;
  
const int PIN_NB_MIN = 2;
const int PIN_NB_MAX = 4;

const int SENSOR_VAL_MIN = 20;
const int SENSOR_VAL_MAX = 358;
const int TEMPERATURE_MIN = -40;
const int TEMPERATURE_MAX = 125;

const int LED_PIN_1 = 4;
const int LED_PIN_2 = 3;
const int LED_PIN_3 = 2;

const int lOOP_DELAY = 300;

void setup()
{
  Serial.begin(SERIAL_PORT);
  
  for(int pinNumber = PIN_NB_MIN; pinNumber <= PIN_NB_MAX; pinNumber++) {
    pinMode(pinNumber, O);
    digitalWrite(pinNumber, L);
  }
}

void loop()
{
  int sensorVal = analogRead(SENSOR_PIN);
  
  Serial.print("\nSensor Value: ");
  Serial.print(sensorVal);
  
  float temperatureDegrees = map(sensorVal, SENSOR_VAL_MIN, SENSOR_VAL_MAX, TEMPERATURE_MIN, TEMPERATURE_MAX);
  
  Serial.print(", degrees C: ");
  Serial.print(temperatureDegrees);
  
  if(temperatureDegrees < BASELINE_TEMP_LEVEL_1) {
    digitalWrite(LED_PIN_1, L);
    digitalWrite(LED_PIN_2, L);
    digitalWrite(LED_PIN_3, L);
  } else if(temperatureDegrees >= BASELINE_TEMP_LEVEL_2 && temperatureDegrees < BASELINE_TEMP_LEVEL_3) {
    digitalWrite(LED_PIN_1, H);
    digitalWrite(LED_PIN_2, L);
    digitalWrite(LED_PIN_3, L);
  } else if(temperatureDegrees >= BASELINE_TEMP_LEVEL_3 && temperatureDegrees < BASELINE_TEMP_LEVEL_4) {
    digitalWrite(LED_PIN_1, H);
    digitalWrite(LED_PIN_2, H);
    digitalWrite(LED_PIN_3, L);
  } else if(temperatureDegrees >= BASELINE_TEMP_LEVEL_4) {
    digitalWrite(LED_PIN_1, H);
    digitalWrite(LED_PIN_2, H);
    digitalWrite(LED_PIN_3, H);
  }
  
  delay(lOOP_DELAY);
}
