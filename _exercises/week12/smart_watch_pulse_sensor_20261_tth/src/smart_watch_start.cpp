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
*/
unsigned long prevMillis = 0;
const unsigned long HEART_SCREEN_UPDATE = 3000;  // experimentally determined
int beatAvg = 0;

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
// TODO:
/*
    how frequently should we update the clock screen?
        -shorter than every sec
        -every second

    what are our constraints?
        -screen refresh rate
        -power / battery

    we don't to update EVERY milliseccond
        why not?
            -redrawing takes a lot power
            -uncecessary repeated work
            -screen flicker (screen is very slow)

    problem: millis timer of 1 second is too long
        why?
            millis timers are not exact
            idea: sample data at twice the frequency it changes

*/
const unsigned long TIME_SCREEN_UPDATE = 500;

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
const unsigned long WEATHER_SCREEN_UPDATE = 3600000;  // once per hour
int temperature;
float humidity;
int weatherCode;
bool runOnce = true; //this is our "gate" to make sure code runs ONCE only

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
enum State { Heart, Weather, Clock };
State currentState = Heart;

///////////////////////////////////////////////////////////////
//               END LIBRARIES AND DECLARATIONS              //
///////////////////////////////////////////////////////////////

/*
we need a millis timer for how often to refresh the heart screen
what design tradeoffs should we consider in setting the redraw time?
    -how quickly can the sensor read? don't any faster than that
    -how often does the user need the update?
    -power!!!!!
    -the oled redrawing is VERY VERY SLOW relative to the HR sensor
        so we need to make sure the HR sensor reads OFTEN and that the
        OLED redrawing does not affect

    solution
        make sure that the HR reading happens often, and the OLED drawing
happens more slowly
*/

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
        if HR is invalid, show heart icon and "---" on OLEd

        invalid is very high or very old
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
            Serial.println(String(beatAvg));
        }

        // skip battery voltage
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
        oled.clear(PAGE);
        oled.drawBitmap(bitmap_clock_16x12);

        String dateFormat = "%b %e";
        String dayFormat = "%a";
        String secondFormat = "%S";
        String timeFormat = "%I:%M";

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

    unsigned long curMillis = millis();
    if (curMillis - prMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        // publish once per hour a request for the weather
        Particle.publish("open_meteo_json", "");
    }
    oled.clear(PAGE);
    if (weatherCode == 61) {
        oled.drawBitmap(bitmap_rainy_16x12)
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

// tells which is the next state
void getNextState() {
    switch (currentState) {
        case Heart:
            currentState = Weather;
            break;
        case Weather:
            currentState = Clock;
            break;
        case Clock:
            currentState = Heart;
            break;
    }
}

// (re)draw the data on the oled
void loadNextScreen() {
    switch (currentState) {
        case Heart:
            runHeartScreen();  // this func will handle millis timing
            break;
        case Weather:
            runWeatherScreen();
            break;
        case Clock:
            runClockScreen();
            break;
    }
}

////////////////////////////
// Pulse Sensor Functions //
////////////////////////////

// this is the event handler for when a HR value is ready
void PulseSensorAmped_data(int BPM, int IBI) {
    // BPM is the heart value
    beatAvg = BPM;
}

void PulseSensorAmped_lost(void) {}

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
        humidity = doc["current"]["relative_humidity_2m"];
        weatherCode = doc["current"]["weather_code"];
        
    }
}

/*
setup runs only once
    --> it doesn't have internet access

if you need something to happne ONLY once AND you need internet access, 
    --> we must loop() with a boolean check/flag
*/

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

    Time.beginDST();
    Time.zone(-7)

    // subscribe to the event response
    Particle.subscribe("hook-response/open_meteo_json", myHandler,
                           MY_DEVICES);
}

void loop() {
    //one more issue: loop doesn't have internet right away
    if(runOnce == true && Particle.connected() == true) {
        Particle.publish("open_meteo_json", "");
        runOnce = false;
    }
    /*
        state machine
            -check input and current state
            -use logic to decide next state
            -update state and output
    */

    // pressing button loads the next screen
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        getNextState();  // we will write this
    }

    loadNextScreen();  // we write this--this draws the info on the oled

    prevButtonVal = curButtonVal;

    // for HR sensor to work, we need to run the .process() function OFTEN
    PulseSensorAmped.process();
    // asynchronous request for HR reading
    //      when reading is ready, then event handler will be called
}

/*
when should loadNextScreen be called
1) button press (inside the if)
2) every loop (outside )

3) every loop WITH millis timing
*/