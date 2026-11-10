//
// Created by Pe1nab on 10/11/2026.
//


//0.6m/s frammåt
// 90deg 1 hjul borde vara 442ms

//Alla konstanter och som är definierade med #define

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//A-motorns tre pins
#define directionA 12
#define pwmA 3
#define brakeA 9

//B-motorns tre pins
#define directionB 13
#define pwmB 11
#define brakeB 8

//den pin som startar bilen när den får ström.
#define startInput 2

//motsvarighet till enums för sensorernas pins.
#define leftEdgeDetector 4
#define leftMidDetector 5
#define midDetector 6 
#define rightMidDetector 7
#define rightEdgeDetector 10

//en tydligare och lättare omskrivning för sensorerna som ska användas när det handlar om vad bilen har gjort snarare än vilken sensor
#define sharpLeft leftEdgeDetector
#define shallowLeft leftMidDetector
#define straightforward midDetector
#define shallowRight rightMidDetector
#define sharpRight rightEdgeDetector

//hur lång tid tar det att svänga 90 grader. Används inte här men är bra att ha för kvadraten
#define turn90Time 223

//hur mycket långsammare ska innermotorn köra i en svag sväng
#define steerfactor 0.4f

//används för att båda motorerna ska köra lika fort med samma input. Eftersom motor A är något långsammare snurrar motor B 98% av sin maxhastighet
#define kalibreringA 1.0f
#define kalibreringB 0.98f

//Definierar hur fort motorerna ska snurra
#define MAXPOWER 255
#define MAXTURNSPEED 255
//hur länge innermotorn ska köra baklänges i en skarp sväng
#define sharpTurnStopTime 34

#define viggoStopTime 400

//använder en boolean för höger och vänster. Det blir mycket tydligare om man då kan skriva RIGHT och LEFT istället
#define RIGHT true
#define LEFT false
//forward och backwards är mycket tydligare än LOW och HIGH
#define FORWARD LOW
#define BACKWARDS HIGH
//on och off är i vissa fall tydligare än HIGH och LOW
#define ON HIGH
#define OFF LOW

//jag skrev fel varje gång jag försökte skriva analogWrite så jag skapade den här för att göra det lättare.
//Den gör varken koden eller bilen bättre eller sämre. Bara lättare att för mig att skriva.

#define analWrite analogWrite
#endif //ARDUINOTEST1_DEFINITIONS_H
