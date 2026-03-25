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
const int PIN_ECHO = D5;
const int PIN_TRIGGER = D6;

const float SPEED_SOUND_CM = 0.03444;
const float CM_TO_IN = 0.393701;

const int MIN_RANGE = 1;
const int WARNING_RANGE = 5; //inches
const int MAX_RANGE = 157; // about 13ft

/*

measure distance
  serial print
    less than 1 in or more than 13ft, show out of range
    less than 5 in, show warning
    otherwise distance

  ultra sonic is needs 5v (...sorta) - use VUSB
    will not work with 3.3v
    kinda works with 3.7V (Li+ pin when lipo connected)
  Servo 100% needs 5v
*/
void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    //remember: pinMode is from the perspective of the Photon
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_TRIGGER, OUTPUT); //starts the pulse
}

/********************************************************************************/
void loop() {
  //how to start measuring?
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);

  // now ultrasonic sends 8 pulses
  //pulseIn measures time
  // returns the lenght of time for a signal to  change from L-H or H-L
  int sensorTime = pulseIn(PIN_ECHO, HIGH);

  // dist = rate * time         dist = velo * speed
  float distCm = SPEED_SOUND_CM * sensorTime / 2;
  float distIn = CM_TO_IN * distCm;

  if (distIn >= MAX_RANGE || distIn <= MIN_RANGE) {
    Serial.println("Our of range");
  }
  else if (distIn <= WARNING_RANGE) {
    Serial.println("Warning: Dist = " + String(distIn) + " in");
  }
  else {
    Serial.println("Dist = " + String(distIn) + " in");
  }


  //good idea to a delay
  delay(500);
}
