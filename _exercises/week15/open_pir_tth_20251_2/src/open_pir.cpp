#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;
int counter = 0;
int prevAlarm = LOW;

void setup() {
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}
void loop() {
    // int currentAlarm = digitalRead(PIN_PIR);
    // // HIGH movement detected
    // // LOW no movement
    // if (currentAlarm == HIGH) {
    //     Serial.println(String(counter++) + " Movement detected");
    // }
    // what if instead we wanted ONE message that says movement detected
    // and one message that says movement stopped?

    int currentAlarm = digitalRead(PIN_PIR);
    if (currentAlarm == HIGH && prevAlarm == LOW) {
        Serial.println("movement detected");
    } else if (currentAlarm == LOW && prevAlarm == HIGH) {
        Serial.println("Movement stopped");
    }
    prevAlarm = currentAlarm;
}