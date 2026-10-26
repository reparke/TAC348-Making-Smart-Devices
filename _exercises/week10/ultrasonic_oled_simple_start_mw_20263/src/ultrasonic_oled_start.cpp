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
const int PIN_TRIGGER = D6;
const int PIN_ECHO = D5;

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
const float SPEED_SOUND_CM = 0.03444;

unsigned long prevMillis = 0;
const unsigned long SCREEN_INTERVAL = 50;  // redraw the screen every 50ms

// what var do we need?
int xPos = 20;
int yPos = 20;

// make life easier by setting the dir and movement at same time
int xSpeed = 1;  // 1 means more to right, -1 means move to left
int ySpeed = 1;

const int RADIUS = 4;
const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 48;

void bounce() {
    unsigned long currMillis = millis();

    if (currMillis - prevMillis > SCREEN_INTERVAL) {
        prevMillis = currMillis;

        oled.setColor(BLACK);
        oled.circleFill(xPos, yPos, RADIUS);

        // if circle hits right or left edge, reverse horiz dir
        //  left boundary: 4
        //  right boundary: 59 <== 64 - 1 - 4
        if (xPos <= RADIUS || xPos >= SCREEN_WIDTH - 1 - RADIUS) {
            xSpeed = -1 * xSpeed;
        }

        // if circle hits top or bottom edge, change vertical dir
        //  top bnd: 4
        //  bottom bnd: 43 <=== 48 - 1 - radius
        if (yPos <= RADIUS || yPos >= SCREEN_HEIGHT - 1 - RADIUS) {
            ySpeed = -1 * ySpeed;
        }

        xPos = xPos + xSpeed;
        yPos = yPos + ySpeed;
        oled.setColor(WHITE);
        oled.circleFill(xPos, yPos, RADIUS);
        oled.display();
    }
}

void measureDistance() {
    // print out distance to serial mon
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);  // don't use millis
    digitalWrite(PIN_TRIGGER, LOW);
    // send 8 pulses

    // wait for time
    int timeMeasure = pulseIn(PIN_ECHO, HIGH);

    float distanceCm = timeMeasure * SPEED_SOUND_CM / 2;
    Serial.println("Distance (cm): " + String(distanceCm));

    // recommended is a 500 ms delay (could use millis)
    delay(500);
}

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    oled.drawBitmap(tac348_bitmap);
    oled.display();
    delay(1000);  // Delay 1000 ms
    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

/********************************************************************************/
void loop() {
    // measureDistance();
    bounce();
}
