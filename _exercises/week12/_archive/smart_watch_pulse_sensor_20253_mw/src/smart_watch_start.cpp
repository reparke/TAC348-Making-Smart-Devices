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

/*
    to get weather data from open-meteo
    -build webhook in particle - done
    - publish a message to webhook
    - subscribe to the webhook response
    - event handler which handles the actual parsing of JSON

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
// TODO:
const unsigned long HEART_SCREEN_UPDATE = 3000;
unsigned long prevMillis = 0;
int beatAvg = 0;

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
const unsigned long CLOCK_SCREEN_UPDATE = 500;  // update every 1/2 s

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* Weatherstack only has 250 API calls in free plan so use
   very long delay (8 times per day)
*/
const unsigned long WEATHER_SCREEN_UPDATE = 60000;
float temperature;
int weatherCode;
int humidity;

// we need to make that the weather publish runs ONCE when the device starts
//  AND we have internet access
bool runOnce = true;

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

//json event handler for parsing
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
        Serial.println(jsonBuffer);
        temperature = doc["current"]["temperature_2m"];
        weatherCode = doc["current"]["weather_code"];
        humidity = doc["current"]["relative_humidity_2m"];
        Serial.println("The weather is " + String(temperature, 1) + " F and " +
                       String(humidity) + "% humidity with weather code " +
                       (weatherCode));
    }
}

// TODO
void runHeartScreen() {
    // // for debugging
    // Serial.println("Heart");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Heart");
    // oled.display();

    /*
        if HR is valid, show heart icon and HR on oled
        if HR is invalid, show hreat icon and "---"

        invalid:very high or very low
    */
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > HEART_SCREEN_UPDATE) {
        prevMillis = curMillis;
        oled.clear(PAGE);
        oled.drawBitmap(bitmap_heart_16x12);
        oled.setFontType(1);
        oled.setCursor(20, 0);
        // what is too high or too low HR?
        if (beatAvg > 50 && beatAvg < 150) {  // valid
            oled.print(String(beatAvg));
            Serial.println("beatAvg: " + String(beatAvg));
        } else {  // invalid
            oled.print("---");
            Serial.println("---");
        }

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

/*
    green check - do weather screen together
    red x - do in groups
*/

// TODO
void runWeatherScreen() {
    // // for debugging
    // Serial.println("Weather");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Weather");
    // oled.display();

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        Particle.publish("OpenMeteoJsonFull", "");
    }
    oled.clear(PAGE);
    // how do we get the little icon?
    switch (weatherCode) {
        case 20:  // rainy
            oled.drawBitmap(bitmap_rainy_16x12);
            break;
        default:
            oled.drawBitmap(bitmap_sunny_16x12);
            break;
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
    // which "page" do we display on the OLED
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
    // this event handler gets calls EVERY TIME that a heart beat is detected
    // one line of code...
    beatAvg = BPM;
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

    Time.zone(-8);
    // Time.beginDST();

    Particle.subscribe("hook-response/OpenMeteoJsonFull", myHandler,
                       MY_DEVICES);
}

void loop() {
    if (runOnce == true && Particle.connected() == true) {
        Particle.publish("OpenMeteoJsonFull", "");
        runOnce = false;  // guarantees only runs once
    }

    // TODO
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        getNextState();
    }
    loadNextScreen();
    // we MUST redraw the OLED every time in loop to capture the time and HR
    // changing BUT we only want to change state when the button is pressed
    prevButtonVal = curButtonVal;

    PulseSensorAmped
        .process();  // continuously check the sensor
                     // when it detects a beat, this AUTOMATCALLY calls
                     //  PulseSEnsorAmped_data
}
