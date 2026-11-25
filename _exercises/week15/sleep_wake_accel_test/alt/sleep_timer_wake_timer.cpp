// Sleep after 30 seconds awake; wake after 10 seconds asleep.
#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;

const unsigned long WAKE_DURATION = 30000;  // Stay awake for 30 seconds
unsigned long prevMillis = 0;
const unsigned long SLEEP_DURATION = 10000;  // Sleep for 10 seconds

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    changeRgbLed(0, 255, 0);  // Green means awake
    Serial.println("Awake. Going to sleep in 30 seconds.");
    prevMillis = millis();
}

void sleepOnTimer() {
    unsigned long curMillis = millis();

    if (curMillis - prevMillis > WAKE_DURATION) {
        prevMillis = curMillis;
        Serial.println("Going to sleep for 10 seconds.");
        changeRgbLed(0, 0, 0);  // LED off while asleep
        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER)
            .duration(SLEEP_DURATION);
        System.sleep(config);

        // Execution continues here after waking.
        prevMillis = millis();  // Start a new 30-second awake timer
        changeRgbLed(0, 255, 0);
        Serial.println("Awake again. Going to sleep in 30 seconds.");
    }
}

void loop() {
    sleepOnTimer();
}
