// Sleep after 30 seconds awake; double tap to wake.
#include "Particle.h"
#include "SparkFun_ADXL345.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;

const unsigned long WAKE_DURATION = 30000;  // Stay awake for 30 seconds
unsigned long prevMillis = 0;

// Connect ADXL345 INT1 to D2, in addition to SDA, SCL, 3V3, and GND.
// Keep the ADXL345 powered while the Photon 2 sleeps.
const int PIN_ADXL_INT = D2;
ADXL345 adxl = ADXL345();

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    pinMode(PIN_ADXL_INT, INPUT);
    adxl.powerOn();
    adxl.setRangeSetting(2);
    adxl.setTapDetectionOnXYZ(0, 0, 1);  // Z-axis double taps
    adxl.setTapThreshold(30);           // 62.5 mg per increment
    adxl.setTapDuration(40);            // 625 microseconds per increment
    adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
    adxl.setDoubleTapWindow(240);       // 1.25 ms per increment
    adxl.doubleTapINT(1);
    // No awake ISR needed: the timer starts sleep, and config.gpio sets wake.

    changeRgbLed(0, 255, 0);  // Green means awake
    Serial.println("Awake. Going to sleep in 30 seconds.");
    prevMillis = millis();
}

void sleepOnTimer() {
    unsigned long curMillis = millis();

    if (curMillis - prevMillis > WAKE_DURATION) {
        prevMillis = curMillis;
        Serial.println("Going to sleep. Double tap to wake.");
        changeRgbLed(0, 0, 0);  // LED off while asleep

        // Clear taps from the awake period so INT1 can signal a new double tap.
        adxl.readDoubleTap();
        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER)
            .gpio(PIN_ADXL_INT, RISING);
        System.sleep(config);

        // Execution continues here after waking.
        adxl.readDoubleTap();  // Clear the double-tap wake event
        prevMillis = millis();  // Start a new 30-second awake timer
        changeRgbLed(0, 255, 0);
        Serial.println("Awake again. Going to sleep in 30 seconds.");
    }
}

void loop() {
    sleepOnTimer();
}
