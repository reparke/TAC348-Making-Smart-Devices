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

how often should we refresh the HR screen?
    what considerations should  factor in this decision?
    -limits of the sensor 
    -buffering
    -battery!!!! (as rarely as possible for a good user exp)

    drawing on the OLED is SLOOOOOOOOOOOOOW
    BUT we need to be checking for a pulse very quickly!


*/
unsigned long prevMillis = 0;
int beatAvg = 0;
const unsigned long HEART_SCREEN_UPDATE = 3000;

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
const unsigned long CLOCK_SCREEN_UPDATE = 500;

//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* Weatherstack only has 250 API calls in free plan so use
   very long delay (8 times per day)
*/
const unsigned long WEATHER_SCREEN_UPDATE = 600000; // 10 minutes
int humidity;
int weatherCode;
float temperature;
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
State currentState = Weather;
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

        Serial.println("temperature: " + String(temperature));
        Serial.println("Code:" + String(weatherCode));
        Serial.println("Humidty: " + String(humidity));
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
    if HR is valid, show heart icon and heart rate on OLED
    if HR is invalid, show heart icon and "---"

    invalid is very high or very low

    consider our millis timer and implement this screen
    */


/*
    to get weather data from API:
    - build webhook - DONE
    - publish a request to webhook
    - subscribe to the response
    - parse the JSON (unpack the keys and values)

    we need to PUBLISH a request to the weather API
    -> where /when in our code should we do that?

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
        oled.print("V: " + String(batteryVoltage, 1));

        oled.display();
    }
}

// TODO
void runClockScreen() {
    // for debugging
    // Serial.println("Clock");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Clock");
    // oled.display();

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > CLOCK_SCREEN_UPDATE) {
        prevMillis = curMillis;

        String dateFormat = "%b %d"; //Nov 14
        String dayFormat = "%a"; //Mon
        String secondFormat = "%S";
        String timeFormat = "%I:%M";

        oled.clear(PAGE);
        oled.drawBitmap(bitmap_clock_16x12);

        //date
        oled.setFontType(0);
        oled.setCursor(25,0);
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
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        Particle.publish("open_meteo_json", "");
    //this code works, but we ALSO want to publish a request when the device starts

    /*
        used to be setup()---but now the photon doesn't have internet access in setup()
        well let's use a flag in loop() to publish ONLY ONCE on startup
    */
    }

    oled.clear(PAGE);

    if (weatherCode == 21) {
        //rain
        oled.drawBitmap(bitmap_rainy_16x12);
    }
    else {
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

// tells what the next state based on current state
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

void PulseSensorAmped_data(int BPM, int IBI) {
    //this event handler is called when a beat detected
    beatAvg = BPM;

    //takes calculate BPM from the library algorithm and stores
    //in our global beatAvg so we can access later when we need it
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

    Particle.subscribe("hook-response/open_meteo_json", myHandler, MY_DEVICES);
}

void loop() {

    if (runOnce == true && Particle.connected() == true) {
        Particle.publish("open_meteo_json", "");
        runOnce = false;
    }

    int curButtonVal = digitalRead(PIN_BUTTON);
    //change state (screen) only when button pressed
    if (curButtonVal == LOW && prevButtonVal == HIGH) {
        getNextState();
    }

    //refresh the screen all the time so that we capture changes in time
    //and heart rate
    loadNextScreen();

    prevButtonVal = curButtonVal;

    //check for beat 
    PulseSensorAmped.process();
    //this func will trigger the event handler PulseSensorAmped_data 
    //when a beat is detected
}
