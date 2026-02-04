

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    Photoresistor
        - varies resistance based on light

        where do use these?
        -light sensor
        -night light, solar light
        -phone screen

        but why..?
        --> adjust brightnesss based on envionment

    analog device --> analog read
        ADC - analog to digital conversion
        12 bit ADC
        range of values: 0-4095

    lets say we read the PR and get a value of 3031
    --> what does this value mean?

    -------> it means nothing!
    PR meanures RELATIVE LIGHTLEVEL


    Goal: use the PR to print out if the light around you is dark, ambient,
   bright also choose an RGB color so show hint: YOU decide what is bright /
   ambient / dark

    Rob office
        bright light was 3500
        ambient light was 800
*/

const int THRESHOLD_AMBIENT = 2700;
const int THRESHOLD_DARK = 400;

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

//create a func to change rgb color
// func order matters!
// so put our functions ABOVE setup()

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_PHOTORESISTOR, INPUT);
    Serial.begin(9600);
}

void loop() {
    int lightLevel = analogRead(PIN_PHOTORESISTOR);
    String roomLight = "";  // empty

    if (lightLevel >= 0 && lightLevel < THRESHOLD_DARK) {
        roomLight = "Dark";
        changeRgbLed(0,0,0);  //off
    } else if (lightLevel >= THRESHOLD_DARK && lightLevel < THRESHOLD_AMBIENT) {
        roomLight = "Ambient";
        changeRgbLed(0, 0, 255); //blue
    } else {
        roomLight = "Bright";
        changeRgbLed(255, 255, 255); //white
    }
    Serial.println("Room Light = " + roomLight +
                   " light level = " + String(lightLevel));

    Particle.publish("Room Light", roomLight);
    Particle.publish("Light Level", String(lightLevel));
    delay(1000); // don't publish more than 1x per sec

}