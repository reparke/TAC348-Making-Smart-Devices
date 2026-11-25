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
volatile bool activityDetected = false;

// Interrupt Service Routine (ISR)
// This function is called when the interrupt pin goes HIGH.
void activityISR() {
    // It's best to do as little as possible in an ISR.
    // Just set a flag. Avoid any I2C/Serial/etc. communication in an ISR.
    activityDetected = true;
}

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    // Configure the interrupt pin as an input with a pull-down resistor
    pinMode(INTERRUPT_PIN, INPUT_PULLDOWN);
    attachInterrupt(INTERRUPT_PIN, activityISR, RISING);

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

    // Setting all interupts to take place on INT1 pin
    // This maps the activity interrupt to the INT1 pin on the ADXL345.
    // adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN);

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    // Enable only the activity interrupt.
    adxl.ActivityINT(1);
    adxl.doubleTapINT(0);
    adxl.singleTapINT(0);
}

void loop() {
    adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's

    if (activityDetected) {
        // Reset the flag for the next detection.
        activityDetected = false;
        activityCount++;

        // IMPORTANT: Read the interrupt source to clear the interrupt on the
        // ADXL345. This allows new interrupts to be detected. This is done here
        // instead of the ISR.
        // adxl.getInterruptSource();
        adxl.readActivity();
        Serial.println("Activity Detected! Count: " + String(activityCount));
    }
}
