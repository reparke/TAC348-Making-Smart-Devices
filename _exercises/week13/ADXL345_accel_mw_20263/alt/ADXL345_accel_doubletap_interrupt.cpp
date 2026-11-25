#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "SparkFun_ADXL345.h"  // SparkFun ADXL345 Library
/*********** COMMUNICATION SELECTION ***********/
/*    Comment Out The One You Are Not Using    */
// ADXL345 adxl = ADXL345(10);  // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
ADXL345 adxl = ADXL345();  // USE FOR I2C COMMUNICATION

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin

// Pin connected to the INT1 pin of the ADXL345
// This must be an interrupt-capable pin on your Particle device.
const int INTERRUPT_PIN = D2;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

int doubleTapCount = 0;
int tapCount = 0;
int activityCount = 0;

// This flag will be set to true in the interrupt service routine.
volatile bool doubleTapDetected = false;

// Interrupt Service Routine (ISR)
// This function is called when the interrupt pin goes HIGH.
void doubleTapISR() {
    // It's best to do as little as possible in an ISR.
    // Just set a flag. Avoid any I2C/Serial/etc. communication in an ISR.
    doubleTapDetected = true;
}

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    // Configure the interrupt pin. The ADXL345 actively drives the interrupt
    // pin, so a pull-up or pull-down resistor is not needed.
    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(INTERRUPT_PIN, doubleTapISR, RISING);

    Serial.begin(9600);  // Start the serial terminal

    adxl.powerOn();  // Power on the ADXL345

    adxl.setRangeSetting(2);  // Give the range settings
                              // Accepted values are 2g, 4g, 8g or 16g
                              // Higher Values = Wider Measurement Range
                              // Lower Values = Greater Sensitivity

    // Configure settings for tap detection
    adxl.setTapDetectionOnXYZ(
        0, 0, 1);  // Detect taps on Z-axis. "adxl.setTapDetectionOnX(X, Y, Z);"
                   // (1==ON, 0==OFF)

    // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
    adxl.setTapThreshold(30);      // 62.5 mg per increment.
    adxl.setTapDuration(40);       // 625 µs per increment
    adxl.setDoubleTapLatency(80);  // 1.25 ms per increment
    adxl.setDoubleTapWindow(240);  // 1.25 ms per increment

    // Setting all interupts to take place on INT1 pin (which is default already)
    // adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN);

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    // Enable the double-tap interrupt. It was found that enabling the
    // single-tap interrupt is not required for this to work.
    adxl.ActivityINT(0);
    adxl.doubleTapINT(1);
    adxl.singleTapINT(0);  // Keep single tap interrupt disabled for simplicity
}

void loop() {
    adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's

    if (doubleTapDetected) {
        // Reset the flag for the next detection.
        doubleTapDetected = false;
        doubleTapCount++;

        // IMPORTANT: Read the interrupt source to clear the interrupt on the
        // ADXL345. This allows new interrupts to be detected. This is done here
        // instead of the ISR.
        // We can use readDoubleTap() which internally calls
        // getInterruptSource().
        adxl.readDoubleTap();
        Serial.println("Double tap = " + String(doubleTapCount));
    }
}
