#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

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
#define BLYNK_TEMPLATE_ID "TMPL25OQvcrVt"
#define BLYNK_TEMPLATE_NAME "Week 6 Lab"
#define BLYNK_AUTH_TOKEN "9rRPPjNcBfUCPEBhP0GBOc5w4odixZri"

#include <blynk.h>
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // aka MOSI pin

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

// button -- app to photon

//string -- photon to app -- Blynk.virtualWrite
/*
    we want to be careful not to call Blynk.virtualWrite too often
    We call virtualWrite in one of two ways
    1) call in an event handler (BLYNK_WRITE)
    2) call in loop and use millis timer
*/
BLYNK_WRITE(V4) {
    /*
        what should happen when the button is pressed?
            -choose a color randomly
            -show LED color
            -display color name
    */

    int buttonVal = param.asInt();
    // by default, 1 means pressed
    if (buttonVal == 1) {
        int rand = random(0, 4);
        if (rand == 0) {  // white
            changeLedColor(255, 255, 255);
            Blynk.virtualWrite(V7, "white");
        } else if (rand == 1) {  // yellow
            changeLedColor(255, 255, 0);
            Blynk.virtualWrite(V7, "yellow");
        } else if (rand == 2) {  // magenta
            changeLedColor(255, 0, 255);
            Blynk.virtualWrite(V7, "magenta");
        } else if (rand == 3) {
            changeLedColor(255, 0, 0);
            Blynk.virtualWrite(V7, "red");
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