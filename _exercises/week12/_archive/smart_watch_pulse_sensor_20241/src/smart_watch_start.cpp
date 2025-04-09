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

  
#include <PulseSensorAmped.h>
const int pulseSignalPin = A4;

//////////////////////////////////
// MicroOLED                    //
//////////////////////////////////
#include <SparkFunMicroOLED.h>  // Include MicroOLED library
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

//////////////////////////
// Heart Screen Vars    //
//////////////////////////
/* refreshing the OLED is very slow and it causes
    the heart rate detection to fail
    This delay was determined experimentally to work well
*/
// TODO:
unsigned long HEART_SCREEN_UPDATE = 3000;  // experimentally derived
unsigned long prevMillis = 0;
int beatAverage = 0;

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
// TODO:
unsigned long CLOCK_SCREEN_UPDATE = 500;

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* Weatherstack only has 250 API calls in free plan so use
   very long delay (8 times per day)
*/
// TODO:

unsigned long WEATHER_SCREEN_UPDATE = 10512000;
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
enum State { Clock, Heart, Weather };
State currentState = Weather;

//////////////////////////////
// Publish after Setup Flag //
//////////////////////////////
// TODO: create flag to publish ONCE after setup to get weather
// this is necessary because with threading enabled, setup() runs
// before cloud connectivity is enabled
// https://community.particle.io/t/cant-particle-publish-in-setup-with-cpp-file/66688/3?u=rob7
bool runOnce = true;

///////////////////////////////////////////////////////////////
//               END LIBRARIES AND DECLARATIONS              //
///////////////////////////////////////////////////////////////

// TODO
void runHeartScreen() {  // updating OLED, not measuring HR
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > HEART_SCREEN_UPDATE) {
        prevMillis = curMillis;
        oled.clear(PAGE);
        oled.drawBitmap(bitmap_heart_16x12);
        oled.setFontType(1);
        oled.setCursor(20, 0);
        if (beatAverage > 230 || beatAverage < 40) {
            Serial.println("HR: ---");
            oled.print("---");
        } else {
            Serial.println("HR: " + String(beatAverage));
            oled.print(String(beatAverage));
        }
        oled.display();
    }
}

// TODO
void runClockScreen() {
    /*
        how often should we update the clock screen?
        1 time per second
        2 times per second
    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > CLOCK_SCREEN_UPDATE) {
        prevMillis = curMillis;

        String dateFormat = "%b %e";
        String dayFormat = "%a";
        String timeFormat = "%I:%M";
        String secondFormat = "%S";

        oled.clear(PAGE);
        oled.drawBitmap(bitmap_clock_16x12);
        oled.setFontType(0);

        // date
        oled.setCursor(25, 0);
        oled.print(Time.format(dateFormat));
        // day
        oled.setCursor(25, 10);
        oled.print(Time.format(dayFormat));
        // time
        oled.setFontType(1);
        oled.setCursor(0, 25);
        oled.print(Time.format(timeFormat));
        // seconds
        oled.setFontType(0);
        oled.setCursor(50, 30);
        oled.print(Time.format(secondFormat));
        oled.display();
    }

    /*
    oled.print
    Nov 14_ (cursor remains after the 14)

    oled.println
    Nov 14 (cursor goes the next line)
    _

    */
}

// TODO
void runWeatherScreen() {
    // 8 times per day we request the weather day
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        Particle.publish("WeatherStackJSON", "", PRIVATE);
    }
    // but we always draw the screen
    oled.clear(PAGE);
    // rain is code 302, 299, 296
    switch (weatherCode) {
        case 302:
        case 299:
        case 296:
            oled.drawBitmap(bitmap_rainy_16x12);
            break;
        // we could have more case statements for other weather
        default:
            oled.drawBitmap(bitmap_sunny_16x12);
            break;
    }
    oled.setFontType(0);
    oled.setCursor(38, 5);
    oled.print(temperature, 0);

    oled.setCursor(0, 28);
    //display the description on one line
    oled.print(weatherDescription.substring(0,9));
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
// this event handler is called asynchronously
void PulseSensorAmped_data(int BPM, int IBI) {
    beatAverage = BPM;  // BPM is a value of the current HR from the sensor
}

void PulseSensorAmped_lost(void) {}

void myHandler(const char *event, const char *data) {
    // declare object to store JSON response
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    // Test to see if was successful
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        return;
    }

    // parse JSON
    weatherCode = doc["code"];
    temperature = doc["temperature"];
    weatherDescription = String(doc["description"]);

    Serial.println("temperature: " + String(temperature));
    Serial.println("Code:" + String(weatherCode));
    Serial.println("Description: " + weatherDescription);
}

void setup() {
    /*
https://community.particle.io/t/pulse-sensor-amped-incompatible-with-os-5-3-0/64313/4?u=rob7
*/
    analogRead(pulseSignalPin);  // bug workaround

    Serial.begin(115200);
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
    Time.zone(-8);
    Time.beginDST();

    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);

}

void loop() {
    if (runOnce == true && Particle.connected() == true) {
        runOnce = false;
        Particle.publish("WeatherStackJSON", "", PRIVATE);
        Serial.println("run once");
    }

    // TODO
    int currentButtonVal = digitalRead(PIN_BUTTON);
    // latch
    if (currentButtonVal == LOW && prevButtonVal == HIGH) {
        // change the state variable
        getNextState();
    }
    loadNextScreen();
    PulseSensorAmped.process();  // measure HR
    /*
        mearsure HR all the time
        - battery drain
        + HR is instantly available on heart screen
        + tracking HR over time
        --> when not on heart screen, sample HR at regular (long spaced)
       intervals
    */
    prevButtonVal = currentButtonVal;
}
