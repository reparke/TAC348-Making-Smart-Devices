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

const float SPEED_SOUND_CM = 0.03444;
const int MIN_RANGE_CM = 2;
const int WARNING_RANGE_CM = 12;
const int MAX_RANGE_CM = 400;

// How often to read the distance
const unsigned long MEASURE_CYCLE = 500;

// How often to move the circle
const unsigned long ANIMATION_CYCLE = 30;

// Maximum time to wait for an echo
const unsigned long ECHO_TIMEOUT_US = 25000;

// Time of the last distance measurement
unsigned long prevMillisMeasure = 0;

// Time of the last animation update
unsigned long prevMillisAnimation = 0;

float distanceCm = 0;

//////////////////////////
// Circle Animation     //
//////////////////////////
const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 48;
const int CIRCLE_RADIUS = 4;

// Starting position of the circle
int xPos = 12;
int yPos = 12;

// How much the circle moves each time
int xSpeed = 1;
int ySpeed = 1;

// void measureDistance() {
//     unsigned long currMillis = millis();

//     if (currMillis - prevMillisMeasure > MEASURE_CYCLE) {
//         prevMillisMeasure = currMillis;

//         digitalWrite(PIN_TRIGGER, LOW);  // Start the sequence
//         delayMicroseconds(2);
//         digitalWrite(PIN_TRIGGER, HIGH);
//         delayMicroseconds(10);
//         digitalWrite(PIN_TRIGGER, LOW);

//         // Wait for the echo, but do not wait longer than the timeout
//         unsigned long timeMeasure = pulseIn(PIN_ECHO, HIGH, ECHO_TIMEOUT_US);

//         distanceCm = timeMeasure * SPEED_SOUND_CM / 2;

//         // Print the new reading once per measurement
//         if (distanceCm <= MIN_RANGE_CM || distanceCm >= MAX_RANGE_CM) {
//             Serial.println("Out of range");
//         } else if (distanceCm <= WARNING_RANGE_CM) {
//             Serial.println("Warning! Distance (cm): " + String(distanceCm, 2));
//         } else {
//             Serial.println("Distance (cm): " + String(distanceCm, 2));
//         }
//     }
// }

// void drawDistance() {
//     // Each bitmap fills the screen, so it also erases the circle's old position
//     if (distanceCm <= MIN_RANGE_CM || distanceCm >= MAX_RANGE_CM) {
//         oled.drawBitmap(no_full_screen_bitmap);
//     } else if (distanceCm <= WARNING_RANGE_CM) {
//         oled.drawBitmap(warning_half_screen_bitmap);
//         oled.setCursor(0, 40);
//         oled.print(String(distanceCm, 1) + " cm");
//     } else {
//         oled.drawBitmap(yes_half_screen_bitmap);
//         oled.setCursor(0, 40);
//         oled.print(String(distanceCm, 1) + " cm");
//     }

//     // Draw the circle on top of the distance display
//     oled.setColor(WHITE);
//     oled.circleFill(xPos, yPos, CIRCLE_RADIUS);

//     // Send the updated picture to the OLED
//     oled.display();
// }

void bounce() {
    unsigned long currMillis = millis();

    if (currMillis - prevMillisAnimation > ANIMATION_CYCLE) {
        prevMillisAnimation = currMillis;

        oled.setColor(BLACK);
        oled.circleFill(xPos, yPos, CIRCLE_RADIUS);

        // If the circle is at the left or right edge,
        // reverse its horizontal direction
        if (xPos <= CIRCLE_RADIUS || xPos >= SCREEN_WIDTH - 1 - CIRCLE_RADIUS) {
            xSpeed = -xSpeed;
        }

        // If the circle is at the top or bottom edge,
        // reverse its vertical direction
        if (yPos <= CIRCLE_RADIUS ||
            yPos >= SCREEN_HEIGHT - 1 - CIRCLE_RADIUS) {
            ySpeed = -ySpeed;
        }

        // Move the circle
        xPos = xPos + xSpeed;
        yPos = yPos + ySpeed;

        // Redraw the background so the old circle disappears

        // Draw the circle at its new position
        oled.setColor(WHITE);
        oled.circleFill(xPos, yPos, CIRCLE_RADIUS);

        // Show the updated frame
        oled.display();

        // Redraw the screen with the circle in its new position
        // drawDistance();
    }
}

void setup() {
    Serial.begin(9600);  // Begin serial communication with the computer

    oled.begin();     // Initialize the OLED
    oled.clear(ALL);  // Clear the display's internal memory
    oled.drawBitmap(tac348_bitmap);
    oled.display();  // Display the splashscreen
    delay(1000);     // Show the splashscreen for 1 second

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void loop() {
    // measureDistance();
    bounce();
}

/*
  Bitmaps
  * Using the ultrasonic distance sensor, display graphics and distance
    measurement on the OLED

  * Large error graphic when out of range (no_full_screen.png)
  * Small warning message when less than 12 cm and the distance
    (warning_half_screen.png)
  * Small graphics and distance message otherwise
    (yes_half_screen.png)
*/