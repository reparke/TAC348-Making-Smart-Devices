#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;

/*
    PIR sensor
        VCC -> 3.3v
        GND -> GND
        OUT -> D2 (digital output)
        A -> nothing (analog output)
*/
int counter = 0;
int prevAlarm = LOW;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_PIR, INPUT);
    Serial.println(9600);
}

void loop() {
    int curAlarm = digitalRead(PIN_PIR);
    // if (curAlarm == HIGH) {
    //     //movement
    //     Serial.println(String(counter++) + ": Movement detected");
    // }

    //what if we want ONE message when there is movement
    //and one message when the movement stop  ---> latch

    //detect moment
    if (prevAlarm == LOW && curAlarm == HIGH) {
        Serial.println("movement started");
    }
    else if (prevAlarm == HIGH && curAlarm == LOW) {
        Serial.println("Movement stopped");
    }
    prevAlarm = curAlarm;

}