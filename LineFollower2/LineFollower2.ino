#include "DriveController.h"
#include "Definitions.h"
#include "LineFollower.h"



bool started;
int lastAction = straightforward;
bool lastDirection = LEFT;


void setup() {
    //serial begin använder 972 bytes av storage space och 175 bytes av dynamiskt minne. använd inte i onödan!
    //Serial.begin(9600);
    driveControllerConstructor();

    pinMode(startInput, INPUT);
    analogWrite(A2, 255);

    started = false;
}

void loop() {
    if (!shouldRun())
    return;

    followLine();
}

void followLine() {
    //Serial.println("follow line");
    if (!shouldRun())  return;
    int triggeredDetector = foundCorner();
    if (triggeredDetector == -1){
        triggeredDetector = lastAction;
    }
    if ((triggeredDetector == midDetector)) {
        lastAction = straightforward;
        driveForward();
    } else{
        turnAroundCorner(triggeredDetector);
    }
}

//void turnLast(){
//    stop();
//    delay(100);
//    if (lastAction == RIGHT){
//        do{
//            sharpRight();
//        } while (foundCorner == -1);
//        sharpCorner(RIGHT);
//    } else{
//        do{
//            turnSharpLeft();
//        } while (foundCorner == -1);
//        sharpCorner(LEFT);
//    }
//}

void turnAroundCorner(int triggeredDetecor) {
    switch (triggeredDetecor) {
        case sharpRight:
        lastAction = sharpRight;
        lastDirection = RIGHT;
        sharpCorner(RIGHT);
        break;

        case sharpLeft:
        lastAction = sharpLeft;
        lastDirection = LEFT;
        sharpCorner(LEFT);
        break;

        case shallowRight:
        lastAction = shallowRight;
        lastDirection = RIGHT;
        shallowCorner(RIGHT, false);
        break;

        case shallowLeft:
        lastAction =shallowLeft;
        lastDirection = LEFT;
        shallowCorner(LEFT, false);
        break;
    }
}

//skarp sväng har högst prio. ska alltid svänga skarpt om kan.

void shallowCorner(int direction, bool straighten) {
    switch (direction) {
        case RIGHT:
        do {
            if (isDetected(rightEdgeDetector)) {
                turnAroundCorner(sharpRight);
                break;
            }
            turnShallowRight();
        } while (!isDetected(midDetector));
        break;

        case LEFT:
        do {
            if (isDetected(leftEdgeDetector)) {
                turnAroundCorner(sharpLeft);
                break;
            }
            turnShallowLeft();
        }  while (!isDetected(midDetector));
        break;

    }


}


void sharpCorner(int direction) {
    //  stop();
    //  delay(100);
    // Serial.println(direction);
    switch (direction) {
        case RIGHT:
        do {
            turnSharpRight();
        } while (isDetected(rightEdgeDetector));
            if (isDetected(midDetector)) straightOut ();
            if(isDetected(rightMidDetector)) turnAroundCorner(shallowRight);


        //turnAroundCorner(shallowRight);
        break;

        case LEFT:
        do {
            turnSharpLeft();
        } while (isDetected(leftEdgeDetector));
            if (isDetected(midDetector)) straightOut ();
            if(isDetected(leftMidDetector)) turnAroundCorner(shallowLeft);

        //turnAroundCorner(shallowLeft);
        break;

        // default: break;
    }
    followLine();
}

void straightOut() {
    lastAction = straightforward;
    do {
        driveForward();
    } while (!isDetected(midDetector));
    shallowCorner(!lastDirection, true);
}


bool shouldRun() {
    if (started == false) {
        if (digitalRead(startInput) == HIGH) {
            started = true;
            delay(startDelay);
            return true;
        } else return false;
    }
    if (digitalRead(startInput) == LOW) {
        started = false;
        stop();
        return false;
    }
    return true;
}
