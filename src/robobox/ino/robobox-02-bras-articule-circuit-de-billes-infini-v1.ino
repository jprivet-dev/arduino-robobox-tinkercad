/*
 * ROBOTIC ARM
 *
 *   by @jprivet_dev <https://twitter.com/jprivet_dev>
 *
 *                    _
 *                   | |
 *                   | |
 *                    |
 *                 . 90° .
 *            .       |       .
 *       135°         |         45°
 *        .           | LINK_0    .
 *                    |
 *      .            | |            .
 *     180°.  .  .  .|o|  . . . . . 0°        SERVO_0
 *                    |
 *                 . 90° .
 *            .       |       .
 *        45°         |         135°
 *        .           | LINK_1    .
 *                    |
 *      .            | |            .
 *      0° .  .  .  .|o|.  .  .  . 180°       SERVO_1
 *            ________|________               BASE
 *
 */

#include <Servo.h>

class RobotArmLink {

  public:
    RobotArmLink(int pin) {
       _pin = pin;
    }

    void init() {
       _servo.attach(_pin);
    }

    int getPin() {
      return _pin;
    }

    int getAngle() {
      return _angle;
    }

    void setAngle(int angle) {
      if(isOutsideTheAngleLimits(angle)) {
        angle = imposeAngleLimits(angle);
      }

      if(sameAsTheCurrentAngle(angle)) {
        return;
      }

      _angle = angle;
      _servo.write(_angle);
    }

    bool isOutsideTheAngleLimits(int angle) {
      return angle < _angleMin || angle > _angleMax;
    }

    int imposeAngleLimits(int angle) {
      if(angle < _angleMin) {
        return _angleMin;
      }

      if(angle > _angleMax) {
        return _angleMax;
      }

      return angle;
    }

    bool sameAsTheCurrentAngle(int angle) {
      return angle == _angle;
    }

    bool moveToAngleTarget(int angle) {
      angle = imposeAngleLimits(angle);
      _moveToAngleCurrent = angle;
      _moveToAngleTarget = angle;
    }

    void moveToAngleNextStep() {
      if(_angle > _moveToAngleTarget) {
        _moveToAngleCurrent = _angle - _step;
      } else if(_angle < _moveToAngleTarget) {
        _moveToAngleCurrent = _angle + _step;
      }

      setAngle(_moveToAngleCurrent);
    }

    bool moveToAngleInProgress() {
      return _angle != _moveToAngleTarget;
    }

  private:
    Servo _servo;
    int _pin;
    int _angle;
    int _angleMin = 0;
    int _angleMax = 180;
    int _step = 1;
    int _moveToAngleCurrent;
    int _moveToAngleTarget;
};

const int STOP = 0;
const int PLAY = 1;

const int DELAY_SHORT = 15;
const int DELAY_DEFAULT = 30;
const int DELAY_LONG = 100;
const int DELAY_WAIT = 500;
const int DELAY_1S = 1000;

const int ROBOT_ARM_LINK_0_PIN = 6;
const int ROBOT_ARM_LINK_1_PIN = 7;
const int BTN_SWITCH_PIN = 2;

const int LED_RED_PIN = 4;
const int LED_GREEN_PIN = 3;

int btnSwitchState = LOW;
int status = STOP;
bool robotIsInTheInitialPosition = false;

RobotArmLink robotArmLink0(ROBOT_ARM_LINK_0_PIN);
RobotArmLink robotArmLink1(ROBOT_ARM_LINK_1_PIN);

void log(char label[]) {
    Serial.println(label);
}

void logLabelNumber(char label[], int number) {
    Serial.print("[ ");
    Serial.print(label);
    Serial.print(" : ");
    Serial.print(number);
    Serial.println(" ]");
}

void robotInit(int angle0, int angle1) {
  log("--- robotInit");
  logLabelNumber("to angle 0", angle0);
  logLabelNumber("to angle 1", angle1);

  robotArmLink0.setAngle(angle0);
  robotArmLink1.setAngle(angle1);

  logLabelNumber("final angle 0", robotArmLink0.getAngle());
  logLabelNumber("final angle 1", robotArmLink1.getAngle());
}

void robotPlay(int angle0, int angle1, int _delay) {
  log("--- robotPlay");
  logLabelNumber("to angle 0", angle0);
  logLabelNumber("to angle 1", angle1);

  robotArmLink0.moveToAngleTarget(angle0);
  robotArmLink1.moveToAngleTarget(angle1);

  while(robotArmLink0.moveToAngleInProgress() || robotArmLink1.moveToAngleInProgress()) {
    robotArmLink0.moveToAngleNextStep();
    robotArmLink1.moveToAngleNextStep();
    delay(_delay);
  }

  logLabelNumber("final angle 0", robotArmLink0.getAngle());
  logLabelNumber("final angle 1", robotArmLink1.getAngle());
}

void robotSequence_manualBallRetrieval() {
    log("> SEQUENCE : manual ball retrieval");

    robotPlay(90, 10, DELAY_SHORT);

    delay(DELAY_1S * 2.5);
};

void robotSequence_retrieveTheBallAtTheEndOfTheCourse() {
    log("> SEQUENCE : retrieve the ball at the end of the course");

    robotPlay(150, 10, DELAY_SHORT);
    robotPlay(180, 40, DELAY_DEFAULT);
    
    delay(DELAY_1S * 3);
    
    log("> SEQUENCE : repositioning after retrieving the ball");
     
    robotPlay(150, 10, DELAY_SHORT);
    robotPlay(90, 20, DELAY_SHORT);
};

void robotSequence_insertTheBallIntoTheCourse() {
    log("> SEQUENCE : insert the ball into the course");

    robotPlay(70, 65, DELAY_DEFAULT);
    
    delay(DELAY_WAIT);
        
    robotPlay(70, 80, DELAY_LONG);

    delay(DELAY_WAIT);
};

void robotSequence_putTheRobotInItsInitialPosition() {
    log("> SEQUENCE : put the robot in its initial position");

    robotPlay(90, 90, DELAY_DEFAULT);
};

void ledsStatus() {
  if(status == STOP) {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
  } else {
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
  }  
}

void btnSwitchStateReadStatus() {
  btnSwitchState = digitalRead(BTN_SWITCH_PIN);
  logLabelNumber("btnSwitchState", btnSwitchState);
  
  if(btnSwitchState == HIGH) {
    logLabelNumber("PREVIOUS status", status);
    status = (status == PLAY) ? STOP : PLAY;
    logLabelNumber("NEW status", status);
  }
  
  ledsStatus();
}

void setup() {
  Serial.begin(9600);
  log("Ready!");

  pinMode(BTN_SWITCH_PIN, INPUT);
  pinMode(ROBOT_ARM_LINK_0_PIN, OUTPUT);
  pinMode(ROBOT_ARM_LINK_1_PIN, OUTPUT); 
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  log("Initialization before loop()");
    
  robotArmLink0.init();
  robotArmLink1.init();

  robotInit(90, 90);
  robotIsInTheInitialPosition = true;
}

void loop() {
  btnSwitchStateReadStatus();

  if(status == STOP) {
    
    if(robotIsInTheInitialPosition == false) {
      robotSequence_putTheRobotInItsInitialPosition();
      robotIsInTheInitialPosition = true;     
    }
            
  } else {

    if(robotIsInTheInitialPosition) {
      robotSequence_manualBallRetrieval();
      robotIsInTheInitialPosition = false;
    } else {
      robotSequence_retrieveTheBallAtTheEndOfTheCourse();
    }
 
    robotSequence_insertTheBallIntoTheCourse();
  } 
}