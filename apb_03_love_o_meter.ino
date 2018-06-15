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
  float t = map(sensorVal, SENSOR_VAL_MIN, SENSOR_VAL_MAX, TEMP_MIN, TEMP_MAX);
  
  Serial.print("\nSensor Value: ");
  Serial.print(sensorVal); 
  Serial.print("\tdegrees C: ");
  Serial.print(t);
  
  if(t < TEMP_LEVEL_0) {
    digitalWrite(LED_1_PIN, L);
    digitalWrite(LED_2_PIN, L);
    digitalWrite(LED_3_PIN, L);
    digitalWrite(LED_4_PIN, L);
  } else if(t >= TEMP_LEVEL_1 && t < TEMP_LEVEL_2) {
    digitalWrite(LED_1_PIN, H);
    digitalWrite(LED_2_PIN, L);
    digitalWrite(LED_3_PIN, L);
    digitalWrite(LED_4_PIN, L);
  } else if(t >= TEMP_LEVEL_2 && t < TEMP_LEVEL_3) {
    digitalWrite(LED_1_PIN, H);
    digitalWrite(LED_2_PIN, H);
    digitalWrite(LED_3_PIN, L);
    digitalWrite(LED_4_PIN, L);
  } else if(t >= TEMP_LEVEL_3 && t < TEMP_LEVEL_4) {
    digitalWrite(LED_1_PIN, H);
    digitalWrite(LED_2_PIN, H);
    digitalWrite(LED_3_PIN, H);
    digitalWrite(LED_4_PIN, L);
  } else if(t >= TEMP_LEVEL_4) {
    digitalWrite(LED_1_PIN, H);
    digitalWrite(LED_2_PIN, H);
    digitalWrite(LED_3_PIN, H);
    digitalWrite(LED_4_PIN, H);
  }
  
  delay(lOOP_DELAY);
}