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
const int PIN_TRIGGER = D6;
const int PIN_ECHO = D5;

const float SPEED_SOUND_CM = 0.03444;
const int MIN_RANGE_CM = 2;
const int WARNING_RANGE_CM = 12;
const int MAX_RANGE_CM = 400;

float distanceCm = 0;

void measureDistance() {
    digitalWrite(PIN_TRIGGER, LOW);  // stars sequence
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    // now send 8 pulses out

    int timeMeasure = pulseIn(PIN_ECHO, HIGH);  // wait for time

    distanceCm = timeMeasure * SPEED_SOUND_CM / 2;
    delay(500);  // need a small delay; should use millis if timing is important
                 // in the device
}

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms
    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
void loop() {
    measureDistance();
    
    if (distanceCm <= MIN_RANGE_CM || distanceCm >= MAX_RANGE_CM) {
        Serial.println("Out of range");
    } else if (distanceCm <= WARNING_RANGE_CM) {
        Serial.println("Warning! Distance (cm): " + String(distanceCm, 2));
    } else {  // valid range
        Serial.println("Distance (cm): " + String(distanceCm, 2));
    }
}

/*
  use the ultra sonic sensor (config it)
  see if we can get a reading
  report the distance in CM to an object

use ranges
  range is 2 cm to 400 cm

  show the distance in serial monitor
  if less than 12 cm, show distance and warning mesage
  otherwise say out of range
*/