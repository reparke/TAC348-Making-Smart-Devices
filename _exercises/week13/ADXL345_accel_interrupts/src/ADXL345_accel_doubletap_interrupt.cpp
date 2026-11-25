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

// Count at most one double-tap event every 300 ms to filter repeated events.
const unsigned long DOUBLE_TAP_COOLDOWN_MS = 300;
unsigned long prevDoubleTapMillis = 0;

// The ISR sets this flag when a double-tap interrupt arrives.
volatile bool doubleTapDetected = false;

// Interrupt Service Routine (ISR)
// This function is called when the double-tap interrupt pin goes HIGH.
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

    // Configure the axes used for double-tap detection.
    adxl.setTapDetectionOnXYZ(
        0, 0, 1);  // Detect double taps on the Z-axis.
                   // (1==ON, 0==OFF)

    // Configure double-tap detection thresholds and timing (0-255).
    adxl.setTapThreshold(30);      // 62.5 mg per increment.
    adxl.setTapDuration(40);       // 625 µs per increment
    adxl.setDoubleTapLatency(80);  // 1.25 ms per increment
    adxl.setDoubleTapWindow(240);  // 1.25 ms per increment

    // Interrupts default to INT1, which is connected to D2.
    // adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN);

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    // Enable double taps for this example.
    adxl.ActivityINT(0);
    adxl.doubleTapINT(1);
    adxl.singleTapINT(0);
}

void loop() {
    unsigned long curMillis = millis();

    // adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's

    if (doubleTapDetected == true) {
        // Reset the flag for the next double-tap detection.
        doubleTapDetected = false;
        // Always read and clear the double-tap interrupt, even during the cooldown.
        // Otherwise INT1 can stay HIGH and prevent the next rising edge.
        bool isDoubleTap = adxl.readDoubleTap();

        if (isDoubleTap == true) {
            // Count another double tap after the debounce time has passed.
            if (curMillis - prevDoubleTapMillis > DOUBLE_TAP_COOLDOWN_MS) {
                prevDoubleTapMillis = curMillis;
                doubleTapCount++;
                Serial.println("Double tap count = " + String(doubleTapCount));
            }
        }
    }
}
