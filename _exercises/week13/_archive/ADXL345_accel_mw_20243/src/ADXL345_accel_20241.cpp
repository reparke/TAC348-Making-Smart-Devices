// Include Particle Device OS APIs
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

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

// printAccelGraph prints a simple ASCII bar graph for a single accelerometer
// axis value. Examples:
//	printAccelGraph(-0.1, "X", 20, 2.0) will print:
// 		X:                    =|                     (0.1 g)
//	printAccelGraph(1.0, "Z", 20, 2.0) will print:
//		Z:                     |==========           (1.0 g)
// Input:
//	- [value]: calculated value of an accelerometer axis (e.g accel.cx,
// accel.cy)
//	- [name]: name of the axis (e.g. "X", "Y", "Z")
//	- [numBarsFull]: Maximum number of bars either right or left of 0 point.
//	- [rangeAbs]: Absolute value of the maximum acceleration range
void printAccelGraph(float value, String name, int numBarsFull,
                     float rangeAbs) {
    // Calculate the number of bars to fill, ignoring the sign of numBars for
    // now.
    int numBars = abs(value / (rangeAbs / numBarsFull));

    Serial.print(name + ": ");  // Print the axis name and a colon:

    // Do the negative half of the graph first:
    for (int i = 0; i < numBarsFull; i++) {
        if (value < 0)  // If the value is negative
        {
            // If our position in the graph is in the range we want to graph
            if (i >= (numBarsFull - numBars))
                Serial.print('=');  // Print an '='
            else
                Serial.print(' ');  // print spaces otherwise
        } else  // If our value is positive, just print spaces
            Serial.print(' ');
    }

    Serial.print('|');  // Print a pipe (|) to represent the 0-point

    // Do the positive half of the graph last:
    for (int i = 0; i < numBarsFull; i++) {
        if (value > 0) {  // If our position in the graph is in the range we
                          // want to graph
            if (i <= numBars)
                Serial.print('=');  // Print an '='
            else
                Serial.print(' ');  // otherwise print spaces
        } else                      // If value is negative, just print spaces
            Serial.print(' ');
    }

    // To end the line, print the actual value:
    Serial.println(" (" + String(value, 2) + " g)");
}

void displayExampleGraphs() {
    // use the printAccelGraph funciton to print the values along with a bar
    // graph, to see their relation to eachother:
    printAccelGraph(adxl.cx, "X", 20, 2.0);
    printAccelGraph(adxl.cy, "Y", 20, 2.0);
    printAccelGraph(adxl.cz, "Z", 20, 2.0);
    Serial.println();
}

/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup() {
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
        1,1, 1);  // Set to activate movement detection in the axes
                   // "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setActivityThreshold(75);  // 62.5mg per increment   // Set activity //
                                    // Inactivity thresholds (0-255)

    adxl.setTapDetectionOnXYZ(
        0, 0, 1);  // Detect taps in the directions turned ON
                   // "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

    // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
    adxl.setTapThreshold(40);      // 62.5 mg per increment
    adxl.setTapDuration(32);       // 625 μs per increment
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
    adxl.ActivityINT(1);
    adxl.doubleTapINT(1);
    adxl.singleTapINT(1);
}

void loop() {
    adxl.readAndCalcAccel();  // reads current x,y,z accel and calculates G's

    /* After reading, six class variables are updated: x, y, z, cx, cy, and
    cz. Those are the raw, 12-bit values (x, y, and z) and the calculated
    acceleration's in units of g (cx, cy, and cz). */
    // displayExampleGraphs();

    /*
        control the RGB led with our acceleration
        adxl.x .y .z --> these are raw acceleration (not super helpful)
        adxl.cx .cy .cz --> calculated acccel as fraction of g (gravity)

        what is the range of cx?
            - in settings, we ask to measure 2g -> -1*g to g
            - we SHOULD in theory get -1 to 1 for cx
            BUT without calibrating, it looks we get -0.8 to +0.8


        settings: measure 2 x force of gravity (9.8 m/s2 = 1 g)
            --> -1 * g to +1 * g

    */
    //    int r = map(adxl.cx, -1.0, 1.0, 0.0, 255.0);
    //    int g = map(adxl.cy, -1.0, 1.0, 0.0, 255.0);
    //    int b = map(adxl.cz, -1.0, 1.0, 0.0, 255.0);
    //    changeRgbLed(r, 0, 0);

    // detecting orientation
    // int orientation = adxl.getOrientation();
    // switch (orientation) {
    //     case ADXL345_ORIENTATION_LANDSCAPE_L:
    //         Serial.println("Landscape Left");
    //         break;
    //     case ADXL345_ORIENTATION_LANDSCAPE_R:
    //         Serial.println("Landscape Right");
    //         break;
    //     case ADXL345_ORIENTATION_PORTRAIT_D:
    //         Serial.println("Portrait Down");
    //         break;
    //     case ADXL345_ORIENTATION_PORTRAIT_U:
    //         Serial.println("Portrait Up");
    //         break;
    //     case ADXL345_ORIENTATION_UNKNOWN:
    //         Serial.println("Unknown");
    //         break;
    // }

    /*
        in theory,  you can measure activity (motion), tap, and double tap in the any direction

        in practice, tap almost always works, tap+double CAN work with right settings, but getting ALL THREE to work at the same time is tricky 

        adxl.readTap    .readDoubleTap      .readActivitt
            all boolean functions

        suggestion: use if/else for these
    */

//    if (adxl.readDoubleTap() == true) {
//     Serial.println("Double tap detected");
//     changeRgbLed(255,0,0);
//     delay(10);
//     changeRgbLed(0,0,0);
//    }
//    else if (adxl.readTap() == true) {
//     Serial.println("Single tap detected");
//     changeRgbLed(0,255,0);
//     delay(10);
//     changeRgbLed(0,0,0);
//    }

    if(adxl.readActivity() == true) {
        Serial.println("Activity detected");
    }

    // delay(500);
}
