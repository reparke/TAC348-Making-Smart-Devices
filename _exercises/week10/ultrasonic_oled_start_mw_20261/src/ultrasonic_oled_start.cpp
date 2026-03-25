#include "Particle.h"
#include "bitmaps.h"
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
// this sensor requires 5v (VUSB)...sorta...kinda get to work with LiPo Li+
// (3.7V pin) just like servo

const float SPEED_OF_SOUND_CM = 0.03444;
const float CM_TO_IN = 0.393701;  

const int WARNING_RANGE = 5;  // inches
const int MIN_RANGE = 1;      // inches
const int MAX_RANGE = 157;    // inches

/*

https://javl.github.io/image2cpp/
  measure distance
  display on serial monitor
    less than min range (1 in) or max range of 13 ft, show out of range AND show
no_full_screen graphic

    less than 5 in, show warning
        show WARNING GRAPHIC HALF SCREEN + distance

    otherwise display distance
        show YES GRAPHIC half screen + distance
*/

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory

    oled.drawBitmap(usc_full_screen);
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_TRIGGER, OUTPUT);
    // pinMode is from the perspective of the photon
}

/********************************************************************************/
void loop() {
    // init sequence for ultra sonic
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delay(10);
    digitalWrite(PIN_TRIGGER, LOW);

    // these 5 lines start the sensor working aka sending 8 pulses

    // pulseIn measure time
    // pulseIn measures the lenght of time for signal to change L-H or H-L

    int sensorTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = sensorTime * SPEED_OF_SOUND_CM /2; //div 2 since time is 
                                                        ///there and back
    float distanceIn = distanceCm * CM_TO_IN;

    //dist = rate * time   (dist = velo * time)

    if (distanceIn <= MIN_RANGE || distanceIn >= MAX_RANGE) {
      Serial.println("Out of range");
    } else if (distanceIn <= WARNING_RANGE) {
        Serial.println("Warning - Dist: " + String(distanceIn));
    } else {
        Serial.println("Dist: " + String(distanceIn));
    }

    delay(500); // delay to add gap between readings
}
