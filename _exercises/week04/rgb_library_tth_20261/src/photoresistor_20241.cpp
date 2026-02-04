

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;

/*
    in programming we can ADD / IMPORT / INCLUDE extra libraries or module

    there are some specific libraries to work with RGBs
*/
// from fade_example.ino

#include "rgb-controls.h"
using namespace RGBControls;

// Led led(D0, D1, D2);
Led led(PIN_RED, PIN_GREEN, PIN_BLUE);
Color red(255, 0, 0);
Color blue(0, 0, 255);

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    led.fade(red, blue, 1000);
}