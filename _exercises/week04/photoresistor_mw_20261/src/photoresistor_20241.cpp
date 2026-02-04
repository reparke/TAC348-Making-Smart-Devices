

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    Photoresistor
        -varies its resistance based on light levels

    where do we use this?
        night lights
        screen dimming (phones, laptops)

    analog device --> analog read
        --> ADC analog to digital conversion
        12 bit ADC
        range of values: 0-4095

    lets say we read the PR and get a value of 3031
    --> what does that value mean?
            could be dim / dark?

    ------> it means NOTHING
    PR measures RELATIVE LIGHT LEVEL

    Goal: use the PR to print out if you dark, ambient, or bright light around
   you also choose an RGB to show to indidcate hint: YOU decide what is light /
   ambient/ dark
*/
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

const int THRESHOLD_AMBIENT = 2700;
const int THRESHOLD_DARK = 400;

//we need to define FUNC ABOVE setup()
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
    //test: covering the sensor, normal levels, cell phone flashlight
    // this again is RELATIVE
    /* Rob's Office
        cover PR - 50
        just sitting here - 800
        flashlight  - 3300
    */

    if (lightLevel >= 0 && lightLevel < THRESHOLD_DARK) {
        Serial.println("Dark");
        changeRgbLed(0,0,0); // off
        //publish syntax:   publish(NAME, VALUE)
        Particle.publish("LightLevel", String(lightLevel));
        Particle.publish("Room State", "Dark");
    }
    else if (lightLevel >= THRESHOLD_DARK && lightLevel < THRESHOLD_AMBIENT) {
        Serial.println("Ambient");
        changeRgbLed(0,0,255); //blue
        Particle.publish("LightLevel", String(lightLevel));
        Particle.publish("Room State", "Ambient");
    }
    else {
        Serial.println("Bright");
        changeRgbLed(255, 255, 255); //white
        Particle.publish("LightLevel", String(lightLevel));
        Particle.publish("Room State", "Bright");
    }

    // the last time use delay like this
    delay(1000);

    
}