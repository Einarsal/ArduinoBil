//
// Created by Pe1nab on 10/11/2026.
//

#ifndef DRIVECONTROLLER_H
#define DRIVECONTROLLER_H

#include <Arduino.h>

void driveControllerConstructor();
void stop();
void driveForward();
void turnShallowRight();
void turnShallowLeft();
void turnSharpRight();
void turnSharpLeft();
void turn(int turnTime, bool direction);
void fullPower();
void toggleBrakes(int direction);
int correctStopTime();
void viggoStop();
void straightOut();
#endif //ARDUINOTEST1_DRIVECONTROLLER_H
