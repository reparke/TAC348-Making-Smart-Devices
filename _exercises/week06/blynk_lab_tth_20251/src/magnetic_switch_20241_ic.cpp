#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

// configuring blynk
// step 1: add the Blynk parameters from the website
// #define BLYNK_TEMPLATE_ID "TMPL2ey3gT1o5"
// #define BLYNK_TEMPLATE_NAME "Week6 Ex"
// #define BLYNK_AUTH_TOKEN "foOrUMLZqexXBn8yk8Hy284D6t1bX9UF"
#define BLYNK_TEMPLATE_ID "TMPL2H3PjSHrt"
#define BLYNK_TEMPLATE_NAME "Week 7 MW Lab"
#define BLYNK_AUTH_TOKEN "JgBegPCcwG3q2bxlO0t6uJXjoDFvE-7T"

// step 2: install and include library
#include <blynk.h>

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;

/*
    3 colors sliders in app that will change RGB led color
        from APP to PHOTON

    button in app that causes the photon to choose one of 4 random colors
    (magenta, white, red, yellow) and diplay that color
        from APP to PHOTON

     based on the random color, send the string of the color to app
        from PHOTON to APP

    1) setup
        -creating Blynk template, building the datastreams, creating a device
        -connecting workbench code to Blynk
    2) creating interface in the app
    3) create the code to cause the RGB LEDs to change color based on the
   sliders
   4) create the code to make the button and the string work
*/

/*
    EVENT DRIVEN PROGRAMMING
        we create function that we don't call!
        the Photon will call the function FOR US AUTOMAGICALLY when the "event"
   happens

    we create a function that the PHOTON will call when a slider is moved
*/

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

// red slider -
//  from APP to PHOTON
// we create an "EVENT HANDLER"
BLYNK_WRITE(V0) {  // this func is called when data comes on virtual pin V0
    // Blynk gives us a way to access any data being sent
    //  param is the way we acces the data
    int r = param.asInt();
    analogWrite(PIN_RED, r);
}

BLYNK_WRITE(V1) {  // this func is called when data comes on virtual pin V0
    // Blynk gives us a way to access any data being sent
    //  param is the way we acces the data
    int g = param.asInt();
    analogWrite(PIN_GREEN, g);
}

BLYNK_WRITE(V2) {  // this func is called when data comes on virtual pin V0
    // Blynk gives us a way to access any data being sent
    //  param is the way we acces the data
    int b = param.asInt();
    analogWrite(PIN_BLUE, b);    
}

// button press event handler (app -> photon)
BLYNK_WRITE(V4) {  // v4 is the datastream for the button
    // this function gets called on PRESS and RELEASE
    int virtualButtonVal = param.asInt();
    if (virtualButtonVal == 1) {  // button press only
        int rand = random(0, 4);  // 0 1 2 3
        if (rand == 0) {          // white
            changeLedColor(255, 255, 255);
            // update the app
            Blynk.virtualWrite(V5, "white");
            // updates the datastream V5 with string
        } else if (rand == 1) {  // yellow
            changeLedColor(255, 255, 0);
            // update the app
            Blynk.virtualWrite(V5, "yellow");
        } else if (rand == 2) {  // white
            changeLedColor(255, 0, 255);
            // update the app
            Blynk.virtualWrite(V5, "magenta");
        } else if (rand == 3) {  // red
            changeLedColor(255, 0, 0);
            // update the app
            Blynk.virtualWrite(V5, "red");
        }
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    Serial.begin(9600);

    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() { Blynk.run(); }