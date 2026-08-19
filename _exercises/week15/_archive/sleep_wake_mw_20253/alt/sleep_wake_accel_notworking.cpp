#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "SparkFun_ADXL345.h"  // SparkFun ADXL345 Library

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin

const int PIN_PIR = D2;
const int PIN_BUTTON = D10;
int prevButton = HIGH;

// This pin must be connected to the INT1 pin on the ADXL345 breakout.
const int PIN_ADXL_INT = D3;

// Volatile flag to be set by our Interrupt Service Routine (ISR)
volatile bool doubleTapOccurred = false;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

int doubleTapCount = 0;
int tapCount = 0;
int activityCount = 0;

ADXL345 adxl = ADXL345();  // USE FOR I2C COMMUNICATION

// This is our Interrupt Service Routine (ISR).
// It will be called automatically when a RISING edge is detected on
// PIN_ADXL_INT. It needs to be as short and fast as possible.
void doubleTapISR() { doubleTapOccurred = true; }

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_ADXL_INT, INPUT);

    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    Serial.begin(9600);  // Start the serial terminal

    adxl.powerOn();  // Power on the ADXL345

    adxl.setRangeSetting(2);  // Give the range settings
                              // Accepted values are 2g, 4g, 8g or 16g
                              // Higher Values = Wider Measurement Range
                              // Lower Values = Greater Sensitivity

    adxl.setActivityXYZ(
        1, 0, 0);  // Set to activate movement detection in the axes
                   // "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setActivityThreshold(5);  // 62.5mg per increment   // Set activity //
                                   // Inactivity thresholds (0-255)

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
    // This maps the double-tap interrupt to the INT1 pin on the ADXL345.
    // adxl.setInterruptMapping(interrupt, pin)
    // (.., DOUBLE_TAP, .., to pin INT1)
    // adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN);

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    // adxl.ActivityINT(1);
    adxl.doubleTapINT(1);
    // adxl.singleTapINT(1);

    // Attach a hardware interrupt to the ADXL's interrupt pin.
    // This will call our `doubleTapISR()` function whenever the pin goes from
    // LOW to HIGH (RISING).
    attachInterrupt(PIN_ADXL_INT, doubleTapISR, RISING);
}

// example 2
void wakeOnButton() {
    // press a button to make device go to sleep
    // then press button again to turn back on
    int curButton = digitalRead(PIN_BUTTON);
    if (curButton == LOW && prevButton == HIGH) {
        Serial.println("About to sleep from button press...");

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER)
            .gpio(PIN_BUTTON, FALLING)
            .gpio(PIN_PIR, RISING);
        System.sleep(config);
    }
    prevButton = curButton;
}

// example 3
// description: photon 2 should sleep on doubleTap and wake on doubleTap
void sleepOnAccel() {
    // The ISR will set this flag to true. We disable interrupts temporarily
    // to safely check and clear the flag, preventing race conditions.
    noInterrupts();
    bool tapped = doubleTapOccurred;
    if (tapped) {
        doubleTapOccurred = false;  // Reset our flag immediately
    }
    interrupts();  // Re-enable interrupts

    // If a tap occurred, now we can handle it.
    if (tapped) {
        Serial.println("Double tap detected. About to sleep...");
        changeRgbLed(0, 0, 0);  // Turn off LED before sleeping

        // We must read the interrupt source register on the ADXL345 to clear
        // the interrupt. This is critical for allowing the next interrupt to
        // occur.
        adxl.readDoubleTap();

        SystemSleepConfiguration config;
        config.mode(SystemSleepMode::ULTRA_LOW_POWER)
            .gpio(PIN_ADXL_INT,
                  RISING);  // Wake on the same pin that the ISR uses
        System.sleep(config);

        // --- EXECUTION RESUMES HERE AFTER WAKING UP ---
        Serial.println("Woke up from double tap!");
        // After waking, the ISR will have already run and set the flag.
        // We need to read the source register again to clear the wake-up
        // interrupt on the ADXL345.
        adxl.readDoubleTap();
        delay(100);  // Short delay to allow hardware to settle.
    }
}

void loop() {
    sleepOnAccel();
    delay(20);  // Small delay to prevent the loop from running too fast
}
