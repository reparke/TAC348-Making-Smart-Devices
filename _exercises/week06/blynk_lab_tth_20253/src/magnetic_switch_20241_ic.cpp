#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

#define BLYNK_TEMPLATE_ID "TMPL2jg6F36rD"
#define BLYNK_TEMPLATE_NAME "Week 6 MW Lab"
#define BLYNK_AUTH_TOKEN "L3oWu4-K8RGwrMU5CGFcQHbrrqovNKZX"

#include <blynk.h>

/*
    3 color sliders in app that will change LED color
        FROM app to photon

    button in app that causes the photon to generate random num (0-3)
        and choose a color based on that number and display
        FROM app to photon

    based on the random color that was chosen, a string will appear in app
        FROM PHOTON to APP

1) setup
    - create blynk template, build datastream, create device
    - connect code in workbench
2) create the interface app on phone
3) create the code to cause the RGB to change based on sliders
4) create the code to make the button and string work


add blynk to workbench
    -install library
    -add our access tokens
    -#include library
    -setup: Blynk.begin
    -loop: Blynk.run

*/
BLYNK_WRITE(V0) {
    int r = param.asInt();
    analogWrite(PIN_RED, r);
}

BLYNK_WRITE(V1) {
    int g = param.asInt();
    analogWrite(PIN_GREEN, g);
}

BLYNK_WRITE(V2) {
    int b = param.asInt();
    analogWrite(PIN_BLUE, b);
}

/*
    get virtual button from app
    what should happen when button is pressed?
        -choose random color
        -change led color
        -send the string back to APP
*/
BLYNK_WRITE(V3) {
    // REMEMBER this event happens TWICE --button press and button release
    Serial.println("Button press");
    if (param.asInt() == 1) {     // just track PRESSES
        int rand = random(0, 4);  // 0 1 2 3
        if (rand == 0) {          // white
            changeLedColor(255, 255, 255);
            Blynk.virtualWrite(V7, "white");
        } else if (rand == 1) {
            changeLedColor(255, 255, 0);
            Blynk.virtualWrite(V7, "yellow");
        } else if (rand == 2) {
            changeLedColor(255, 0, 255);
            Blynk.virtualWrite(V7, "magenta");
        } else if (rand == 3) {
            changeLedColor(255, 0, 0);
            Blynk.virtualWrite(V7, "red");
        }
    }
}

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    Serial.begin(9600);

    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() { Blynk.run(); }
