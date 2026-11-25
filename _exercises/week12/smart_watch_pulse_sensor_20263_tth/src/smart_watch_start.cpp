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

we are deciding how often to refresh the HR screen
    --> what consideration / constraints should we think about?
    - accuracy
        - how fast does the HR sensor need to read to get a valid measurement?
        - limitations of the HR sensor
        - limitations in OLED
    - battery
        - more frequent updates means greater battery use
we will update teh HR screen every 3 sec (determined experimentally)
*/
unsigned long prevMillis = 0;
const unsigned long HEART_SCREEN_UPDATE = 3000;
int beatAvg = 0;  // global var for heart rate

//////////////////////////
// Clock  Screen  Var   //
//////////////////////////
/*
how frequently should we update the clock screen?
    - every second (for now) -- too slow
    why? 
        latency
        delay in millis 
    
    let redraw the screen at twice the change frequency --> twice per sec (500ms)


why not update 10 times per second?
    - excessive bcz time changes once per sec
    - nothing changes on the screen
    - redundant
    ---> wastes battery power
    ---> can the oled every update that fast (latency)
*/
const unsigned long TIME_SCREEN_UPDATE = 500;


//////////////////////////
// Weather Screen  Var  //
//////////////////////////
/* 
    open meteo
    what design considerations should we consider when deciding 
        how oftento update screen?
        -once a minute
        -every 10 min
        - how often do we need to know the weather
        - how acessible the info needs to be
        - how often does open meteo update its weather
        - how variable is our weather
        - how we use the data and what data we want
 */
const unsigned long WEATHER_SCREEN_UPDATE = 1800000; //30 min
int humidity = 0;
float temperature = 0;
int weatherCode = 0;
// we can a boolean flag (var)
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
enum State { Clock, Heart, Weather };
State currentState = Weather;

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
        if the HR is valid, show heart icon and beatAvg on OLED (print serial)
        if the HR is invalid, show heart icon and "---"

        invalid is up to us: > 230 or < 40

        use millis timer
    */

    unsigned long curMillis = millis();
    if (curMillis - prevMillis > HEART_SCREEN_UPDATE) {
        prevMillis = curMillis;

        oled.clear(PAGE);
        oled.drawBitmap(bitmap_heart_16x12);
        oled.setCursor(20, 0);
        oled.setFontType(1);
        if (beatAvg > 230 || beatAvg < 40) {
            //invalid
            oled.print("---");
            Serial.println("---");    
        }
        else {
            //valid
            oled.print(beatAvg);
            Serial.println(beatAvg);
        }
        //skip battery
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

        //month date
        oled.setFontType(0);
        oled.setCursor(25, 0);
        oled.print(Time.format("%b %e"));

        //day
        oled.setCursor(25, 10);
        oled.print(Time.format("%a"));

        //second
        oled.setCursor(50,30);
        oled.print(Time.format("%S"));

        //time
        oled.setFontType(1);
        oled.setCursor(0,25);
        // oled.print(Time.format("%R"));      //24 hr time -- 14:54
        oled.print(Time.format("%I:%M"));
        
        oled.display();
    }
}

/*
remind me: what are the steps we need to in order to connect a web api, get response, and get the data into the photon

- publish the request 
- get the API URL from open meteo
- build the webhook on particle console
- subscribe to response
- build the event handler (handle the web response)
    - unpack or PARSE The json


WHERE should we put the particle.publish?
    millis timer in weather screen

problem: we will have to wait 30 min! to see any weather
    what is the solution to this?
    --> put the request in setup() because this is called ONCE when the device turns on
    ---> THIS DOES NOT WORK!

new problem
    in setup() we DO NOT HAVE WIFI
    sometimes in loop when the device just turns on, we ALSO DONT have wifi



*/
void runWeatherScreen() {
    // // for debugging
    // Serial.println("Weather");
    // oled.clear(PAGE);  // Clear the display
    // oled.setCursor(0, 0);
    // oled.print("Weather");
    // oled.display();

    //come back to timer later
    unsigned long curMillis = millis();
    if (curMillis - prevMillis > WEATHER_SCREEN_UPDATE) {
        prevMillis = curMillis;
        //publish the request
        Particle.publish("open_meteo", "");
    }

    //build the screen now imagining we'll have to weather data later
    oled.clear(PAGE);
    if(weatherCode == 61)  {
        //rainy
        oled.drawBitmap(bitmap_rainy_16x12);
    }
    else {
        oled.drawBitmap(bitmap_sunny_16x12);
    }
    oled.setFontType(1);
    oled.setCursor(38,5);
    oled.print(String(temperature,0));
    oled.display();

}
void myHandler(const char* event, const char* data) {
    // Handle the integration response
    // assemble/parse
    // Part 1: helper function allows for webhook responses to be delivered in
    // multple "chunks"; you don't need to change these lines
    String fullJson = json_webhook_response_helper(event, data);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, fullJson);

    // Part 2 is where you can parse the actual data; you code goes in the IF
    if (!error) {
        /*          ============
        Here is where your parsing code goes
                    ============
        */
        temperature = doc["current"]["temperature_2m"];
        humidity = doc["current"]["relative_humidity_2m"];
        weatherCode = doc["current"]["weather_code"];

        Serial.println("In LA, the temperature now is " +
                       String(temperature, 0) + " and the humidity is " +
                       String(humidity) + "%");
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

// everytime the sensor detects a heart bear 
// this function is called automatically
//  and the BPM param is the most recent pulse averge
void PulseSensorAmped_data(int BPM, int IBI) { beatAvg = BPM; }

void PulseSensorAmped_lost(void) {}

void setup() {
    // Subscribe to the integration response event
    Particle.subscribe("hook-response/open_meteo", myHandler, MY_DEVICES);

    //we dont need daylight

    Time.zone(-8);
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
}

void loop() {

    //publish a message ONCE when the photon has wifi
    if (runOnce == true && Particle.connected() == true) {
        runOnce = false;    
        Particle.publish("open_meteo", "");
    }


    //function will trigger the event handler everytime a beat
    //is detected
    PulseSensorAmped.process();


    // lets make sure that we can switch from state to state
    int curButtonVal = digitalRead(PIN_BUTTON);
    if (curButtonVal == HIGH && prevButtonVal == LOW) {
        getNextState();

        /* in the past (e.g. tea brewer, washing machine)
        --> we would change the state var AND update the outputs at the same

        should we change the var and update the screen BOTH HERE in latch?
        --NO -- we cannot update the screen here--why not?

        how do we here in this if block (latch)?
            when the button is pressed
        how often is the button pressed?
            we don't know

        BUT how often do we want to update the clock screen?
            question: dp we want to redraw the clock screen
                a)  only when the button pressed and we land on clock state
                b)  at a regular interval when we are in the clock state

               B!
            --> we need to put the screen update OUTSIDE the latch to change
        state
        */
    }
    prevButtonVal = curButtonVal;

    loadNextScreen();  // this happens every loop (and we'll add millis timers)
}
