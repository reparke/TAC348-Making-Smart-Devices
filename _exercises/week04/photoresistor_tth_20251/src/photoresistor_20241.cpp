#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
Photoresistor
  changes resistance when exposed to light
  is digital or analog? ANALOG device
  uses: changing screen brightness

  analog device --> ADC
  input: analog voltage --> analogRead --> range: 0-4095

  what does a value of 3000 mean?
    NOTHING!

  measures RELATIVE light level

  Goal: use the PR to tell us if it is dark, bright, or ambient (light)
    hint: I'm not telling you what is dark, bright or ambient
    use serial monitor to display dark, ambient or light
    AND change LED color based on dark, ambient, or light
      ex: dark is red, ambient is blue, bright is white

*/
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

const int THRESHOLD_DARK = 1500;
const int THRESHOLD_AMBIENT = 3000;

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
    int lightValue = analogRead(PIN_PHOTORESISTOR);

    String roomLight = ""; 

    int pwmVal = map(lightValue, 0, 4095, 0, 255); //standard
  
    // int pwmVal = map(lightValue, THRESHOLD_DARK, THRESHOLD_AMBIENT, 100, 255); //standard
    changeRgbLed(255, pwmVal, pwmVal);

    if (lightValue >= 0 && lightValue < THRESHOLD_DARK) {  // dark
        // changeRgbLed(0, 0, 0);  //off
        Serial.println("Light value = " + String(lightValue) + " DARK");
        roomLight = "dark";

    } else if (lightValue >= THRESHOLD_DARK &&
               lightValue < THRESHOLD_AMBIENT) {  // ambient yellow
        // changeRgbLed(255, 255, 0);
        Serial.println("Light value = " + String(lightValue) + " AMBIENT");
        roomLight = "ambient";
    } else {  // bright whtie
        // changeRgbLed(255, 255, 255);
        Serial.println("Light value = " + String(lightValue) + " BRIGHT");
        roomLight = "bright";
    }
    // Particle.publish("Room Light", roomLight);
    // Particle.publish("Light Value", String(lightValue));
    // //don't want to publish too often, add delay

    // delay(5000);
}

/*
  what if we want to use the PR to control the brightnesss of the LED
    as room brightness increases, let's change the LED brightness
    convert 0-4095 ADC to 0-255 PWM

  1) Use math
  2) use MAP function

  outVal = map(inVal, inRangeMin, inRangeMax, outRangeMin, outRangeMax)

*/
