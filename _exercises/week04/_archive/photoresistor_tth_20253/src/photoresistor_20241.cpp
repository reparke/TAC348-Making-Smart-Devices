
#include "Particle.h"
SYSTEM_MODE(SEMI_AUTOMATIC);
// SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
Photoresistor
    changes resistance to light --> and we will use voltage div to measure
change in voltage

    change screen brightness

    analog device / voltage --> ADC
    input: voltage -> analogRead -> range 0-4095

    what does a reading of 3031 mean?
        digital value from ADC of the input voltage

        --> means NOTHING!

    PR measures RELATIVE light level

    Goal: use the PR to tell us if we have dark, ambient, or bright light
        hint: you will decide what is dark, ambient or bright
        display the PR value and dark/ambient/bright in serial mon
        AND
        change LED color based on dark/ambient/bright


*/
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

const int THRESDHOLD_AMBIENT = 3000;
const int THRESHOLD_DARK = 500;

//create function ABOVE setup
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

/*

    just sitting with photon--800
    cover PR -- 50
    use flashlight -- 3300

    dark - red, ambient- magenta, bright-white, 
*/

void loop() {
    // int lightLevel = analogRead(PIN_PHOTORESISTOR);
    // // converted "digital ADC value" from analog voltage    (0-4095)

    // Serial.println("Light level = " + String(lightLevel));

    // if (lightLevel >= 0 && lightLevel < THRESHOLD_DARK) {
    //     Serial.println("Room is dark");
    //     // analogWrite RED
    //     // analogWrite GREEN PIN
    //     // analogWRite BLUE
    //     changeRgbLed(255, 0, 0); //red
    // } else if (lightLevel <= THRESHOLD_DARK && lightLevel < THRESDHOLD_AMBIENT) {
    //     Serial.println("Room is ambient");
    //     changeRgbLed(255, 0, 255); // magenta - red and blue
    // } else {
    //     Serial.println("Room is bright");
    //     changeRgbLed(255, 255, 255); //white
    // }

    // delay(500);

    int lightLevel = analogRead(PIN_PHOTORESISTOR);
    // converted "digital ADC value" from analog voltage    (0-4095)
    //new goal: have PR control LED brightness
    /*
        two ways
        1) math
        2) map function
            converts input range of numbers to output of numbers, assuming a linear relationship

    outVal = map(inVal, inRangeMin, inRangeMax, outRangeMin, outRangeMax)

    */

    // int brightness = map(lightLevel, 0, 4 095, 0, 255); // this is valid
    // in my office, I got about 50 to 3200
    int brightness = map(lightLevel, 50, 3200, 0, 255);  // this is valid

    changeRgbLed(brightness, brightness, brightness);


    Serial.println("Light level = " + String(lightLevel));

    if (lightLevel >= 0 && lightLevel < THRESHOLD_DARK) {
        Serial.println("Room is dark");
  
    } else if (lightLevel <= THRESHOLD_DARK &&
               lightLevel < THRESDHOLD_AMBIENT) {
        Serial.println("Room is ambient");
    } else {
        Serial.println("Room is bright");
    }

}