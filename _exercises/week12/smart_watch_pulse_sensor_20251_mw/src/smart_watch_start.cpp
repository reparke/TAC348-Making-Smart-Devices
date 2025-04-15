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

//////////////////////////
// Heart Screen Vars    //
//////////////////////////
/* refreshing the OLED is very slow and it causes
    the heart rate detection to fail
    This delay was determined experimentally to work well
*/
//need a global var to store HR
int beatAverage = 0;
unsigned long HEART_SCREEN_UPDATE = 3000;
unsigned long prevMillis = 0;

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
// TODO:
const unsigned long CLOCK_SCREEN_UPDATE = 500;

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* Weatherstack only has 250 API calls in free plan so use
   very long delay (8 times per day)
*/
// TODO:
const unsigned long WEATHER_SCREEN_UPDATE = 10512000; //roughly 8 hours


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
State currentState = Heart;

bool runOnce = true;    //flag var to make sure weather publish works first time

///////////////////////////////////////////////////////////////
//               END LIBRARIES AND DECLARATIONS              //
///////////////////////////////////////////////////////////////

/*
    at a certain interval HEART_SCREEN_UPDATE
    if the beat is in valid range, show
        heart graphic
        current heart beat rate
    if beat is invalid, show
        heart graphic
        "---"
*/
void runHeartScreen() {
unsigned long curMillis = millis();
if (curMillis-prevMillis > HEART_SCREEN_UPDATE) {
    prevMillis = curMillis;
    oled.clear(PAGE);
    oled.drawBitmap(bitmap_heart_16x12);
    oled.setFontType(1);
    oled.setCursor(20,0);
    if (beatAverage > 230 || beatAverage < 40) {
        oled.print("---");
        Serial.println("---");
    }
    else {
        //valid HR
        Serial.println(beatAverage);
        oled.print(String(beatAverage));
    }
    oled.display();
}
    //     // for debugging
//     Serial.println("Heart");
//     oled.clear(PAGE);  // Clear the display
//     oled.setCursor(0, 0);
//     oled.print("Heart");
//     oled.display();
}

// TODO
void runClockScreen() {
    // // for debugging
    // Serial.println("Clock");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Clock");
    // oled.display();

    // what should CLOCK_SCREEN_UPDATE be?
    // goal: screen should redraws as infrequently as posssible
    //       while still maintaining the user performance / expectation
    //  --> update 1/2 s
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > CLOCK_SCREEN_UPDATE) {
        prevMillis = curMillis;

        String dateFormat = "%b %e";
        String dayFormat = "%a";
        String timeFormat = "%I:%M";
        String secondFormat = "%S";

        oled.clear(PAGE);
        //we must always draw image first
        oled.drawBitmap(bitmap_clock_16x12);
        oled.setFontType(0);
        //date
        oled.setCursor(25,0);
        oled.print(Time.format(dateFormat));
        //day
        oled.setCursor(25, 10);
        oled.print(Time.format(dayFormat));
        //second
        oled.setCursor(50,30);
        oled.print(Time.format(secondFormat));
        //time
        oled.setFontType(1);
        oled.setCursor(0, 25);
        oled.print(Time.format(timeFormat));

        oled.display();

        //time zone only needs to be done once so lets do it in setup()


    }

}

/*
    problem: we won't request the weather for 8 hours
    solution: let's request the weather when the device first states, and then 
                let the millis timer take over

    there is a little trick here
    in theory! we could put code in setup if we want it to run once on startup
        BUT there's another problem...in setup, we don't have wifi yet!

        so! if we want to run ONCE at startup AND that code needs internet, we need to actually put the code in loop and do some checks 
*/
// TODO
void runWeatherScreen() {
//     // for debugging
//     Serial.println("Weather");
//     oled.clear(PAGE);  // Clear the display
//     oled.setCursor(0, 0);
//     oled.print("Weather");
//     oled.display();
/*
    how often should we request the weather data?
        with free plan, we get 100 request / month
        --> in order to stay under our max, we should request
        no more than 3 times per day
*/
    unsignged long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        Particle.publish("WeatherStackJSON", "");
    }
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
// this is an EVENT HANDLER which is called automatically by the HR library
//everytime it detects a beat
void PulseSensorAmped_data(int BPM, int IBI) {
    beatAverage = BPM;
    //stores most recent detected BPM from the event handler into 
    //   our global var
}

void PulseSensorAmped_lost(void) {}



void myHandler(const char *event, const char *data) {
    // Handle the integration response
}

void setup() {
    Particle.subscribe("hook-response/WeatherStackJSON", myHandler, MY_DEVICES);
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

    // Time.beginDST(); // not yet
    Time.zone(-8);
}

/*
    Screen display logic
    each time through the loop, call function to show oled screen based on state
        loadNextState
    In loadNextState, we will look at the currentState to show the appropriate
   screen BUT within each of the display functions, we are going to have a timer
        this will prevent the DRAWING from happening to frequently
        by DRAWING, we mean calling oled.display()
*/

//there is a chance that when loop() runs the first time, we STILL won't have wifi
void loop() {
    if(runOnce == true && Particle.connected() == true) {
        runOnce = false; //don't run a scond time
        Particle.publish("WeatherStackJSON", "");
    }

    int curButtonVal = digitalRead(PIN_BUTTON);
    // latch
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        // change the state
        getNextState();  // update to next state
    }
    loadNextScreen();
    prevButtonVal = curButtonVal;

    //check HR sensor reading
    PulseSensorAmped.process();     //measure HR

    /*
        measure HR all the time
        - battery drain
        + HR is instantly availaable
        + tracking HR over time
        --> when not on the heart screen, we could sample HR at longer intervals
    */
}
