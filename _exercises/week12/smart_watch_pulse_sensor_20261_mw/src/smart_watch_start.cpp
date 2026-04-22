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
#include "bitmaps_sunrise_sunset.h"
#include "bitmaps_watch.h"
#include "bitmaps_weather.h"

//////////////////////////
// Heart Screen Vars    //
//////////////////////////
/* refreshing the OLED is very slow and it causes
    the heart rate detection to fail
    This delay was determined experimentally to work well


refreshing OLED IS VERY SLOW --- so if we update the screen TOO frequently,
    the HR detection will fail

how often should we refresh the HR screen?
    or, what considerations should factor into the decision?
    - how fast does the HR change?
    - battery life
    - limitations of sensor
    */
unsigned long prevMillis = 0;
int beatAvg = 0;
const unsigned long HEART_SCREEN_UPDATE = 3000;  // determine experimentally

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
// how frequently to update
/*
    constraints
        latency in oled
        battery life
        refresh rate

    ex: 1 milli is unnecessarily fast


    1 minute -- too slow because we need to show sec
    1 second -- actually (surprisingly is too slow)

    we want to update screen at 2x the frequency the data changes
        because there are all types of delays in our system
*/
const unsigned long TIME_SCREEN_UPDATE = 500;

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/*
 */
// how often should we update weather?
/*
    2-3 hours
    every hour

*/
const unsigned long WEATHER_SCREEN_UPDATE = 3600000;  // once an hour
int humidity = 0;
float temperature = 0;
int weatherCode = 0;
bool runOnce = true; //this is our "gate" to run weather publish just once!

//////////////////////////
// Sunrise Screen  Var  //
//////////////////////////
/*
   very long delay (8 times per day)
*/
// TODO:

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

void myHandler(const char* event, const char* data) {
    // Part 1 allows for webhook responses to be delivered in multple "chunks";
    // you don't need to change this
    static String jsonBuffer;  // store json response
    int responseIndex = 0;
    const char* slashOffset = strrchr(event, '/');
    if (slashOffset) responseIndex = atoi(slashOffset + 1);
    if (responseIndex == 0) jsonBuffer = "";
    jsonBuffer += data;

    // Part 2 is where you can parse the actual data; you code goes in the IF
    DynamicJsonDocument doc(12288);
    DeserializationError error = deserializeJson(doc, jsonBuffer);

    if (!error) {  // Test to see if was successful

        temperature = doc["current"]["temperature_2m"];
        weatherCode = doc["current"]["weather_code"];
        humidity = doc["current"]["relative_humidity_2m"];
    }
}

// TODO
void runHeartScreen() {
    // for debugging
    // Serial.println("Heart");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Heart");
    // oled.display();

    /*
        if HR is valid, show heart icon and heart on OLEd
        if HR is invalid, show heart icon and "---"

        invalid is very high or very low

        consider millis timer
    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > HEART_SCREEN_UPDATE) {
        prevMillis = curMillis;

        oled.clear(PAGE);
        oled.drawBitmap(bitmap_heart_16x12);
        oled.setFontType(1);
        oled.setCursor(20, 0);
        // address out of range values
        if (beatAvg > 230 || beatAvg < 40) {
            oled.print("---");
            Serial.println("---");
        } else {
            oled.print(String(beatAvg));
            Serial.println(String(beatAvg));
        }

        // show the photon 2 voltage -- this from documentation
        oled.setCursor(0, 30);
        float batteryVoltage = analogRead(A6) / 819.2;
        oled.print("Batt: " + String(batteryVoltage));

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

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > TIME_SCREEN_UPDATE) {
        prevMillis = curMillis;

        // create formats
        String dateFormat = "%b %e";  // Nov 3
        String dayFormat = "%a";      // Mon
        String secondFormat = "%S";   // seconds
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
    // // for debugging
    // Serial.println("Weather");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Weather");
    // oled.display();

    /*
    I turn on watch and go to weather
    1) what will i see? 
    2) how long will I see that?

    but we also need to publish ONCe(onlyonce) when device starts


    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;

        // lets imagine we have have weather data
        // we need to request new weather once a hour
        // but we want to draw the weather screen more freq
    
        Particle.publish("open_meteo_json", "");
    }

    oled.clear(PAGE);
    if (weatherCode == 21) {
        oled.drawBitmap(bitmap_rainy_16x12);
    } else {
        oled.drawBitmap(bitmap_sunny_16x12);
    }
    oled.setFontType(1);
    oled.setCursor(38, 5);
    oled.print(temperature, 0);

    oled.setFontType(0);
    oled.print("o");

    oled.setCursor(0, 40);
    oled.print("Hum: ");
    oled.print(humidity);
    oled.display();
}

// sets the next state value based on the current state
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

// draw / load the screen on the OLED based on the currentState
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

void PulseSensorAmped_data(int BPM, int IBI) {
    // this is the event handler for when a beat is detected
    beatAvg = BPM;

    // takes the calculated BPM from the library's algorithm
    //  and stores it in our global variables for when we need ti
}

void PulseSensorAmped_lost(void) {}

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

    // timezone
    Time.zone(-8);
    Time.beginDST();  // April so we are in DST

    Particle.subscribe("hook-response/open_meteo_json", myHandler, MY_DEVICES);
}

void loop() {
    /*
    to run code that needs internet access ONCE, we might think that it 
    should be in setup()
    --> problem! the photon doesn't have access to wifi in setup()

    instead, we need to put this code in loop but create barriers it only runs once
    BUT the first time through Loop() we STILL may not have have wifi
    */
    if (runOnce == true && Particle.connected() == true) {
        Particle.publish("open_meteo_json", "");
        runOnce = false;
    }


    // change state (screen) only when button is pressed
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        getNextState();  // we will write this fn to change to the next state
    }
    prevButtonVal = curButtonVal;

    // we will write this fn
    // refresh/redraw the screen all the time so we captures changes in the data
    //       inside this fn, we will deal millis timer
    loadNextScreen();

    // check for beat
    PulseSensorAmped.process();
    // this func will trigger the event handler PulseSensorAmped_data
    //   everytime a beat is detected
}
