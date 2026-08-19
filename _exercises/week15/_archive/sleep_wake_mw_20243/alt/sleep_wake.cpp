#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// version 1 - have argon sleep and wake automatically
//  go to sleep for certain amount of time, wake up and stay for a certain time,
//  then repeat CAVEAT! set the WAKE duration to be long enough that you can
//  reflash your device if device is only sleeping for < 1 min, then just keep
//  it on one more thing: we are turning the argon fully on and enabling wifi
//       BUT  you can turn it on, and NOT turn on Wifi
unsigned long WAKE_DURATION = 120000;  // awake for 2 min
unsigned long SLEEP_DURATION = 20000;  // sleep for 20 sec
unsigned long prevMillis = 0;

int curButtonVal = HIGH;
int prevButtonVal = HIGH;

void lowPowerWakeOnTimer() {
    // set a millis timer for how long device should be AWAKE
    // when timer expires, put the device to sleep a certain time
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WAKE_DURATION) {  // time now to go to sleep
        prevMillis = curMillis;
        Serial.println("About to go to sleep...");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(SLEEP_DURATION);
        System.sleep(config);

        Serial.println("...Just woke up");
    }
}

// version 2 - press a button to make device sleep, then press button to wake up
// CAVEAT: in order to wakeup device with button press, you have to connect
// button to pin D10 (WKP pin)
void lowPowerWakeOnButton() {
    // read WKP pin
    // using latch, on rising edge, cause device to sleep
    // set sleep config so a button press wakes it back up again
    curButtonVal = digitalRead(WKP);  // notice we did not create pin label
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        Serial.println("About to sleep on button press");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(WKP, CHANGE);
        System.sleep(config);
    }
    prevButtonVal = curButtonVal;
}

void setup() {
    Serial.begin(9600);
    pinMode(WKP, INPUT);
}

void loop() {
    // lowPowerWakeOnTimer();
    lowPowerWakeOnButton();
}