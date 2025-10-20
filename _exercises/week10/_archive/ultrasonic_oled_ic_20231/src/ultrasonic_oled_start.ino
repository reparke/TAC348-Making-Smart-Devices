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
const int PIN_TRIGGER = D6;
const int PIN_ECHO = D5;

const double SPEED_SOUND_CM_ROOM_TEMP_FAHR = 0.03444;
const double CONV_FACTOR_CM_TO_IN = 0.3437;
const int MAX_RANGE_CM = 400;     // 30 in
const int WARNING_RANGE_CM = 12;  // 4.7
const int MIN_RANGE_CM = 2;

void setup() {
    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.drawBitmap(USC_BITMAP);
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
}

/********************************************************************************/
void loop() {
    // start trigger sequence
    digitalWrite(PIN_TRIGGER, LOW);  // prepare
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);

    // now we wait...

    int roundTripTime = pulseIn(PIN_ECHO, HIGH);
    float distanceCm = roundTripTime * SPEED_SOUND_CM_ROOM_TEMP_FAHR / 2;
    float distanceIn = distanceCm * CONV_FACTOR_CM_TO_IN;

    Serial.print("Dist to object:");
    if (distanceCm >= MAX_RANGE_CM ||
        distanceCm <= MIN_RANGE_CM) {  // these units can be CM only because
                                       // that is what the sensor reports

        Serial.println("out of range: " + String(distanceIn, 2) + " in");
        oled.clear(PAGE);
        oled.drawBitmap(NO_BITMAP);
        oled.display();

    } else if (distanceCm > MIN_RANGE_CM && distanceCm < WARNING_RANGE_CM) {
        Serial.println("Warning: " + String(distanceIn, 2) + " in");

        oled.clear(PAGE);
        oled.drawBitmap(WARNING_SMALL_BITMAP);
        oled.setFontType(0);
        oled.setCursor(0, 40);  // below graphic
        oled.print(String(distanceIn, 2));
        oled.display();

    } else {
        Serial.println("OK distance: " + String(distanceIn, 2) + " in");
        oled.clear(PAGE);
        oled.drawBitmap(YES_SMALL_BITMAP);
        oled.setFontType(0);
        oled.setCursor(0, 40);  // below graphic
        oled.print(String(distanceIn, 2));
        oled.display();
    }
    delay(500);
}
