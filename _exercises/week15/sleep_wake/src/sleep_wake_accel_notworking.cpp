#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "SparkFun_ADXL345.h"  // SparkFun ADXL345 Library

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin

// This pin must be connected to the INT1 pin on the ADXL345 breakout.
const int PIN_ADXL_INT = D2;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

int doubleTapCount = 0;
int tapCount = 0;
int activityCount = 0;

ADXL345 adxl = ADXL345();  // USE FOR I2C COMMUNICATION

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_ADXL_INT, INPUT);

    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    Serial.begin(9600);  // Start the serial terminal

    adxl.powerOn();  // Power on the ADXL345

    adxl.setRangeSetting(2);  // Give the range settings
                              // Accepted values are 2g, 4g, 8g or 16g
                              // Higher Values = Wider Measurement Range
                              // Lower Values = Greater Sensitivity

    adxl.setTapDetectionOnXYZ(
        0, 0, 1);  // Detect taps in the directions turned ON
                   // "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

    // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
    adxl.setTapThreshold(30);      // 62.5 mg per increment
    adxl.setTapDuration(40);       // 625 μs per increment
    adxl.setDoubleTapLatency(80);  // 1.25 ms per increment
    adxl.setDoubleTapWindow(240);  // 1.25 ms per increment

    // Setting all interupts to take place on INT1 pin
    // adxl.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets
    // "adxl.setEveryInterruptMapping(single tap, double tap, free fall,
    // activity, inactivity);"
    // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin
    // on the ADXL345 to use for Interrupts. This library may have a problem
    // using INT2 pin. Default to INT1 pin.

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    adxl.ActivityINT(0);
    adxl.doubleTapINT(1);
    adxl.singleTapINT(0);

    // It's good practice to read the interrupt source register to clear any
    // lingering interrupts from startup or a previous run. This prevents an
    // immediate trigger on the first loop.
    adxl.getInterruptSource();

    // adxl.readAndCalcAccel();
    // adxl.readDoubleTap();
}

// example 3
// description: photon 2 should sleep on doubleTap and wake on doubleTap
void wakeOnAccel() {
    adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's

    // A double tap from the ADXL345 will trigger this function to put the
    // device to sleep. The ADXL345 INT1 pin (connected to PIN_ADXL_INT) will go
    // HIGH when a double tap occurs. We configure the system to wake up on the
    // next double tap, which will also cause a RISING edge on PIN_ADXL_INT.
    if (adxl.readDoubleTap() == true) {
        Serial.println("Double tap detected. About to sleep...");
        changeRgbLed(0, 0, 0);  // Turn off LED before sleeping

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER)
            .gpio(PIN_ADXL_INT,
                  RISING);  // Wake on RISING edge from ADXL345 INT1 pin
        // System.sleep(config);

        // adxl.getInterruptSource();

        // After waking up, you might want to re-initialize things or just
        // continue.
        Serial.println("Woke up from double tap!");
    }
}

void loop() {
    // adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's
    wakeOnAccel();

}
