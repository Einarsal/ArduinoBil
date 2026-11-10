//main metoden

#include "DriveController.h"
#include "Definitions.h"
#include "LineFollower.h"


//om started == false ska bilen inte köra
bool started;
//används när ingen av sensorerna ger utslag
int lastAction = straightforward;
//används för att räta ut bilen. Då ska den svänga åt motsatta hållet tills den är rak
bool lastDirection = LEFT;


void setup() {
    driveControllerConstructor();
    //använder pin 2 som startsignal. Om 2 inte är på ska den inte köra
    pinMode(startInput, INPUT);
    started = false;
}

void loop() {
    if (!shouldRun())
    return;
    followLine();
}

//metoden tar reda på vart bilen ska svänga baserat på vilka sensorer som ger utslag.
//kantsensorerna ska prioriteras.
void followLine() {
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

//anropar rätt metod för att svänga i DriveController.cpp bilen kan både svänga skarpt och svagt
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
        shallowCorner(RIGHT);
        break;

        case shallowLeft:
        lastAction =shallowLeft;
        lastDirection = LEFT;
        shallowCorner(LEFT);
        break;
    }
}

//denna metod anropar shallowRight eller shallowLeft i drivecontroller. Bilen ska bara svänga svagt om de yttre sensorerna är av.
//Metoden används också till att räta ut bilen och kan anropas då av straightOut.
void shallowCorner(int direction) {
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

//anropar sharpLeft och shallowRight från drivecontroller.cpp. Eftersom skarpa svängar prioriteras ska bilen svänga skarpt tills något
//annat sägs. Om de yttre sensorer slutar ge utslag kollar bilen om mitten är på och rätar därefter ut. Om inte kollar den om den ska
//fortsätta svänga svagt och om inte går den tillbaks till followLine. Den går inte till loop för startkontrollen tar mycket tid
void sharpCorner(int direction) {
    switch (direction) {
        case RIGHT:
        do {
            turnSharpRight();
        } while (isDetected(rightEdgeDetector));
            if (isDetected(midDetector)) straightOut ();
            if(isDetected(rightMidDetector)) turnAroundCorner(shallowRight);
        break;

        case LEFT:
        do {
            turnSharpLeft();
        } while (isDetected(leftEdgeDetector));
            if (isDetected(midDetector)) straightOut ();
            if(isDetected(leftMidDetector)) turnAroundCorner(shallowLeft);
        break;
    }
    followLine();
}

//rätar ut bilen efter en sväng. Den kör rakt fram tills mitten slutar ge utslag och svänger därefter åt det motsatta hållet.
void straightOut() {
    lastAction = straightforward;
    do {
        driveForward();
    } while (!isDetected(midDetector));
    shallowCorner(!lastDirection);
}

//kollar om pin 2 är high eller low. Om den är high och started är false kör den igång startsekvensen som ska vänta i 2 sekunder innan
//bilen börjar köra.
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
