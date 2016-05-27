#include <Servo.h>
#include "USMXpoints.h"

// Range [600,2200] ~180 deg ==> 9ms ~ 1 degree
Servo mServo[2];
const int SERVO_RANGE[2] = {50, 30}; // 90 ~10 deg

// {BASE,LASER}
const int SERVO_PIN[2] = {3, 5};
const int SERVO_CENTER[2] = {1460, 1530};
const int LASER_PIN = 6;

int mPosition = 0;
const int mDELAY = 4000;

void setup() {
  for (short i = 0; i < 2; i++) {
    mServo[i].attach(SERVO_PIN[i]);
    mServo[i].writeMicroseconds(SERVO_CENTER[i]);
  }
  pinMode(LASER_PIN, OUTPUT);
  analogWrite(LASER_PIN, LOW);
}

void loop() {
  analogWrite(LASER_PIN, (mPosition == 0) ? 0 : 255);

  for (short i = 0; i < 2; i++) {
    mServo[i].writeMicroseconds(SERVO_CENTER[i] + SERVO_RANGE[i] - mPoints[mPosition][i] * 2 * SERVO_RANGE[i]);
  }
  delayMicroseconds(mDELAY);

  if (mPosition == 0) {
    delay(500);
  }

  mPosition = (mPosition + 1) % NUM_POINTS;
}

