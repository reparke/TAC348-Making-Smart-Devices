#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_WARN);

const int PIN_RED = A2;
const int PIN_GREEN = A5;
const int PIN_BLUE = MOSI;  // photon say "MO"

#include "rgb-controls.h"
using namespace RGBControls;

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
    // Fade the light between red and blue every second
    led.fade(red, blue, 1000);
}