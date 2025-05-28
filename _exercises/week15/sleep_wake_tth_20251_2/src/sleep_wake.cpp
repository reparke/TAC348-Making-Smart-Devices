#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;
int counter = 0;
int prevAlarm = LOW;
int prevButton = HIGH;

unsigned long prevMillis = 0;

// example 1 - timer
void wakeOnTimer() {
    // set a millis timer for how the device should be AWAKE
    // when the timer is up, put the device to sleep for certain time
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > 60000) {
        prevMillis = curMillis;
        Serial.println("Going to sleep...");

        // sleep code from particle documentation
        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).duration(20000);
        System.sleep(config);
    }
}

// example 2
void wakeOnButton() {
    // press a button to make device go to sleep
    // then press button again to turn back on
    int curButton = digitalRead(PIN_BUTTON);
    if (curButton == LOW && prevButton == HIGH) {
        Serial.println("About to sleep from button press...");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER).gpio(PIN_BUTTON, FALLING).gpio(PIN_PIR, RISING);
        System.sleep(config);
    }
    prevButton = curButton;
}

void setup() {
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    Serial.begin(9600);
}
void loop() {
    // wakeOnTimer();
    wakeOnButton();

    // int currentAlarm = digitalRead(PIN_PIR);
    // // HIGH movement detected
    // // LOW no movement
    // if (currentAlarm == HIGH) {
    //     Serial.println(String(counter++) + " Movement detected");
    // }
    // what if instead we wanted ONE message that says movement detected
    // and one message that says movement stopped?

    // int currentAlarm = digitalRead(PIN_PIR);
    // if (currentAlarm == HIGH && prevAlarm == LOW) {
    //     Serial.println("movement detected");
    // } else if (currentAlarm == LOW && prevAlarm == HIGH) {
    //     Serial.println("Movement stopped");
    // }
    // prevAlarm = currentAlarm;
}