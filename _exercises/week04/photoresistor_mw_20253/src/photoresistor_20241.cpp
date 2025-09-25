
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
    Photoresistor
        changes reistance when exposed to light

        analog input device: range 0-4095

        what does a value of 3002 mean for photoresistor?
            NOTHING

        PR measures RELATIVE brightness

        dark is red
        ambient magenta
        bright will white
*/

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

const int THRESHOLD_DARK = 400;
const int THRESHOLD_AMBIENT = 1200;

// create a function to set RGB colors
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
    int lightValue = analogRead(PIN_PHOTORESISTOR);  // range 0-4095

    Serial.println("Light Value = " + String(lightValue));

    //let's map the Photoresistor values to led brightness
    // we know that ADC value 0-4095
    //      BUT in practice Rob's room was 50 (dark) to 3200 (bright)
    // let's use the ACTUAL readings
    // we could math! BUT lets use the MAP function

    /*
        outputVal = map(inputVal, inputMin, inputMax, outputMin, outputMax )
        input: actual PR readings (50 to 3200)
        output:  0-255
    */
   int ledBrightness = map(lightValue, 50, 3200, 0, 255);
    changeRgbLed(ledBrightness, ledBrightness, 255);
    
    if (lightValue >= 0 && lightValue < THRESHOLD_DARK) {
        Serial.println("Room is Dark");

        // changeRgbLed(255, 0, 0);  // red
    } else if (lightValue >= THRESHOLD_DARK && lightValue < THRESHOLD_AMBIENT) {
        Serial.println("Room is Ambient");
        // changeRgbLed(255, 0, 255);
    } else {  // bright
        Serial.println("Room is Bright");
        // show white on LED
        //  analogWrite(PIN_RED, 255);
        //  analogWrite(PIN_GREEN,255);
        //  analogWrite(PIN_BLUE, 255);

        // changeRgbLed(255, 255, 255);
    }

    delay(1000);
}