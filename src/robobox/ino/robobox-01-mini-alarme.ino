int ledPin = 5;               
int inputPin = 2;               
int pinSpeaker = 6;        
int pirState = LOW;           
int val = 0;                  

void setup() {
  pinMode(ledPin, OUTPUT);     
  pinMode(inputPin, INPUT);    
  pinMode(pinSpeaker, OUTPUT);
}

void joueSon (long duree, int frequence) {
    duree *= 1000;
    int period = (1.0 / frequence) * 1000000;
    long temps_passe = 0;
    while (temps_passe < duree) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        temps_passe += (period);
    }
}


void loop(){
  val = digitalRead(inputPin); 

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);  
    joueSon(300, 160);
    delay(150);
    } 
  
  else {
      digitalWrite(ledPin, LOW);
      joueSon(0, 0);
      delay(300);    
   }
}