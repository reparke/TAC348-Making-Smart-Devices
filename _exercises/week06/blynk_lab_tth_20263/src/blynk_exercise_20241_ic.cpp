#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#define BLYNK_TEMPLATE_ID "TMPL2WgQ7SsqM"
#define BLYNK_TEMPLATE_NAME "Week 6 MW Lab 20263"
#define BLYNK_AUTH_TOKEN "QgEs9cb06nxPd1nreI-Bsc_ZTvC8s-Jl"

#include <blynk.h>

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_SWITCH = D2;

void changeLedColor(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

/*
1) Use three sliders to control RGB LED on pins V0 V1 V2 (app –> Photon 2)

2) Use a button on V4 to trigger the RGB LED to display a color randomly chosen
   from white, yellow, magenta, or red (app –> Photon 2)

   3) When one of the four
  random colors is displayed on the RGB LED, send a string representing that
color to the app on pin V7 (Photon 2 –> app)

---

how we approach the sliders?
    APP ---> PHOTON
    - EVENT DRIVEN
    - BLYNK_WRITE --> one func for each widget
*/
// red sliders
BLYNK_WRITE(V0) {
    int red = param.asInt();
    analogWrite(PIN_RED, red);
}

// green sliders
BLYNK_WRITE(V1) {
    int green = param.asInt();
    analogWrite(PIN_GREEN, green);
}

// blue sliders
BLYNK_WRITE(V2) {
    int blue = param.asInt();
    analogWrite(PIN_BLUE, blue);
}

// button is same as before
BLYNK_WRITE(V4) {
    int buttonVal = param.asInt();

    // remember this fires on press and release so we should only trigger once
    if (buttonVal == 1) {  // just track presses
        // display random color: red, white, yellow, magenta

        int randChoice = random(0, 4);  // 0 1 2 3
        if (randChoice == 0) {
            // white
            changeLedColor(255, 255, 255);
            Blynk.virtualWrite(V7, "white");
        } else if (randChoice == 1) {
            // yellow
            changeLedColor(255, 255, 0);
            Blynk.virtualWrite(V7, "yellow");

        } else if (randChoice == 2) {
            // magenta
            Blynk.virtualWrite(V7, "magenta");
            changeLedColor(255, 0, 255);
        } else {
            // red
            Blynk.virtualWrite(V7, "red");
            changeLedColor(255, 0, 0);
        }
    }
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_SWITCH, INPUT);
    Serial.begin(9600);
    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop() { Blynk.run(); }
