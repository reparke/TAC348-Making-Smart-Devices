/*
 * Particle ADXL345 Z-axis Tap Interrupt Example
 * Rob Parke
 * Based on SparkFun's ADXL345 example
 * Wiring: ADXL345 INT1 -> Particle D2
 */
#include "Particle.h"
#include "SparkFun_ADXL345.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = D15;  // aka MOSI pin
const int PIN_ADXL_INTERRUPT = D2;
const unsigned long LED_ON_TIME = 500;  // milliseconds

ADXL345 adxl = ADXL345();  // USE FOR I2C COMMUNICATION

// This flag is shared by the interrupt handler and loop().
volatile bool tapDetected = false;
bool ledIsOn = false;
unsigned long prevLedMillis = 0;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/****************** INTERRUPT ******************/
void tapInterrupt() {
    // Keep the ISR short. Read the sensor and change the LED in loop().
    tapDetected = true;
}

/******************** SETUP ********************/
void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_ADXL_INTERRUPT, INPUT);
    changeRgbLed(0, 0, 0);

    Serial.begin(9600);
    adxl.powerOn();  // Starts I2C and powers on the sensor

    // Disable sensor interrupts before configuring single-tap detection.
    for (int interruptBit = 0; interruptBit < 8; interruptBit++) {
        adxl.setInterrupt(interruptBit, 0);
    }

    adxl.setRangeSetting(2);
    adxl.setTapDetectionOnXYZ(0, 0, 1);  // Z only (X, Y, Z)
    adxl.setSuppressBit(false);
    adxl.setTapThreshold(24);  // 24 x 62.5 mg = 1.5 g
    adxl.setTapDuration(80);   // 80 x 625 microseconds = 50 ms

    adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN);
    adxl.setInterruptLevelBit(false);  // INT1 is active HIGH
    adxl.getInterruptSource();  // Clear any old tap

    attachInterrupt(PIN_ADXL_INTERRUPT, tapInterrupt, RISING);
    adxl.singleTapINT(1);
}

void loop() {
    unsigned long curMillis = millis();

    //////////////////////////////////
    //     Tap Detection            //
    //////////////////////////////////
    if (tapDetected == true) {
        // Clear our flag BEFORE reading the sensor and handling the tap.
        tapDetected = false;

        // readTap() checks for a tap and clears INT1 for the next interrupt.
        adxl.status = ADXL345_OK;
        if (adxl.readTap() == true && adxl.status == ADXL345_OK) {
            Serial.println("** Z TAP **");
            changeRgbLed(0, 255, 0);  // Green
            ledIsOn = true;
            prevLedMillis = curMillis;  // Restart the timer on each tap
        }
    }

    //////////////////////////////////
    //     Turn Off the LED         //
    //////////////////////////////////
    if (ledIsOn == true) {
        if (curMillis - prevLedMillis > LED_ON_TIME) {
            prevLedMillis = curMillis;
            changeRgbLed(0, 0, 0);
            ledIsOn = false;
        }
    }
}
