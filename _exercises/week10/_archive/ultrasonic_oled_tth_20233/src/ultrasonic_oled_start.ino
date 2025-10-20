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

const int MAX_RANGE = 400; //4m = 400 cm
const int MIN_RANGE = 2;  // cm
const int WARNING_RANGE = 12; //cm 

//speed of sound is 343 m/s
//we are concerned with cm, and we are given microseconds
//  343 m / s --> 343 * 100 cm / s --> 34300 / 10^6 
const double SPEED_SOUND_CM = 0.0343;


void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    pinMode(PIN_ECHO, INPUT);     //receive INPUT signal from sensor to tell us the time
    pinMode(PIN_TRIGGER, OUTPUT); //send OUTPUT signal to sensor to start measuring
}

/********************************************************************************/
void loop() {
  //sequence to starting the ultra sonic sensor
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2); //really short LOW for 2 micro sec
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);

  //now we wait... to measure
  int sensorTime = pulseIn(PIN_ECHO, HIGH); //time for the echo to be sent, bounce, and return
  // time in microseconds
  // speed of sound is 343.5 m/s
  double distanceCm = sensorTime * SPEED_SOUND_CM / 2;

  // ifs...
  //out of range
  if(distanceCm < MIN_RANGE || distanceCm > MAX_RANGE) { //OR doesn't work in C++
    Serial.println("Error out of range");
  }
  else if (distanceCm >= MIN_RANGE && distanceCm < WARNING_RANGE ) {
    Serial.println("Warning! Distance is " + String(distanceCm, 1) + " cm");
  }
  else {
    Serial.println("Distance is " + String(distanceCm, 1) + " cm");
  }

  //if you are constantly going to reading distance, then you need a 500 ms delay between read
  delay(500); //if not reading all the time, don't the delay

}

/*
  using the serial monitor,
    show an error message when out of range (2cm - 4m)
    show distance and warning if less than 12 cn (5 in)
    otherwise just show the distance
*/