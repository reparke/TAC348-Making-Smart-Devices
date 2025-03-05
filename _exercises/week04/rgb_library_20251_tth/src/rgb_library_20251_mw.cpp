#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

#include "rgb-controls.h"
using namespace RGBControls;

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

// Led led(D0, D1, D2);
Led led(PIN_RED, PIN_GREEN, PIN_BLUE);
Color red(255, 0, 0);
Color blue(0, 0, 255);
Color white(255,255,255);
Color green(0,255,0);

void changeRgbLed(int r, int g, int b) {
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // Fade the light between red and blue every second
    // led.fade(red, blue, 1000);
    led.fade(green, white, 5000);
}
