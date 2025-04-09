/* NOTE - Rob Parke 9/25/2021

Updated version for Qwiic I2C OLED + MAX30101

Eliminated software timers

*/
/*
  Optical Heart Rate Detection (PBA Algorithm) using the MAX30105 Breakout
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  This is a demo to show the reading of heart rate or beats per minute (BPM)
  using a Penpheral Beat Amplitude (PBA) algorithm.

  It is best to attach the sensor to your finger using a rubber band or other
  tightening device. Humans are generally bad at applying constant pressure to a
  thing. When you press your finger against the sensor it varies enough to cause
  the blood in your finger to flow differently which causes the sensor readings
  to go wonky.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering
  the board with 5V but it will also run at 3.3V.
*/

#include "MAX30105.h"
#include "heartRate.h"
// libraries for OLED
#include "SparkFunMicroOLED.h"  // Include MicroOLED library
#include "bitmaps_watch.h"
#include "bitmaps_weather.h"
MAX30105 particleSensor;

const byte RATE_SIZE = 4;  // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];     // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;  // Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
//////////////////////////
// Heart Screen         //
//////////////////////////
/* refreshing the OLED is very slow and it causes
    the heart rate detection to fail
    This delay was determined experimentally to work well
*/
unsigned long prevScreenUpdateMillis = 0;
unsigned long HEART_SCREEN_UPDATE_MS = 3000;
unsigned long TIME_SCREEN_UPDATE_MS = 500;

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
// The library assumes a reset pin is necessary. The Qwiic OLED has RST
// hard-wired, so pick an arbitrarty IO pin that is not being used
#define PIN_RESET 9

// The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is
// open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1
MicroOLED oled(MODE_I2C, PIN_RESET, DC_JUMPER);  // I2C declaration
#include <Wire.h>
//////////////////////////
// Button Variables     //
//////////////////////////
const int PIN_BUTTON = D3;
int prevReading = HIGH;     // the last VERIFIED state
int curButtonState;         // the current VERIFIED state
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 200;   // the debounce time; increase if the output
//////////////////////////
// States               //
//////////////////////////
// need to build this
enum State { HEART, TIME, WEATHER };
State currentState = HEART;
void getNextState() {
    switch (currentState) {
        case HEART:
            currentState = TIME;
            break;
        case TIME:
            currentState = WEATHER;
            break;
        case WEATHER:
            currentState = HEART;
            break;
    }
}
void loadNextScreen() {
    switch (currentState) {
        case HEART:
            runHeartScreen();
            break;
        case TIME:
            runTimeScreen();
            break;
        case WEATHER:
            runWeatherScreen();
            break;
    }
}
void runTimeScreen() {
    unsigned long curMillis = millis();
    if (curMillis - prevScreenUpdateMillis > TIME_SCREEN_UPDATE_MS) {
        prevScreenUpdateMillis = curMillis;

        String dateFormat = "%b %d";
        String dayFormat = "%a";
        String timeFormat = "%I:%M";
        String secondsFormat = "%S";
        // String timeFormat = "%I:%M ";
        // for debugging
        Serial.println("Time");

        oled.clear(PAGE);  // Clear the display
        delay(10);
        oled.drawBitmap(clock_16x12);

        oled.setCursor(25, 0);
        oled.setFontType(0);
        oled.print(Time.format(dateFormat));

        oled.setCursor(25, 10);
        oled.setFontType(0);
        oled.print(Time.format(dayFormat));

        oled.setFontType(1);
        oled.setCursor(0, 25);
        oled.print(Time.format(timeFormat));

        oled.setFontType(0);
        oled.setCursor(50, 30);
        oled.print(Time.format(secondsFormat));

        oled.display();
    }
}

void runWeatherScreen() {  // doesn't use JSON or webhook
    unsigned long curMillis = millis();
    if (curMillis - prevScreenUpdateMillis > HEART_SCREEN_UPDATE_MS) {
        prevScreenUpdateMillis = curMillis;

        // for debugging
        Serial.println("Weather");
        // testing variables -- replace with JSON values later
        float tempWeather = 74.24;
        String city = "Los Angeles";

        oled.clear(PAGE);  // Clear the display
        oled.drawBitmap(weather_sunny_16x12);

        oled.setCursor(32, 5);
        oled.setFontType(1);
        oled.print(tempWeather, 0);

        oled.setFontType(0);
        oled.setCursor(0, 30);
        oled.print(city);

        oled.display();
    }
}
void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    // Initialize sensor
    if (!particleSensor.begin(
            Wire, I2C_SPEED_FAST))  // Use default I2C port, 400kHz speed
    {
        Serial.println("MAX30105 was not found. Please check wiring/power. ");
        while (1)
            ;
    }
    Serial.println(
        "Place your index finger on the sensor with steady pressure.");

    particleSensor.setup();  // Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(
        0x0A);  // Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0);  // Turn off Green LED

    // initialize OLED
    oled.begin();      // Initialize the OLED
    oled.clear(PAGE);  // Clear the display
    oled.drawBitmap(trojan_bmp);
    oled.display();
    delay(1000);  // Delay 1000 ms
    oled.drawBitmap(usc_bmp);
    oled.display();
    delay(1000);  // Delay 1000 ms

    pinMode(PIN_BUTTON, INPUT);
}

unsigned long lastRead = 0;
unsigned long samples = 0;

const int LOW_BPM_THRESHOLD = 40;
const int LOW_IR_THRESHOLD = 50000;
float bodyTempF;
void loop() {
    int curReading = digitalRead(PIN_BUTTON);  // check button read

    if (curReading == HIGH && prevReading == LOW) {
        getNextState();  // button was pressed down, we should change
        prevScreenUpdateMillis = 0;  // make sure next screen loads
                                     // immediately instead of waiting
    }

    // FINALLY! here is your button code
    // if want to execute when button pressed down ONLY

    loadNextScreen();
    prevReading = curReading;  // update for next loop
}
long irValue = 0;

void runHeartScreen() {
    updateBPM();
    unsigned long curMillis = millis();
    if (curMillis - prevScreenUpdateMillis > HEART_SCREEN_UPDATE_MS) {
        prevScreenUpdateMillis = curMillis;

        // calcHeartBeatAvg();  // this is slow! -- beatAvg
        if (beatAvg > LOW_BPM_THRESHOLD &&
            irValue > LOW_IR_THRESHOLD) {  // VALID!
            oled.clear(PAGE);
            oled.drawBitmap(heart16x12);
            oled.setFontType(1);
            oled.setCursor(20, 0);
            oled.print(String(beatAvg));
        } else {
            // INVALID!
            oled.clear(PAGE);
            oled.drawBitmap(heart16x12);
            oled.setFontType(1);
            oled.setCursor(20, 0);
            oled.print("---");
        }
        bodyTempF = particleSensor.readTemperatureF();
        oled.setCursor(0, 20);
        oled.setFontType(1);
        oled.print("Temp ");
        oled.print(String(bodyTempF, 0));

        float voltage = analogRead(BATT) * 0.0011224;
        oled.setCursor(0, 40);
        oled.setFontType(0);
        oled.print("Batt ");
        oled.print(String(voltage, 2));
        oled.display();
        Serial.print("BPM: " + String(beatsPerMinute) +
                     ", Avg: " + String(beatAvg));
        Serial.println(", IRvalue: " + String(irValue) +
                       ", Temp: " + String(bodyTempF));
    }
    // consider adding battery status bands
    // https://community.particle.io/t/can-argon-or-xenon-read-the-battery-state/45554/35?u=rob7
}

/* ====================== HEART RATE FUNCTIONS ===============
  These functions are completed and shouldn't be modified
*/
/* fn: updateBPM
This function is called by timer. It needs to execute
quickly otherwise sensor won't properly register beats
and BPM will be off
*/
void updateBPM() {
    irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
        // We sensed a beat!
        long delta = millis() - lastBeat;
        lastBeat = millis();

        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            rates[rateSpot++] =
                (byte)beatsPerMinute;  // Store this reading in the array
            rateSpot %= RATE_SIZE;     // Wrap variable

            calcHeartBeatAvg();
        }
    }

    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);

    if (irValue < 50000) Serial.print(" No finger?");

    unsigned long curRead = millis();
    samples++;
    Serial.print("\t\t\t\tHz[");
    Serial.print((float)1000.0 / (curRead - lastRead), 2);
    Serial.print("] Avg Hz[");
    Serial.print((float)samples * 1000.0 / (curRead), 2);
    Serial.print("]");
    Serial.println();
    lastRead = curRead;
    Serial.println();
    //   delay(50);
}

/* fn: calcHeartBeatAvg
This function is slow so it should be done during display
 NOT during timer reading of heart rate
*/
void calcHeartBeatAvg() {
    beatAvg = 0;
    for (byte x = 0; x < RATE_SIZE; x++) {
        beatAvg += rates[x];
    }
    beatAvg /= RATE_SIZE;
}
