#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;
int count = 0;
int prevAlarm = LOW;

void setup() {
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() {
    int currentAlarm = digitalRead(PIN_PIR);
    // HIGH movement detected
    // LOW no movement detected

    // if(currentAlarm == HIGH) {
    //     Serial.println(String(count++) + ": Movement detected");
    // }

    // what if instead we wanted ONE message that says Movement Detected, and then stopped?

    //mvmt detected
    if ( currentAlarm == HIGH && prevAlarm == LOW) {
        Serial.println("Movement has started");
    }
    else if (currentAlarm == LOW && prevAlarm == HIGH) {
        Serial.println("Movement has stopped");
    }
    prevAlarm = currentAlarm;

}