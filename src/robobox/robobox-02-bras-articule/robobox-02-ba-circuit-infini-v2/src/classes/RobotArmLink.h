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