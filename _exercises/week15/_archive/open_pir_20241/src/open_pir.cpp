#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_LED = D7;

void setup() {
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // simple -- read sensor and report
    //  to detect movement, look for a HIGH signal
    int currentAlarm = digitalRead(PIN_PIR);

    if (currentAlarm == HIGH) {
        digitalWrite(PIN_LED, HIGH);
        Serial.println("Movement detected");
    } 
    else {
        digitalWrite(PIN_LED, LOW);
        Serial.println("Movement stopped");
    }
}