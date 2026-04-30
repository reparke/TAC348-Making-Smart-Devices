

#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_BUTTON = D10;
// wake on button
int prevButton = HIGH;

// wake on timer
unsigned long prevMillis = 0;
const unsigned long WAKE_DURATION = 60000;
const unsigned long SLEEP_DURATION = 20000;

// example 1 - timer
//  set a millis timer to put device to sleep every minute
//  once it is asleep, then have it WAKE UP after 20 sec]
/*
why would we use this type of wake/sleep process?
- non-real time enviro monitor
*/
void wakeOnTimer() {
    // set the millis timer for long the device should be awake
    unsigned long curMillis = millis();

    if (curMillis - prevMillis > WAKE_DURATION) {  // stay awake for 1 minute
        prevMillis = curMillis;

        Serial.println("About to go to sleep...");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(SLEEP_DURATION);
        System.sleep(config);

        Serial.println("...just woke up!");  // should show up but isn't
    }
}

// example 2 - button
// have a button press put the device to sleep
// and then have a second press wake the device back up

void wakeOnButton() {
    // create a latch to trigger the device going to sleep
    int curButtonVal = digitalRead(PIN_BUTTON);

    // latch to trigger sleep
    if (curButtonVal == LOW && prevButton == HIGH) {
        Serial.println("About to sleep....");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(PIN_BUTTON, FALLING);
        System.sleep(config);
        Serial.println("...just woke up");
    }
    prevButton = curButtonVal;
}

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    Serial.println(9600);
}
void loop() { 
    // wakeOnTimer(); 
        
}
