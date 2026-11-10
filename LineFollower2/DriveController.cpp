//
// Created by Pe1nab on 10/11/2026.
// DriveController är en mvc controller. När jag skrev namnet tänkte jag inte att det kunde vara relvant

#include "DriveController.h"
#include "Definitions.h"
#include "LineFollower.h"

int fullSpeedA;
int fullSpeedB;
int drivingSpeed;

const int a[] = { directionA, pwmA, brakeA };
const int b[] = { directionB, pwmB, brakeB };

//konstruktor.
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

//används inte men finns kvar för att minnas viggos vinnande idé för att svänga skarpare och köra snabbare
//void viggoStop() {
//  digitalWrite(directionA, BACKWARDS);
//  digitalWrite(directionB, BACKWARDS);
//  fullPower();
//  delay(correctStopTime());
//  drivingSpeed = STOPPED;
//  stop();
//}

//stannar bilen
void stop() {
  //sätt på bromsarna
  toggleBrakes(ON);

  //stäng av motorerna
  analWrite(pwmA, OFF);
  analWrite(pwmB, OFF);
}

//kör rakt fram i maxhastighet
void driveForward() {
  toggleBrakes(OFF);

  //motorerna ska köra frammåt
  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, FORWARD);

  fullPower();
}

//svänger svagt höger genom att köra den yttre motorn snabbare än den inre
void turnShallowRight() {
  //Serial.println("shallowRight");
  toggleBrakes(OFF);

  //motorerna ska köra frammåt
  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, FORWARD);

  analWrite(pwmA, fullSpeedA);
  analWrite(pwmB, (int)(steerfactor * fullSpeedB));
}

//svänger svagt vänster genom att köra den yttre motorn snabbare än den inre
void turnShallowLeft() {
  //Serial.println("shallow left");
  toggleBrakes(OFF);

  //motorerna ska köra frammåt
  digitalWrite(directionA, FORWARD);
  digitalWrite(directionB, FORWARD);

  analWrite(pwmA, (int)(steerfactor * fullSpeedA));
  analWrite(pwmB, fullSpeedB);
}

//svänger skarpt höger genom att köra den inre motorn baklänges en kort stund och sedan stanna den helt.
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

//svänger skarpt vänster genom att köra den inre motorn baklänges en kort stund och sedan stanna den helt.
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

//maxhastighet på båda motorerna
void fullPower() {
  analWrite(pwmA, fullSpeedA);
  analWrite(pwmB, fullSpeedB);
  drivingSpeed = FULLSPEED;
}

//på/av båda bromsarna
void toggleBrakes(int direction) {
  digitalWrite(brakeA, direction);
  digitalWrite(brakeB, direction);
}
}
