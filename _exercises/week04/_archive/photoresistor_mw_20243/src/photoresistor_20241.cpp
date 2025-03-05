#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

/*
  Photoresistor
  -
  purpose: resistor that changes when exposure to light
  is it analog or digital? ANALOG
  what process do use to read the PR (analog)?
      analogRead-->range 0-4095
      ADC - analog to digital conversion

  what does 3000 mean when we read the PR?
    NOTHING
    PR measures relative difference in light levels

  for the values from a PR to have ANY meaning, we need to calibrate it

  Goal: use the PR to tell you if it is dark, bright, or ambient (light)
    -> use serial monitor to print out dark, bright, or ambient
    -> AND change the RGB color based on the lighting condition (dark off,
  bright white, ambient yellow)
*/
const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"
const int PIN_PHOTORESISTOR = A1;

// thresholds - unique to each setup
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

    //variation: adjust the brightness of the RGB based on PR values
    /*
      outputVal = map(inputVal, outputRangeMin, outputRangeMax, inputRangeMin, inputRangeMax)
    */
    int pwmValue = map(lightValue, 0, 4095, 0, 255);
    changeRgbLed(255, pwmValue, pwmValue);

    if (lightValue >= 0 && lightValue < THRESHOLD_DARK) {  // dark
        // changeRgbLed(0, 0, 0);
        Serial.println("Light value = " + String(lightValue) + " DARK");

        Particle.publish("Room Status", "dark");
        Particle.publish("Light value", String(lightValue));
    }
    else if (lightValue >= THRESHOLD_DARK && lightValue < THRESHOLD_AMBIENT) {  // ambient yellow
        // changeRgbLed(255, 255, 0);
        Serial.println("Light value = " + String(lightValue) + " AMBIENT");

        Particle.publish("Room Status", "ambient");
        Particle.publish("Light value", String(lightValue));
    }
    else {  //bright whtie
      // changeRgbLed(255, 255, 255);
      Serial.println("Light value = " + String(lightValue) + " BRIGHT");

      Particle.publish("Room Status", "bright");
      Particle.publish("Light value", String(lightValue));
    }

    //only send to cloud once per sec
    delay(1000);
}

/*
  in the past, we converted the potentiometer ADC values to LED PWM values
    approach #1: we did some math

    approach #2: we can use the map fn()

*/