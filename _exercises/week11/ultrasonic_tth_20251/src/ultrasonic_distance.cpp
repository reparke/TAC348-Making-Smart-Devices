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

// ultra sonic pins
const int PIN_ECHO = D5;
const int PIN_TRIGGER = D6;

const int WARNING_RANGE = 5;
const int MIN_RANGE = 1;
const int MAX_RANGE = 157;

const float SPEED_SOUND_CM = 0.03444;
const float CM_TO_IN = 0.393701;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_TRIGGER, OUTPUT);

    oled.begin();
    oled.clear(ALL);
    oled.drawBitmap(usc_bitmap);
    oled.display();

}
/*
    display all info on OLED
    * show large graphic when out of range (no_full_screen)
    * show the distance AND small warning graphic when in warning range (warning half screen)
    * otherwise, show the distance and yes half screen
*/


// important: make sure that Ultra VCC is connnected to VUSB

/*
measure distance
display
    less than min range(1 in) or more than 157 in, show out of range
    less than 5 in, show warning
    otherwise, display distance


*/

void loop() {
    // how to measure distance?
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    // these 5 lines of code start the sensor reading
    // aka sending out the 8 pulses

    // pulseIn to measure time
    // pulseIn returns the length of time for a signal to change from L-H or H-L
    int sensorTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;
    float distanceIn = distanceCm * CM_TO_IN;

    // OR in C+ is ||
    if (distanceIn <= MIN_RANGE || distanceIn >= MAX_RANGE) {
        Serial.println("Out of range");
        oled.clear(PAGE);
        oled.drawBitmap(no_full_screen_bitmap);
        oled.display();
    } else if (distanceIn <= WARNING_RANGE) {
        Serial.println("Warning: " + String(distanceIn, 1) + " in");
        oled.clear(PAGE);
        oled.drawBitmap(warning_half_screen_bitmap);

        oled.setCursor(0,30);
        oled.setFontType(1);
        oled.setColor(BLACK);
        oled.print(String(distanceIn, 1) + " in");

        oled.display();

    } else {
        Serial.println("Distance: " + String(distanceIn, 1) + " in");
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