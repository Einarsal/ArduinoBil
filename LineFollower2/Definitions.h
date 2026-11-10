//
// Created by Pe1nab on 10/11/2026.
//


//0.6m/s frammåt
// 90deg 1 hjul borde vara 442ms

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define directionA 12
#define pwmA 3
#define brakeA 9

#define directionB 13
#define pwmB 11
#define brakeB 8

#define startInput 2

#define leftEdgeDetector 4
#define leftMidDetector 5
#define midDetector 6 
#define rightMidDetector 7
#define rightEdgeDetector 10

#define sharpLeft leftEdgeDetector
#define shallowLeft leftMidDetector
#define straightforward midDetector
#define shallowRight rightMidDetector
#define sharpRight rightEdgeDetector


#define turn90Time 223
#define steerfactor 0.4f

#define kalibreringA 1.0f
#define kalibreringB 0.98f

#define minCentiDistance 40.0

#define MAXPOWER 255
#define MAXTURNSPEED 255
#define sharpTurnStopTime 34

#define stoppedStopTime 0
#define fullSpeedStopTime 100
#define turnSpeedStopTime 100
#define viggoStopTime 400
#define startDelay 2000
#define straightTime 50

//olika hastigheter tar olika lång tid att bromsa
#define STOPPED 0
#define FULLSPEED 1
#define TURNSPEED 2
#define VIGGOSTOP 3

#define RIGHT true
#define LEFT false
#define FORWARD LOW
#define BACKWARDS HIGH
#define ON HIGH
#define OFF LOW

#define analWrite analogWrite
#endif //ARDUINOTEST1_DEFINITIONS_H
