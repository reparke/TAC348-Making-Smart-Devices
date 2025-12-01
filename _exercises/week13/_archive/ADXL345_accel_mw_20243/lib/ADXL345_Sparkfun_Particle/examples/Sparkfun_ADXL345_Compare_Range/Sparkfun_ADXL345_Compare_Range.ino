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

#include "SparkFun_ADXL345.h"  // SparkFun ADXL345 Library

/*********** COMMUNICATION SELECTION ***********/
/*    Comment Out The One You Are Not Using    */
// ADXL345 adxl = ADXL345(10);  // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
ADXL345 adxl = ADXL345();  // USE FOR I2C COMMUNICATION

void compareMeasurementRanges() {
    Serial.print("\n2G  ");
    adxl.setRangeSetting(1);
    adxl.readAndCalcAccel();
    Serial.print("x, y, z Raw: ");
    Serial.print(adxl.x);
    Serial.print(", ");
    Serial.print(adxl.y);
    Serial.print(", ");
    Serial.print(adxl.z);
    Serial.print("\tCalc G: ");
    Serial.print(adxl.cx);
    Serial.print(", ");
    Serial.print(adxl.cy);
    Serial.print(", ");
    Serial.print(adxl.cz);
    Serial.println(", ");

    Serial.print("4G  ");
    adxl.setRangeSetting(4);
    adxl.readAndCalcAccel();
    Serial.print("x, y, z Raw: ");
    Serial.print(adxl.x);
    Serial.print(", ");
    Serial.print(adxl.y);
    Serial.print(", ");
    Serial.print(adxl.z);
    Serial.print("\tCalc G: ");
    Serial.print(adxl.cx);
    Serial.print(", ");
    Serial.print(adxl.cy);
    Serial.print(", ");
    Serial.print(adxl.cz);
    Serial.println(", ");

    Serial.print("8G  ");
    adxl.setRangeSetting(8);
    adxl.readAndCalcAccel();
    Serial.print("x, y, z Raw: ");
    Serial.print(adxl.x);
    Serial.print(", ");
    Serial.print(adxl.y);
    Serial.print(", ");
    Serial.print(adxl.z);
    Serial.print("\tCalc G: ");
    Serial.print(adxl.cx);
    Serial.print(", ");
    Serial.print(adxl.cy);
    Serial.print(", ");
    Serial.print(adxl.cz);
    Serial.println(", ");

    Serial.print("16G ");
    adxl.setRangeSetting(16);
    adxl.readAndCalcAccel();
    Serial.print("x, y, z Raw: ");
    Serial.print(adxl.x);
    Serial.print(", ");
    Serial.print(adxl.y);
    Serial.print(", ");
    Serial.print(adxl.z);
    Serial.print("\tCalc G: ");
    Serial.print(adxl.cx);
    Serial.print(", ");
    Serial.print(adxl.cy);
    Serial.print(", ");
    Serial.print(adxl.cz);
    Serial.println(", ");
}

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
    Serial.begin(9600);  // Start the serial terminal

    adxl.powerOn();  // Power on the ADXL345

    adxl.setRangeSetting(2);  // Give the range settings
                              // Accepted values are 2g, 4g, 8g or 16g
                              // Higher Values = Wider Measurement Range
                              // Lower Values = Greater Sensitivity

    adxl.setActivityXYZ(
        1, 0, 0);  // Set to activate movement detection in the axes
                   // "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setActivityThreshold(75);  // 62.5mg per increment   // Set activity //
                                    // Inactivity thresholds (0-255)

    adxl.setTapDetectionOnXYZ(
        0, 0, 1);  // Detect taps in the directions turned ON
                   // "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

    // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
    adxl.setTapThreshold(50);      // 62.5 mg per increment
    adxl.setTapDuration(15);       // 625 μs per increment
    adxl.setDoubleTapLatency(80);  // 1.25 ms per increment
    adxl.setDoubleTapWindow(200);  // 1.25 ms per increment

    // Setting all interupts to take place on INT1 pin
    // adxl.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets
    // "adxl.setEveryInterruptMapping(single tap, double tap, free fall,
    // activity, inactivity);"
    // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin
    // on the ADXL345 to use for Interrupts. This library may have a problem
    // using INT2 pin. Default to INT1 pin.

    // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
    adxl.ActivityINT(1);
    adxl.doubleTapINT(1);
    adxl.singleTapINT(1);
}

void loop() {
    adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's

    /* Compare readings for different measurement ranges */
    compareMeasurementRanges();
    delay(500);
}
