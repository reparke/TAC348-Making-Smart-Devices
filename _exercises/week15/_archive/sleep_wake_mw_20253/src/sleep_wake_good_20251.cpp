#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUTTON = D10;
int prevButtonVal = HIGH;

/*
    press a button to make device go to sleep
    then press a button AGAIN to turn back on
*/
void wakeOnButton() {
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        // this is the button to PUT TO SLEEP

        Serial.println("About to sleep...");
        SystemSleepConfiguration config;  // sleep config mgr
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(PIN_BUTTON, FALLING);
        System.sleep(config);
        // now a button press wakes it up

        // this is where the photon PAUSES while sleeping

        Serial.println("Waking up...");
    }
    prevButtonVal = curButtonVal;
}

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}

void loop() { wakeOnButton(); }