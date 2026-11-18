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

#include "json_webhook_response_helper.h"

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
#include "bitmaps_sunrise_sunset.h"
#include "bitmaps_watch.h"
#include "bitmaps_weather.h"

//////////////////////////
// Heart Screen Vars    //
//////////////////////////
/* refreshing the OLED is very slow and it causes
    the heart rate detection to fail
    This delay was determined experimentally to work well


    how fast? fast enough to  show meaningful changes but not so often that it
drains battery power or slows HR reading

    experimentally, 3 s between heart screen redraws is ok.

if we starting fresh with no knowledge of this watch,
    how often should we refresh, or what considerations should we factor in the
decision? -cost / feasibility -size -battery -how often does the HR update
        -responsiveness
*/
// TODO:
unsigned long prevMillis = 0;
int beatAvg = 0;
const unsigned long HEART_SCREEN_UPDATE =
    3000;  // just determined experimentally

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
/*

how frequently should we update the clock screen?
    - once per second (if we're showing seconds) - too slow
    - once per minute (if we're just minutes)   - too slow
    --> only as often as we need to (as often as the data changes)


    why not update 10 times per second?
        - maybe the oled can't even update that fast (sensor constraint)
        - time doesn't even change that fast --> waste of battery/electricity

    one small things we to consider
        if we want to show the second, updating once per second is too slow
        why not?
            - latency / lag in oled
        -> update screen at twice the frequency which would every 500ms


*/

const unsigned long TIME_SCREEN_UPDATE = 500;

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* Open Meteo
    how often should we update the weather screen?
        -hourly?
        -10 min?
        -every two hours?

    what would influence our choice of update frequency?
        - how variable is the weather where live
        - do you go outside even?
        - time of day
        - how often does the service itself?
        - what is our purpose?
 */
const unsigned long WEATHER_SCREEN_UPDATE = 1800000;  // 30 min
int humidity = 0;
float temperature = 0;
int weatherCode = 0;
/*
    remind us: what is the process/steps we use to be able to access the weather
from open meteo API

- particle.publish to webhoook
- build the URL which shows which pieces of weather data
- go particle and build the webhook / integration
- "receive the json" with GET ---> we have to subscribe to response
- parse the json with our event handler


phase 2: we realize that the request for the happens only every 30 min
    --> we should make the request in setup so it will happen once on startup
    ==========>>>>>>> we can't do this!
    in order to publish, we  need wifi --> setup() doesn't have wifi yet

    so instead, we will create a boolean flag which guarantees we run once

*/
bool runOnce = true;

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
    // // for debugging
    // Serial.println("Heart");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Heart");
    // oled.display();

    /*
        if HR is valid, show heart icon and HR on OLED
        if HR is invalid, show icon and "---"

        invalid is very high or very low
    */

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > HEART_SCREEN_UPDATE) {
        prevMillis = curMillis;

        oled.clear(PAGE);
        oled.drawBitmap(bitmap_heart_16x12);
        oled.setFontType(1);
        oled.setCursor(20, 0);
        // handle invalid reading
        if (beatAvg < 40 || beatAvg > 230) {
            oled.print("---");
            Serial.println("---");
        } else {
            oled.print(beatAvg);
            Serial.print(beatAvg);
        }
        oled.display();
    }
}

// TODO
void runClockScreen() {
    //     // for debugging
    //     Serial.println("Clock");
    //     oled.clear(PAGE);  // Clear the display
    //     oled.setCursor(0, 0);
    //     oled.print("Clock");
    //     oled.display();

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > TIME_SCREEN_UPDATE) {
        prevMillis = curMillis;

        // create formats
        String dateFormat = "%b %e";  // Nov 18
        String dayFormat = "%a";      // Mon
        String secondFormat = "%S";
        String timeFormat = "%I:%M";

        oled.clear(PAGE);
        oled.drawBitmap(bitmap_clock_16x12);

        // date
        oled.setFontType(0);
        oled.setCursor(25, 0);
        oled.print(Time.format(dateFormat));

        // day
        oled.setCursor(25, 10);
        oled.print(Time.format(dayFormat));

        // seconds
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
    // for debugging
    // Serial.println("Weather");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Weather");
    // oled.display();

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;

        Particle.publish("open_meteo", "");
    }

    oled.drawBitmap(
        bitmap_sunny_16x12);  // if statement for weather code to change image
    oled.setFontType(1);
    oled.setCursor(38, 5);
    oled.print(temperature);

    oled.display();
}

// sets the next state based on the current state
void getNextState() {
    switch (currentState) {
        case Clock:
            currentState = Weather;
            break;
        case Weather:
            currentState = Heart;
            break;
        case Heart:
            currentState = Clock;
            break;
    }
}

// draw / load the next scren on the oled based on current state
void loadNextScreen() {
    switch (currentState) {
        case Clock:
            runClockScreen();
            break;
        case Weather:
            runWeatherScreen();
            break;
        case Heart:
            runHeartScreen();
            break;
    }
}

////////////////////////////
// Pulse Sensor Functions //
////////////////////////////
// this function is part of the library
// it is called automaticlaly everything the sensor detects a new HR
// the parameter BPM tell us the new HR
void PulseSensorAmped_data(int BPM, int IBI) {
    // update our global var for the HR
    beatAvg = BPM;
}

void PulseSensorAmped_lost(void) {}

void myHandler(const char* event, const char* data) {
    // Part 1: helper function allows for webhook responses to be delivered in
    // multple "chunks"; you don't need to change these lines
    String fullJson = json_webhook_response_helper(event, data);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (!error) {
        // Serial.println(fullJson);
        temperature = doc["current"]["temperature_2m"];
        humidity = doc["current"]["relative_humidity_2m"];
        weatherCode = doc["current"]["weather_code"];
    }
}

void setup() {
    Particle.subscribe("hook-response/open_meteo", myHandler, MY_DEVICES);
    /*
https://community.particle.io/t/pulse-sensor-amped-incompatible-with-os-5-3-0/64313/4?u=rob7
*/
    Time.zone(-8);
    // Time.beginDST();

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
}

void loop() {
    // lets first make sure we can change to each state/screen
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == HIGH && prevButtonVal == LOW) {
        getNextState();  // decides what the state is
    }
    prevButtonVal = curButtonVal;
    // this drawing CANNOT be in the latch
    loadNextScreen();  // draws the new screen for the new state

    // we need to actually run the HR sensor pulse checking
    PulseSensorAmped.process();

    // SOMETIMES! loop() ALSO DOES NOT HAVE WIFI
    if (runOnce == true && Particle.connected() == true) {
        Particle.publish("open_meteo", "");
        runOnce = false;
    }
}
