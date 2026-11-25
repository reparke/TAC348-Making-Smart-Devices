/*
 * Project ADXL345 Z-axis tap interrupt example
 * Author: Rob Parke
 * Date: November 23, 2026
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*  *********************************************
 *  Particle ADXL 345 Example
 *  Rob Parke
 *  Created 10.8.2022
 *
 *  Based on SparkFun_ADXL345_Example
 *  Triple Axis Accelerometer Breakout - ADXL345
 *  Hook Up Guide Example
 *
 *  Utilizing Sparkfun's ADXL345 Library
 *  Bildr ADXL345 source file modified to support
 *  both I2C and SPI Communication
 *
 *  E.Robert @ SparkFun Electronics
 *  Created: Jul 13, 2016
 *  Updated: Sep 06, 2016
 *  *********************************************/
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin
const int PIN_ADXL_INTERRUPT = D2;  // Connect ADXL345 INT1 to D2
const unsigned long LED_ON_TIME = 500;  // milliseconds
const unsigned long DEBUG_UPDATE = 2000;  // milliseconds
const bool DEBUG_TAPS = true;  // Set false after troubleshooting

#include "SparkFun_ADXL345.h"  // SparkFun ADXL345 Library

ADXL345 adxl = ADXL345();  // USE FOR I2C COMMUNICATION

// volatile tells the compiler this value can change inside the interrupt.
volatile bool tapDetected = false;
bool ledIsOn = false;
unsigned long prevLedMillis = 0;
bool interruptAttached = false;
unsigned long prevDebugMillis = 0;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/***************** DIAGNOSTICS *****************/
void showTapDiagnostics() {
    Serial.println("--- Tap diagnostics ---");
    Serial.printlnf("D2: %d | handler attached: %d",
                   digitalRead(PIN_ADXL_INTERRUPT), interruptAttached);

    // Use the same acceleration-reading method as the working example.
    // Reading acceleration does not clear the sensor's tap interrupt.
    adxl.status = ADXL345_OK;
    adxl.readAndCalcAccel();
    if (adxl.status == ADXL345_OK) {
        Serial.printlnf("Acceleration: X=%.2f Y=%.2f Z=%.2f g",
                       adxl.cx, adxl.cy, adxl.cz);
    } else {
        Serial.println("The library reported an acceleration read error.");
    }

    adxl.status = ADXL345_OK;
    bool tapEnabled = adxl.isInterruptEnabled(ADXL345_INT_SINGLE_TAP_BIT);
    bool tapOnInt2 = adxl.getInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT);
    bool zEnabled = adxl.isTapDetectionOnZ();
    int threshold = adxl.getTapThreshold();
    int duration = adxl.getTapDuration();
    if (adxl.status == ADXL345_OK) {
        Serial.printlnf("Tap enabled: %d (expect 1), mapped to INT%d (expect INT1), Z enabled: %d (expect 1)",
                       tapEnabled, tapOnInt2 ? 2 : 1, zEnabled);
        Serial.printlnf("Tap threshold: %d (expect 24), duration: %d (expect 80)",
                       threshold, duration);
    } else {
        Serial.println("The library reported an interrupt-settings read error.");
    }
}

/****************** INTERRUPT ******************/
/*       Runs when the INT1 pin goes HIGH      */
void tapInterrupt() {
    // Keep the interrupt service routine (ISR) short!
    // Do the I2C reads, Serial prints, and LED changes in loop().
    tapDetected = true;
}

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_ADXL_INTERRUPT, INPUT);
    changeRgbLed(0, 0, 0);  // Start with the RGB LED off

    Serial.begin(9600);  // Start the serial terminal

    if (DEBUG_TAPS == true) {
        // Test the LED before configuring the sensor or attaching the ISR.
        changeRgbLed(0, 255, 0);
        delay(500);  // Startup test only; tap handling below is nonblocking
        changeRgbLed(0, 0, 0);
    }

    // Use the original example's initialization. powerOn() starts I2C.
    adxl.powerOn();  // Power on the ADXL345

    // Disable all sensor interrupts while changing their settings.
    // There are eight interrupt bits, numbered 0 through 7.
    for (int interruptBit = 0; interruptBit < 8; interruptBit++) {
        adxl.setInterrupt(interruptBit, 0);
    }

    adxl.setRangeSetting(2);  // Same range as the original example

    adxl.setTapDetectionOnXYZ(
        0, 0, 1);  // Detect taps on Z only (X, Y, Z; 1 == ON, 0 == OFF)
    adxl.setSuppressBit(false);  // Clear any setting left by another example
    // More sensitive starting values for testing taps on the mounted board.
    // Raise the threshold later if normal handling causes unwanted triggers.
    adxl.setTapThreshold(24);  // 62.5 mg per increment: 24 = 1.5 g
    adxl.setTapDuration(80);   // 625 microseconds per increment: 80 = 50 ms
    adxl.setDoubleTapLatency(80);  // Retain the original timing settings
    adxl.setDoubleTapWindow(240);  // Double-tap interrupts remain disabled

    // Route single taps to the ADXL345 INT1 output, active HIGH.
    adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN);
    adxl.setInterruptLevelBit(false);
    adxl.getInterruptSource();  // Clear any old sensor interrupt

    // Attach the Particle handler BEFORE enabling the sensor interrupt.
    interruptAttached = attachInterrupt(PIN_ADXL_INTERRUPT, tapInterrupt, RISING);
    adxl.singleTapINT(1);  // Only single-tap interrupts are enabled
    // Catch a tap already holding INT1 HIGH when the interrupt was enabled.
    if (digitalRead(PIN_ADXL_INTERRUPT) == HIGH) {
        tapDetected = true;
    }
}

void loop() {
    unsigned long curMillis = millis();
    bool debugDue = false;
    if (DEBUG_TAPS == true && Serial) {
        if (curMillis - prevDebugMillis > DEBUG_UPDATE) {
            prevDebugMillis = curMillis;
            debugDue = true;
        }
    }
    //////////////////////////////////
    //     Tap Detection            //
    //////////////////////////////////
    // Copy and clear the shared flag together so an interrupt cannot
    // arrive between these two operations and get accidentally erased.
    noInterrupts();
    bool tapPending = tapDetected;
    tapDetected = false;
    interrupts();

    if (tapPending == true || debugDue == true) {
        // Reading INT_SOURCE clears the sensor's latched tap interrupt,
        // allowing INT1 to go LOW and signal the next tap with a new edge.
        int interruptPinLevel = digitalRead(PIN_ADXL_INTERRUPT);
        adxl.status = ADXL345_OK;
        int interruptSource = adxl.getInterruptSource();
        if (adxl.status != ADXL345_OK) {
            interruptSource = -1;
        }
        if (DEBUG_TAPS == true) {
            Serial.printlnf("%s; INT_SOURCE = %d; tap bit = %d (-1 = I2C error)",
                           tapPending ? "D2 interrupt serviced" : "Automatic sensor check",
                           interruptSource,
                           interruptSource < 0 ? -1 : ((interruptSource >> 6) & 1));
            Serial.printlnf("D2 before clearing sensor: %d", interruptPinLevel);
        }

        // The automatic check can find a tap even with INT1 disconnected.
        // It clears the tap latch, but only the interrupt path lights the LED.
        if (tapPending == false && interruptSource >= 0 &&
            adxl.triggered(interruptSource, ADXL345_SINGLE_TAP)) {
            Serial.println("Sensor detected a tap without a pending ISR flag. Check INT1 -> D2.");
        }
        if (tapPending == true && interruptSource >= 0 &&
            adxl.triggered(interruptSource, ADXL345_SINGLE_TAP)) {
            Serial.println("** Z TAP **");
            changeRgbLed(0, 255, 0);  // Green
            ledIsOn = true;
            prevLedMillis = curMillis;  // Restart the LED timer on each tap
        }
    }

    //////////////////////////////////
    //     Troubleshooting          //
    //////////////////////////////////
    if (debugDue == true) {
        showTapDiagnostics();
    }

    //////////////////////////////////
    //     Turn Off the LED         //
    //////////////////////////////////
    // Use millis() so loop() can keep handling taps while the LED is on.
    // Another tap restarts the half-second timer.
    if (ledIsOn == true) {
        if (curMillis - prevLedMillis > LED_ON_TIME) {
            prevLedMillis = curMillis;
            changeRgbLed(0, 0, 0);
            ledIsOn = false;
        }
    }
}
