
#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);


#include "rgb-controls.h"
using namespace RGBControls;

const int PIN_RGB_RED = A2;
const int PIN_RGB_GREEN = A5;
const int PIN_RGB_BLUE = D15; // aka MOSI pin



Led led(PIN_RGB_RED, PIN_RGB_GREEN, PIN_RGB_BLUE);
Color red(255, 0, 0);
Color blue(0, 0, 255);


void changeLedColor(int r, int g, int b) {
    // theoretical "recipe" or algorithm using these input
    analogWrite(PIN_RGB_RED, r);
    analogWrite(PIN_RGB_GREEN, g);
    analogWrite(PIN_RGB_BLUE, b);
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RGB_RED, OUTPUT);
    pinMode(PIN_RGB_GREEN, OUTPUT);
    pinMode(PIN_RGB_BLUE, OUTPUT);
}

void loop() {
     led.fade(red, blue, 1000); 
     }