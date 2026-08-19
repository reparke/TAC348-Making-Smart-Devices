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
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// these need to go first
//////////////////////////////////
// Arduino JSON                 //
//////////////////////////////////
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

//////////////////////////////////
// Pulse Sensor                 //
//////////////////////////////////
/* These three lines are different from the video */
#include <PulseSensorAmped.h>
const int pulseSignalPin = A1;
PulseSensor PulseSensorAmped;

//////////////////////////////////
// MicroOLED                    //
//////////////////////////////////
#include "SparkFunMicroOLED.h"  // Include MicroOLED library
// The library assumes a reset pin is necessary. The Qwiic OLED has RST
// hard-wired, so pick an arbitrarty IO pin that is not being used
#define PIN_RESET 9

// The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is
// open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1
MicroOLED oled(MODE_I2C, PIN_RESET, DC_JUMPER);  // I2C declaration
#include <Wire.h>

//////////////////////////////////
// Bitmaps                      //
//////////////////////////////////
#include "bitmaps_watch.h"
#include "bitmaps_weather.h"

boolean runOnce = true;

//////////////////////////
// Heart Screen Vars    //
//////////////////////////
/* refreshing the OLED is very slow and it causes
    the heart rate detection to fail
    This delay was determined experimentally to work well
*/
// calling oled.display() takes a long time
const unsigned long HEART_SCREEN_UPDATE = 3000;
unsigned long prevMillis = 0;
int beatAvg = 0;

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
// TODO:
const unsigned long CLOCK_SCREEN_UPDATE = 500;  // update every 1/2 s

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* Weatherstack only has 250 API calls in free plan so use
   very long delay (8 times per day)
*/
// TODO:
const unsigned long WEATHER_SCREEN_UPDATE = 10512000;  // 8 hours
float temperature;
String weatherDescription;
int weatherCode;
int uvIndex;

//////////////////////////
// Button Variables     //
//////////////////////////
const int PIN_BUTTON = D3;
int prevButtonVal = HIGH;  // the last VERIFIED state

//////////////////////////
// States               //
//////////////////////////
// TODO: create state enum and variable(s) to track state
enum State { Clock, Weather, Heart };
State currentState = Heart;

///////////////////////////////////////////////////////////////
//               END LIBRARIES AND DECLARATIONS              //
///////////////////////////////////////////////////////////////

// TODO
void runHeartScreen() {
    //     // for debugging
    //     Serial.println("Heart");
    //     oled.clear(PAGE);  // Clear the display
    //     oled.setCursor(0, 0);
    //     oled.print("Heart");
    //     oled.display();
    /*
        if HR is valid, show heart icon and HR on oled
        if HR is invalid, show heart icon and "---"

        invalid: very very high or very very low
    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > HEART_SCREEN_UPDATE) {
        prevMillis = curMillis;
        oled.clear(PAGE);
        oled.drawBitmap(bitmap_heart_16x12);
        oled.setFontType(1);
        oled.setCursor(20, 0);
        if (beatAvg > 230 || beatAvg < 40) {
            oled.print("---");
            Serial.println("---");

        } else {
            oled.print(String(beatAvg));
            Serial.println(beatAvg);
        }

        oled.setCursor(0, 30);

        // from Photon 2 documentation
        float batteryVoltage = analogRead(A6) / 819.2;
        oled.print("%: " + String(batteryVoltage, 1));

        oled.display();
    }
}

// TODO
void runClockScreen() {
    // // for debugging
    // Serial.println("Clock");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Clock");
    // oled.display();
    /*

        question: how often does the data update?
                once per second because the seconds change every second

        how often should we update/redraw the clock screen?
            goal: draw as INFREQUENTLY as possible as long as we can ensure
                  the user experience is positive

            options: redraw the screen
            1 time per second
            2 times per second
    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > CLOCK_SCREEN_UPDATE) {
        prevMillis = curMillis;
        oled.clear(PAGE);
        oled.drawBitmap(bitmap_clock_16x12);

        // make the formatting variables
        String dateFormat = "%b %e";
        String dayFormat = "%a";
        String timeFormat = "%I:%M";
        String secondFormat = "%S";

        oled.setFontType(0);
        // date
        oled.setCursor(25, 0);
        oled.print(Time.format(dateFormat));

        // day
        oled.setCursor(25, 10);
        oled.print(Time.format(dayFormat));

        // second
        oled.setCursor(50, 30);
        oled.print(Time.format(secondFormat));

        // time
        oled.setFontType(1);
        oled.setCursor(0, 25);
        oled.print(Time.format(timeFormat));

        oled.display();
    }
}

// TODO
void runWeatherScreen() {
    // // for debugging
    // Serial.println("Weather");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Weather");
    // oled.display();

    /*
        what should WEATHER_SCREEN_UPDATE be?
            or, how often should we redraw the screen?
        --> we have a unique constraint
            we get 100 API requests / month with free weatherstack
            ==> we should update 3 times per day (30 days in month)
    */

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        // get new weather
        Particle.publish("WeatherStackJSON", "");
    }
    oled.clear(PAGE);

    //rain is code 302, 299, 296
    switch(weatherCode) {
        case 302:
        case 299:
        case 296:   //this is an OR
            oled.drawBitmap(bitmap_rainy_16x12);
            break;
        //we could many more here...
        default:
            oled.drawBitmap(bitmap_sunny_16x12);
            break;
    }
    oled.setFontType(1);
    oled.setCursor(38, 5);
    oled.print(temperature,0);

    oled.setFontType(0);
    oled.print("o");

    oled.setCursor(0, 28);
    oled.print(weatherDescription);
    oled.setCursor(0, 40);
    oled.print("UV Ind: ");
    oled.print(uvIndex);
    oled.display();
    
}

// TODO
void getNextState() {
    switch (currentState) {
        case Clock:
            currentState = Heart;
            break;
        case Heart:
            currentState = Weather;
            break;
        case Weather:
            currentState = Clock;
            break;
    }
}

// TODO
void loadNextScreen() {
    switch (currentState) {
        case Clock:
            runClockScreen();
            break;
        case Heart:
            runHeartScreen();
            break;
        case Weather:
            runWeatherScreen();
            break;
    }
}

////////////////////////////
// Pulse Sensor Functions //
////////////////////////////

// event handler
void PulseSensorAmped_data(int BPM, int IBI) { beatAvg = BPM; }

void PulseSensorAmped_lost(void) {}

void myHandler(const char *event, const char *data) {
    // Handle the integration response
    Serial.println(String(data));

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    /* template
    {"name":"{{location.name}}", "temperature":"{{current.temperature}}",
    "description":"{{current.weather_descriptions.0}}",
    "uvIndex":"{{current.uv_index}}","code":"{{current.weather_code}}"
    }
    */

    /* Here is where your parsing code goes */
    // parse JSON
    temperature = doc["temperature"];
    weatherCode = doc["code"];
    weatherDescription = String(doc["description"]);
    uvIndex = doc["uvIndex"];

    Serial.println("Description = " + weatherDescription);
    Serial.println("Code = " + String(weatherCode));
    Serial.println("Temperature = " + String(temperature));
    Serial.println("UV Index = " + String(uvIndex));
}

void setup() {
    /*
https://community.particle.io/t/pulse-sensor-amped-incompatible-with-os-5-3-0/64313/4?u=rob7
*/
    analogRead(pulseSignalPin);  // bug workaround

    Serial.begin(9600);
    Serial.println("Initializing...");

    PulseSensorAmped.attach(pulseSignalPin);
    PulseSensorAmped.start();

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

    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
}

/*
    goal: we would like to make ONE weatherStack request everytime the photon
   turns on      --> this SHOULD BE IN SETUP problem: in the setup, the photon
   does not YET HAVE INTERNET ACCESS!

    solution: put publish, and create a boolean flag to make sure it only runs
   once
*/

void loop() {
    if (runOnce == true && Particle.connected() == true) {
        runOnce = false;
        Particle.publish("WeatherStackJSON", "");
    }
    // latch
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        getNextState();
    }
    loadNextScreen();
    // takes a reading
    PulseSensorAmped.process();

    prevButtonVal = curButtonVal;
}