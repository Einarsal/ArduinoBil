#include "LineFollower.h"
#include "DriveController.h"
#include "Definitions.h"




const int detectors[] = { leftEdgeDetector, leftMidDetector,
  midDetector, rightMidDetector,
  rightEdgeDetector
};

const int turnDetectors[] = {leftEdgeDetector, rightEdgeDetector, leftMidDetector, rightMidDetector, midDetector};

void linefollowerConstructor() {
  for (int i = 0; i < 5; i++) {
    pinMode(detectors[i], INPUT);
  }
}

int foundCorner() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(turnDetectors[i]) == HIGH){
      return turnDetectors[i];
    } 
  }
  return -1;
}

bool isDetected(int detector){
  return digitalRead(detector);
}

/*
bool isStraight(){
  return digitalRead(midDetector);
}

bool foundRightEdge(){
return digitalRead(rightEdgeDetector);
}
bool foundLeftEdge(){
return digitalRead(leftEdgeDetector);
}

bool foundRightMiddle(){
return digitalRead(rightMidDetector);
}

bool foundLeftMiddle(){
return digitalRead(leftMidDetector);
}
*/

