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

uint8_t is a 8 bit int
char is an an 8 bit int

uint8_t is the same as char

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

const int MIN_RANGe = 2;  // 2 cm
const int WARNING_RANGE = 12;
const int MAX_RANGE = 400;

const double SPEED_SOUND_CM = 0.03444;

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.drawBitmap(tac348_bitmap);
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/

/*
  use the ultra sonic sensor
    meeasure distance
    use serial to display distance + mesage
      less than 12 cm, say warning
      less than 2 cm or more than 400 cm, say out or range
      otherwise, just distance

  Now OLED

  * Large error graphic when out of range (`no_full_screen.png`)
  * Small warning message when less than 12 cm and the distance
(`warning_half_screen.png`)
  * Small graphics and distance message otherwise and the distance
(`yes_half_screen.png`)

*/
void loop() {
    // start trigger
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);
    // right now, the 8 sonic pulses are sent automatically

    int sensorTime = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = sensorTime * SPEED_SOUND_CM / 2;

    if (distanceCm <= MIN_RANGe || distanceCm >= MAX_RANGE) {
        Serial.println("Out of range " + String(distanceCm));
        oled.clear(PAGE);
        oled.drawBitmap(no_full_screen_bitmap);
        oled.display();
    } else if (distanceCm > MIN_RANGe && distanceCm <= WARNING_RANGE) {
        Serial.println("Warning: " + String(distanceCm, 2) + " cm");

        oled.clear(PAGE);
        oled.drawBitmap(warning_half_screen_bitmap);

        oled.setCursor(0, 40);
        oled.print(String(distanceCm, 1) + " cm");

        oled.display();
    } else {  // good range
        Serial.println("Distance: " + String(distanceCm, 2) + " cm");

        oled.clear(PAGE);
        oled.drawBitmap(yes_half_screen_bitmap);

        oled.setCursor(0, 40);
        oled.print(String(distanceCm, 1) + " cm");

        oled.display();
    }

    delay(500);
}

/*
  Ultra sonic notes
    - works best with 5v but LiPo is usually ok
    - range up to 13 feet
    - works better at shorter distances
    - works better to register larger object that have a pependicular reflection
  to sensor
    - affected temp / wind conditions
*/