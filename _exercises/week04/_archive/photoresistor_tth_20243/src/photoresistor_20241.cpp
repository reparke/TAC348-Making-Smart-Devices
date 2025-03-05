#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

/*
    Photoresistor
    --
    purpose: senses changes in light
    Analog or digital? analog
    expected range of values: 0-4095
        ADC  (analog to digital conversion  )

    what does a reading of 3000 mean? NOTHING
        we are measuring absoluate amounte of light
    we are measuring RELATIVE light changes

    in order for a PR reading ot make any sense, we need to always calibrate it

    Goal: use the PR to tell you if the light levels where you are dark, ambient, or bright
        --> Use Serial mon to display dark, ambient, bright
        --> change RGB based on light- dark (off), ambient (yellow), bright (white)

  mapping
    - divide range (0-4095) evenly
    - experimentally using serial monitor **
*/

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI; //photon says "MO"
const int PIN_PHOTO = A1;

//thresholds
const int THRESHOLD_DARK = 1500;
const int THRESHOLD_AMBIENT = 2800;

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_PHOTO, INPUT);
    Serial.begin(9600);
}

void loop() {
    int lightValue = analogRead(PIN_PHOTO);

    //to calibrate, cover sensor with your hand and note value
    // Serial.println(lightValue);

    //variation
    /*
        vary the RGB color by the photoresistor reading
        -->   PWM will change LED brightness
         two approaches:
         1) MATHS! float(PR) * 4095 / 255
         2) MAP: takes a number within an INPUT range and convert a number in an OUTPUT (linear)

         outVal = map(inVal, inputRangeMin, inputRangeMax, outputRangeMin, outputRangMax)
    */
        // int pwmVal = map(lightValue, 0, 4095, 0, 255); //default
        int pwmVal = map(lightValue, 400, 3800, 50, 255); //calibrated
        int invPwmVal = map(lightValue, 400, 3800, 255, 50); //calibrated

    changeRgbLed(255, pwmVal, pwmVal);

    if (lightValue >= 0 && lightValue < THRESHOLD_DARK) {
        Serial.println("Dark: "+ String(lightValue));
        // changeRgbLed(0,0,0);
        //cloud publish
        Particle.publish("LightValue", String(lightValue));
        Particle.publish("Room State:", "Dark");
    }
    else if (lightValue >= THRESHOLD_DARK && lightValue < THRESHOLD_AMBIENT) {
        Serial.println("Ambient: " + String(lightValue));
        // changeRgbLed(255, 255, 0);
        Particle.publish("LightValue", String(lightValue));
        Particle.publish("Room State:", "Ambient");

    }
    else { //bright
        Serial.println("Bright: " + String(lightValue));
        // changeRgbLed(255, 255, 255);
        Particle.publish("LightValue", String(lightValue));
        Particle.publish("Room State:", "Bright");
    }
    // delay(100);
    delay(1000);        //shouldn't publish more than once per sec
}