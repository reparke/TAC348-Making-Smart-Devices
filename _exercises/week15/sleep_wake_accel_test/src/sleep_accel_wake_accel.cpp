// Double tap to sleep; double tap again to wake.
#include "Particle.h"
#include "SparkFun_ADXL345.h"

// This classroom example does not need a cloud connection.
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;

// Connect ADXL345 INT1 to D2, in addition to SDA, SCL, 3V3, and GND.
// Keep the ADXL345 powered while the Photon 2 sleeps.
const int PIN_ADXL_INT = D2;
ADXL345 adxl = ADXL345();

const unsigned long DOUBLE_TAP_COOLDOWN_MS = 300;
unsigned long prevDoubleTapMillis = 0;
int doubleTapCount = 0;
volatile bool doubleTapDetected = false;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void doubleTapISR() {
    // Only set a flag here. Handle I2C, printing, and sleep in loop().
    doubleTapDetected = true;
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

    attachInterrupt(PIN_ADXL_INT, doubleTapISR, RISING);
    adxl.doubleTapINT(1);

    changeRgbLed(0, 255, 0);  // Green means awake
    Serial.println("Awake. Double tap to sleep.");
}

void sleepOnAccel() {
    unsigned long curMillis = millis();

    if (doubleTapDetected == true) {
        doubleTapDetected = false;

        // Read and clear the sensor interrupt, even during the debounce time.
        bool isDoubleTap = adxl.readDoubleTap();
        if (isDoubleTap == true) {
            if (curMillis - prevDoubleTapMillis > DOUBLE_TAP_COOLDOWN_MS) {
                prevDoubleTapMillis = curMillis;
                doubleTapCount++;
                Serial.println("Double tap count = " + String(doubleTapCount));
                Serial.println("Going to sleep. Double tap again to wake.");
                changeRgbLed(0, 0, 0);  // LED off while asleep

                // The next double tap raises INT1 and wakes the Photon 2.
                SystemSleepConfiguration config;
                config.mode(SystemSleepMode::ULTRA_LOW_POWER)
                    .gpio(PIN_ADXL_INT, RISING);
                System.sleep(config);

                // Execution continues here after waking.
                // Clear the wake event so it does not send us back to sleep.
                if (adxl.readDoubleTap() == true) {
                    doubleTapCount++;
                }
                doubleTapDetected = false;
                prevDoubleTapMillis = millis();

                changeRgbLed(0, 255, 0);  // Green means awake
                Serial.println("Awake again. Double tap to sleep.");
                Serial.println("Double tap count = " + String(doubleTapCount));
            }
        }
    }
}

void loop() {
    sleepOnAccel();
}
