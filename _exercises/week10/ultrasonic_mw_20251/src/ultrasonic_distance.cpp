#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

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

// ultrasonic pins
const int PIN_ECHO = D5;
const int PIN_TRIGGER = D6;

const int WARNING_RANGE = 5; //5 inches
const int MIN_RANGE = 1; 
const int MAX_RANGE = 157;

float SPEED_SOUND_CM = 0.03444;
float CM_TO_IN = 0.393701;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_ECHO, INPUT); //Ultra -> P2
    pinMode(PIN_TRIGGER, OUTPUT); //P2 -> Ultra

    oled.begin();
    oled.clear(ALL);
    oled.drawBitmap(usc_bitmap);
    oled.display();

}

/*
display all info on the screen (not serial monitor)

* show large graphic when out of range (no_full_screen)
* show distance AND small warning graphic when less than 5 cm (warning_half_screen)
* otherwise, show distance and yes_half_screen

*/

/*
    measure distance
    display
        less than 1 in or more than 157 in, show out of range

        less than 5 in, show warning

        otherwise, show distance
*/

void loop() {
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    //these 5 lines of code start the sensor reading
    //aka sending the 8 pulses out

    //pulseIn -- returns the time for signal to change
    int sensorTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;

    float distanceIn = distanceCm * CM_TO_IN;

    // OR is C++ is ||
    if (distanceIn <= MIN_RANGE ||distanceIn >= MAX_RANGE ) {
        Serial.println("Out of range: " + String(distanceIn, 1));
        oled.clear(PAGE);
        oled.drawBitmap(no_full_screen_bitmap);
        oled.display();
    }
    else if (distanceIn <= WARNING_RANGE) {
        Serial.println("Warning: " + String(distanceIn, 1));
        oled.clear(PAGE);
        oled.drawBitmap(warning_half_screen_bitmap);

        oled.setCursor(0, 30);
        oled.setFontType(1);
        oled.setColor(BLACK);
        oled.print(String(distanceIn, 1) + " in");
        oled.display();
    }
    else {
        Serial.println("Distance: " + String(distanceIn, 1));
        oled.clear(PAGE);
        oled.drawBitmap(yes_half_screen_bitmap);

        oled.setCursor(0, 30);
        oled.setFontType(1);
        oled.setColor(BLACK);
        oled.print(String(distanceIn, 1) + " in");
        oled.display();
    }
    delay(500);
}
