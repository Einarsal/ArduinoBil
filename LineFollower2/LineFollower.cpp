#include "LineFollower.h"
#include "DriveController.h"
#include "Definitions.h"




const int detectors[] = { leftEdgeDetector, leftMidDetector,
  midDetector, rightMidDetector,
  rightEdgeDetector
};

//de yttre sensorerna ligger först i listan för att prioriteras av foundCorner()
const int turnDetectors[] = {leftEdgeDetector, rightEdgeDetector, leftMidDetector, rightMidDetector, midDetector};

//konstruktor
void linefollowerConstructor() {
  for (int i = 0; i < 5; i++) {
    pinMode(detectors[i], INPUT);
  }
}

//returnerar den första sensorn som ger utslag. Om ingen ger utslag returneras -1. Ett värde som aldrig ska kunna returneras annars
int foundCorner() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(turnDetectors[i]) == HIGH){
      return turnDetector[i];
    } 
  }
  return -1;
}

//kollar om en specifik linjeföljare ger utslag.
bool isDetected(int detector){
  return digitalRead(detector);
}
