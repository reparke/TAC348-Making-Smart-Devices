/* NOTE - Rob Parke
4/14/2022
    -Adding Weatherstack API / JSON

9/25/2021
    -Updated version for Qwiic I2C OLED + MAX30101
    -Eliminated software timers

8/29/2022
    -updated to use pulse sensor
    note from Bill Siever: Most of the real work is done by interrupts.  The
process() is needed to do the callbacks to user code (triggers the call to
either PulseSensorAmped_data() or PulseSensorAmped_lost ()).  If you’d want to
try to catch an individual beat, it should be called faster than the expected
heart rate (maybe 2x faster….So maybe 6x per second or ~166ms?) .  If you just
want occasional updates, you can call it less frequently.

*/

// libraries for OLED
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

#include "SparkFunMicroOLED.h"  // Include MicroOLED library
#include "bitmaps_watch.h"
#include "bitmaps_weather.h"

// const byte RATE_SIZE = 4;  // Increase this for more averaging. 4 is good.
// byte rates[RATE_SIZE];     // Array of heart rates
// byte rateSpot = 0;
// long lastBeat = 0;  // Time at which the last beat occurred
const int pulseSignalPin = A0;

// #include <PulseSensorAmped.h>
#include "PulseSensor.h"
PulseSensor pulseSensor;
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

const int LOW_BPM_THRESHOLD = 40;
const int HIGH_BPM_THRESHOLD = 200;

//////////////////////////
// Time  Screen         //
//////////////////////////
/*
 */
unsigned long TIME_SCREEN_UPDATE_MS = 500;

//////////////////////////
// Weather Screen         //
//////////////////////////
/* Weatherstack only has 250 API calls in free plan so use
   very long delay (8 times per day)
*/
unsigned long WEATHER_SCREEN_UPDATE_MS = 10512000;
float tempWeather = 0;
String city = "city";
String weatherDescription = "desc";
int weatherCode = 0;
int uvIndex = 0;

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
int prevButtonVal = HIGH;  // the last VERIFIED state

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
        oled.drawBitmap(bitmap_clock_16x12);

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
    if (curMillis - prevScreenUpdateMillis > WEATHER_SCREEN_UPDATE_MS) {
        prevScreenUpdateMillis = curMillis;
        String data = "90089";
        Particle.publish("WeatherStackJSON", data, PRIVATE);
    }

    oled.clear(PAGE);
    switch (weatherCode) {
        case 296:
        case 302:
        case 308:
            oled.drawBitmap(bitmap_rainy_16x12);
            break;
        case 116:
        case 119:
        case 122:
            oled.drawBitmap(bitmap_cloudy_16x12);
            break;
        case 227:
            oled.drawBitmap(bitmap_snowing_16x12);
            break;

        default:
            oled.drawBitmap(bitmap_sunny_16x12);
            break;
    }

    oled.setCursor(38, 5);
    oled.setFontType(1);
    // oled.print(tempWeather, 0);
    oled.print(77);
    oled.setFontType(0);
    oled.print("o");

    oled.setFontType(0);
    oled.setCursor(0, 28);
    oled.print(weatherDescription.substring(0, 9));

    oled.setFontType(0);
    oled.setCursor(0, 40);
    oled.print("UV Ind: ");
    oled.print(uvIndex);

    oled.display();
}

void runHeartScreen() {
    unsigned long curMillis = millis();
    if (curMillis - prevScreenUpdateMillis > HEART_SCREEN_UPDATE_MS) {
        prevScreenUpdateMillis = curMillis;

        if (beatAvg > LOW_BPM_THRESHOLD &&
            beatAvg < HIGH_BPM_THRESHOLD) {  // VALID!
            oled.clear(PAGE);
            oled.drawBitmap(bitmap_heart_16x12);
            oled.setFontType(1);
            oled.setCursor(20, 0);
            oled.print(String(beatAvg));
        } else {
            // INVALID!
            oled.clear(PAGE);
            oled.drawBitmap(bitmap_heart_16x12);
            oled.setFontType(1);
            oled.setCursor(20, 0);
            oled.print("---");
        }

        // float voltage = analogRead(BATT) * 0.0011224;
        float voltage = 0;
        oled.setCursor(0, 40);
        oled.setFontType(0);
        oled.print("Batt ");
        oled.print(String(voltage, 2));
        oled.display();
        Serial.println("BPM: " + String(beatAvg));
    }
    // consider adding battery status bands
    // https://community.particle.io/t/can-argon-or-xenon-read-the-battery-state/45554/35?u=rob7
    /*

Charging ( V > 4.3)
Full Charge (V >=4.2
Nominal (4.2 > V > 3.5)
Low/Needs Recharge (3.5 > V >= 3.4)
Critical (3.4 > V)

    */
}
void setup() {
    // analogRead(pulseSignalPin);

    Serial.begin(115200);
    Serial.println("Initializing...");

    pulseSensor.attach(pulseSignalPin);
    pulseSensor.start();

    // initialize OLED
    oled.begin();      // Initialize the OLED
    oled.clear(PAGE);  // Clear the display
    oled.drawBitmap(bitmap_trojan_64x48);
    oled.display();
    delay(1000);  // Delay 1000 ms
    oled.drawBitmap(bitmap_usc_64x48);
    oled.display();
    delay(1000);  // Delay 1000 ms

    pinMode(PIN_BUTTON, INPUT);
    Particle.subscribe("hook-response/WeatherStackJSON",
                       jsonSubscriptionHandler, MY_DEVICES);

    String data = "90089";
    Particle.publish("WeatherStackJSON", data, PRIVATE);
	
	  Time.zone(-8);
    Time.beginDST();
}

void loop() {
    int curButtonVal = digitalRead(PIN_BUTTON);  // check button read

    if (curButtonVal == HIGH && prevButtonVal == LOW) {
        getNextState();  // button was pressed down, we should change
        prevScreenUpdateMillis = 0;  // make sure next screen loads
                                     // immediately instead of waiting
    }
    pulseSensor.process();

    // FINALLY! here is your button code
    // if want to execute when button pressed down ONLY

    loadNextScreen();
    prevButtonVal = curButtonVal;  // update for next loop
}

void jsonSubscriptionHandler(const char *event, const char *data) {
    // Handle the integration response
    // Serial.println(String(data) + "\n\n");

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }
    /* temporary workaround for global String variable issue */
    weatherDescription = String(doc["description"]);
    city = String(doc["name"]);

    weatherCode = doc["weather_code"];
    uvIndex = doc["uv_index"];
    tempWeather = doc["temperature"];

    Serial.println("The weather in " + city + " is " + weatherDescription +
                   " and " + String(tempWeather) +
                   " degrees C with UV index of " + String(uvIndex));
}

// An optional function to recieve the Beats Per Minute (BPM) and Interbeat
// Interval (IBI) in mS
void PulseSensorAmped_data(int BPM, int IBI) {
    // Serial.print("BPM:");
    // Serial.print(BPM);
    // Serial.print(" IBI: ");
    // Serial.println(IBI);
    beatAvg = BPM;
}

// An optional function to indicate that the pulse signal has been lost
// (Due to the nature of pulse detection via reflected light, spurios signals
// are possible.
//  i.e. received data may not be valid)
void PulseSensorAmped_lost(void) {
    // Serial.println("Pulse Lost");
    // beatAvg = 0;
}
