#include "Particle.h"
SYSTEM_MODE(AUTOMATIC); 
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D3;

/*
    PIR sensor
        VCC -> 3.3v
        GND -> GND
        OUT -> D2 (digital output)
        A -> nothing (analog output)
*/
int counter = 0;
int prevAlarm = LOW;
unsigned long prevMillis = 0;
const unsigned long WAKE_DURATION = 60000;
const unsigned long SLEEP_DURATION = 20000;

int prevButton = HIGH;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_PIR, INPUT);
    Serial.println(9600);
}

//example 1 - timer
// set a millis timer to put the device every minute
// then we add the WAKE code to make the device wake up after 20 sec
void wakeOnTimer() {
    //set the millis timer for how long the device should be awake
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WAKE_DURATION) {
        prevMillis = curMillis;

        Serial.println("About to sleep...");
        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(SLEEP_DURATION);
        System.sleep(config);
        Serial.println("Just woke up");
    }
}

//example 2 - button
// have a button press put the device to sleep
// and another press wake it back up
void wakeOnButton() {
    int currButton = digitalRead(PIN_BUTTON);
    if (currButton == LOW && prevButton == HIGH) {
        Serial.println("About to sleep");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(PIN_BUTTON, FALLING).gpio(PIN_PIR, RISING);
        System.sleep(config);
    }
    prevButton = currButton;
}

void loop() {
    // wakeOnTimer();
    wakeOnButton();

    // int curAlarm = digitalRead(PIN_PIR);
    // if (curAlarm == HIGH) {
    //     //movement
    //     Serial.println(String(counter++) + ": Movement detected");
    // }

    // what if we want ONE message when there is movement
    // and one message when the movement stop  ---> latch

    // // detect moment
    // if (prevAlarm == LOW && curAlarm == HIGH) {
    //     Serial.println("movement started");
    // } else if (prevAlarm == HIGH && curAlarm == LOW) {
    //     Serial.println("Movement stopped");
    // }
    // prevAlarm = curAlarm;
}