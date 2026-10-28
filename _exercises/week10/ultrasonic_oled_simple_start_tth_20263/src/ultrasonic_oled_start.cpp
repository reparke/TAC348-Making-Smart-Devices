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
const int PIN_ECHO = D5;
const int PIN_TRIGGER = D6;

const float SPEED_SOUND_CM = 0.03444;


unsigned long prevMillis = 0;
const unsigned long INTERVAL = 50;

//what else do we need to animate the ball?
int xPos = 20;
int yPos = 20;

int xSpeed = 1; //-1 will be oppostite dir
int ySpeed = 1;

void bounce() {
  unsigned long currMillis = millis();
  if(currMillis - prevMillis > INTERVAL) {
    prevMillis = currMillis;

    oled.setColor(BLACK);
    oled.circleFill(xPos, yPos, 4);

    //how do make the ball "bounce" off the walls?
    //if we hit right or left edge, just inverse the speed
    if (xPos <= 4 || xPos >= 59){
      xSpeed = -1 * xSpeed;
    }

    //if we hit upper or lower edge, invert speed
    if (yPos <=4 || yPos >= 43) {
      ySpeed = -1 * ySpeed;
    }

    xPos = xPos + xSpeed;
    yPos = yPos + ySpeed;

    oled.setColor(WHITE);
    oled.circleFill(xPos,yPos, 4);
    oled.display();
  }
}

void measureDistance() {
  //take a measurement of distance
  //display on serial
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
  //now 8 pulses are sent

  //wait for the response
  //pulseIn tells us the time to get response
  int timeMeasured = pulseIn(PIN_ECHO, HIGH);

  //calc dist
  float distanceCm = SPEED_SOUND_CM * timeMeasured / 2;

  Serial.println("Distance cm: " + String(distanceCm, 1));

  //we need a "pause" in between readings
  delay(500); //also could use millis if we needed to


}

void setup() {
    Serial.begin(9600);  // begin serial communication with the computer
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.display();      // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 1000 ms

    //from the perspective of the photon
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_TRIGGER, OUTPUT);

    oled.drawBitmap(spongebob_bitmap);
    oled.display();

  }

/********************************************************************************/
void loop() {
  // measureDistance();
  bounce();
}
