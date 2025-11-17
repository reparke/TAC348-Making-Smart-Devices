#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*  Wiring

  OLED
  ----
    MicroOLED -------------  Argon
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
      SDA ------------------- SDA
      SCL ------------------- SCL


Ultrasonic Sensor
    VCC: VUSB (5v)
    Trigger: D6
    Echo: D5
    GND: GND

*/
#include "SparkFunMicroOLED.h"  // Include MicroOLED library

#include "bitmaps.h"
//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
#define PIN_RESET 9
// The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is
// open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
MicroOLED oled(MODE_I2C, PIN_RESET, DC_JUMPER);  // I2C declaration

//////////////////////////
// Ultrasonic Distance  //
//////////////////////////

const int PIN_ECHO = D5;
const int PIN_TRIGGER = D6;

const int WARNING_RANGE = 5;
const int MIN_RANGE = 1;
const int MAX_RANGE = 157;

const float CM_TO_IN = 0.393701;
const float SPEED_SOUND_CM = 0.034444;

/*
Monday 
measure distance
use serial monitor
  less than min range (1 inch), then print out of range
  less than 5 in, print out of range
  otherwise, who
*/

/*
Wednesday
    display all info on OLED
    * show large graphic when out of range (no_full_screen)
    * show the distance AND small warning graphic when in warning range (warning
   half screen)
    * otherwise, show the distance and yes half screen
*/


void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.drawBitmap(usc_full_screen);
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
void loop() {
    // start sequence
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    // these 5 lines of code start the sensor sending pulses

    // pulseIn - to measure time
    // pulseIn returns the length of tiem for a signal to change (L->H or H->L)
    //  int sensorTime = pulseIn(PIN_ECHO, HIGH);
    int roundTripTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = roundTripTime * SPEED_SOUND_CM / 2;
    float distanceIn = distanceCm * CM_TO_IN;

    if (distanceIn <= MIN_RANGE || distanceIn >= MAX_RANGE) {
        Serial.println("Out of range");
    } else if (distanceIn > MIN_RANGE && distanceIn <= WARNING_RANGE) {
        Serial.println("Warning: very close");
    } else {
        Serial.println("Distance = " + String(distanceIn, 1));
    }
}
