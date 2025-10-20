/*  Wiring

  OLED
  ----
    MicroOLED -------------  Argon
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
      SDA ------------------- SDA
      SCL ------------------- SCL


Ultrasonic Sensor
    Trigger: D6
    Echo: D5

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
const float CONV_CM_IN = 0.3437;

// range: 2cm - 400cm
const int MIN_RANGE = 2;      // cm
const int WARNING_RANGE = 12;  // 5 in ~~ 12 cm
const int MAX_RANGE = 400;    // cm

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    // trigger and ethco
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_TRIGGER,
            OUTPUT);  // argon sends OUTPUT signal on trigger
                      // ultrasonic starts sends pulses out
                      // Argon receives INPUT from the ultra sonic on ECHO Pin
}

/********************************************************************************/
void loop() {
    // start the measuring -- sequence
    digitalWrite(PIN_TRIGGER, LOW);  // resets sensor and prepare for
                                     // measurement
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);  // start device
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);

    // now we wait...
    // what does this represent? time for sound wave to come back
    //
    int sensorTime = pulseIn(PIN_ECHO, HIGH);
    float distanceCm =
        sensorTime * SPEED_SOUND_CM / 2;  // m/s is speed of sound
    float distanceIn = distanceCm * CONV_CM_IN;

    // error is > 400 or < 2
    if (distanceCm < MIN_RANGE || distanceCm > MAX_RANGE) {
        Serial.println("Out of range");
    } else if (distanceCm >= MIN_RANGE && distanceCm < WARNING_RANGE) {
        Serial.println("Warning: " + String(distanceIn, 2));
    } else {
        Serial.println("Distance: " + String(distanceIn, 2));
    }

    //if we aren't slowing this down at all (e.g. with oled), they we should add delay
    //if doing constant reading as in this example
    delay(500);
}

/*
Using the serial monitor, display

    Error message when out of range
    Warning message when less than 5 inches
    Distance message otherwise

*/