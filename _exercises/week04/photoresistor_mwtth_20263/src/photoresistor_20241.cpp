#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    Photoresistor
        varies resistance based on light

    where do we see these used?
        -light sensor
        -phone or laptop

    why?
        want a screen to adjust brightness based on enviro


    analog device --> analog read
        ADC - analog to digital conversation
        12 bit ADC
        range  0 to 4095

    lets say we read PR and get a value of 3031
    --> what does this mean?

    -----------> MEANS NOTHING!
    PR measures RELATIVE LIGHT LEVEL


    Goal: use the PR to print out if the light around is dark, ambient, or bright

    also, use an RGB color show that status (functions)

    hint: we each individually decide what is bright, ambient and dark


    dark - off
    ambient - blue
    bright - white
*/

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;
const int PIN_PHOTORESISTOR = A1;

const int THRES_AMBIENT = 2700;
const int THRES_DARK = 700;

//millis timing - publish the value
unsigned long prevMillis = 0;
const unsigned long INTERVAL_PUBLISH = 5000;

/*
    create a func to change the RGB color that we can reuse anywhere
    note about C++
        - function order MATTERS!
        - define a function before call it
        - so...we define our functions BEFORE setup / loop
*/

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void randomRgbLed() {
    analogWrite(PIN_RED, random(0,256)); //random number from 0-255
    analogWrite(PIN_GREEN, random(0,256));
    analogWrite(PIN_BLUE, random(0,256));
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_PHOTORESISTOR, INPUT);
    Serial.begin(9600);
}
void loop() {
    //simple read
    int lightLevel = analogRead(PIN_PHOTORESISTOR);
    String roomLight = "";

    if (lightLevel >= 0 && lightLevel < THRES_DARK) {
        roomLight = "dark";
        changeRgbLed(0, 0, 0);

    }
    else if (lightLevel >= THRES_DARK && lightLevel < THRES_AMBIENT) {
        roomLight = "ambient";
        // changeRgbLed(0, 0, 255);
        randomRgbLed();
    }
    else {
        roomLight = "bright";
        changeRgbLed(255, 255, 255);
    }

    unsigned long currMillis = millis();
    if (currMillis - prevMillis > INTERVAL_PUBLISH) {
        prevMillis = currMillis;

        Serial.println("lightLevel = " + String(lightLevel));
        Particle.publish("lightLevel", String(lightLevel));
        Particle.publish("roomLight", roomLight);
    }
    
}