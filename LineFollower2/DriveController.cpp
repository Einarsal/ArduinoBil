//
// Created by Pe1nab on 10/11/2026.
//

#include "DriveController.h"
#include "Definitions.h"
#include "LineFollower.h"

int fullSpeedA;
int fullSpeedB;
int drivingSpeed;

const int a[] = { directionA, pwmA, brakeA };
const int b[] = { directionB, pwmB, brakeB };

void driveControllerConstructor() {
  //sätt alla pins för a och b till output
  for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
    pinMode(a[i], OUTPUT);
    pinMode(b[i], OUTPUT);
  }

  fullSpeedA = (int)(kalibreringA * MAXPOWER);
  fullSpeedB = (int)(kalibreringB * MAXPOWER);
  drivingSpeed = STOPPED;
}

void viggoStop() {
  digitalWrite(directionA, BACKWARDS);
  digitalWrite(directionB, BACKWARDS);
  fullPower();
  delay(correctStopTime());
  drivingSpeed = STOPPED;
  stop();
}

void stop() {
  //sätt på bromsarna
  toggleBrakes(ON);

  //stäng av motorerna
  analWrite(pwmA, OFF);
  analWrite(pwmB, OFF);

  //delay(correctStopTime());
}

void driveForward() {
  toggleBrakes(OFF);

  //motorerna ska köra frammåt
  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, FORWARD);

  fullPower();
}


void turnShallowRight() {
  //Serial.println("shallowRight");
  toggleBrakes(OFF);

  //motorerna ska köra frammåt
  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, FORWARD);

  analWrite(pwmA, fullSpeedA);
  analWrite(pwmB, (int)(steerfactor * fullSpeedB));
}

void turnShallowLeft() {
  //Serial.println("shallow left");
  toggleBrakes(OFF);

  //motorerna ska köra frammåt
  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, FORWARD);

  analWrite(pwmA, (int)(steerfactor * fullSpeedA));
  analWrite(pwmB, fullSpeedB);
}
/*
void turnSharpRight() {
    //   Serial.println("sharpRight");
    analWrite(pwmA, (int) (kalibreringA * MAXTURNSPEED));
    analWrite(pwmB, OFF);

    digitalWrite(brakeA, OFF);
    digitalWrite(brakeB, ON);

    //toggleBrakes(OFF);

    digitalWrite(directionA, FORWARD);
    digitalWrite(directionB, FORWARD);
}

void turnSharpLeft() {
    // Serial.println("sharpLeft");

    analWrite(pwmA, OFF);
    analWrite(pwmB, (int) (kalibreringB * MAXTURNSPEED));

    digitalWrite(brakeA, ON);
    digitalWrite(brakeB, OFF);

    // toggleBrakes(OFF);

    digitalWrite(directionA, FORWARD);
    digitalWrite(directionB, FORWARD);
}
*/



void turnSharpRight() {
  //   Serial.println("sharpRight");
  //analWrite(pwmA, (int) (kalibreringA * MAXTURNSPEED));
  //analWrite(pwmB, 255);

  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, BACKWARDS);

  fullPower();

  delay(sharpTurnStopTime);

  analWrite(pwmB, OFF);
  digitalWrite(brakeA, OFF);
  digitalWrite(brakeB, ON);

  //toggleBrakes(OFF);
}

void turnSharpLeft() {
  // Serial.println("sharpLeft");

  // analWrite(pwmA, 255);
  //analWrite(pwmB, (int)(kalibreringB * MAXTURNSPEED));

  digitalWrite(directionA, BACKWARDS);
  digitalWrite(directionB, FORWARD);

  fullPower();

  delay(sharpTurnStopTime);

  analWrite(pwmA, OFF);
  digitalWrite(brakeA, ON);
  digitalWrite(brakeB, OFF);

  // toggleBrakes(OFF);
}
//räta ut bilen efter sväng


void turn(int turnTime, bool direction) {
  toggleBrakes(OFF);

  digitalWrite(directionA, direction);
  digitalWrite(directionB, !direction);

  fullPower();

  delay(turnTime);
}

void fullPower() {
  analWrite(pwmA, fullSpeedA);
  analWrite(pwmB, fullSpeedB);
  drivingSpeed = FULLSPEED;
}

void toggleBrakes(int direction) {
  digitalWrite(brakeA, direction);
  digitalWrite(brakeB, direction);
}

//hur lång tid behövs för att stanna
int correctStopTime() {
  switch (drivingSpeed) {
    case STOPPED: return 0;
    case FULLSPEED: return fullSpeedStopTime;
    case TURNSPEED: return turnSpeedStopTime;
    case VIGGOSTOP: return viggoStopTime;
    default: return 1000;
  }
}
