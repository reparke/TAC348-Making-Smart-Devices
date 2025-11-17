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

const int MIN_RANGE = 2;       // 2 cm
const int WARNING_RANGE = 12;  // 5 in
const int MAX_RANGE = 400;

float SPEED_SOUND_CM = 0.03444;
float CM_TO_IN = 0.393701;

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory

    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
/*
  use ultrasonic sensor
    measure the distance
    use serial monitor to display ...
      less than 2 cm or more than 400, show "out of range"
      less than 12 cm, show "warning" and the distance
      otherwise, show the distance
*/
void loop() {
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    // sensor starts sending pulses

    int sensorTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;
    float distanceIn = CM_TO_IN * distanceCm;

    // if (distanceCm <= MIN_RANGE || distanceCm >= MAX_RANGE) {
    //     Serial.println("Out of range: " + String(distanceCm, 1) + " cm; " +
    //                    String(distanceIn, 1) + " in");
    // } else if (distanceCm <= WARNING_RANGE) {
    //     Serial.println("Warning: " + String(distanceCm, 1) + " cm; " +
    //                    String(distanceIn, 1) + " in");
    // } else {
    //     Serial.println("Distance: " + String(distanceCm, 1) + " cm; " +
    //                    String(distanceIn, 1) + " in");
    // }

    delay(500);  // in a perfect world, lets use a millis timer
}
